#include "web_server.h"

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
#include "udp_server.h"
#include "OscMessage.hpp"

char* OscCmd_status              = (char*)"/status";
char* OscCmd_led                 = (char*)"/led";
char* OscCmd_ip                  = (char*)"/localip";
char* OscCmd_port                = (char*)"/localport";
char* OscCmd_ping                = (char*)"/ping";
char* OscCmd_note_on             = (char*)"/note_on";
char* OscCmd_note_off            = (char*)"/note_off";
char* OscCmd_control_change      = (char*)"/cc";
char* OscCmd_pitch_bend          = (char*)"/pb";

OscMessage note_on_msg(OscCmd_note_on);
OscMessage note_off_msg(OscCmd_note_off);
OscMessage control_change_msg(OscCmd_control_change);
OscMessage pitch_bend_msg(OscCmd_pitch_bend);

MidiWriter writer(0);

#define SYSEX_MANUFACTURER_ID 0x7d /* educational use */

void debug_message(const char* string){
  uint16_t len = strlen(string);
  writer.sysex(SYSEX_MANUFACTURER_ID, (uint8_t*)string, len);
}

void sendMessage(OscMessage& msg){
  uint8_t buf[64];
  int len = msg.copy(buf, sizeof(buf));
  if(len > 0)
    udp_send_packet(buf, len);
  else
    WPRINT_APP_INFO(("Failed to send osc message: %d", len));
}

class LilBug : public MidiReader {
public:

  void setup(){
    Serial_println("Setup MidiReader");

  note_on_msg.add((int32_t)0);
  note_on_msg.add((int32_t)0);
  note_on_msg.add((int32_t)0);
  note_off_msg.add((int32_t)0);
  note_off_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  pitch_bend_msg.add((int32_t)0);
  pitch_bend_msg.add((int32_t)0);

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
    note_on_msg.set(0, (int32_t)channel);
    note_on_msg.set(4, (int32_t)note);
    note_on_msg.set(8, (int32_t)velocity);
    sendMessage(note_on_msg);
  }

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

