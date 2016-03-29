#ifndef __MIDI_H
#define __MIDI_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

   void midiSetup();
   void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value);

   void midiReceiveCC(uint8_t ch, uint8_t cc, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __MIDI_H */
