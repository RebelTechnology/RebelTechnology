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
  static uint32_t id = 0;
  static uint32_t uuid[2][3] = {
    { 0x12341234, 0x23412341, 0x13412324 },
    { 0x13214327, 0x21432183, 0x21312493 }
  };
  // give out two different uuids
  return (uint8_t*)uuid[(id++)&0x1];
}

void bus_setup(){
  debug << "bus_setup\r\n";
  Bus1::bus.reset();
  Bus2::bus.reset();
}

// void Bus1::serial_read(uint8_t* data, uint16_t size){
//   debug << "Bus1 read [" << size << "]\r\n" ;
// }

void Bus1::serial_write(uint8_t* data, uint16_t size){
  BOOST_CHECK_EQUAL(size, 4);
  debug << "bus1 [" << (int)data[0] << "][" << (int)data[1] << "][" << (int)data[2] << "]["  << (int)data[3] << "]\r\n" ;
  Bus2::bus.readBusFrame(data);
}

void Bus2::serial_write(uint8_t* data, uint16_t size){
  debug << "bus2 [" << (int)data[0] << "][" << (int)data[1] << "][" << (int)data[2] << "]["  << (int)data[3] << "]\r\n" ;
  BOOST_CHECK_EQUAL(size, 4);
  Bus1::bus.readBusFrame(data);
}

int16_t parameters[256] = { 0 };
uint16_t buttons[256] = { 0 };
uint16_t commands[256] = { 0 };
char* message = NULL;
void bus_rx_parameter(uint8_t pid, int16_t value){
  debug << "rx parameter [" << pid << "][" << value << "]\r\n";
  parameters[pid] = value;
}
void bus_rx_button(uint8_t bid, int16_t value){
  debug << "rx button [" << bid << "][" << value << "]\r\n" ;
  buttons[bid] = value;
}
void bus_rx_command(uint8_t cmd, int16_t data){
  debug << "rx command [" << cmd << "][" << data << "]\r\n" ;
  commands[cmd] = data;
}
void bus_rx_message(const char* msg){
  debug << "rx msg [" << msg << "]\r\n" ;
  message = msg;
}
void bus_rx_data(uint8_t* data, uint16_t size){
  debug << "rx data [" << size << "]\r\n" ;
}
void bus_rx_error(const char* reason){
  debug << "Digital bus receive error: " << reason << ".\r\n";
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
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 0);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 0);
  BOOST_CHECK_EQUAL(Bus1::bus.getUid(), 255);
  BOOST_CHECK_EQUAL(Bus2::bus.getUid(), 255);
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 1);
  Bus2::bus_status();
  Bus1::bus_status();
  Bus2::bus_status();
  Bus1::bus_status();
  Bus2::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus1::bus.getUid(), 0);
  BOOST_CHECK_EQUAL(Bus2::bus.getUid(), 1);
  BOOST_CHECK_EQUAL(Bus1::bus.getNuid(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getNuid(), 0);
}

BOOST_AUTO_TEST_CASE(testOneSidedStatus){
  bus_setup();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 0);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 0);
  BOOST_CHECK_EQUAL(Bus1::bus.getUid(), 255);
  BOOST_CHECK_EQUAL(Bus2::bus.getUid(), 255);
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 1);
  for(int i=0; i<20; ++i)
    Bus1::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus1::bus.getUid(), 0);
  BOOST_CHECK_EQUAL(Bus2::bus.getUid(), 1);
  BOOST_CHECK_EQUAL(Bus1::bus.getNuid(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getNuid(), 0);
  // reset and test other side
  bus_setup();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 0);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 0);
  for(int i=0; i<20; ++i)
    Bus2::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getPeers(), 1);
  BOOST_CHECK_EQUAL(Bus1::bus.getUid(), 0);
  // Bus2 is waiting for uid 0 to start enum
  // by design, uid 0 must initiate enumeration
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(Bus1::bus.getNuid(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getUid(), 1);
  BOOST_CHECK_EQUAL(Bus2::bus.getNuid(), 0);
}

BOOST_AUTO_TEST_CASE(testParameters){
  bus_setup();
  Bus2::bus_status();
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(parameters[0x10], 0);
  BOOST_CHECK_EQUAL(parameters[0x20], 0);
  Bus1::bus.sendParameterChange(0x10, 0x1234);
  BOOST_CHECK_EQUAL(parameters[0x10], 0x1234);
  Bus2::bus.sendParameterChange(0x20, 0x1324);
  BOOST_CHECK_EQUAL(parameters[0x20], 0x1324);
}

BOOST_AUTO_TEST_CASE(testButtons){
  bus_setup();
  Bus1::bus_status();
  Bus2::bus_status();
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(buttons[0x12], 0);
  BOOST_CHECK_EQUAL(buttons[0x34], 0);
  Bus1::bus.sendButtonChange(0x12, 0x12);
  BOOST_CHECK_EQUAL(buttons[0x12], 0x12);
  Bus2::bus.sendButtonChange(0x34, 0x3124);
  BOOST_CHECK_EQUAL(buttons[0x34], 0x3124);
}

BOOST_AUTO_TEST_CASE(testCommands){
  bus_setup();
  Bus2::bus_status();
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(commands[0x1], 0);
  BOOST_CHECK_EQUAL(commands[0x2], 0);
  Bus1::bus.sendCommand(0x1, 0x1212);
  BOOST_CHECK_EQUAL(commands[0x1], 0x1212);
  Bus2::bus.sendCommand(0x2, 0x3232);
  BOOST_CHECK_EQUAL(commands[0x2], 0x3232);
}

BOOST_AUTO_TEST_CASE(testMessage){
  bus_setup();
  Bus2::bus_status();
  Bus1::bus_status();
  BOOST_CHECK_EQUAL(message, NULL);
  BOOST_CHECK_EQUAL(message, NULL);
  const char msg[] = "Here's a message";
  Bus1::bus.sendMessage(msg);
  BOOST_CHECK(strcmp(message, msg) == 0);
}
