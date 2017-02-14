#ifndef __OWL_CONTROL_H
#define __OWL_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f1xx_hal.h"
/* #include "device.h" */
/* #include "gpio.h" */

#ifdef __cplusplus
 extern "C" {
#endif

   /* typedef enum { */
   /*   NONE  = 0, */
   /*   GREEN = LED_GREEN, */
   /*   RED   = LED_RED */
   /* }  LedPin; */

#define LED_FULL 127
   /* LedPin getLed(); */
   void setLed1(uint16_t brightness);
   void setLed2(uint16_t brightness);
   /* void setLed(LedPin led); */
   /* void toggleLed(); */

   /* void ledSetup(); */
   /* void pushButtonSetup(void (*f)()); */
   /* void triggerInputSetup(void (*f)()); */
   /* void timerSetup(uint16_t period, void (*f)()); */
   /* void timerSet(uint16_t period); */
   /* void dacSetup(); */
   /* void adcSetup(); */

   /* uint16_t getAnalogValue(uint8_t index); */
   /* uint16_t* getAnalogValues(); */

   /* void setupSwitchA(void (*f)()); */
   /* void setupSwitchB(void (*f)()); */

#ifdef __cplusplus
}
#endif

#endif /* __OWL_CONTROL_H */
