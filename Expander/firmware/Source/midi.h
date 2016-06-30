#ifndef __MIDI_H
#define __MIDI_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

   void midi_setup();
   void midi_send_cc(uint8_t ch, uint8_t cc, uint8_t value);
   void midi_receive_cc(uint8_t ch, uint8_t cc, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __MIDI_H */
