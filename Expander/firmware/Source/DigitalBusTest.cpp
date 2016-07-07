/*
  g++ -ISource -I/opt/local/include -L/opt/local/lib -std=c++11 Source/DigitalBusTest.cpp -lboost_unit_test_framework -o DigitalBusTest && ./DigitalBusTest
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <inttypes.h>

#include "DigitalBusHandler.cpp"
#include "DigitalBusReader.cpp"
#include "MidiHandler.cpp"
#include "MidiReader.cpp"

void Debug::print(char arg){
  std::cout << arg;
}

void Debug::print(const char* arg){
  std::cout << arg;
}

void Debug::print(float arg){
  std::cout << arg;
}

void Debug::print(int arg){ 
  std::cout << arg;
}

Debug debug;

DigitalBusHandler bushandler;

uint8_t* bus_deviceid(){
  static uint32_t uuid[3] = { 0x12341234, 0x12341234, 0x12341234 };
  return (uint8_t*)uuid;
}

void bus_setup(){
  debug << "bus_setup\r\n";
  serial_setup(115200);
}

int bus_status(){
  static uint32_t lastpolled = 0;
  if(lastpolled++ > 100){
    bushandler.connected();
    lastpolled = 0;
  }
  return bushandler.getStatus();
}

void serial_read(uint8_t* data, uint16_t size){}
void serial_write(uint8_t* data, uint16_t size){}
void serial_setup(uint32_t baudRate){}

void bus_tx_parameter(uint8_t pid, int16_t value){}
void bus_tx_button(uint8_t bid, int16_t value){}
void bus_tx_command(uint8_t cmd, int16_t data){}
void bus_tx_message(const char* msg){}
void bus_tx_data(uint8_t* data, uint16_t size){}
void bus_tx_error(const char* reason){
  debug << "Digital bus send error: " << reason << ".";
}

void bus_rx_parameter(uint8_t pid, int16_t value){}
void bus_rx_button(uint8_t bid, int16_t value){}
void bus_rx_command(uint8_t cmd, int16_t data){}
void bus_rx_message(const char* msg){}
void bus_rx_data(uint8_t* data, uint16_t size){}
void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".";
}

#define FLOAT_TEST_TOLERANCE 0.00001 // percent tolerance when comparing floats

BOOST_AUTO_TEST_CASE(universeInOrder){
  BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(testSetup){
  bus_setup();
}
