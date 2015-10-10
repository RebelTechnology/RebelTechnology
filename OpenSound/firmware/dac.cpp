#include "dac.h"
#include "application.h"

void dac_init() {
  pinMode(DAC1, OUTPUT);
  pinMode(DAC2, OUTPUT);

  //HAL_DAC_Init();
  DAC_InitTypeDef DAC_InitStructure;

  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  DAC_DeInit();
  /* DAC channel1 & channel2 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* Enable DAC Channel2 */
  DAC_Cmd(DAC_Channel_2, ENABLE);
}

void dac_set_a(uint16_t value){
  value = 4095 - max(0, min(4095, value));
  pinMode(DAC1, OUTPUT);
  analogWrite(DAC1, value); 
  /* Set the DAC Channel1 data */
  //  DAC_SetChannel1Data(DAC_Align_12b_R, value);
}

void dac_set_b(uint16_t value){
  value = 4095 - max(0, min(4095, value));
  pinMode(DAC2, OUTPUT);
  analogWrite(DAC2, value); 
  /* Set the DAC Channel2 data */
  //  DAC_SetChannel2Data(DAC_Align_12b_R, value);
}
