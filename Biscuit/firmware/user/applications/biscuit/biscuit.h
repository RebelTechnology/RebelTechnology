#ifndef BISCUIT_H
#define BISCUIT_H

#include <stdint.h>
#include <stddef.h>

#define SPARK_NO_CLOUD

#define SERIAL_DEBUG
#define SERIAL_CONSOLE

#define ANALOG_THRESHOLD            31

#define ASSERT(cond, msg) if(!(cond)){assert_failed(msg, __PRETTY_FUNCTION__, __LINE__);}

#define NETWORK_LOCAL_WIFI   0
#define NETWORK_ACCESS_POINT 1

// pin mappings
#define CS_RX                TX
#define CS_TX                RX
#define CS_RST               D6
#define CS_D3                D7
#define RELAY1               D4
#define RELAY2               D5
#define PIR_SIG              A4

#ifdef  __cplusplus

#include "application.h"

template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

// print floats to 8 decimal places
inline Print &operator <<(Print &obj, float arg)
{ obj.print(arg, 8); return obj; }

class Debug : public Print {
  size_t write(uint8_t data){
#ifdef SERIAL_DEBUG
    return Serial.write(data);
#else
    return 1;
#endif
  }
  size_t write(const uint8_t* data, size_t size){
#ifdef SERIAL_DEBUG
    return Serial.write(data, size);
#else
    return size;
#endif
  }
};
extern Debug debug;

void printSensors(Print& out);
#endif

#ifdef  __cplusplus
extern "C" {
#endif
  void startServers();
  void stopServers();
  void reload();
  void setRemoteIpAddress(const char* ip);
  void factoryReset();
  const char* getDeviceName();
  void setDeviceName(const char* name);
  void debugMessage(const char* msg);
  void assert_failed(const char* msg, const char* location, int line);
#ifdef  __cplusplus
}
#endif

#endif  /* BISCUIT_H */
