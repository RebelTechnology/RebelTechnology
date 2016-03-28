#include <stdlib.h>
#include "periph.h"
#include "Pixi.h"
#include "serial.h"

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
  setupSerialPort(9600);
  pixi.begin();
  printString("hello expander");
}

volatile float temp[3] = {0};
volatile int dac[8];
volatile int adc[8];
void run(){

  int pixi_id = pixi.config();
  printHex(pixi_id);
  for(int ch=0; ch<8; ++ch){
    pixi.configChannel ( CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_5N_TO_5P, ADC_MODE_CONT );
    pixi.configChannel ( CHANNEL_15-ch, CH_MODE_DAC, 0, CH_5N_TO_5P, 0 );
  }

  uint16_t i = 0;
  for(;;){
    temp[0] = pixi.readTemperature ( TEMP_CHANNEL_INT );
    temp[1] = pixi.readTemperature ( TEMP_CHANNEL_EXT0 );
    temp[2] = pixi.readTemperature ( TEMP_CHANNEL_EXT1 );

    for(int ch=0; ch<8; ++ch){
      // dac[ch] = pixi.ReadRegister( PIXI_DAC_DATA+CHANNEL_15-ch, false );
      // adc[ch] = pixi.ReadRegister( PIXI_ADC_DATA+CHANNEL_0+ch, false );
      adc[ch] = pixi.readAnalog(ch);
      pixi.writeAnalog(CHANNEL_15-ch, adc[ch]);

      printHex(adc[ch]);
    }

    if(i++ == (1<<12)-1)
      i = 0;
  }
}

extern "C" {
  void USART1_IRQHandler(void){
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
      char c = USART_ReceiveData(USART1);
    }
  }
}
