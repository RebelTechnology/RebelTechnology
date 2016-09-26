#include "stm32f1xx_hal.h"
#include "bus.h"
#include "message.h"
#include "serial.h"
#include "clock.h"
#include "DigitalBusReader.h"
#include "mxconstants.h"
#include "SerialBuffer.hpp"

static DigitalBusReader bus;
// static uint8_t busframe[4];
static SerialBuffer<128> rxbuf;

extern "C" {
  void serial_rx_callback(uint8_t c);
#define NO_ERROR            0x00
#define HARDFAULT_ERROR     0x10
#define BUS_ERROR           0x20
#define MEM_ERROR           0x30
#define NMI_ERROR           0x40
#define USAGE_ERROR         0x50
#define PROGRAM_ERROR       0x60
#define CONFIG_ERROR        0x70
#define UART_ERROR          0x80

  void setErrorMessage(int8_t err, const char* msg){
    debug << "Error " << (int)err << ": " << msg << ".";
  }
}

uint8_t* bus_deviceid(){
  return ((uint8_t*)0x1ffff7e8); /* STM32F1 */
  // return ((uint8_t *)0x1FFF7A10); /* STM32F4, STM32F0 */ 
}

void bus_setup(){
  debug << "bus_setup\r\n";
  extern UART_HandleTypeDef huart1;
  UART_HandleTypeDef *huart = &huart1;
  /* Enable the UART Parity Error Interrupt */
  __HAL_UART_ENABLE_IT(huart, UART_IT_PE);
  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

#define BUS_IDLE_INTERVAL 2300

int bus_status(){
  while(rxbuf.notEmpty() && rxbuf.available() >= 4){
    uint8_t* frame = rxbuf.getReadHead();
    rxbuf.incrementReadHead(4);
    bus.readBusFrame(frame);
  }
  static uint32_t lastpolled = 0;
  if(getSysTicks() > lastpolled + BUS_IDLE_INTERVAL){
    bus.connected();
    lastpolled = getSysTicks();
  }
  return bus.getStatus();
}

extern "C" {

  void serial_rx_callback(uint8_t c){
    rxbuf.push(c);
  }

  // void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
  //   bus.reset();
  // }

  // void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  //   bus.readBusFrame(busframe);
  // }

  // void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  // }

}

void bus_tx_parameter(uint8_t pid, int16_t value){
  debug << "tx parameter [" << pid << "][" << value << "]" ;
  bus.sendParameterChange(pid, value);
}

void bus_tx_button(uint8_t bid, int16_t value){
  debug << "tx button [" << bid << "][" << value << "]" ;
  bus.sendButtonChange(bid, value);
}

void bus_tx_command(uint8_t cmd, int16_t data){
  debug << "tx command [" << cmd << "][" << data << "]" ;
  bus.sendCommand(cmd, data);
}

void bus_tx_message(const char* msg){
  debug << "tx msg [" << msg << "]" ;
  bus.sendMessage(msg);
}

void bus_tx_error(const char* reason){
  debug << "Digital bus send error: " << reason << ".";
}

void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".";
  bus.reset();
  rxbuf.reset();
}
