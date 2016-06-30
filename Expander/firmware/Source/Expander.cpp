#include <stdlib.h>
#include "periph.h"
#include "Pixi.h"
#include "bus.h"
#include "message.h"
#include "OpenWareMidiControl.h"

#define HYSTERESIS_DELTA 3

Pixi pixi;
void setup(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(TOGGLE_R_CLOCK, ENABLE);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_B, true);
//   configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
// #ifdef DEBUG_PINS
//   configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
// #endif

  configureDigitalOutput(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin);
  setPin(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin); // bring BLANK high to turn LEDs off

  pixi.begin();

  bus_setup();
}

enum ChannelMode {
  ADC_5TO5,
  ADC_0TO10,
  ADC_10TO0,
  DAC_MODE,
  DAC_5TO5,
  DAC_0TO10,
  DAC_10TO0
};

uint8_t cc_values[16] = {0};
volatile ChannelMode cfg[16];
volatile int dac[16];
volatile int adc[16];

// #define USE_TEMP
#ifdef USE_TEMP
volatile float temp[3] = {0};
#endif

void configureChannel(uint8_t ch, ChannelMode mode){
  switch(mode){
  case ADC_5TO5:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_5N_TO_5P, ADC_MODE_CONT);
    break;
  case ADC_0TO10:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_0_TO_10P, ADC_MODE_CONT);
    break;
  case DAC_5TO5:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_DAC, 0, CH_5N_TO_5P, 0);
    break;
  case DAC_0TO10:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_DAC, 0, CH_0_TO_10P, 0);
    break;
  }
  cfg[ch] = mode;
}

void run(){
  int pixi_id = pixi.config();
  for(int ch=0; ch<16; ++ch){
    adc[ch] = 0;
    dac[ch] = 2048;
    cfg[ch] = ADC_5TO5;
  }
  for(int ch=0; ch<16; ++ch)
    configureChannel(ch, cfg[ch]);
  uint16_t i = 0;
  for(;;){
#ifdef USE_TEMP
    temp[0] = pixi.readTemperature ( TEMP_CHANNEL_INT );
    temp[1] = pixi.readTemperature ( TEMP_CHANNEL_EXT0 );
    temp[2] = pixi.readTemperature ( TEMP_CHANNEL_EXT1 );
#endif
    for(int ch=0; ch<16; ++ch){
      if(cfg[ch] < DAC_MODE){
	adc[ch] = pixi.readAnalog(ch);
	uint8_t cc = adc[ch] >> 5;
	if(abs(cc - cc_values[ch]) > HYSTERESIS_DELTA){
	  bus_tx_parameter(PARAMETER_AA+ch, adc[ch]);
	  cc_values[ch] = cc;
	}
      }
    }
    // pixi.writeAnalog(CHANNEL_7, i); // output ramp on
    // pixi.writeAnalog(CHANNEL_8, dac[8]);
    // pixi.writeAnalog(CHANNEL_7, dac[7]);
    if(i++ >= 2048)
      i = 0;
  }
}

void bus_rx_parameter(uint8_t pid, int16_t value){
  debug << "rx parameter [" << pid << "][" << value << "]" ;
  if(pid >= PARAMETER_AA && pid <= PARAMETER_BH){
    uint8_t ch = pid-PARAMETER_AA;
    if(cfg[ch] < DAC_MODE){
      if(value < 0){ // auto configure to output
	configureChannel(ch, DAC_5TO5);
      }else{
	configureChannel(ch, DAC_0TO10);
      }
    }
    dac[ch] = value;
  }
}

void bus_rx_button(uint8_t bid, int16_t value){
  debug << "rx button [" << bid << "][" << value << "]" ;
}

