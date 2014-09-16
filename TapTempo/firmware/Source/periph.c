#include "periph.h"
#include <string.h>
#include "stm32f10x.h"
#include "device.h"
#include "gpio.h"


void setLed(LedPin led){
  clearPin(LED_PORT, led ^ (LED_RED|LED_GREEN));
  setPin(LED_PORT, led);
}

void toggleLed(){
  togglePin(LED_PORT, LED_RED|LED_GREEN);
}

char* getFirmwareVersion(){ 
  return HARDWARE_VERSION "-" FIRMWARE_VERSION ;
}

bool isClockExternal(){
/* return RCC_HSE_ON */
  return RCC_WaitForHSEStartUp() == SUCCESS;
}

/* Unique device ID register (96 bits: 12 bytes) */
uint8_t* getDeviceId(){
  const uint32_t* addr = (uint32_t*)0x1fff7a10;
  static uint32_t deviceId[3];
  deviceId[0] = addr[0];
  deviceId[1] = addr[1];
  deviceId[2] = addr[2];
  return (uint8_t*)deviceId;

  // read location 0xE0042000
  // 16 bits revision id, 4 bits reserved, 12 bits device id
  /* 0x1000 = Revision A, 0x1001 = Revision Z */

/* The ARM CortexTM-M4F integrates a JEDEC-106 ID code. It is located in the 4KB ROM table mapped on the internal PPB bus at address 0xE00FF000_0xE00FFFFF. */

/*   return DBGMCU_GetREVID() << 16 | DBGMCU_GetDEVID(); */
}

__attribute__((naked))
void dfu_reboot(void){
  /* asm volatile("ldr  r0, =0x1fff0000\n" */
  /* 	       "ldr  sp, [r0, #0]\n" */
  /* 	       "ldr  r0, [r0, #4]\n" */
  /* 	       "bx   r0\n"); */

  /* This address is within the first 64k of memory.
   * The magic number must match what is in the bootloader */
  *((unsigned long *)0x2000FFF0) = 0xaeaaefaf ^ 0x00f00b44ff;

  NVIC_SystemReset();

  /* Shouldn't get here */
  while(1);
}

/* /\* Jump to the internal STM32 bootloader. The way this works is that we */
/*  * set a magic number in memory that our startup code looks for (see startup.s). */
/*  * RAM is preserved across system reset, so when it finds this magic number, it will go */
/*  * to the bootloader code rather than the application code. */
/*  *\/ */
/* void jump_to_bootloader(void){ */
/*   uint16_t i; */
/*   volatile uint32_t delayCounter; */

/*   /\* Disable USB in advance: this will give the computer time to */
/*    * recognise it's been disconnected, so when the system bootloader */
/*    * comes online it will get re-enumerated. */
/*    *\/ */
/*   usb_deinit(); */

/*   /\* Disable all interrupts *\/ */
/*   RCC->CIR = 0x00000000; */

/*   /\* Blink LEDs *\/ */
/*   setLed(RED); */
/*   for(i = 0; i < 3; i++) { */
/*     for(delayCounter = 0; delayCounter < 2000000; delayCounter++); */
/*     setLed(NONE); */
/*     for(delayCounter = 0; delayCounter < 2000000; delayCounter++); */
/*     setLed(RED); */
/*   } */

/*   dfu_reboot(); */
/* } */

LedPin getLed(){
  if(getPin(LED_PORT, LED_GREEN))
    return GREEN;
  else if(getPin(LED_PORT, LED_RED))
    return RED;
  else
    return NONE;
}

void ledSetup(){
  configureDigitalOutput(LED_PORT, LED_RED|LED_GREEN);
  clearPin(LED_PORT, LED_RED|LED_GREEN);
}

bool isPushButtonPressed(){
  return !getPin(PUSHBUTTON_PORT, PUSHBUTTON_PIN);
}

