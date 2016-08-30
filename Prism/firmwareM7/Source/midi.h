#ifndef __MIDI_H
#define __MIDI_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

   void midiSendPC(uint8_t ch, uint8_t pc);
   void midiSendCC(uint8_t ch, uint8_t cc, uint8_t value);
   /* void midiReceivePC(uint8_t ch, uint8_t pc); */
   /* void midiReceiveCC(uint8_t ch, uint8_t cc, uint8_t value); */

   void midi_rx_usb_buffer(uint8_t *buffer, uint32_t length);
   void midi_tx_usb_buffer(uint8_t* buffer, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* __MIDI_H */
