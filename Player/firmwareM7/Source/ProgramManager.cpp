extern "C" {
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
}

#include <string.h>
#include "ProgramManager.h"
#include "ProgramVector.h"
#include "device.h"
#include "DynamicPatchDefinition.hpp"
#include "errorhandlers.h"
#include "Graphics.h"
#include "ScreenBuffer.h"
#include "SampleBuffer.hpp"
#include "Codec.h"

// FreeRTOS low priority numbers denote low priority tasks. 
// The idle task has priority zero (tskIDLE_PRIORITY).
#define SCREEN_TASK_STACK_SIZE (2*1024/sizeof(portSTACK_TYPE))
#define SCREEN_TASK_PRIORITY 3
#define AUDIO_TASK_STACK_SIZE  (2*1024/sizeof(portSTACK_TYPE))
#define AUDIO_TASK_PRIORITY  4
// #define MANAGER_TASK_STACK_SIZE  (2*1024/sizeof(portSTACK_TYPE))
#define MANAGER_TASK_PRIORITY  (3 | portPRIVILEGE_BIT)

#define OLED_DATA_LENGTH (OLED_WIDTH*OLED_HEIGHT/8)
uint8_t pixelbuffer[OLED_DATA_LENGTH];

#define START_PROGRAM_NOTIFICATION  0x01
#define STOP_PROGRAM_NOTIFICATION   0x02
#define PROGRAM_FLASH_NOTIFICATION  0x04
#define ERASE_FLASH_NOTIFICATION    0x08
#define PROGRAM_CHANGE_NOTIFICATION 0x10

ProgramManager program;
static ProgramVector staticVector;
ProgramVector* programVector = &staticVector;
static TaskHandle_t screenTask = NULL;
static TaskHandle_t audioTask = NULL;
static TaskHandle_t managerTask = NULL;
ScreenBuffer screen(OLED_WIDTH, OLED_HEIGHT);
SampleBuffer samples;
static DynamicPatchDefinition dynamo;

extern "C" {
  void updateProgramVector(ProgramVector* pv);
  ProgramVector* getProgramVector() { return programVector; }
  void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size);
  void encoderChanged(uint8_t encoder, int32_t value);
}

#include "SplashPatch.hpp"
static SplashPatch splash;
static Patch* patches[] = {&splash};
static uint8_t currentPatch = 0;

static int16_t encoders[2] = {INT16_MAX/2, INT16_MAX/2};
static int16_t deltas[2] = {0, 0};
void encoderChanged(uint8_t encoder, int32_t value){
  // // todo: debounce
  // // pass encoder change event to patch
  int32_t delta = value - encoders[encoder];
  encoders[encoder] = value;
  deltas[encoder] = delta;
  patches[currentPatch]->encoderChanged(encoder, delta);
}

PatchDefinition* getPatchDefinition(){
  return program.getPatchDefinition();
}

void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size){
  DWT->CYCCNT = 0;
  getProgramVector()->audio_input = rx;
  getProgramVector()->audio_output = tx;
  getProgramVector()->audio_blocksize = size;
  // vTaskSuspend(screenTask);
  BaseType_t yield;
  vTaskNotifyGiveFromISR(audioTask, &yield);
  portYIELD_FROM_ISR(yield);
}

/* called by the program when an error or anomaly has occured */
void onProgramStatus(ProgramVectorAudioStatus status){
  // setLed(RED);
  for(;;);
}

/* called by the program when a block has been processed */
void onAudioReady(){
  ProgramVector* pv = getProgramVector();
  pv->cycles_per_block = DWT->CYCCNT;
  uint32_t ulNotifiedValue = 0;
  while(ulNotifiedValue <= 0){
    const TickType_t xBlockTime = portMAX_DELAY;  /* Block indefinitely. */
    // const TickType_t xBlockTime = pdMS_TO_TICS( 500 );
    ulNotifiedValue = ulTaskNotifyTake(pdTRUE, xBlockTime);
  }
  // ready to run block again
}

void onScreenReady(){
  const TickType_t delay = 20 / portTICK_PERIOD_MS;
  ProgramVector* pv = getProgramVector();
  // if(dodisplay && graphics.isReady()){
  // graphics.display(pv->pixels, pv->screen_width*pv->screen_height);
  graphics.display(pv->pixels, OLED_WIDTH*OLED_HEIGHT);
    // taskYIELD();
    // swap pixelbuffer
    // pv->pixels = pixelbuffer[swappb];
    // swappb = !swappb;
  vTaskDelay(delay);  
}