#define NOF_ADC_VALUES 1
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
uint16_t adc_values[NOF_ADC_VALUES];
void adcSetup(){
  memset(adc_values, 0, sizeof adc_values);

#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
  /* ADCCLK = PCLK2/2 */
  RCC_ADCCLKConfig(RCC_PCLK2_Div2); 
#else
  /* ADCCLK = PCLK2/4 */
  RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
#endif
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Configure PA1 (ADC Channel1) as analog input -------------------------*/
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_values;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = NOF_ADC_VALUES;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitTypeDef ADC_InitStructure;
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel1 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

uint16_t getAnalogValue(uint8_t index){
  assert_param(index < sizeof(adc_values));
  return adc_values[index];
}

uint16_t* getAnalogValues(){
  return adc_values;
}

void (*externalInterruptCallbackA)();
void (*externalInterruptCallbackB)();

void triggerInputSetup(void (*f)()){
  externalInterruptCallbackB = f;
  /* Configure pin */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = TRIGGER_INPUT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(TRIGGER_INPUT_CLOCK, ENABLE);

  /* Connect EXTI Line to pin */
  GPIO_EXTILineConfig(TRIGGER_INPUT_PORT_SOURCE, TRIGGER_INPUT_PIN_SOURCE);

  /* Configure EXTI line */
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Line = TRIGGER_INPUT_PIN_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable and set EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = TRIGGER_INPUT_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TRIGGER_INPUT_HANDLER(void){
  if(EXTI_GetITStatus(TRIGGER_INPUT_PIN_LINE) != RESET){
    /* Clear the  EXTI line pending bit */
    EXTI_ClearITPendingBit(TRIGGER_INPUT_PIN_LINE);
    /* call the callback function */
    (*externalInterruptCallbackB)();
  }
}

void pushButtonSetup(void (*f)()){
  externalInterruptCallbackA = f;

  /* EXTIn connects to pins PAn, PBn et c */

  /* Configure PA2 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = PUSHBUTTON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(PUSHBUTTON_CLOCK, ENABLE);

  /* Connect EXTI Line to pin */
  GPIO_EXTILineConfig(PUSHBUTTON_PORT_SOURCE, PUSHBUTTON_PIN_SOURCE);

  /* Configure EXTI line */
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Line = PUSHBUTTON_PIN_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable and set EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = PUSHBUTTON_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void PUSHBUTTON_HANDLER(void){
  if(EXTI_GetITStatus(PUSHBUTTON_PIN_LINE) != RESET){
    /* Clear the  EXTI line pending bit */
    EXTI_ClearITPendingBit(PUSHBUTTON_PIN_LINE);
    /* call the callback function */
    (*externalInterruptCallbackA)();
  }
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

void dacSetup(){
  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically 
     connected to the DAC converter. In order to avoid parasitic consumption, 
     the GPIO pin should be configured in analog */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  DAC_InitTypeDef DAC_InitStructure;
  /* DAC channel1 Configuration */
  DAC_StructInit(&DAC_InitStructure);
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  /* Conversion is automatic once the DAC1_DHRxxxx register 
     has been loaded, and not by external trigger */
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  /* DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1; */
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* DAC channel2 Configuration */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);

  /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA4 is 
     automatically connected to the DAC converter. */
  DAC_Cmd(DAC_Channel_1, ENABLE);

  /* Enable DAC Channel2: Once the DAC channel2 is enabled, PA5 is 
     automatically connected to the DAC converter. */
  DAC_Cmd(DAC_Channel_2, ENABLE);

  /* Set DAC dual channel DHR12RD register */
  DAC_SetDualChannelData(DAC_Align_12b_R, 0x100, 0x100);

  /* /\* Set DAC Channel1 DHR12L register *\/ */
  /* DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0); */

  /* /\* Set DAC Channel2 data *\/ */
  /* DAC_SetChannel2Data(DAC_Align_12b_L, 0x7FF0); */

  /* /\* Start DAC Channel1 conversion by software *\/ */
  /* DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE); */
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
  for(;;);
}
#endif