#include "periph.h"
#include <string.h>
#include "stm32f10x.h"
#include "device.h"
#include "gpio.h"


void setLed(LedPin led){
  clearPin(LED_PORT, led ^ (LED_RED|LED_GREEN));
  setPin(LED_PORT, led);
#ifdef OWLMODULAR
  if(led == LED_RED)
    clearPin(GPIOB, GPIO_Pin_7); // PB7 OWL Modular digital output high
  else
    setPin(GPIOB, GPIO_Pin_7); // PB7 OWL Modular digital output low
#endif
}

void toggleLed(){
  togglePin(LED_PORT, LED_RED|LED_GREEN);
#ifdef OWLMODULAR
  togglePin(GPIOB, GPIO_Pin_7); // PB7 OWL Modular digital output
#endif
}

void blink(){
  togglePin(LED_PORT, LED_RED|LED_GREEN);
#ifdef OWLMODULAR
  togglePin(GPIOB, GPIO_Pin_7); // PB7 OWL Modular digital output
#endif
  togglePin(LED_PORT, LED_RED|LED_GREEN);
#ifdef OWLMODULAR
  togglePin(GPIOB, GPIO_Pin_7); // PB7 OWL Modular digital output
#endif
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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* RCC_AHB1PeriphClockCmd(LED_CLOCK, ENABLE); */
  /* RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); */
  configureDigitalOutput(LED_PORT, LED_RED|LED_GREEN);
  clearPin(LED_PORT, LED_RED|LED_GREEN);
}

bool isPushButtonPressed(){
  return !getPin(PUSHBUTTON_PORT, PUSHBUTTON_PIN);
}

/* uint16_t adc_values[NOF_ADC_VALUES]; */
/* void adcSetup(){ */
/*   memset(adc_values, 0, sizeof adc_values); */
/*   adcSetupDMA(&adc_values[0]); */
/* } */

/* uint16_t getAnalogValue(uint8_t index){ */
/*   assert_param(index < sizeof(adc_values)); */
/*   return adc_values[index]; */
/* } */

/* uint16_t* getAnalogValues(){ */
/*   return adc_values; */
/* } */

/* void (*externalInterruptCallbackA)(); */

void pushButtonSetup(){
  /* EXTIn connects to pins PAn, PBn et c */

  /* Configure PA7 */
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  /* GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Connect EXTI Line to PA7 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);

  /* Configure EXTI line */
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

 NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable and set EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void){
  if(EXTI_GetITStatus(EXTI_Line7) != RESET){
    /* Clear the  EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line7);
    toggleLed();
  }
}

/* /\**  */
/*  * Configure EXTI callback */
/*  *\/ */
/* void setupSwitchA(void (*f)()){ */
/*   externalInterruptCallbackA = f; */

/*   EXTI_InitTypeDef EXTI_InitStructure; */
/*   NVIC_InitTypeDef NVIC_InitStructure; */

/*   /\* Enable the clocks *\/ */
/*   RCC_AHB1PeriphClockCmd(PUSHBUTTON_CLOCK, ENABLE); */
/*   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); */

/*   /\* Configure switch pin *\/ */
/*   configureDigitalInput(PUSHBUTTON_PORT, PUSHBUTTON_PIN, GPIO_PuPd_UP); */

/*   /\* Connect EXTI Line to GPIO Pin *\/ */
/*   SYSCFG_EXTILineConfig(PUSHBUTTON_PORT_SOURCE, PUSHBUTTON_PIN_SOURCE); */

/*   /\* Configure EXTI line *\/ */
/*   EXTI_StructInit(&EXTI_InitStructure); */
/*   EXTI_InitStructure.EXTI_Line = PUSHBUTTON_PIN_LINE; */
/*   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; */
/*   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; */
/*   EXTI_InitStructure.EXTI_LineCmd = ENABLE; */
/*   EXTI_Init(&EXTI_InitStructure); */

/*   /\* Enable and set EXTI Interrupt *\/ */
/*   NVIC_InitStructure.NVIC_IRQChannel = PUSHBUTTON_IRQ; */
/*   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PUSHBUTTON_PRIORITY; */
/*   NVIC_InitStructure.NVIC_IRQChannelSubPriority = PUSHBUTTON_SUBPRIORITY; */
/*   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; */
/*   NVIC_Init(&NVIC_InitStructure); */
/* } */

/* void PUSHBUTTON_HANDLER(void) { */
/*   if(EXTI_GetITStatus(PUSHBUTTON_PIN_LINE) != RESET){  */
/*     (*externalInterruptCallbackA)(); */
/*     /\* Clear the EXTI line pending bit *\/ */
/*     EXTI_ClearITPendingBit(PUSHBUTTON_PIN_LINE); */
/*   } */
/* } */