void updateProgramVector(ProgramVector* pv){
  pv->checksum = PROGRAM_VECTOR_CHECKSUM_V13;
  pv->hardware_version = PLAYER_HARDWARE;
  pv->parameters_size = 2;
  pv->parameters = NULL; // adc_values;
  pv->audio_bitdepth = 24;
  pv->audio_samplingrate = 48000;
  pv->buttons = 0;
  pv->registerPatch = NULL;
  pv->registerPatchParameter = NULL;
  pv->cycles_per_block = 0;
  pv->heap_bytes_used = 0;
  pv->audioReady = onAudioReady;
  pv->screenReady = onScreenReady;
  pv->programStatus = onProgramStatus;
  pv->serviceCall = NULL;
  pv->message = NULL;
  pv->pixels = pixelbuffer;
  pv->screen_width = OLED_WIDTH;
  pv->screen_height = OLED_HEIGHT;
}

void runScreenTask(void* p){
  ProgramVector* pv = getProgramVector();
  updateProgramVector(pv);
  for(;;){
    pv->screenReady();
    screen.setBuffer(pv->pixels);
    patches[currentPatch]->processScreen(screen);
  }
}

void runAudioTask(void* p){
  ProgramVector* pv = getProgramVector();
  updateProgramVector(pv);
  patches[currentPatch]->reset();
  codec.start();
  for(;;){
    pv->audioReady();
    samples.split(pv->audio_input, pv->audio_blocksize);
    patches[currentPatch]->processAudio(samples);
    samples.comb(pv->audio_output);
    // done processing one audio block
  }
}

void runManagerTask(void* p){
  uint32_t ulNotifiedValue = 0;
  TickType_t xMaxBlockTime = portMAX_DELAY;  /* Block indefinitely. */
  for(;;){
    /* Block indefinitely (without a timeout, so no need to check the function's
       return value) to wait for a notification.
       Bits in this RTOS task's notification value are set by the notifying
       tasks and interrupts to indicate which events have occurred. */
    xTaskNotifyWait(pdFALSE,          /* Don't clear any notification bits on entry. */
		    UINT32_MAX,       /* Reset the notification value to 0 on exit. */
		    &ulNotifiedValue, /* Notified value pass out in ulNotifiedValue. */
		    xMaxBlockTime); 
    if(ulNotifiedValue & STOP_PROGRAM_NOTIFICATION){ // stop program
      // audioStatus = AUDIO_EXIT_STATUS;
      // codec.softMute(true);
      // codec.pause();
      if(audioTask != NULL){
	codec.stop();
	programVector = &staticVector;
	vTaskDelete(audioTask);
	audioTask = NULL;
      }
    }
    // allow idle task to garbage collect if necessary
    vTaskDelay(20);
    // vTaskDelay(pdMS_TO_TICKS(200));
    // if(ulNotifiedValue & PROGRAM_FLASH_NOTIFICATION){ // program flash
    //   bool ret = utilityTask.create(programFlashTask, "Flash Write", FLASH_TASK_PRIORITY);
    //   if(!ret)
    // 	error(PROGRAM_ERROR, "Failed to start Flash Write task");
    // }else if(ulNotifiedValue & ERASE_FLASH_NOTIFICATION){ // erase flash
    //   bool ret = utilityTask.create(eraseFlashTask, "Flash Erase", FLASH_TASK_PRIORITY);
    //   if(!ret)
    //   	error(PROGRAM_ERROR, "Failed to start Flash Erase task");
    // }
    // vTaskDelay(20);
    if(ulNotifiedValue & START_PROGRAM_NOTIFICATION){ // start
      // PatchDefinition* def = getPatchDefinition();
      // if(audioTask == NULL && def != NULL){
      // 	static StaticTask_t programTaskBuffer;
      // 	if(def->getStackBase() != 0 && 
      // 	   def->getStackSize() > configMINIMAL_STACK_SIZE*sizeof(portSTACK_TYPE)){
      // 	  audioTask = xTaskCreateStatic(runAudioTask, "Audio", 
      // 					def->getStackSize()/sizeof(portSTACK_TYPE),
      // 					NULL, AUDIO_TASK_PRIORITY, 
      // 					(StackType_t*)def->getStackBase(), 
      // 					&programTaskBuffer);
      // 	}else{
      // 	  xTaskCreate(runAudioTask, "Audio", AUDIO_TASK_STACK_SIZE, NULL, AUDIO_TASK_PRIORITY, &audioTask);
      // 	  // error(PROGRAM_ERROR, "Invalid program stack");
      // 	}
      // 	if(audioTask == NULL)
      // 	  error(PROGRAM_ERROR, "Failed to start program task");
      // }
      // todo: make sure no two tasks are using the same stack
      if(audioTask == NULL)
	xTaskCreate(runAudioTask, "Audio", AUDIO_TASK_STACK_SIZE, NULL, AUDIO_TASK_PRIORITY, &audioTask);
      if(audioTask == NULL)
	error(PROGRAM_ERROR, "Failed to start program task");
    }
  }
}

