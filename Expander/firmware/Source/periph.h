#ifndef __OWL_CONTROL_H
#define __OWL_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "device.h"
#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

   /* typedef enum { */
   /*   NONE  = 0, */
   /*   GREEN = LED_GREEN, */
   /*   RED   = LED_RED */
   /* }  LedPin; */

#define LED_FULL 100
   /* LedPin getLed(); */
   void setLed(uint16_t brightness);
   /* void setLed(LedPin led); */
   /* void toggleLed(); */

   void ledSetup();
   void pushButtonSetup(void (*f)());
   void triggerInputSetup(void (*f)());
   void timerSetup(uint16_t period, void (*f)());
   void timerSet(uint16_t period);
   void dacSetup();
   void adcSetup();
   uint16_t getAnalogValue(uint8_t index);
   uint16_t* getAnalogValues();

   bool isPushButtonPressed();
   bool isTriggerHigh();

   void setupSwitchA(void (*f)());
   void setupSwitchB(void (*f)());

#ifdef __cplusplus
}
#endif

#endif /* __OWL_CONTROL_H */
