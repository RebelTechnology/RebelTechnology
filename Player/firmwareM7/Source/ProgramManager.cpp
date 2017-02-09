#include <string.h>
#include "ProgramManager.h"
#include "ProgramVector.h"
// #include "owlcontrol.h"
// #include "eepromcontrol.h"
#include "device.h"
#include "DynamicPatchDefinition.hpp"
#include "FreeRTOS.h"
// #include "PatchRegistry.h"
#include "ApplicationSettings.h"
// #include "CodecController.h"
#include "errorhandlers.h"
#include "Graphics.h"

// FreeRTOS low priority numbers denote low priority tasks. 
// The idle task has priority zero (tskIDLE_PRIORITY).
#define PROGRAM_TASK_PRIORITY            (2)
#define MANAGER_TASK_PRIORITY            (4 | portPRIVILEGE_BIT)
#define FLASH_TASK_PRIORITY              (3 | portPRIVILEGE_BIT)
#define PC_TASK_PRIORITY                 (2)

#include "task.h"

static DynamicPatchDefinition dynamo;
ProgramManager program;
ProgramVector staticVector;
ProgramVector* programVector = &staticVector;
static volatile ProgramVectorAudioStatus audioStatus = AUDIO_IDLE_STATUS;
static DynamicPatchDefinition flashPatches[MAX_USER_PATCHES];

#define OLED_DATA_LENGTH (OLED_WIDTH*OLED_HEIGHT/8)
uint8_t pixelbuffer[OLED_DATA_LENGTH];

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

#define START_PROGRAM_NOTIFICATION  0x01
#define STOP_PROGRAM_NOTIFICATION   0x02
#define PROGRAM_FLASH_NOTIFICATION  0x04
#define ERASE_FLASH_NOTIFICATION    0x08
#define PROGRAM_CHANGE_NOTIFICATION 0x10

PatchDefinition* getPatchDefinition(){
  return program.getPatchDefinition();
}

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