ProgramManager::ProgramManager(){
}

void ProgramManager::startManager(){
  xTaskCreate(runScreenTask, "Screen", SCREEN_TASK_STACK_SIZE, NULL, SCREEN_TASK_PRIORITY, &screenTask);
  // xTaskCreate(runAudioTask, "Audio", AUDIO_TASK_STACK_SIZE, NULL, AUDIO_TASK_PRIORITY, &audioTask);
  xTaskCreate(runManagerTask, "Manager", MANAGER_TASK_STACK_SIZE, NULL, MANAGER_TASK_PRIORITY, &managerTask);
}

void ProgramManager::notifyManagerFromISR(uint32_t ulValue){
  BaseType_t xHigherPriorityTaskWoken = 0; 
  if(managerTask != NULL)
    xTaskNotifyFromISR(managerTask, ulValue, eSetBits, &xHigherPriorityTaskWoken );
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  // managerTask.notifyFromISR(ulValue);
}

void ProgramManager::notifyManager(uint32_t ulValue){
  if(managerTask != NULL)
    xTaskNotify(managerTask, ulValue, eSetBits );
  // managerTask.notify(ulValue);
}

void ProgramManager::startProgram(bool isr){
  if(isr)
    notifyManagerFromISR(START_PROGRAM_NOTIFICATION);
  else
    notifyManager(START_PROGRAM_NOTIFICATION);
}

void ProgramManager::exitProgram(bool isr){
  if(isr)
    notifyManagerFromISR(STOP_PROGRAM_NOTIFICATION);
  else
    notifyManager(STOP_PROGRAM_NOTIFICATION);
}

/* exit and restart program */
void ProgramManager::resetProgram(bool isr){
  if(isr)
    notifyManagerFromISR(STOP_PROGRAM_NOTIFICATION|START_PROGRAM_NOTIFICATION);
  else
    notifyManager(STOP_PROGRAM_NOTIFICATION|START_PROGRAM_NOTIFICATION);
}

void ProgramManager::startProgramChange(bool isr){
  if(isr)
    notifyManagerFromISR(STOP_PROGRAM_NOTIFICATION|PROGRAM_CHANGE_NOTIFICATION);
  else
    notifyManager(STOP_PROGRAM_NOTIFICATION|PROGRAM_CHANGE_NOTIFICATION);
}

void ProgramManager::loadDynamicProgram(void* address, uint32_t length){
  dynamo.load(address, length);
}

void ProgramManager::saveProgramToFlash(uint8_t sector, void* address, uint32_t length){
}

extern "C" {
  static StaticTask_t xIdleTaskTCBBuffer;// CCM;
  static StackType_t xIdleStack[IDLE_TASK_STACK_SIZE];// CCM;
  void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = IDLE_TASK_STACK_SIZE;
  }
  void vApplicationMallocFailedHook(void) {
    // taskDISABLE_INTERRUPTS();
    // for(;;);
    // exitProgram(false);
    error(PROGRAM_ERROR, "malloc failed");
  }
  void vApplicationIdleHook(void) {
  }
  void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;
    /* Run time stack overflow checking is performed if
       configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
       function is called if a stack overflow is detected. */
    // exitProgram(false);
    error(PROGRAM_ERROR, "stack overflow");
    // taskDISABLE_INTERRUPTS();
    // for(;;);
  }
}

#if 0
// #include "PatchRegistry.h"
// #include "ApplicationSettings.h"
// #include "CodecController.h"
// #include "owlcontrol.h"
// #include "eepromcontrol.h"
// #include "FreeRTOS.h"

