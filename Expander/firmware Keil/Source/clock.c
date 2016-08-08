#include "clock.h"
#include "stm32f1xx_hal.h"

volatile uint32_t systicks = 0;

void clock_setup(){
  /* Configures SysTick to be called every ms */
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000); // divide by 100 for 10ms period
}

void SysTick_Handler(void){
  systicks++;
}