extern "C" {
  void runManagerTask(void* p){
    // setup(); // call main OWL setup
    program.runManager();
  }

  void runProgramTask(void* p){
    PatchDefinition* def = getPatchDefinition();
    ProgramVector* vector = def->getProgramVector();
    if(def != NULL && vector != NULL){
      updateProgramVector(vector);
      programVector = vector;
      audioStatus = AUDIO_IDLE_STATUS;
      setErrorStatus(NO_ERROR);
      // setLed(GREEN);
      // codec.softMute(false);
      def->run();
      error(PROGRAM_ERROR, "Program exited");
    }else{
      error(PROGRAM_ERROR, "Invalid program");
    }
    // setLed(RED);
    for(;;);
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

#ifdef DEBUG_DWT
// volatile uint32_t *DWT_CYCCNT = (volatile uint32_t *)0xE0001004; //address of the register
#define DWT_CYCCNT CYCCNT
#endif /* DEBUG_DWT */
ProgramManager::ProgramManager() {
#ifdef DEBUG_DWT
  // initialise DWT cycle counter
  volatile unsigned int *DWT_CONTROL = (volatile unsigned int *)0xE0001000; // address of the register
  volatile unsigned int *SCB_DEMCR = (volatile unsigned int *)0xE000EDFC; // address of the register
  *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
  *DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter
#endif /* DEBUG_DWT */
}

void ProgramManager::startManager(){
  bool ret = managerTask.create(runManagerTask, "Manager", MANAGER_TASK_PRIORITY);
  if(!ret)
    error(PROGRAM_ERROR, "Failed to start manager task");
}

void ProgramManager::notifyManagerFromISR(uint32_t ulValue){
  managerTask.notifyFromISR(ulValue);
}

void ProgramManager::notifyManager(uint32_t ulValue){
  managerTask.notify(ulValue);
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

void ProgramManager::loadProgram(uint8_t pid){
  // PatchDefinition* def = registry.getPatchDefinition(pid);
  // if(def != NULL && def != patchdef && def->getProgramVector() != NULL){
  //   patchdef = def;
  // // if(def != NULL && def->getProgramVector() != NULL){
  // //   currentpatch = def;
  //   updateProgramIndex(pid);
  // }
}

void ProgramManager::loadDynamicProgram(void* address, uint32_t length){
  dynamo.load(address, length);
  // if(dynamo.getProgramVector() != NULL){
  //   patchdef = &dynamo;
  //   registry.setDynamicPatchDefinition(patchdef);
  //   // currentpatch = &dynamo;
  //   // registry.setDynamicPatchDefinition(currentpatch);
  //   updateProgramIndex(0);
  // }else{
  //   registry.setDynamicPatchDefinition(NULL);
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

void ProgramManager::runManager(){
  uint32_t ulNotifiedValue = 0;
  // TickType_t xMaxBlockTime = pdMS_TO_TICKS( 1000 );
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
      audioStatus = AUDIO_EXIT_STATUS;
      // codec.softMute(true);
      if(xProgramHandle != NULL){
	programVector = &staticVector;
	vTaskDelete(xProgramHandle);
	xProgramHandle = NULL;
      }
    }
    // allow idle task to garbage collect if necessary
    vTaskDelay(20);
    // vTaskDelay(pdMS_TO_TICKS(200));
    if(ulNotifiedValue & PROGRAM_FLASH_NOTIFICATION){ // program flash
      bool ret = utilityTask.create(programFlashTask, "Flash Write", FLASH_TASK_PRIORITY);
      if(!ret)
	error(PROGRAM_ERROR, "Failed to start Flash Write task");
    }else if(ulNotifiedValue & ERASE_FLASH_NOTIFICATION){ // erase flash
      bool ret = utilityTask.create(eraseFlashTask, "Flash Erase", FLASH_TASK_PRIORITY);
      if(!ret)
      	error(PROGRAM_ERROR, "Failed to start Flash Erase task");
    }
    vTaskDelay(20);
    if(ulNotifiedValue & START_PROGRAM_NOTIFICATION){ // start
      PatchDefinition* def = getPatchDefinition();
      if(xProgramHandle == NULL && def != NULL){
	static StaticTask_t xProgramTaskBuffer;
	if(def->getStackBase() != 0 && 
	   def->getStackSize() > configMINIMAL_STACK_SIZE*sizeof(portSTACK_TYPE)){
	  xProgramHandle = xTaskCreateStatic(runProgramTask, "Program", 
					     def->getStackSize()/sizeof(portSTACK_TYPE),
					     NULL, PROGRAM_TASK_PRIORITY, 
					     (StackType_t*)def->getStackBase(), 
					     &xProgramTaskBuffer);
	}else{
	  xTaskCreate(runProgramTask, "Program", PROGRAM_TASK_STACK_SIZE, NULL, PROGRAM_TASK_PRIORITY, &xProgramHandle);
	  // error(PROGRAM_ERROR, "Invalid program stack");
	}
	if(xProgramHandle == NULL)
	  error(PROGRAM_ERROR, "Failed to start program task");
      }
      // todo: make sure no two tasks are using the same stack
    }
  }
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

/* called by the audio interrupt when a block should be processed */
  void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size){
    // getProgramVector()->audio_input = src;
    // getProgramVector()->audio_output = dst;
      programVector->audio_input = rx;
      programVector->audio_output = tx;
      programVector->audio_blocksize = size;
    // program.audioReady();
    audioStatus = AUDIO_READY_STATUS;

    // if(!doProcessAudio){
    //   programVector->audio_input = rx;
    //   programVector->audio_output = tx;
    //   programVector->audio_blocksize = size;
    //   doProcessAudio = true;
    // }else{
    //   dropouts++;
    // }
  }

/* called by the audio interrupt when a block should be processed */
// __attribute__ ((section (".coderam")))
// void onAudioReady(){
//   audioStatus = AUDIO_READY_STATUS;
// }

/* called by the program when an error or anomaly has occured */
void onProgramStatus(ProgramVectorAudioStatus status){
  // setLed(RED);
  for(;;);
}

/* called by the program when a block has been processed */
// __attribute__ ((section (".coderam")))
void onProgramReady(){
#ifdef DEBUG_DWT
  programVector->cycles_per_block = *DWT_CYCCNT;
  // getProgramVector()->cycles_per_block = *DWT_CYCCNT;
    // (*DWT_CYCCNT + getProgramVector()->cycles_per_block)>>1;
#endif /* DEBUG_DWT */
#ifdef DEBUG_AUDIO
  clearPin(GPIOC, GPIO_Pin_5); // PC5 DEBUG
#endif
  extern Graphics graphics;
  if(audioStatus != AUDIO_IDLE_STATUS)
    graphics.display(programVector->pixels, OLED_WIDTH*OLED_HEIGHT);
  while(audioStatus != AUDIO_READY_STATUS);
  audioStatus = AUDIO_PROCESSING_STATUS;
#ifdef DEBUG_DWT
  *DWT_CYCCNT = 0; // reset the performance counter
#endif /* DEBUG_DWT */
#ifdef DEBUG_AUDIO
  setPin(GPIOC, GPIO_Pin_5); // PC5 DEBUG
#endif
}

//   void onProgramReady(){
//     ProgramVector* vec = getProgramVector();
// #ifdef DEBUG_DWT
//     vec->cycles_per_block = *DWT_CYCCNT;
// #endif /* DEBUG_DWT */
// #ifdef DEBUG_AUDIO
//     clearPin(GPIOC, GPIO_Pin_5); // PC5 DEBUG
// #endif
//     while(audioStatus != AUDIO_READY_STATUS);
//     audioStatus = AUDIO_PROCESSING_STATUS;
// #ifdef DEBUG_DWT
//     *DWT_CYCCNT = 0; // reset the performance counter
// #endif /* DEBUG_DWT */
// #ifdef DEBUG_AUDIO
//     setPin(GPIOC, GPIO_Pin_5); // PC5 DEBUG
// #endif
//     if(vec->buttonChangedCallback != NULL && stateChanged.getState()){
//       int bid = stateChanged.getFirstSetIndex();
//       do{
// 	vec->buttonChangedCallback(bid, getButton((PatchButtonId)bid)?4095:0, timestamps[bid]);
// 	timestamps[bid] = 0;
// 	stateChanged.clear(bid);
// 	bid = stateChanged.getFirstSetIndex();
//       }while(bid > 0); // bid 0 is bypass button which we ignore
//     }
// #if defined OWLRACK || defined OWLMODULAR
//     bus_status();
// #endif
//   }
// }

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
  pv->programReady = onProgramReady;
  pv->programStatus = onProgramStatus;
  pv->serviceCall = NULL;
  pv->message = NULL;
  pv->pixels = pixelbuffer;
  pv->screen_width = OLED_WIDTH;
  pv->screen_height = OLED_HEIGHT;
}

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
