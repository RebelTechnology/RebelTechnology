#include <stdint.h>
#include "stm32f10x.h"

extern void setup();
extern void run();

int main(void){
  /* Configure 24MHz PLL */
  RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_6);
  RCC_PLLCmd(ENABLE);
  /* Wait till PLL is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}  
  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  /* Wait till PLL is used as system clock source */
  while(RCC_GetSYSCLKSource() != 0x08){}
  SystemCoreClockUpdate();

  setup();
  run();

  return 0;
}
