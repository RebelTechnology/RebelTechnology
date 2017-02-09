extern "C" {
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "HAL_Triggers.h"
#include "HAL_Encoders.h"
#include "HAL_CV_IO.h"
#include "usb_device.h"
#include "usb_host.h"
}
#include "device.h"
#include "Graphics.h"
#include "Codec.h"
#include "ProgramVector.h"
#include "ScreenBuffer.h"
#include "SampleBuffer.hpp"
#include "midi.h"
#include "usbh_midi.h"
#include "BitState.hpp"
#include "MidiReader.h"
#include "ProgramManager.h"
#include "ApplicationSettings.h"
extern ProgramManager program;
ApplicationSettings settings;
Graphics graphics;

extern "C" {
  void setup(void);
  void loop(void);
}
extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// there are only really 2 timestamps needed: LED pushbutton and midi gate
uint16_t timestamps[NOF_BUTTONS]; 
BitState32 stateChanged;

bool getButton(uint8_t bid){
  return getProgramVector()->buttons & (1<<bid);
}

extern "C" {
  void encoderChanged(uint8_t encoder, int32_t value);
  void delay(uint32_t ms){
    osDelay(ms);
  }
}

#include "sdram.h"

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

#define RX_BUFF_SIZE   64  /* Max Received data 64 bytes */
extern uint8_t USBHOST_RX_Buffer[RX_BUFF_SIZE];

// #define OLED_HEIGHT 64
// #define OLED_WIDTH 128
static bool dodisplay = true;
Codec codec;
ScreenBuffer screen(OLED_WIDTH, OLED_HEIGHT);
SampleBuffer samples;
MidiReader midireader;

#include "SplashPatch.hpp"
SplashPatch splash;
Patch* patches[] = {&splash};
uint8_t currentPatch = 0;

volatile bool doProcessAudio = false;
uint32_t dropouts = 0;
extern "C" {
  void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size){
    if(!doProcessAudio){
      getProgramVector()->audio_input = rx;
      getProgramVector()->audio_output = tx;
      getProgramVector()->audio_blocksize = size;
      doProcessAudio = true;
    }else{
      dropouts++;
    }
  }
}

void switchInA(){}
void switchInB(){}
void triggerInA(){}
void triggerInB(){}

extern "C"{
  void HAL_GPIO_EXTI_Callback(uint16_t pin){
  // sw1() pg14
  // sw2() pb4
  // tr1() pc11
  // tr2() pc10
    switch(pin){
    case GPIO_PIN_14:
      switchInA();
      break;
    case GPIO_PIN_4:
      switchInB();
      break;
    case GPIO_PIN_11:
      triggerInA();
      break;
    case GPIO_PIN_10:
      triggerInB();
      break;
    }
  }
}

void setup(void){
  // if(testram8(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram8 failed");
  // if(testram16(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram16 failed");
  // if(testram32(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram32 failed");

  // memset(pixelbuffer, 0xAA, 1024);
// Product Specific Initialisation
  // Triggers_Config();
  // Encoders_Config();

  // enable sw1/sw2 and tr1/tr2 callbacks
  // HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0x00);
  // HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  // HAL_NVIC_SetPriority(EXTI4_IRQn, 0x0F, 0x00);
  // HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  CV_IO_Config();
  CV_Out_A(&hdac, 0);
  CV_Out_B(&hdac, 0);

#ifdef USE_CODEC
  codec.reset();
  codec.start();
  codec.ramp(1<<23);
#endif

  graphics.begin(&hspi2);

  __HAL_TIM_SetCounter(&htim2, INT16_MAX/2);
  __HAL_TIM_SetCounter(&htim3, INT16_MAX/2);
  HAL_TIM_Encoder_Start_IT(&htim2, 0);
  HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);

  patches[currentPatch]->reset();

#ifndef USE_CODEC
  doProcessAudio = true;
#endif

  program.startManager();

  program.loadProgram(
}

extern "C" {

  // void processBlock(ProgramVector* pv){
  //   samples.split(pv->audio_input, pv->audio_blocksize);
  //   screen.setBuffer(pv->pixels);
  //   patches[currentPatch]->processAudio(samples);
  //   // screen.setTextSize(1);
  //   // screen.print(0, screen.getHeight()-8, "Rebel Technology");
  //   samples.comb(pv->audio_output);
  // }

  void loop(void){
    if(doProcessAudio){
      ProgramVector* pv = getProgramVector();
      processBlock(pv);
      if(dodisplay){
	// if(dodisplay && graphics.isReady()){
	graphics.display(pv->pixels, OLED_WIDTH*OLED_HEIGHT);
	// swap pixelbuffer
	// pv->pixels = pixelbuffer[swappb];
	// swappb = !swappb;
      }
#ifdef USE_CODEC
      doProcessAudio = false;
#endif
    }
  }

  void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost){
    uint8_t* ptr = USBHOST_RX_Buffer;
    uint16_t len = USBH_MIDI_GetLastReceivedDataSize(phost);
    for(uint32_t i=0; i<len; i+=4)
      midireader.readMidiFrame(ptr+i); 
    USBH_MIDI_Receive(phost, USBHOST_RX_Buffer, RX_BUFF_SIZE); // start a new reception
  }

  void USBH_MIDI_TransmitCallback(USBH_HandleTypeDef *phost){
    // get ready to send some data
  }

  // more from USB device interface
  void midi_rx_usb_buffer(uint8_t *buffer, uint32_t length){
    for(uint32_t i=0; i<length; i+=4)
      midireader.readMidiFrame(buffer+i);
  }
  // void midi_tx_usb_buffer(uint8_t* buffer, uint32_t length);

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

  void encoderReset(uint8_t encoder, int32_t value){
    if(encoder == 0)
      __HAL_TIM_SetCounter(&htim2, value);
    else if(encoder == 1)
      __HAL_TIM_SetCounter(&htim3, value);
  }

  void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if(htim == &htim2)
      encoderChanged(0, __HAL_TIM_GET_COUNTER(&htim2));
    else if(htim == &htim3)
      encoderChanged(1, __HAL_TIM_GET_COUNTER(&htim3));
  }
}
