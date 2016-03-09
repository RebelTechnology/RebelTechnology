#include <stdlib.h>
#include "periph.h"

void setAnalogValue(uint8_t channel, uint16_t value){
  value = value & 0xfff;
  // if(channel == 0)
  //   DAC_SetChannel1Data(DAC_Align_12b_R, value);
  // else if(channel == 1)
  //   DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

void setup(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_A, true);
  configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(TOGGLE_R_CLOCK, ENABLE);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_B, true);
  configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
#ifdef DEBUG_PINS
  configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
#endif

}


void run(){
  for(;;)
{
  }
}
