#ifndef _MIDIWRITER_H_
#define _MIDIWRITER_H_

#include <inttypes.h>
// #include <stdio.h>
// #include "usart.h"
#include "MidiStatus.h"
// #include <stdio.h>
#include "uart.h"

class MidiWriter { // : public MidiInterface {
public:

  MidiWriter(int ch) : channel(ch) {}

  void channelPressure(uint8_t channel, uint8_t value){
    write(0xd0 | channel);
    write(value & 0x7f);
  }

  void startSong(){
    write(0xfa);
  }

  void stopSong(){
    write(0xfc);
  }

  void continueSong(){
    write(0xfb);
  }

  void midiClock(){
    write(0xf8);
  }

  void pitchBend(uint8_t channel, uint16_t value){
    write(0xe0 | channel);
    write(value & 0x7f);
    write((value>>7) & 0x7f);
  }

  void controlChange(uint8_t channel, uint8_t cc, uint8_t value){
#if 1
    uint8_t packet[4] = { USB_COMMAND_CONTROL_CHANGE,
    			  (uint8_t)(CONTROL_CHANGE | channel),
    			  cc, value };
    serial_write(packet, sizeof(packet));
#else
    uint8_t packet[3] = { 
			  (uint8_t)(CONTROL_CHANGE | channel),
			  cc, value };
    serial_write(packet, sizeof(packet));
#endif
  }

  void programChange(uint8_t channel, uint8_t pc){
#if 1
    uint8_t packet[4] = { USB_COMMAND_PROGRAM_CHANGE,
    			  (uint8_t)(PROGRAM_CHANGE | channel),
    			  pc, 0 };
    serial_write(packet, sizeof(packet));
#else
    uint8_t packet[2] = { 
			  (uint8_t)(PROGRAM_CHANGE | channel),
			  pc };
    serial_write(packet, sizeof(packet));
#endif
  }

  void noteOff(uint8_t channel, uint8_t note, uint8_t velocity){
    write(0x80 | channel);
    write(note & 0x7f);
    write(velocity & 0x7f);
  }

  void noteOn(uint8_t channel, uint8_t note, uint8_t velocity){
    write(0x90 | channel);
    write(note & 0x7f);
    write(velocity & 0x7f);
  }

  void afterTouch(uint8_t channel, uint8_t note, uint8_t value){
    write(POLY_KEY_PRESSURE | channel);
    write(note & 0x7f);
    write(value & 0x7f);
  }

  void pitchBend(uint16_t value){
    write(0xe0 | channel);
    write(value & 0x7f);
    write((value>>7) & 0x7f);
  }

  void controlChange(uint8_t cc, uint8_t value){
    write(0xb0 | channel);
    write(cc & 0x7f);
    write(value & 0x7f);
  }

  void programChange(uint8_t pg){
    write(0xc0 | channel);
    write(pg & 0x7f);
  }

  void noteOff(uint8_t note, uint8_t velocity){
    write(0x80 | channel);
    write(note & 0x7f);
    write(velocity & 0x7f);
  }

  void noteOn(uint8_t note, uint8_t velocity){
    write(0x90 | channel);
    write(note & 0x7f);
    write(velocity & 0x7f);
  }

  void afterTouch(uint8_t note, uint8_t value){
    write(POLY_KEY_PRESSURE | channel);
    write(note & 0x7f);
    write(value & 0x7f);
  }

  void allNotesOff(){
    controlChange(channel, 0x7b, 00);
  }

  void sysex(uint8_t manufacturer, uint8_t device, uint8_t *data, uint16_t size){
#if 1
    uint8_t packet[4] = { USB_COMMAND_SYSEX, SYSEX, manufacturer, device };
    serial_write(packet, sizeof(packet));
    int count = size/3;
    uint8_t* src = data;
    while(count-- > 0){
      packet[1] = (*src++ & 0x7f);
      packet[2] = (*src++ & 0x7f);
      packet[3] = (*src++ & 0x7f);
      serial_write(packet, sizeof(packet));
    }
    count = size % 3;
    switch(count){
    case 0:
      packet[0] = USB_COMMAND_SYSEX_EOX1;
      packet[1] = SYSEX_EOX;
      packet[2] = 0;
      packet[3] = 0;
      break;
    case 1:
      packet[0] = USB_COMMAND_SYSEX_EOX2;
      packet[1] = (*src++ & 0x7f);
      packet[2] = SYSEX_EOX;
      packet[3] = 0;
      break;
    case 2:
      packet[0] = USB_COMMAND_SYSEX_EOX3;
      packet[1] = (*src++ & 0x7f);
      packet[2] = (*src++ & 0x7f);
      packet[3] = SYSEX_EOX;
      break;
    }
    serial_write(packet, sizeof(packet));
#else
    write(SYSEX);
    write(manufacturer & 0x7f);
    for(int i=0; i<size; ++i)
      write(data[i] & 0x7f);
    write(SYSEX_EOX);
#endif
  }

  void write(uint8_t *data, uint8_t length){
    // Serial1.write(data, length);
    // for(int i=0; i<length; ++i)
    //   write(data[i]);
    // uart_transmit_bytes(data, length );
    serial_write(data, length);
  }

  void write(uint8_t data){
    /* Wait until end of previous transmit */
    // while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    // /* send data */
    // USART_SendData(USART_PERIPH, data);
    // serialputchar(data);
    write(&data, 1);
  }

private:
  uint8_t channel;

};


#endif /* _MIDIWRITER_H_ */