// FreeRTOS low priority numbers denote low priority tasks. 
// The idle task has priority zero (tskIDLE_PRIORITY).
#define PROGRAM_TASK_PRIORITY            (2)
#define MANAGER_TASK_PRIORITY            (4 | portPRIVILEGE_BIT)
#define FLASH_TASK_PRIORITY              (3 | portPRIVILEGE_BIT)
#define PC_TASK_PRIORITY                 (2)

#include "task.h"

static volatile ProgramVectorAudioStatus audioStatus = AUDIO_IDLE_STATUS;
static DynamicPatchDefinition flashPatches[MAX_USER_PATCHES];

extern "C" {
  void updateProgramVector(ProgramVector* pv);
  ProgramVector* getProgramVector() { return programVector; }
}

// static uint32_t getFlashAddress(int sector){
//   uint32_t addr = ADDR_FLASH_SECTOR_11;
//   addr -= sector*128*1024; // count backwards by 128k blocks, ADDR_FLASH_SECTOR
//   return addr;
// }

TaskHandle_t xProgramHandle = NULL;

uint8_t ucHeap[configTOTAL_HEAP_SIZE];
// uint8_t ucHeap[configTOTAL_HEAP_SIZE] CCM;

template<uint32_t STACK_SIZE>
class StaticTask {
private:
  StaticTask_t xTaskBuffer;
  StackType_t xStack[STACK_SIZE]; // long unsigned int
public:
  TaskHandle_t handle = NULL;
  bool create(TaskFunction_t pxTaskCode, const char * const pcName,
	      UBaseType_t uxPriority){
    if(handle != NULL)
      vTaskDelete(handle);
    handle = xTaskCreateStatic(pxTaskCode, pcName, STACK_SIZE, NULL, uxPriority, xStack, &xTaskBuffer);
    return handle != NULL;
  }
  void notify(uint32_t ulValue){
    if(handle != NULL)
      xTaskNotify(handle, ulValue, eSetBits );
  }
  void notifyFromISR(uint32_t ulValue){
    BaseType_t xHigherPriorityTaskWoken = 0; 
    if(handle != NULL)
      xTaskNotifyFromISR(handle, ulValue, eSetBits, &xHigherPriorityTaskWoken );
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
};

StaticTask<MANAGER_TASK_STACK_SIZE> managerTask;
StaticTask<UTILITY_TASK_STACK_SIZE> utilityTask;

volatile int flashSectorToWrite;
volatile void* flashAddressToWrite;
volatile uint32_t flashSizeToWrite;

static void eraseFlashProgram(int sector){
  // uint32_t addr = getFlashAddress(sector);
  // eeprom_unlock();
  // int ret = eeprom_erase(addr);
  // eeprom_lock();
  // if(ret != 0)
  //   error(PROGRAM_ERROR, "Failed to erase flash sector");
}

  /*
   * re-program firmware: this entire function and all subroutines must run from RAM
   * (don't make this static!)
   */
  // __attribute__ ((section (".coderam")))
  void flashFirmware(uint8_t* source, uint32_t size){
    // __disable_irq(); // Disable ALL interrupts. Can only be executed in Privileged modes.
    // // setLed(RED);
    // eeprom_unlock();
    // if(size > (16+16+64+128)*1024){
    //   eeprom_erase_sector(FLASH_Sector_6);
    //   toggleLed(); // inline
    // }
    // if(size > (16+16+64)*1024){
    //   eeprom_erase_sector(FLASH_Sector_5);
    //   toggleLed();
    // }
    // if(size > (16+16)*1024){
    //   eeprom_erase_sector(FLASH_Sector_4);
    //   toggleLed();
    // }
    // if(size > 16*1024){
    //   eeprom_erase_sector(FLASH_Sector_3);
    //   toggleLed();
    // }
    // eeprom_erase_sector(FLASH_Sector_2);
    // toggleLed();
    // eeprom_write_block(ADDR_FLASH_SECTOR_2, source, size);
    // eeprom_lock();
    // eeprom_wait();
    // NVIC_SystemReset(); // (static inline)
  }

