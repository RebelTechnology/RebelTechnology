#include "gpio.h"

bool getPin(GPIO_TypeDef* port, uint32_t pin){
  return port->IDR & pin;
}

void setPin(GPIO_TypeDef* port, uint32_t pin){
  port->BSRR = pin;
}

void clearPin(GPIO_TypeDef* port, uint32_t pin){
  port->BRR = pin;
}

void togglePin(GPIO_TypeDef* port, uint32_t pin){
  port->ODR ^= pin;
/*      GPIO_ToggleBits(port, pin); */
}
