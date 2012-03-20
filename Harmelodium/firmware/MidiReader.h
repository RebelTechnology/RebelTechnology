#ifndef _MIDIREADER_H_
#define _MIDIREADER_H_

#include <inttypes.h>
#include "MidiInterface.h"

#define STANDBY  0
#define NOTE_ON  1
#define NOTE_OFF 2
#define CONTROL_CHANGE 3
#define PITCH_BEND 4
#define CHANNEL_PRESSURE 5

class MidiReader {
public:

  void init(MidiInterface* _midi){
    midi = _midi;
    reset();
  }

  void read(char incomingByte){
    switch(state){
    case NOTE_ON:
      if(data1 == -1){
        data1 = incomingByte;
      }else if(data2 == -1){
        data2 = incomingByte;
        midi->noteOn(data1, data2);
        reset();
      }else{
        reset();
      }
      break;
    case NOTE_OFF:
      if(data1 == -1){
        data1 = incomingByte;
      }else if(data2 == -1){
        data2 = incomingByte;
        midi->noteOff(data1, data2);
        reset();
      }else{
        reset();
      }
      break;
    case CONTROL_CHANGE:
      if(data1 == -1){
        data1 = incomingByte;
      }else if(data2 == -1){
        data2 = incomingByte;
        midi->controlChange(data1, data2);
        if(data1 == 0x7b)
          midi->allNotesOff();
        reset();
      }else{
        reset();
      }
      break;
    case PITCH_BEND:
      if(data1 == -1){
        data1 = incomingByte;
      }else if(data2 == -1){
        data2 = incomingByte;
        midi->pitchBend((data2 << 7) | data1);
        reset();
      }else{
        reset();
      }
      break;
    case CHANNEL_PRESSURE:
      if(data1 == -1){
        data1 = incomingByte;
        midi->channelPressure(data1);
        reset();
      }else{
        reset();
      }
      break;
    case STANDBY:
    default:
      switch(incomingByte){
      case 0xf8:
        midi->midiClock();
        break;
      case 0xf9:
        // A MIDI Tick message is sent at regular intervals of one message every 10 milliseconds. 
        midi->midiTick();
        break;
      case 0xfa:
        midi->startSong();
        break;
      case 0xfb:
        midi->continueSong();
        break;
      case 0xfc:
        midi->stopSong();
        break;
      default:
        switch(incomingByte & 0xf0){
        case 0x80:
          state = NOTE_OFF;
          break;
        case 0x90:
          state = NOTE_ON;
          break;
        case 0xb0:
          state = CONTROL_CHANGE;
          break;
        case 0xd0:
          state = CHANNEL_PRESSURE;
          break;
        case 0xe0:
          state = PITCH_BEND;
          break;
        }
      }
    }
  }

private:
  int8_t state, data1, data2;
  MidiInterface* midi;

  void reset(){
    data1 = -1;
    data2 = -1;
    state = STANDBY;
  }
};

#endif /* _MIDIREADER_H_ */
