/*
  g++ -ISource -I/opt/local/include -L/opt/local/lib -std=c++11 Source/DigitalBusTest.cpp -lboost_unit_test_framework -o DigitalBusTest && ./DigitalBusTest
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <inttypes.h>

#include "message.h"
#include "bus.h"
#include "MidiStatus.h"

namespace Bus1 {
#include "DigitalBusTestInstance.cpp"
};

namespace Bus2 {
#include "DigitalBusTestInstance.cpp"
};

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

uint8_t* bus_deviceid(){
  static uint32_t uuid[3] = { 0x12341234, 0x12341234, 0x12341234 };
  return (uint8_t*)uuid;
}

void bus_setup(){
  debug << "bus_setup\r\n";
  // Bus1::serial_setup(115200);
  // Bus2::serial_setup(115200);
}

// void Bus1::serial_read(uint8_t* data, uint16_t size){
//   debug << "Bus1 read [" << size << "]\r\n" ;
// }

void Bus1::serial_write(uint8_t* data, uint16_t size){
  debug << "bus1 [" << size << "]\r\n" ;
  BOOST_CHECK_EQUAL(size, 4);
  Bus2::bus.readBusFrame(data);
}

void Bus2::serial_write(uint8_t* data, uint16_t size){
  debug << "bus2 [" << size << "]\r\n" ;
  BOOST_CHECK_EQUAL(size, 4);
  Bus1::bus.readBusFrame(data);
}

// void Bus1::serial_setup(uint32_t baudRate){
// }

void bus_rx_parameter(uint8_t pid, int16_t value){
  debug << "rx parameter [" << pid << "][" << value << "]\r\n" ;
}
void bus_rx_button(uint8_t bid, int16_t value){
  debug << "rx button [" << bid << "][" << value << "]\r\n" ;
}
void bus_rx_command(uint8_t cmd, int16_t data){
  debug << "rx command [" << cmd << "][" << data << "]\r\n" ;
}
void bus_rx_message(const char* msg){
  debug << "rx msg [" << msg << "]\r\n" ;
}
void bus_rx_data(uint8_t* data, uint16_t size){
  debug << "rx data [" << size << "]\r\n" ;
}
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

BOOST_AUTO_TEST_CASE(testStatus){
  bus_setup();
  Bus1::bus_status();
  Bus2::bus_status();
}
