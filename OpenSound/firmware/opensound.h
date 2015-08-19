#ifndef OPENSOUND_H
#define OPENSOUND_H

#include <stdint.h>
#include <stddef.h>

#define SERIAL_DEBUG

#define WEBSOCKET_BUFFER_SIZE 64
#define UDP_TX_BUFFER_SIZE    32
#define UDP_RX_BUFFER_SIZE    32
#define SERIAL_RX_BUFFER_SIZE 32
#define OSC_MESSAGE_MAX_PREFIX_SIZE 16
#define OSC_MESSAGE_MAX_DATA_SIZE 38

#define MAX_URL_LENGTH 128
// #define USE_HEADERS
#ifdef USE_HEADERS
#define MAX_HEADER_FIELD_LENGTH 128
#define MAX_HEADER_VALUE_LENGTH 128
#endif

#define assert(cond, msg) if(!(cond)){assert_failed(msg, __PRETTY_FUNCTION__, __LINE__);}

#ifdef  __cplusplus
extern "C" {
#endif
  void debugMessage(const char* msg);
  void process_opensound(uint8_t* data, size_t dataSize);    
  void assert_failed(const char* msg, const char* location, int line);
  void udp_recv_packet(uint8_t* buffer, int size);
#ifdef  __cplusplus
}
#endif

#endif  /* OPENSOUND_H */
