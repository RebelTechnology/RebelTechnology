#include "uart.h"

#include "stm32f7xx_hal.h"
#include "errorhandlers.h"
#include "mxconstants.h"

extern UART_HandleTypeDef huart1;

void serial_read(uint8_t* data, uint16_t size){
  if(HAL_UART_Receive_IT(&huart1, data, size) != HAL_OK)
    ASSERT(0, "UART rx failed");
}

void serial_write(uint8_t* data, uint16_t size){
  if(HAL_UART_Transmit_IT(&huart1, data, size) != HAL_OK)
    ASSERT(0, "UART tx failed");
}
