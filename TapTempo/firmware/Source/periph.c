#include "main.h"
#include "periph.h"
#include <string.h>
#include "stm32f1xx_hal.h"
#include "device.h"
#include "gpio.h"

const uint16_t pwmvalues[LED_FULL+1] = { 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 13, 14, 16, 17, 18, 20, 21, 23, 25, 27, 29, 32, 34, 37, 40, 43, 47, 50, 55, 59, 64, 69, 74, 80, 87, 94, 101, 110, 118, 128, 138, 149, 161, 174, 188, 203, 219, 237, 256, 277, 299, 323, 349, 377, 407, 439, 474, 512, 553, 598, 646, 697, 753, 813, 879, 949, 1025, 1107, 1195, 1291, 1394, 1506, 1627, 1757 
};

void setPWM1(uint16_t pulse){
  TIM3->CCR1 = pulse;
}

void setPWM2(uint16_t pulse){
  TIM1->CCR1 = pulse;
}

void setLed1(uint16_t brightness){
  static uint16_t value = 0;
  if(brightness != value && brightness <= LED_FULL){
    setPWM1(pwmvalues[brightness]);
    value = brightness;
  }
}

void setLed2(uint16_t brightness){
  static uint16_t value = 0;
  if(brightness != value && brightness <= LED_FULL){
    setPWM2(pwmvalues[brightness]);
    value = brightness;
  }
}

char* getFirmwareVersion(){ 
  return HARDWARE_VERSION "-" FIRMWARE_VERSION ;
}
