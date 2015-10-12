#ifndef OPENSOUND_H
#define OPENSOUND_H

#include <stdint.h>
#include <stddef.h>

#define SERIAL_DEBUG

#define OSC_MESSAGE_MAX_PREFIX_SIZE 16
#define OSC_MESSAGE_MAX_DATA_SIZE 38

#define MAX_URL_LENGTH 128
// #define USE_HEADERS
#ifdef USE_HEADERS
#define MAX_HEADER_FIELD_LENGTH 128
#define MAX_HEADER_VALUE_LENGTH 128
#endif

#define ASSERT(cond, msg) if(!(cond)){assert_failed(msg, __PRETTY_FUNCTION__, __LINE__);}

#define NETWORK_LOCAL_WIFI   0
#define NETWORK_ACCESS_POINT 1

#ifdef  __cplusplus

#include "application.h"
class Debug : public Print {
  size_t write(uint8_t data){
    return Serial.write(data);
  }
  size_t write(const uint8_t* data, size_t size){
    return Serial.write(data, size);
  }
};
extern Debug debug;
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

enum LedPin {
  LED_NONE,
  LED_GREEN,
  LED_YELLOW
};

void setLed(LedPin led);
void toggleLed();

#endif

#ifdef  __cplusplus
extern "C" {
#endif
  void startServers();
  void stopServers();
  void reload();
  void setRemoteIpAddress(const char* ip);

  uint16_t getCVA();
  uint16_t getCVB();
  void setCVA(uint16_t cv);
  void setCVB(uint16_t cv);
  void setTriggerA(int value);
  void setTriggerB(int value);
  void toggleTriggerA();
  void toggleTriggerB();
  void factoryReset();

  void debugMessage(const char* msg);
  void assert_failed(const char* msg, const char* location, int line);

#ifdef  __cplusplus
}
#endif

#endif  /* OPENSOUND_H */
