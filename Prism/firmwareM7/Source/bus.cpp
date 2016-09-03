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
#include "errorhandlers.h"

#ifdef USE_UART

// static uint8_t busframe[4];
MidiWriter writer;
static DigitalBusReader bus;

void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value){
  writer.controlChange(ch, cc, value);
}

void midiSendPC(uint8_t ch, uint8_t pc){
  writer.programChange(ch, pc);
}

template<uint16_t size>
class SerialBuffer {
private:
  volatile uint16_t writepos = 0, readpos = 0;
  uint8_t buffer[size];
public:
  // uint8_t* enqueue(uint16_t len){
  //   if(writepos+len > size)
  //     writepos = 0;
  //   uint8_t* ptr = buffer+writepos;
  //   writepos += len;
  //   return ptr;
  // }
  // uint8_t* dequeue(uint16_t len){
  //   if(readpos+len > size)
  //     readpos = 0;
  //   uint8_t* ptr = buffer+readpos;
  //   readpos += len;
  //   return ptr;
  // }

  void push(uint8_t c){
    buffer[writepos++] = c;
    if(writepos >= size)
      writepos = 0;
  }

  uint8_t* getReadHead(){
    return buffer+readpos;
  }

  uint8_t* getWriteHead(){
    return buffer+writepos;
  }

  void incrementWriteHead(uint16_t len){
    // ASSERT((writepos >= readpos && writepos+len <= size) ||
    // 	   (writepos < readpos && writepos+len <= readpos), "uart rx overflow");
    writepos += len;
    if(writepos >= size)
      writepos = 0;
  }

  void incrementReadHead(uint16_t len){
    // ASSERT((readpos >= writepos && readpos+len <= size) ||
    // 	   (readpos < writepos && readpos+len <= writepos), "uart rx underflow");
    readpos += len;
    if(readpos >= size)
      readpos = 0;
  }

  // void enqueue(uint8_t* frame){
  //   buffer[writepos++] = frame[0];
  //   buffer[writepos++] = frame[1];
  //   buffer[writepos++] = frame[2];
  //   buffer[writepos++] = frame[3];
  //   if(writepos == size)
  //     writepos = 0;
  // }
  // void dequeue(uint8_t* dest){
  //   dest[0] = buffer[readpos++];
  //   dest[1] = buffer[readpos++];
  //   dest[2] = buffer[readpos++];
  //   dest[3] = buffer[readpos++];
  //   if(readpos == size)
  //     readpos = 0;
  // }
  bool notEmpty(){
    return writepos != readpos;
  }
  void reset(){
    readpos = writepos = 0;
  }
};

static SerialBuffer<128> rxbuf;

extern "C" {

  void serial_rx_callback(uint8_t c){
    rxbuf.push(c);
  }

  // void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
  //   error(UART_ERROR, "uart error");
  //   bus.reset();
  //   rxbuf.reset();
  // }

  // void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  //   rxbuf.incrementWriteHead(4);
  //   __HAL_UART_FLUSH_DRREGISTER(huart);
  //   serial_read(rxbuf.getWriteHead(), 4);
  // }

  // void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  // }
}

uint8_t* bus_deviceid(){
  // return ((uint8_t*)0x1ffff7e8); /* STM32F1 */
  return ((uint8_t *)0x1FFF7A10); /* STM32F4, STM32F0 */ 
}

void bus_setup(){
  // debug << "bus_setup\r\n";
  // serial_setup(USART_BAUDRATE);
  bus.sendReset();

  extern UART_HandleTypeDef huart1;
  UART_HandleTypeDef *huart = &huart1;
  /* Enable the UART Parity Error Interrupt */
  SET_BIT(huart->Instance->CR1, USART_CR1_PEIE);
  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  // SET_BIT(huart->Instance->CR3, USART_CR3_EIE);
  /* Enable the UART Data Register not empty Interrupt */
  SET_BIT(huart->Instance->CR1, USART_CR1_RXNEIE);

  // serial_read(rxbuf.getWriteHead(), 4);
}

#define BUS_IDLE_INTERVAL 2197

int bus_status(){

  if(rxbuf.notEmpty()){
    uint8_t* frame = rxbuf.getReadHead();
    rxbuf.incrementReadHead(4);
    bus.readBusFrame(frame);
    if((frame[0]&0xf0) == 0) // midi frame
      midi_tx_usb_buffer(frame, 4); // forward serial bus to USB MIDI
  }
  // extern UART_HandleTypeDef huart1;
  // static int waitms = 1;
  // if(HAL_UART_Receive(&huart1, busframe, 4, waitms) == HAL_OK){
  //   bus.readBusFrame(busframe);
  //   if((busframe[0]&0xf0) == 0) // midi frame
  //     midi_tx_usb_buffer(busframe, 4); // forward serial bus to USB MIDI
  // }
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

void bus_rx_parameter(uint8_t pid, int16_t value){}
void bus_rx_button(uint8_t bid, int16_t value){}
void bus_rx_command(uint8_t cmd, int16_t data){}
void bus_rx_message(const char* msg){}
void bus_rx_data(const uint8_t* data, uint16_t size){}

void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".";
  // bus_rx_index = 0;
  extern UART_HandleTypeDef huart1;
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
  bus.reset();
  rxbuf.reset();
  // bus_setup();
}

extern "C" {
  void midi_rx_usb_buffer(uint8_t *buffer, uint32_t length){
    bus.sendFrame(buffer); // forward USB MIDI to serial bus
    // bus.readMidiFrame(buffer);
  }
}

#endif /* USE_UART */
