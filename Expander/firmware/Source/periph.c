#include "periph.h"
#include <string.h>
#include "stm32f10x.h"
#include "device.h"
#include "gpio.h"

char* getFirmwareVersion(){ 
  return HARDWARE_VERSION "-" FIRMWARE_VERSION ;
}

uint16_t timerPeriod;
void (*timerCallbackA)();
void timerSet(uint16_t period){
  timerPeriod = period;
  TIM_SetCompare1(TIM2, timerPeriod);
}

void timerSetup(uint16_t period, void (*f)()){
  timerCallbackA = f;
  timerPeriod = period;

  /* PCLK1 = HCLK/4 */
  RCC_PCLK1Config(RCC_HCLK_Div4);

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* Enable the TIM2 global Interrupt */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

  /* ---------------------------------------------------------------
     TIM2 Configuration: Output Compare Timing Mode:
     TIM2 counter clock at 6 MHz
     CC1 update rate = TIM2 counter clock / CCR1_Val = 146.48 Hz
     CC2 update rate = TIM2 counter clock / CCR2_Val = 219.7 Hz
     CC3 update rate = TIM2 counter clock / CCR3_Val = 439.4 Hz
     CC4 update rate = TIM2 counter clock / CCR4_Val = 878.9 Hz
     --------------------------------------------------------------- */

  /* Compute the prescaler value */
  /* pre = (uint16_t) (SystemCoreClock / 12000000) - 1; */
  uint16_t pre = 1;

  /* Time base configuration */
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM2, pre, TIM_PSCReloadMode_Immediate);

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = period;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* TIM IT enable */
  // TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void){
uint16_t capture = 0;
  if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
    /* call the callback function */
    (*timerCallbackA)();
    capture = TIM_GetCapture1(TIM2);
    TIM_SetCompare1(TIM2, capture + timerPeriod);
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
  for(;;);
}
#endif
