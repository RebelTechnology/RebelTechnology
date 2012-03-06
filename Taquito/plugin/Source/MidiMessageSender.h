#ifndef __MIDIMESSAGESENDER_H__
#define __MIDIMESSAGESENDER_H__

#include "../JuceLibraryCode/JuceHeader.h"

class MidiMessageSender {
 public:
 MidiMessageSender() : midiout(NULL) {
  };

  ~MidiMessageSender(){
    delete midiout;
  }

  void setMidiOutput(juce::MidiOutput* output){
    if(midiout != NULL)
      delete midiout;
    midiout = output;
  }

  void handleByte(uint8_t bt){
    buf[topos++] = bt;
    len = topos-frompos;
    if(len > 0)
      process();
  }

  void process(){
    uint8_t msglen = 0;
    switch(buf[frompos] & 0xf0){
    case MIDI_NOTE_OFF:
    case MIDI_NOTE_ON:
    case MIDI_CONTROL_CHANGE:
    case MIDI_AFTERTOUCH:
    case MIDI_PITCH_BEND:
      msglen = 3;
      break;
    case MIDI_PROGRAM_CHANGE:
    case MIDI_CHANNEL_PRESSURE:
      msglen = 2;
      break;
    case MIDI_SYSTEM_MESSAGE:
      if(buf[frompos] != 0xf0 && buf[frompos] != 0xff){
	msglen = 1;
	break;
      }
      // conditional fall-through
    default:
      std::cerr << "invalid midi message: 0x" << std::hex << (int)buf[frompos] << std::endl;
      len = topos - ++frompos;
      if(len <= 0)
	topos = frompos = len = 0;
      return;
    }
/*     std::cout << "midi message: " << (int)msglen << " / " << (int)len << std::endl; */
    if(msglen > 0 && msglen <= len){
      int used;
      msg = juce::MidiMessage(&buf[frompos], msglen, used, msg.getRawData()[0]);
      if(midiout != NULL)
	midiout->sendMessageNow(msg);
/*       if(m_verbose) */
/* 	std::cout << "rx" << print(msg) << std::endl; */
      // 	std::cout << "rx:" << frompos << "-" << topos << " " << used << "/" << len << std::endl;
      if(used == len)
	frompos = topos = 0;
      else
	frompos += used;
      len = topos-frompos;
      if(topos >= MIDI_MESSAGE_SENDER_BUFFER_LENGTH){
	std::cerr << "buffer overflow!" << std::endl;
	frompos = topos = len = 0;
      }else if(len > 0){
	process();
      }
    }
  }
 private:
  juce::MidiMessage msg;
  juce::MidiOutput* midiout;
  size_t len;
  unsigned char buf[MIDI_MESSAGE_SENDER_BUFFER_LENGTH];
  int frompos;
  int topos;
};

#endif  // __MIDIMESSAGESENDER_H__
