#ifndef _MIDIREADER_H_
#define _MIDIREADER_H_

#include <inttypes.h>
#include "MidiStatus.h"
#include <stdio.h>

class MidiReader;
typedef MidiReader MidiMessage;

enum MidiReaderStatus {
  READY_STATUS, INCOMPLETE_STATUS, ERROR_STATUS
};

class MidiReader {
private:
  uint8_t* message;
  MidiReaderStatus status; // state, should be status: READY / INCOMPLETE / ERROR
  unsigned char runningStatus;
  uint16_t size;
  uint16_t pos;
public:
  MidiReader(uint8_t* buffer, uint16_t sz) : 
  message(buffer), 
    status(READY_STATUS), 
    runningStatus(0), 
    size(sz), 
    pos(0) {
  }

  ~MidiReader(){
  }

  uint8_t getStatus(){
    return message[0] & MIDI_STATUS_MASK;;
  }

  uint8_t getChannel(){
    return message[0] & MIDI_CHANNEL_MASK;
  }

  void handleSystemCommon(uint8_t){}
  void handleProgramChange(uint8_t channel, uint8_t value){
#ifdef DEBUG_USART
    Serial_printf("program change: %d %d\n", channel, value);
#endif /* DEBUG_USART */
  }
  void handleChannelPressure(uint8_t channel, uint8_t value){
#ifdef DEBUG_USART
    Serial_printf("channel pressure: %d %d\n", channel, value);
#endif /* DEBUG_USART */
  }
  void handleControlChange(uint8_t channel, uint8_t cc, uint8_t value){
#ifdef DEBUG_USART
    Serial_printf("cc: %d %d %d\n", channel, cc, value);
#endif /* DEBUG_USART */
  }
  void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity){
#ifdef DEBUG_USART
    Serial_printf("Note off: %d %d %d\n", channel, note, velocity);
#endif /* DEBUG_USART */
  }
  void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity){
#ifdef DEBUG_USART
    Serial_printf("Note on: %d %d %d\n", channel, note, velocity);
#endif /* DEBUG_USART */
  }
  void handlePitchBend(uint8_t channel, uint8_t high, uint8_t low){
#ifdef DEBUG_USART
    Serial_printf("pb: %d %d %d\n", channel, high, low);
#endif /* DEBUG_USART */
  }
  void handleSysEx(uint8_t* data, uint8_t size){
#ifdef DEBUG_USART
    Serial_printf("sysex: %d\n", size);
#endif /* DEBUG_USART */
  }

  void clear(){
    runningStatus = message[0];
    pos = 0;
    status = READY_STATUS;
  }

  unsigned char* getMessage(int& length){
    length = pos;
    return message;
  }

  MidiReaderStatus read(unsigned char data){
    if(status == READY_STATUS){
      clear(); // discard previous message
    }else if(pos > size){
      status = ERROR_STATUS;
      return status;
    }
    message[pos++] = data;
    switch(message[0] & MIDI_STATUS_MASK){
      // two byte messages
    case PROGRAM_CHANGE:
      if(pos == 2){
	status = READY_STATUS;
	handleProgramChange(message[0] & MIDI_CHANNEL_MASK, message[1]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case CHANNEL_PRESSURE:
      if(pos == 2){
	status = READY_STATUS;
	handleChannelPressure(message[0] & MIDI_CHANNEL_MASK, message[1]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
      // three byte messages
    case NOTE_OFF:
      if(pos == 3){
	status = READY_STATUS;
	handleNoteOff(message[0] & MIDI_CHANNEL_MASK, message[1], message[2]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case NOTE_ON:
      if(pos == 3){
	status = READY_STATUS;
	handleNoteOn(message[0] & MIDI_CHANNEL_MASK, message[1], message[2]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case POLY_KEY_PRESSURE:
      if(pos == 3){
	status = READY_STATUS;
	handlePitchBend(message[0] & MIDI_CHANNEL_MASK, message[1], message[2]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case CONTROL_CHANGE:
      if(pos == 3){
	status = READY_STATUS;
	handleControlChange(message[0] & MIDI_CHANNEL_MASK, message[1], message[2]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case PITCH_BEND_CHANGE:
      if(pos == 3){
	status = READY_STATUS;
	handlePitchBend(message[0] & MIDI_CHANNEL_MASK, message[1], message[2]);
      }else{
	status = INCOMPLETE_STATUS;
      }
      break;
    case SYSTEM_COMMON:
      switch(message[0]){
      case TIME_CODE_QUARTER_FRAME:
      case RESERVED_F4:
      case RESERVED_F9:
      case TUNE_REQUEST:
      case TIMING_CLOCK:
      case START:
      case CONTINUE:
      case STOP:
      case RESERVED_FD:
      case ACTIVE_SENSING:
      case SYSTEM_RESET:
	// one byte messages
	status = READY_STATUS;
	handleSystemCommon(message[0]);
	break;
      case SYSEX:
	if(data == SYSEX_EOX && pos > 1){
	  status = READY_STATUS;
	  handleSysEx(message+1, pos-2);
	}else if(data >= STATUS_BYTE && pos > 1){
	  // SysEx message terminated by a status byte different from 0xf7
	  message[pos-1] = SYSEX_EOX;
	  status = READY_STATUS;
	  handleSysEx(message+1, pos-2);
	  message[0] = data; // save status byte for next message - will be saved as running status
	}else{
	  status = INCOMPLETE_STATUS;
	}
	break;
      case SYSEX_EOX: // receiving SYSEX_EOX on its own is really an error
      default:
	status = ERROR_STATUS;
	break;
      }
      break;
    default:
      if(pos == 1 && data < STATUS_BYTE && runningStatus >= STATUS_BYTE){
	// MIDI running status: this message is missing the status byte, re-use previous status
	message[pos++] = data;
	message[0] = runningStatus;
      }else{
	status = ERROR_STATUS;
      }
    }
    return status;
  }

  /* MidiMessage methods below */
  bool isNoteOn(){
    return getStatus() == NOTE_ON;
  }

  bool isNoteOff(){
    return getStatus() == NOTE_OFF || (isNoteOn() && getVelocity() == 0);
  }

  bool isChannelPressure(){
    return getStatus() == CHANNEL_PRESSURE;
  }

  bool isAftertouch(){
    return getStatus() == POLY_KEY_PRESSURE;
  }

  bool isController(){
    return getStatus() == CONTROL_CHANGE;
  }

  bool isPitchWheel(){
    return getStatus() == PITCH_BEND_CHANGE;
  }

  bool isAllNotesOff(){
    return isController() && message[1] == 123;
  }

  bool isAllSoundOff(){
    return isController() && message[1] == 120;
  }

  uint8_t getNoteNumber(){
    return message[1];
  }

  uint8_t getVelocity(){
    return message[2];
  }

  uint8_t getControllerNumber(){
    return message[1];
  }

  uint8_t getControllerValue(){
    return message[2];
  }

  uint8_t getChannelPressureValue(){
    return message[1];
  }

  uint8_t getAfterTouchValue(){
    return message[1];
  }

  uint16_t getPitchWheelValue(){
    return (message[1]<<7) | message[2];
  }

  uint16_t getRawDataSize(){
    return pos;
  }

  uint8_t* getRawData(){
    return message;
  }
};


#endif /* _MIDIREADER_H_ */