  void pollMidi(){
    char c;
    for(;;){
      if(uart_receive_bytes(&c, 1) == 0){
	MidiReaderStatus status = MidiReader::read(c);
	if(status == ERROR_STATUS){
	  MidiReader::clear();
	  Serial_println("MIDI read error");
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

/* web handler todo: factor out */
#include <stdlib.h>

static const char no_content_header[] = "HTTP/1.1 204 No Content\r\n\r\n";  
static const char empty_page[] = "<html/>\n";
static const char empty_image[] = "\x00";
static const char pitch_param[] = "pitch";
static const char velocity_param[] = "velocity";
int process_midi_note(void* socket, char* params, int params_len){
  char* pitch_loc = NULL;
  char* velocity_loc = NULL;
  char end_found = 0;
  /* Process the GET parameter list to determine if buttons have been pressed */
  int pitch = 0;
  int velocity = 0;
  /* Cycle through parameter list string until end or newline */
  while(end_found == 0){
    /* Check if parameter matches */
    if(0 == strncmp(params, pitch_param, sizeof(pitch_param)-1))
      pitch_loc = params + sizeof(pitch_param);
    else if(0 == strncmp(params, velocity_param, sizeof(velocity_param)-1))
      velocity_loc = params + sizeof(velocity_param);
    /* Scan ahead to the next parameter or the end of the parameter list */
    while((*params != '&') && (*params != '\n') && (params_len > 0)){
      params++;
      params_len--;
    }
    if(*params != '&')
      end_found = 1;
    if(pitch_loc != NULL){
      /* *params = '\x00'; // not required for atoi which stops at first non-digit */
      pitch = atoi(pitch_loc);
      pitch_loc = NULL;
    }
    if(velocity_loc != NULL){
      /* *params = '\x00'; // not required for atoi which stops at first non-digit */
      velocity = atoi(velocity_loc);
      velocity_loc = NULL;
    }
    if(end_found == 0){
      /* Skip over the "&" which joins parameters if found */
      params++;
      params_len--;
    }
  }
  // WPRINT_APP_INFO(("MIDI Note: %d %d", pitch, velocity));
  if(velocity > 0)
    writer.noteOn(pitch, velocity);
  else
    writer.noteOff(pitch, velocity);
  // send a 204 No Content
  // send_web_data( socket, (unsigned char*) no_content_header, sizeof( no_content_header ) - 1 );
  // send_web_data(socket, (unsigned char*)empty_page, sizeof(empty_page)-1);
  /* minus one is to avoid copying terminating null */
  return 0;
}

static const char cc_param[] = "cc";
static const char value_param[] = "value";
int process_midi_cc(void* socket, char* params, int params_len){
  char* cc_loc = NULL;
  char* value_loc = NULL;
  char end_found = 0;
  /* Process the GET parameter list to determine if buttons have been pressed */
  int cc = 0;
  int value = 0;
  /* Cycle through parameter list string until end or newline */
  while(end_found == 0){
    /* Check if parameter matches */
    if(0 == strncmp(params, cc_param, sizeof(cc_param)-1))
      cc_loc = params + sizeof(cc_param);
    else if(0 == strncmp(params, value_param, sizeof(value_param)-1))
      value_loc = params + sizeof(value_param);
    /* Scan ahead to the next parameter or the end of the parameter list */
    while((*params != '&') && (*params != '\n') && (params_len > 0)){
      params++;
      params_len--;
    }
    if(*params != '&')
      end_found = 1;
    if(cc_loc != NULL){
      cc = atoi(cc_loc);
      cc_loc = NULL;
    }
    if(value_loc != NULL){
      /* *params = '\x00'; // not required for atoi which stops at first non-digit */
      value = atoi(value_loc);
      value_loc = NULL;
    }
    if(end_found == 0){
      /* Skip over the "&" which joins parameters if found */
      params++;
      params_len--;
    }
  }
  WPRINT_APP_INFO(("MIDI CC: %d %d", cc, value));
  writer.controlChange(cc, value);
  // send a 204 No Content
  // send_web_data( socket, (unsigned char*) no_content_header, sizeof( no_content_header ) - 1 );
  // send_web_data(socket, (unsigned char*)empty_page, sizeof(empty_page)-1);
  /* minus one is to avoid copying terminating null */
  return 0;
}

void oscNoteOn(OscMessage &message){
  if(message.size() > 2){
    int channel = message.getInt(0);
    int note = message.getInt(1);
    int velocity = message.getInt(2);
    writer.noteOn(channel, note, velocity);
  }
}

void oscNoteOff(OscMessage &message){
  if(message.size() > 1){
    int channel = message.getInt(0);
    int note = message.getInt(1);
    writer.noteOff(channel, note, 0);
  }
}

void oscControlChange(OscMessage &message){
  if(message.size() > 2){
    int channel = message.getInt(0);
    int cc = message.getInt(1);
    int value = message.getInt(2);
    writer.controlChange(channel, cc, value);
  }
}

void oscPitchBend(OscMessage &message){
  if(message.size() > 1){
    int channel = message.getInt(0);
    int value = message.getInt(1);
    writer.pitchBend(channel, value);
  }
}

void oscStatus(OscMessage &message){
  // todo: send ip and port details
}

void oscLed(OscMessage &message){
  // todo: toggle led
}

void udp_recv_packet(uint8_t* buffer, int size){
  OscMessage msg;
  msg.parse(buffer, size);
  // WPRINT_APP_INFO(("received UDP message %s", msg.getAddress()));  
  char* address = msg.getAddress();
  if(strcmp(OscCmd_status, address) == 0){
    oscStatus(msg);
  }else if(strcmp(OscCmd_led, address) == 0){
    oscLed(msg);
  }else if(strcmp(OscCmd_note_on, address) == 0){
    oscNoteOn(msg);
  }else if(strcmp(OscCmd_note_off, address) == 0){
    oscNoteOff(msg);
  }else if(strcmp(OscCmd_control_change, address) == 0){
    oscControlChange(msg);
  }else if(strcmp(OscCmd_pitch_bend, address) == 0){
    oscPitchBend(msg);
  }

  // WPRINT_APP_INFO(("sent UDP message %s", buffer));  
}
