#include "stm32f10x.h"

#include "periph.h"

/* void setClock(){ */
/*   FLASH_SetLatency(FLASH_Latency_0);                                                          */
/*   /\* Start with HSI clock (internal 8mhz), divide by 2 and multiply by 9 to                    */
/*    * get maximum allowed frequency: 36Mhz                                                      */
/*    * Enable PLL, wait till it's stable, then select it as system clock*\/                      */
/*   RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_6); // 24MHz */
/*   RCC_PLLCmd(ENABLE);                                                                          */
/*   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {} */
/*   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                                                  */
/*   /\* Set HCLK, PCLK1, and PCLK2 to SCLK (these are default *\/                                  */
/*   RCC_HCLKConfig(RCC_SYSCLK_Div1);                                                            */
/*   RCC_PCLK1Config(RCC_HCLK_Div1);                                                              */
/*   RCC_PCLK2Config(RCC_HCLK_Div1);                                                              */
/*   SystemCoreClockUpdate(); */
/* } */

int main(void) {
  ledSetup();
  setLed(RED);
  int count = 0;
  for(;;){
    if(count++ % 0x10 == 0){
      toggleLed();
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
  for(;;);
}
#endif
