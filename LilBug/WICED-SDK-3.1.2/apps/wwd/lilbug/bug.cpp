// #include "wiced.h"

#define DEBUG_USART

#ifdef DEBUG_USART
#define Serial_printf(fmt, ...) printf(fmt, __VA_ARGS__)
#define Serial_print(x) puts(x)
#define Serial_println(x) puts(x "\n")
#else // DEBUG_USART
#define Serial_printf(...) 
#define Serial_print(x) 
#define Serial_println(x) 
#endif // DEBUG_USART

#include "bug.h"
#include "uart.h"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#include <string.h>

MidiWriter writer;  

#define SYSEX_MANUFACTURER_ID 0x7d /* educational use */

void debug_message(const char* string){
  uint16_t len = strlen(string);
  writer.sysex(SYSEX_MANUFACTURER_ID, (uint8_t*)string, len);
}

class LilBug : public MidiReader {
public:

  void setup(){
    Serial_println("Setup MidiReader");
  }
  /*
  void setTrigger(int pin, OSCMessage &message){
    if(message.size() > 0){
      bool value;
      switch(message.getType(0)){
      case 'i':
      case 'h':
	value = message.getInt(0) != 0;
	break;
      case 'f':
	value = message.getFloat(0) != 0.0;
	break;
      case 'd':
	value = message.getDouble(0) != 0.0;
	break;
      case 'T':
      case 'I':
	value = true;
	break;
      case 'F':
      case 'N':
      default:
	value = false;
	break;
      }
      digitalWrite(pin, value ? LOW : HIGH);    
      Serial_println("Set trigger " + String(pin) + " " + String(value));
    }
  }
  */
  /*
  float getFloatValue(OSCMessage &message, int index){
    float value = 0.0f;
    if(message.size() > index){
      switch(message.getType(index)){
      case 'i':
      case 'h':
	value = message.getInt(index)/4095.0f;
	break;
      case 'f':
	value = message.getFloat(index);
	break;
      case 'd':
	value = message.getDouble(index);
	break;
      case 'T':
      case 'I':
	value = 1.0f;
	break;
      case 'F':
      case 'N':
      default:
	value = 0.0f;
	break;
      }
    }
    return min(max(value, 0.0f), 1.0f);
  }
  */

#define MIDI_BUFFER_LENGTH 128
  uint8_t buffer[MIDI_BUFFER_LENGTH];
  // MidiReader reader(buffer, MIDI_BUFFER_LENGTH);
  LilBug() : MidiReader(buffer, MIDI_BUFFER_LENGTH) {}

  void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity){
    if(velocity == 0)
      return handleNoteOff(channel, note, velocity);
    MidiReader::handleNoteOn(channel, note, velocity);

    writer.noteOn(channel, note, velocity);
    // note_on_msg.set(0, (int32_t)channel);
    // note_on_msg.set(4, (int32_t)note);
    // note_on_msg.set(8, (int32_t)velocity);
    // sendMessage(note_on_msg);
  }

  /*
  void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity){
    MidiReader::handleNoteOff(channel, note, velocity);
    note_off_msg.set(0, (int32_t)channel);
    note_off_msg.set(4, (int32_t)note);
    sendMessage(note_off_msg);
  }

  void handleControlChange(uint8_t channel, uint8_t cc, uint8_t value){
    MidiReader::handleControlChange(channel, cc, value);
    control_change_msg.set(0, (int32_t)channel);
    control_change_msg.set(4, (int32_t)cc);
    control_change_msg.set(8, (int32_t)value);
    sendMessage(control_change_msg);
  }

  void handlePitchBend(uint8_t channel, int16_t value){
    MidiReader::handlePitchBend(channel, value);
    pitch_bend_msg.set(0, (int32_t)channel);
    pitch_bend_msg.set(4, (int32_t)value);
    sendMessage(pitch_bend_msg);
  }
  */
  void pollMidi(){
    // char c = getchar(); // blocking?
    char c;
    for(;;){
      if(uart_receive_bytes(&c, 1) == 0){
	// uart_receive_bytes(&c, 1);
	MidiReaderStatus status = read(c);
	if(status == ERROR_STATUS){
	  MidiReader::clear();
	  Serial_println("MIDI read error");
	  // }else{
	  // 	Serial_print(".");
	}
      }
    }
  }
};

LilBug bug;

void setupMidi(void){
  bug.setup();

  debug_message("showtime");
}

void pollMidiTask(void*){
  for(;;)
    bug.pollMidi();
}
