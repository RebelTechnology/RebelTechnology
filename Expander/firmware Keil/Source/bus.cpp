#include "stm32f1xx_hal.h"
#include "bus.h"
#include "message.h"
#include "serial.h"
#include "clock.h"
#include "DigitalBusReader.h"
#include "mxconstants.h"

static DigitalBusReader bus;

uint8_t* bus_deviceid(){
  return ((uint8_t*)0x1ffff7e8); /* STM32F1 */
  // return ((uint8_t *)0x1FFF7A10); /* STM32F4, STM32F0 */ 
}

void bus_setup(){
  debug << "bus_setup\r\n";
  serial_setup(USART_BAUDRATE);
}

#define BUS_IDLE_INTERVAL 2300

int bus_status(){
  static uint32_t lastpolled = 0;
  if(getSysTicks() > lastpolled + BUS_IDLE_INTERVAL){
    bus.connected();
    lastpolled = getSysTicks();
  }
  return bus.getStatus();
}

extern "C" {
  static uint8_t bus_rx_index = 0;
  void USART1_IRQHandler(void){
    static uint8_t frame[4];
    /* If overrun condition occurs, clear the ORE flag and recover communication */
    if(USART_GetFlagStatus(USART_PERIPH, USART_FLAG_ORE) != RESET){
      USART_ReceiveData(USART_PERIPH);
      bus_rx_index = 0;
    }else if(USART_GetITStatus(USART_PERIPH, USART_IT_RXNE) != RESET){    
      // Reading the receive data register clears the RXNE flag implicitly
      char c = USART_ReceiveData(USART_PERIPH);
      frame[bus_rx_index++] = c;
      if(bus_rx_index == 4){
	bus_rx_index = 0;
	bus.readBusFrame(frame);
      }
    }
  }
}

// extern "C" {
//   static uint8_t bus_rx_index = 0;
//   void USART1_IRQHandler(void){
//     static uint8_t frame[4];
//     /* RXNE handler */
//     if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
//       char c = USART_ReceiveData(USART1);
//       reader.read(c);
//     }
//   }
// }

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
  bus_rx_index = 0;
  bus.reset();
}
