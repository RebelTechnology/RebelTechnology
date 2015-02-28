#ifndef _MIDIINTERFACE_H_
#define _MIDIINTERFACE_H_

#include <inttypes.h>

class MidiInterface {
 public:
  virtual void startSong(){}
  virtual void stopSong(){}
  virtual void continueSong(){}
  virtual void midiClock(){}
  virtual void midiTick(){}
  virtual void pitchBend(uint16_t value){}
  virtual void controlChange(uint8_t cc, uint8_t value){}
  virtual void channelPressure(uint8_t value){}
  virtual void programChange(uint8_t pg){}
  virtual void noteOff(uint8_t note, uint8_t velocity){}
  virtual void noteOn(uint8_t note, uint8_t velocity){}
  virtual void allNotesOff(){}
};


#endif /* _MIDIINTERFACE_H_ */
