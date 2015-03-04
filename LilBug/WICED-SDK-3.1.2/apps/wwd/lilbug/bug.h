#ifndef INCLUDED_BUG_H
#define INCLUDED_BUG_H

#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

  void setupMidi();
  void pollMidiTask(void*);
  int process_midi_note(void* socket, char* params, int params_len);
  int process_midi_cc(void* socket, char* params, int params_len);
  int process_websocket(void* socket);

  void udp_server_task(void*); // defined in udp_server?

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_BUG_H */
