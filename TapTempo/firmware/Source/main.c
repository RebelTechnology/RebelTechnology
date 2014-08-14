#include "stm32f10x.h"

int main(void) {
  int count = 0;

  for(;;)
    count++;

  for(;;);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
  for(;;);
}
#endif
