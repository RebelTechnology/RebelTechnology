#ifndef INCLUDED_BUG_H
#define INCLUDED_BUG_H

#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

  void setupMidi();
  void pollMidiTask(void*);

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_BUG_H */
