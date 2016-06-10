#include "midi.h"
#include "uart.h"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#include "stm32f4xx_hal.h"
#include "mxconstants.h"

#ifdef USE_UART

static uint8_t frame[4];
static uint8_t rxbuffer[256];
MidiReader reader(rxbuffer, 256);
MidiWriter writer(0);

void midiSetup(){
  // setupSerialPort(31250);
  serial_read(frame, 4);
}

void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value){
  writer.controlChange(ch, cc, value);
}

void midiSendPC(uint8_t ch, uint8_t pc){
  writer.programChange(ch, pc);
}

extern "C" {

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  switch(frame[0]){
  case USB_COMMAND_MISC:
  case USB_COMMAND_CABLE_EVENT:
    // ignore
    break;
  case USB_COMMAND_SINGLE_BYTE:
  case USB_COMMAND_SYSEX_EOX1:
    // one byte message
    reader.read(frame[1]);
    break;
  case USB_COMMAND_2BYTE_SYSTEM_COMMON:
  case USB_COMMAND_SYSEX_EOX2:
  case USB_COMMAND_PROGRAM_CHANGE:
  case USB_COMMAND_CHANNEL_PRESSURE:
    reader.read(frame[1]);
    reader.read(frame[2]);
    break;
  default:
    // three byte message
    reader.read(frame[1]);
    reader.read(frame[2]);
    reader.read(frame[3]);
    break;
  }
}

  void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  }

}

//   void USART1_IRQHandler(void){
//     /* RXNE handler */
//   if((__HAL_UART_GET_IT(huart, UART_IT_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE) != RESET))

//     if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
//       char c = USART_ReceiveData(USART1);
//       reader.read(c);
//     }
//   }
// }

#endif
