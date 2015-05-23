#ifndef INCLUDED_BUG_H
#define INCLUDED_BUG_H

#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

  void setup();
  void pollOpenSoundTask(void*);
  int process_websocket(void* socket);
  void process_opensound(uint8_t* data, size_t dataSize);

  void udp_server_task(void*); // defined in udp_server?

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_BUG_H */
