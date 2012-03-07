#include "TaquitoClient.h"
#include "hidapi.h"
#include <string.h>
#include <iostream>
#include <exception>

#define VENDOR_ID   0x1fc9
#define DEVICE_ID   0x0003

class TaquitoException : public std::exception {};

static hid_device *USBHandle = NULL;

// TaquitoClient::TaquitoClient() : 
//   USBHandle(NULL) {

TaquitoClient::TaquitoClient() {
//   USBHandle = NULL;
  memset(data, 0, sizeof(data));
//   if(!hid_init()){
//     std::cerr << "hid initialisation error" << std::endl;
//     throw TaquitoException();
//   }
}

#define MAX_SENSOR_VALUE_FLOAT 1023.0
#define MAX_BREATH_VALUE_FLOAT 700.0
#define BREATH_THRESHOLD 60

float TaquitoClient::getBreath(){
  return data[1] > BREATH_THRESHOLD ? data[1]/MAX_BREATH_VALUE_FLOAT : 0;
}

float TaquitoClient::getPosition(){
  return getPressure() > getPressureThreshold() ? data[2]/MAX_SENSOR_VALUE_FLOAT : 0;
}

float TaquitoClient::getPressure(){
  return data[0]/MAX_SENSOR_VALUE_FLOAT;
}

float TaquitoClient::getPressureThreshold(){
  return 0.1;
}

void TaquitoClient::connect(){
  std::cerr << "connecting" << std::endl;
  if(USBHandle)
    return;
//     disconnect();
  USBHandle = hid_open(VENDOR_ID, DEVICE_ID, NULL);    // attempt to open device
  if(USBHandle) {
    // if handle is set, then connection has been made
    hid_set_nonblocking(USBHandle, 1);                // set hid_read() in non-blocking mode
  }else{
    std::cerr << "connection failure" << std::endl;
    throw TaquitoException();
  }
}

void TaquitoClient::disconnect(){
  std::cerr << "disconnecting" << std::endl;
  if(USBHandle) 
    hid_close(USBHandle);
  USBHandle = NULL;
}

void TaquitoClient::read(){
//   std::cout << "reading" << std::endl;
  if(USBHandle == NULL)
    return;
  unsigned char buf[sizeof(data)*2];
  memset(buf, 0, sizeof(buf));
  int res = hid_read(USBHandle, buf, sizeof(buf));
  if(res > 0){
    // if result is bigger than zero, then it's data
    // print data on std out
    for(int i=0; i<sizeof(data); ++i)
      data[i] = (buf[i*2] << 8) | buf[i*2+1];
  }else if(res < 0){
    // if result is smaller than zero, then it's an error, so disconnect
    disconnect();
//     USBHandle = NULL;
    std::cerr << "read error" << std::endl;
    throw TaquitoException();
  }
}
