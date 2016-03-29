#include "midi.h"
#include "serial.h"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#include "stm32f10x.h"

static uint8_t rxbuffer[256];
MidiReader reader(rxbuffer, 256);
MidiWriter writer(0);

void midiSetup(){
  setupSerialPort(31250);
}

void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value){
  writer.controlChange(ch, cc, value);
}

extern "C" {
  void USART1_IRQHandler(void){
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
      char c = USART_ReceiveData(USART1);
      reader.read(c);
    }
  }
}
