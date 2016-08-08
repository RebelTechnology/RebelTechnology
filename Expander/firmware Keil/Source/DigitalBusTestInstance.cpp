#include <inttypes.h>
#include <stdlib.h>

#undef _DigitalBusReader_h_
#undef _DigitalBusHandler_h_
#undef _MidiReader_h_
#undef _MidiHandler_h_
#define __SERIAL_H

void serial_write(uint8_t* data, uint16_t size);

#include "DigitalBusHandler.cpp"
#include "DigitalBusReader.cpp"
#include "MidiHandler.cpp"
#include "MidiReader.cpp"

DigitalBusReader bus;

int bus_status(){
  static uint32_t lastpolled = 0;
  // if(lastpolled++ > 100){
    bus.connected();
    lastpolled = 0;
  // }
  return bus.getStatus();
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

void bus_tx_data(const uint8_t* data, uint16_t size){
  debug << "tx data [" << size << "]" ;
  bus.sendData(data, size);
}

void bus_tx_error(const char* reason){
  debug << "Digital bus send error: " << reason << ".";
}

void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".";
  bus.reset();
}
