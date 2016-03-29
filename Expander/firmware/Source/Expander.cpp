#include <stdlib.h>
#include "periph.h"
#include "Pixi.h"
#include "midi.h"

void setAnalogValue(uint8_t channel, uint16_t value){
  value = value & 0xfff;
  // if(channel == 0)
  //   DAC_SetChannel1Data(DAC_Align_12b_R, value);
  // else if(channel == 1)
  //   DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

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
  midiSetup();
  pixi.begin();
}

uint8_t cc_values[16] = {0};

volatile int dac[16];
volatile int adc[16];

// #define USE_TEMP
#ifdef USE_TEMP
volatile float temp[3] = {0};
#endif

void midiReceiveCC(uint8_t ch, uint8_t cc, uint8_t value){
  ch = cc-20;
  if(ch < 16)
    dac[ch] = value << 5;
}

void run(){
  int pixi_id = pixi.config();
  for(int ch=7; ch<16; ++ch)
    dac[ch] = 2048;
  for(int ch=0; ch<7; ++ch){
    // pixi.configChannel ( CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_5N_TO_5P, ADC_MODE_CONT );
    // pixi.configChannel ( CHANNEL_15-ch, CH_MODE_DAC, 0, CH_5N_TO_5P, 0 );
    // pixi.configChannel ( CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_0_TO_10P, ADC_MODE_CONT );
    // pixi.configChannel ( CHANNEL_15-ch, CH_MODE_DAC, 0, CH_0_TO_10P, 0 );
    pixi.configChannel ( CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_0_TO_10P, ADC_MODE_CONT );
    pixi.configChannel ( CHANNEL_15-ch, CH_MODE_ADC_P, 0, CH_5N_TO_5P, ADC_MODE_CONT );
  }
  pixi.configChannel ( CHANNEL_7, CH_MODE_DAC, 0, CH_0_TO_10P, 0 );
  pixi.configChannel ( CHANNEL_8, CH_MODE_DAC, 0, CH_5N_TO_5P, 0 );

  uint16_t i = 0;
  for(;;){
#ifdef USE_TEMP
    temp[0] = pixi.readTemperature ( TEMP_CHANNEL_INT );
    temp[1] = pixi.readTemperature ( TEMP_CHANNEL_EXT0 );
    temp[2] = pixi.readTemperature ( TEMP_CHANNEL_EXT1 );
#endif
    for(int ch=0; ch<16; ++ch){
      if(ch != 7 && ch != 8){
	adc[ch] = pixi.readAnalog(ch);
	uint8_t cc = adc[ch] >> 5;
	if(abs(cc - cc_values[ch]) > 3){
	  midiSendCC(0, 20+ch, cc);
	  cc_values[ch] = cc;
	}
      }
    }
    pixi.writeAnalog(CHANNEL_7, i); // output ramp on
    pixi.writeAnalog(CHANNEL_8, dac[8]);
    // pixi.writeAnalog(CHANNEL_7, dac[7]);
    if(i++ >= 2048)
      i = 0;
  }
}
