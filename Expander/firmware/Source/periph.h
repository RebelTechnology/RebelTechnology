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

   void timerSetup(uint16_t period, void (*f)());
   void timerSet(uint16_t period);
   void adcSetup();

#ifdef __cplusplus
}
#endif

#endif /* __OWL_CONTROL_H */