  void programFlashTask(void* p){
    // int sector = flashSectorToWrite;
    // uint32_t size = flashSizeToWrite;
    // uint8_t* source = (uint8_t*)flashAddressToWrite;
    // if(sector >= 0 && sector < MAX_USER_PATCHES && size <= 128*1024){
    //   uint32_t addr = getFlashAddress(sector);
    //   eeprom_unlock();
    //   int ret = eeprom_erase(addr);
    //   if(ret == 0)
    // 	ret = eeprom_write_block(addr, source, size);
    //   eeprom_lock();
    //   registry.init();
    //   if(ret == 0){
    // 	// load and run program
    // 	int pc = registry.getNumberOfPatches()-MAX_USER_PATCHES+sector;
    // 	program.loadProgram(pc);
    // 	// program.loadDynamicProgram(source, size);
    // 	program.resetProgram(false);
    //   }else{
    // 	error(PROGRAM_ERROR, "Failed to write program to flash");
    //   }
    // }else if(sector == 0xff && size < MAX_SYSEX_FIRMWARE_SIZE){
    //   flashFirmware(source, size);
    // }else{
    //   error(PROGRAM_ERROR, "Invalid flash program command");
    // }
    vTaskDelete(NULL);
  }

  void eraseFlashTask(void* p){
    // int sector = flashSectorToWrite;
    // if(sector == 0xff){
    //   for(int i=0; i<MAX_USER_PATCHES; ++i)
    // 	eraseFlashProgram(i);
    //   settings.clearFlash();
    // }else if(sector >= 0 && sector < MAX_USER_PATCHES){
    //   eraseFlashProgram(sector);
    // }else{
    //   error(PROGRAM_ERROR, "Invalid flash erase command");
    // }
    // registry.init();
    vTaskDelete(NULL);
  }
}


void ProgramManager::loadProgram(uint8_t pid){
  // PatchDefinition* def = registry.getPatchDefinition(pid);
  // if(def != NULL && def != patchdef && def->getProgramVector() != NULL){
  //   patchdef = def;
  // // if(def != NULL && def->getProgramVector() != NULL){
  // //   currentpatch = def;
  //   updateProgramIndex(pid);
  // }
}

#ifdef DEBUG_STACK
uint32_t ProgramManager::getProgramStackUsed(){
  if(xProgramHandle == NULL)
    return 0;
  uint32_t ph = uxTaskGetStackHighWaterMark(xProgramHandle);
  return getProgramStackAllocation() - ph*sizeof(portSTACK_TYPE);
}

uint32_t ProgramManager::getProgramStackAllocation(){
  uint32_t ss = 0;
  if(patchdef != NULL)
    ss = patchdef->getStackSize();
  // if(currentpatch != NULL)
  //   ss = currentpatch->getStackSize();
  if(ss == 0)
    ss = PROGRAM_TASK_STACK_SIZE*sizeof(portSTACK_TYPE);
  return ss;
}

uint32_t ProgramManager::getManagerStackUsed(){
  if(managerTask.handle == NULL)
    return 0;
  uint32_t mh = uxTaskGetStackHighWaterMark(managerTask.handle);
  return getManagerStackAllocation() - mh*sizeof(portSTACK_TYPE);
}

uint32_t ProgramManager::getManagerStackAllocation(){
  return MANAGER_TASK_STACK_SIZE*sizeof(portSTACK_TYPE);
}

uint32_t ProgramManager::getFreeHeapSize(){
  return xPortGetFreeHeapSize();
}
#endif /* DEBUG_STACK */

uint32_t ProgramManager::getCyclesPerBlock(){
  return getProgramVector()->cycles_per_block;
}

uint32_t ProgramManager::getHeapMemoryUsed(){
  return getProgramVector()->heap_bytes_used;
}

PatchDefinition* ProgramManager::getPatchDefinitionFromFlash(uint8_t sector){
  // if(sector >= MAX_USER_PATCHES)
  //   return NULL;
  // uint32_t addr = getFlashAddress(sector);
  // ProgramHeader* header = (ProgramHeader*)addr;
  // DynamicPatchDefinition* def = &flashPatches[sector];
  // uint32_t size = (uint32_t)header->endAddress - (uint32_t)header->linkAddress;
  // if(header->magic == 0xDADAC0DE && size <= 80*1024){
  //   if(def->load((void*)addr, size) && def->verify())
  //     return def;
  // }
  // return NULL;
}

void ProgramManager::eraseProgramFromFlash(uint8_t sector){
  flashSectorToWrite = sector;
  notifyManagerFromISR(STOP_PROGRAM_NOTIFICATION|ERASE_FLASH_NOTIFICATION);
}

void ProgramManager::saveProgramToFlash(uint8_t sector, void* address, uint32_t length){
  flashSectorToWrite = sector;
  flashAddressToWrite = address;
  flashSizeToWrite = length;
  notifyManagerFromISR(STOP_PROGRAM_NOTIFICATION|PROGRAM_FLASH_NOTIFICATION);
}


#endif
