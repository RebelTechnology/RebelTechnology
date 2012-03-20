#ifndef _MIDIINTERFACE_H_
#define _MIDIINTERFACE_H_

#include <inttypes.h>

#define BANK_SELECT_CC 0
#define MOD_WHEEL_CC   1
#define BREATH_CC      2
#define FOOT_PEDAL_CC  4
#define PORTAMENTO_CC  5
#define VOLUME_CC      7
#define BALANCE_CC     8
#define PAN_CC        10
#define EXPRESSION_CC 11
#define EFFECT1_CC    12
#define EFFECT2_CC    13

class MidiInterface {
 public:
  virtual void channelPressure(uint8_t value){}
  virtual void startSong(){}
  virtual void stopSong(){}
  virtual void continueSong(){}
  virtual void midiClock(){}
  virtual void midiTick(){}
  virtual void pitchBend(uint16_t value){}
  virtual void controlChange(uint8_t cc, uint8_t value){}
  virtual void programChange(uint8_t pg){}
  virtual void noteOff(uint8_t note, uint8_t velocity){}
  virtual void noteOn(uint8_t note, uint8_t velocity){}
  virtual void allNotesOff(){}
};


#endif /* _MIDIINTERFACE_H_ */
