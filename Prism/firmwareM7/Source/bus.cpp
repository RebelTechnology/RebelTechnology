#include "bus.h"
#include "midi.h"
#include "serial.h"
#include "message.h"
#include "DigitalBusReader.h"
#include "cmsis_os.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "mxconstants.h"
#include "MidiWriter.hpp"

#ifdef USE_UART

static uint8_t busframe[4];
MidiWriter writer(0);
static DigitalBusReader bus;

void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value){
  writer.controlChange(ch, cc, value);
}

void midiSendPC(uint8_t ch, uint8_t pc){
  writer.programChange(ch, pc);
}

extern "C" {

  void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
    bus.reset();
  }

  void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    bus.readBusFrame(busframe);
  }

  void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  }

}

uint8_t* bus_deviceid(){
  // return ((uint8_t*)0x1ffff7e8); /* STM32F1 */
  return ((uint8_t *)0x1FFF7A10); /* STM32F4, STM32F0 */ 
}

void bus_setup(){
  // debug << "bus_setup\r\n";
  // serial_setup(USART_BAUDRATE);
  serial_read(busframe, 4);
}

#define BUS_IDLE_INTERVAL 2300

int bus_status(){
  static uint32_t lastpolled = 0;
  if(osKernelSysTick() > lastpolled + BUS_IDLE_INTERVAL){
    bus.connected();
    lastpolled = osKernelSysTick();
  }
  return bus.getStatus();
}

// extern "C" {
//   static uint8_t bus_rx_index = 0;
//   void USARTx_IRQHandler(void){
//   // void USART1_IRQHandler(void){
//     static uint8_t frame[4];
//     /* If overrun condition occurs, clear the ORE flag and recover communication */
//     if(USART_GetFlagStatus(USART_PERIPH, USART_FLAG_ORE) != RESET){
//       USART_ReceiveData(USART_PERIPH);
//       bus_rx_index = 0;
//     }else if(USART_GetITStatus(USART_PERIPH, USART_IT_RXNE) != RESET){    
//       // Reading the receive data register clears the RXNE flag implicitly
//       char c = USART_ReceiveData(USART_PERIPH);
//       frame[bus_rx_index++] = c;
//       if(bus_rx_index == 4){
// 	bus_rx_index = 0;
// 	bus.readBusFrame(frame);
//       }
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
  // bus_rx_index = 0;

  bus.reset();
}


#endif /* USE_UART */