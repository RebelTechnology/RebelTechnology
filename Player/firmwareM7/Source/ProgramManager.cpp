#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include <string.h>
#include "PatchRegistry.h"
#include "ProgramManager.h"
#include "ProgramVector.h"
#include "device.h"
#include "DynamicPatchDefinition.hpp"
#include "errorhandlers.h"
#include "Graphics.h"
#include "ScreenBuffer.h"
#include "SampleBuffer.hpp"
#include "Codec.h"
#include "ServiceCall.h"

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
PatchRegistry registry;
ProgramVector staticVector;
ProgramVector* programVector = &staticVector;
static TaskHandle_t screenTask = NULL;
static TaskHandle_t audioTask = NULL;
static TaskHandle_t managerTask = NULL;
SampleBuffer samples;
static DynamicPatchDefinition dynamo;

ProgramVector* getProgramVector() { return programVector; }

class ParameterController {
public:
  const uint8_t parameters_size = 8;
  int16_t parameters[8];
  const char* names[8] = { "Parameter A",  "Parameter B",  "Parameter C",  "Parameter D", 
			   "Parameter E",  "Parameter F",  "Parameter G",  "Parameter H" };
  int8_t selected = 0;
  void draw(uint8_t* pixels, uint16_t width, uint16_t height){
    static ScreenBuffer screen(width, height);
    screen.setBuffer(pixels);
    draw(screen);
  }
  void draw(ScreenBuffer& screen){
    if(sw1()){
      screen.clear();
      drawStats(screen);
      // todo: show patch name and next/previous patch
    }else if(sw2()){
      screen.clear();
      screen.setTextSize(1);
      screen.print(2, 0, names[selected]);
      screen.setTextSize(3);
      screen.setCursor(30, 20);
      screen.print(parameters[selected]/41); // assuming parameter value [0-4095]
      screen.print("%");
    }else if(getErrorStatus() != NO_ERROR && getErrorMessage() != NULL){
      screen.clear();
      screen.setTextSize(1);
      screen.print(2, 20, getErrorMessage());
    }else{
      screen.setTextSize(1);
      screen.print(2, 56, names[selected]);
      screen.print(": ");
      screen.print(parameters[selected]/41);
    }
  }
  void drawStats(ScreenBuffer& screen){
    ProgramVector* pv = getProgramVector();
    if(pv->message != NULL)
      screen.print(2, 36, pv->message);
    screen.print(2, 46, "cpu/mem: ");
    screen.print((int)((pv->cycles_per_block)/pv->audio_blocksize)/35);
    screen.print("% ");
    screen.print((int)(pv->heap_bytes_used)/1024);
    screen.print("kB");
  }
  void encoderChanged(uint8_t encoder, int32_t delta){
    if(encoder == 0){
      if(sw2()){
	if(delta > 1)
	  selected = min(parameters_size-1, selected+1);
	else if(delta < 1)
	  selected = max(0, selected-1);
      }else{
	parameters[selected] += delta*10;
	parameters[selected] = min(4095, max(0, parameters[selected]));
      }
    } // todo: change patch with enc1/sw1
  }
private:
  bool tr1(){
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_SET;
  }
  bool tr2(){
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_SET;
  }
  bool sw1(){
    return HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) != GPIO_PIN_SET;
  }
  bool sw2(){
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) != GPIO_PIN_SET;
  }
};

ParameterController params;

static int16_t encoders[2] = {INT16_MAX/2, INT16_MAX/2};
static int16_t deltas[2] = {0, 0};
void encoderChanged(uint8_t encoder, int32_t value){
  // // todo: debounce
  // // pass encoder change event to patch
  int32_t delta = value - encoders[encoder];
  encoders[encoder] = value;
  deltas[encoder] = delta;
  params.encoderChanged(encoder, delta);
  // todo: save changes and pass at programReady()
  // if(getProgramVector()->encoderChangedCallback != NULL)
  //   getProgramVector()->encoderChangedCallback(encoder, delta, 0);
}

PatchDefinition* getPatchDefinition(){
  return program.getPatchDefinition();
}

void audioCallback(int32_t* rx, int32_t* tx, uint16_t size){
  DWT->CYCCNT = 0;
  getProgramVector()->audio_input = rx;
  getProgramVector()->audio_output = tx;
  getProgramVector()->audio_blocksize = size;
  // vTaskSuspend(screenTask);
  if(audioTask != NULL){
    BaseType_t yield;
    vTaskNotifyGiveFromISR(audioTask, &yield);
    portYIELD_FROM_ISR(yield);
  }
}

/* called by the program when an error or anomaly has occured */
void onProgramStatus(ProgramVectorAudioStatus status){
  // setLed(RED);
  program.exitProgram(false);
  char msg[] = "Err xx";
  msg[4] = '0'+(status/10);
  msg[5] = '0'+(status%10);
  error(PROGRAM_ERROR, msg);
  for(;;);
}

/* called by the program when a block has been processed */
void onProgramReady(){
  ProgramVector* pv = getProgramVector();
  pv->cycles_per_block = DWT->CYCCNT;
  uint32_t ulNotifiedValue = 0;
  while(ulNotifiedValue <= 0){
    const TickType_t xBlockTime = portMAX_DELAY;  /* Block indefinitely. */
    // const TickType_t xBlockTime = pdMS_TO_TICS( 500 );
    ulNotifiedValue = ulTaskNotifyTake(pdTRUE, xBlockTime);
  }
  params.parameters[0] = getAnalogValue(0);
  params.parameters[1] = getAnalogValue(1);
  // ready to run block again
}

