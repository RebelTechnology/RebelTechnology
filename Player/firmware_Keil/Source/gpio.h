#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f746xx.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Every GPIO port has an input and */
/* output data register, ODR and IDR */
/* respectively, which hold the status of the pin */
   inline bool getPin(GPIO_TypeDef* port, uint32_t pin){
     return port->IDR & pin;
/*      return GPIO_ReadInputDataBit(port, pin); */
   }
   inline void setPin(GPIO_TypeDef* port, uint32_t pin){
     port->BSRR = pin;
   }
   inline void clearPin(GPIO_TypeDef* port, uint32_t pin){
     port->BSRR = pin << 16;
   }
   inline void togglePin(GPIO_TypeDef* port, uint32_t pin){
     port->ODR ^= pin;
   }

   /* void configureDigitalInput(GPIO_TypeDef* port, uint32_t pin, GPIOPuPd_TypeDef pull); */
   /* void configureDigitalOutput(GPIO_TypeDef* port, uint32_t pin); */

   /* void configureAnalogInput(GPIO_TypeDef* port, uint32_t pin); */
   /* void configureAnalogOutput(GPIO_TypeDef* port, uint32_t pin); */

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
