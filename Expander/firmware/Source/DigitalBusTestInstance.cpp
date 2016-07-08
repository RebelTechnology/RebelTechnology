#include <inttypes.h>
#undef _DigitalBusReader_h_
#undef _DigitalBusHandler_h_
#undef _MidiReader_h_
#undef _MidiHandler_h_
#include "DigitalBusHandler.cpp"
#include "DigitalBusReader.cpp"
#include "MidiHandler.cpp"
#include "MidiReader.cpp"

DigitalBusHandler bushandler;


int bus_status(){
  static uint32_t lastpolled = 0;
  if(lastpolled++ > 100){
    bushandler.connected();
    lastpolled = 0;
  }
  return bushandler.getStatus();
}

void bus_tx_parameter(uint8_t pid, int16_t value){
  debug << "tx parameter [" << pid << "][" << value << "]" ;
  bushandler.sendParameterChange(pid, value);
}

void bus_tx_button(uint8_t bid, int16_t value){
  debug << "tx button [" << bid << "][" << value << "]" ;
  bushandler.sendButtonChange(bid, value);
}

void bus_tx_command(uint8_t cmd, int16_t data){
  debug << "tx command [" << cmd << "][" << data << "]" ;
  bushandler.sendCommand(cmd, data);
}

void bus_tx_message(const char* msg){
  debug << "tx msg [" << msg << "]" ;
  bushandler.sendMessage(msg);
}

void bus_tx_error(const char* reason){
  debug << "Digital bus send error: " << reason << ".";
}

void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".";
  bushandler.reset();
}