// called from program
void onSetPatchParameter(uint8_t pid, int16_t value){     
}
// called from program
void onSetButton(uint8_t bid, uint16_t state, uint16_t samples){
}

void updateProgramVector(ProgramVector* pv){
  pv->checksum = PROGRAM_VECTOR_CHECKSUM_V13;
  pv->hardware_version = PLAYER_HARDWARE;
  pv->parameters_size = params.parameters_size;
  pv->parameters = params.parameters;
  pv->audio_bitdepth = 24;
  pv->audio_samplingrate = 48000;
  pv->audio_blocksize = CODEC_BLOCKSIZE; // todo!
  pv->buttons = 0;
  pv->registerPatch = NULL;
  pv->registerPatchParameter = NULL;
  pv->cycles_per_block = 0;
  pv->heap_bytes_used = 0;
  pv->programReady = onProgramReady;
  pv->programStatus = onProgramStatus;
  pv->serviceCall = serviceCall;
  pv->setButton = onSetButton;
  pv->setPatchParameter = onSetPatchParameter;

  pv->buttonChangedCallback = NULL;
  pv->encoderChangedCallback = NULL;
  pv->drawCallback = NULL;
  pv->message = NULL;
}

void defaultDrawCallback(uint8_t* pixels, uint16_t width, uint16_t height){
  static ScreenBuffer screen(width, height);
  screen.setBuffer(pixels);
  screen.clear();

  // ProgramVector* pv = getProgramVector();
  // if(pv->message != NULL){
  //   screen.setTextSize(1);
  //   screen.print(2, 40, pv->message);
  // }
  // if(getErrorStatus() != NO_ERROR && getErrorMessage() != NULL){
  //   screen.setTextSize(1);
  //   screen.print(2, 20, getErrorMessage());
  // }else{
  //   screen.setTextSize(1);
  //   screen.print(2, 46, "cps/mem: ");
  //   screen.print((int)(pv->cycles_per_block)/pv->audio_blocksize);
  //   screen.print("/");
  //   screen.print((int)(pv->heap_bytes_used)/1024);
  //   screen.print("kB");
  // }
  screen.setTextSize(1);
  screen.print(20, 0, "Rebel Technology");
}

void runScreenTask(void* p){
  const TickType_t delay = 20 / portTICK_PERIOD_MS;
  for(;;){
    ProgramVector* pv = getProgramVector();
    if(pv->drawCallback != NULL){
      pv->drawCallback(pixelbuffer, OLED_WIDTH, OLED_HEIGHT);
    }else{
      defaultDrawCallback(pixelbuffer, OLED_WIDTH, OLED_HEIGHT);
    }
    params.draw(pixelbuffer, OLED_WIDTH, OLED_HEIGHT);
    graphics.display(pixelbuffer, OLED_WIDTH*OLED_HEIGHT);
    vTaskDelay(delay); // allow a minimum amount of time for pixel data to be transferred
  }
}

void runAudioTask(void* p){
    PatchDefinition* def = getPatchDefinition();
    ProgramVector* pv = def == NULL ? NULL : def->getProgramVector();
    if(pv != NULL && def->verify()){
      updateProgramVector(pv);
      programVector = pv;
      // audioStatus = AUDIO_IDLE_STATUS;
      setErrorStatus(NO_ERROR);
      // setLed(GREEN);
      // codec.softMute(false);
      codec.resume();
      def->run();
      error(PROGRAM_ERROR, "Program exited");
    }else{
      error(PROGRAM_ERROR, "Invalid program");
    }
    // setLed(RED);
    program.exitProgram(false);
    for(;;);
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
	codec.pause();
	programVector = &staticVector;
	programVector->drawCallback = NULL;
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
      else
	error(PROGRAM_ERROR, "Program already running");

      if(audioTask == NULL)
	error(PROGRAM_ERROR, "Failed to start program task");
    }
  }
}

ProgramManager::ProgramManager(){
}

void ProgramManager::startManager(){
  registry.init();
  codec.start();
  codec.pause();
  updateProgramVector(getProgramVector());
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
  if(dynamo.getProgramVector() != NULL){
    patchdef = &dynamo;
    registry.setDynamicPatchDefinition(patchdef);
    // updateProgramIndex(0);
  }else{
    registry.setDynamicPatchDefinition(NULL);
  }
}

void ProgramManager::saveProgramToFlash(uint8_t sector, void* address, uint32_t length){
}

void ProgramManager::loadProgram(uint8_t pid){
  PatchDefinition* def = registry.getPatchDefinition(pid);
  if(def != NULL && def != patchdef && def->getProgramVector() != NULL){
    patchdef = def;
    // updateProgramIndex(pid);
  }
  // patchdef = &dynamo;
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
    program.exitProgram(false);
    error(PROGRAM_ERROR, "malloc failed");
    for(;;);
  }
  void vApplicationIdleHook(void) {
  }
  void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;
    /* Run time stack overflow checking is performed if
       configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
       function is called if a stack overflow is detected. */
    program.exitProgram(false);
    error(PROGRAM_ERROR, "Stack overflow");
    // taskDISABLE_INTERRUPTS();
    for(;;);
  }
}
