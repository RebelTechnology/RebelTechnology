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

#include "MidiReader.h"

#include "ProgramManager.h"
#include "ApplicationSettings.h"
ProgramManager program;
ApplicationSettings settings;

extern "C" {
  void setup(void);
  void loop(void);
}
extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void encoderChanged(uint8_t encoder, int32_t value);

extern "C" {
  void delay(uint32_t ms){
    osDelay(ms);
  }
}

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
#define OLED_DATA_LENGTH (OLED_WIDTH*OLED_HEIGHT/8)
Graphics graphics;
static uint8_t pixelbuffer[OLED_DATA_LENGTH];
static bool dodisplay = true;
Codec codec;
ProgramVector programVector;
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
      programVector.audio_input = rx;
      programVector.audio_output = tx;
      programVector.audio_blocksize = size;
      doProcessAudio = true;
    }else{
      dropouts++;
    }
  }
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
  pv->programReady = NULL;
  pv->programStatus = NULL;
  pv->serviceCall = NULL;
  pv->message = NULL;
  pv->pixels = pixelbuffer;
  pv->screen_width = OLED_WIDTH;
  pv->screen_height = OLED_HEIGHT;
}

void setup(void){
  // memset(pixelbuffer, 0xAA, 1024);

// Product Specific Initialisation
  Triggers_Config();
  // Encoders_Config();
  CV_IO_Config();
  CV_Out_A(&hdac, 0);
  CV_Out_B(&hdac, 0);
  updateProgramVector(&programVector);
#ifdef USE_CODEC
  /* SAI rx and tx DMA interrupt init */
  // HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  // HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  // HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 5, 0);
  // HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

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
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  screen.setBuffer(pv->pixels);
  patches[currentPatch]->processAudio(samples);
  // screen.setTextSize(1);
  // screen.print(0, screen.getHeight()-8, "Rebel Technology");
  samples.comb(pv->audio_output);
}

void loop(void){
  if(doProcessAudio){
    processBlock(&programVector);
    if(dodisplay){
      // if(dodisplay && graphics.isReady()){
      graphics.display(programVector.pixels, OLED_WIDTH*OLED_HEIGHT);
      // swap pixelbuffer
      // programVector.pixels = pixelbuffer[swappb];
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
    // get ready to send some called
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

extern "C" {
  void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if(htim == &htim2)
      encoderChanged(0, __HAL_TIM_GET_COUNTER(&htim2));
    else if(htim == &htim3)
      encoderChanged(1, __HAL_TIM_GET_COUNTER(&htim3));
  }
}
