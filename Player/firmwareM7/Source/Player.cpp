extern "C" {
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usb_host.h"
}
#include "device.h"
#include "Graphics.h"
#include "Codec.h"
#include "ProgramVector.h"
#include "midi.h"
#include "usbh_midi.h"
#include "BitState.hpp"
#include "MidiReader.h"
#include "ProgramManager.h"
#include "ApplicationSettings.h"
ApplicationSettings settings;
Graphics graphics;

extern "C" {
  void setup(void);
  void loop(void);
  void updateProgramVector(ProgramVector* pv);

  extern DAC_HandleTypeDef hdac;
  extern SDRAM_HandleTypeDef hsdram1;
  extern SPI_HandleTypeDef hspi2;
  extern TIM_HandleTypeDef htim2;
  extern TIM_HandleTypeDef htim3;
  extern TIM_HandleTypeDef htim6;
  extern SAI_HandleTypeDef hsai_BlockA1;
  extern SAI_HandleTypeDef hsai_BlockB1;
  extern ADC_HandleTypeDef hadc1;

  uint16_t getAnalogValue(uint8_t index);
  void setAnalogValue(uint8_t ch, uint16_t value);
}

uint16_t adc_values[2];
uint16_t dac_values[2];

uint16_t getAnalogValue(uint8_t index){
  return adc_values[index];
}

void setAnalogValue(uint8_t ch, uint16_t value){
  value &= 0xfff;
  dac_values[ch] = value;
}

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

#define RX_BUFF_SIZE   64  /* Max Received data 64 bytes */
extern uint8_t USBHOST_RX_Buffer[RX_BUFF_SIZE];

// #define OLED_HEIGHT 64
// #define OLED_WIDTH 128
// static bool dodisplay = true;
Codec codec;
MidiReader midireader;


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
  void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    assert_param(0);
  }
  void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }
  void HAL_DAC_ErrorCallbackCh2(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }
}

// FreeRTOS low priority numbers denote low priority tasks. 
// The idle task has priority zero (tskIDLE_PRIORITY).

void setup(void){
  // if(testram8(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram8 failed");
  // if(testram16(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram16 failed");
  // if(testram32(&hsdram1) != 0)
  //   error(PROGRAM_ERROR, "testram32 failed");

  // DWT cycle count enable
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->LAR = 0xC5ACCE55;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

  graphics.begin(&hspi2);

  __HAL_TIM_SET_COUNTER(&htim2, INT16_MAX/2);
  __HAL_TIM_SET_COUNTER(&htim3, INT16_MAX/2);
  HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);

  // updateProgramVector(getProgramVector());
  // patches[currentPatch]->reset();

#ifdef USE_CODEC
  codec.reset();
  // codec.start();
  codec.ramp(1<<23);
#endif

  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)&dac_values[0], 1, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)&dac_values[1], 1, DAC_ALIGN_12B_R);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 2);

  program.startManager();

  // vTaskDelay(20);

  // program.loadProgram();

  setAnalogValue(0, 1023);
  setAnalogValue(1, 2048);

  program.startProgram(false);
}

extern "C" {

  void loop(void){
    taskYIELD();
    // setAnalogValue(0, getAnalogValue(0));
    // setAnalogValue(1, getAnalogValue(1));
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
