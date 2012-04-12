#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
// #include "DiscreteController.h"
#include "globals.h"
#include "MidiWriter.h"

void setup();
void loop();
// debug
// #include "wiring.h"

#define MIDI_CHANNEL 1
#define SERIAL_SPEED 31250L
// #define SERIAL_SPEED 38400L

MidiWriter midi;

void setup(){
  cli();
  setup_adc();

  HARMELODIUM_BUTTON_BANK_A_DDR &= ~_BV(HARMELODIUM_BUTTON_A1_PIN);
  HARMELODIUM_BUTTON_BANK_A_DDR &= ~_BV(HARMELODIUM_BUTTON_A2_PIN);
  HARMELODIUM_BUTTON_BANK_A_DDR &= ~_BV(HARMELODIUM_BUTTON_A3_PIN);
  HARMELODIUM_BUTTON_BANK_A_DDR &= ~_BV(HARMELODIUM_BUTTON_A4_PIN);

  HARMELODIUM_BUTTON_BANK_A_PORT |= _BV(HARMELODIUM_BUTTON_A1_PIN);
  HARMELODIUM_BUTTON_BANK_A_PORT |= _BV(HARMELODIUM_BUTTON_A2_PIN);
  HARMELODIUM_BUTTON_BANK_A_PORT |= _BV(HARMELODIUM_BUTTON_A3_PIN);
  HARMELODIUM_BUTTON_BANK_A_PORT |= _BV(HARMELODIUM_BUTTON_A4_PIN);

  HARMELODIUM_BUTTON_BANK_B_DDR &= ~_BV(HARMELODIUM_BUTTON_B1_PIN);
  HARMELODIUM_BUTTON_BANK_B_DDR &= ~_BV(HARMELODIUM_BUTTON_B2_PIN);
  HARMELODIUM_BUTTON_BANK_B_DDR &= ~_BV(HARMELODIUM_BUTTON_B3_PIN);
  HARMELODIUM_BUTTON_BANK_B_DDR &= ~_BV(HARMELODIUM_BUTTON_B4_PIN);

  HARMELODIUM_BUTTON_BANK_B_PORT |= _BV(HARMELODIUM_BUTTON_B1_PIN);
  HARMELODIUM_BUTTON_BANK_B_PORT |= _BV(HARMELODIUM_BUTTON_B2_PIN);
  HARMELODIUM_BUTTON_BANK_B_PORT |= _BV(HARMELODIUM_BUTTON_B3_PIN);
  HARMELODIUM_BUTTON_BANK_B_PORT |= _BV(HARMELODIUM_BUTTON_B4_PIN);

  sei();

  beginSerial(SERIAL_SPEED);

  midi.init(MIDI_CHANNEL);

  // debug
  midi.noteOn(10, 10);
  midi.noteOff(10, 0);
  midi.allNotesOff();

//   // debug
//   beginSerial(9600);
//   printString("hello\n");
// //   serialWrite('h');
// //   serialWrite('\n');
}

// #define BANK_A_MASK HARMELODIUM_BUTTON_A1_PIN | HARMELODIUM_BUTTON_A2_PIN | HARMELODIUM_BUTTON_A3_PIN | HARMELODIUM_BUTTON_A4_PIN;

// uint8_t keycodes[];
// };

// void populateKeyCodes(){
// }

uint8_t tonic = 60; // middle c

uint8_t getKeyValue(){
//   uint16_t code = (HARMELODIUM_BUTTON_BANK_A_PINS & BANK_A_MASK) << 8 | (HARMELODIUM_BUTTON_BANK_B_PINS & BANK_B_MASK);
  uint8_t value = tonic;
  if(!(HARMELODIUM_BUTTON_BANK_B_PINS & _BV(HARMELODIUM_BUTTON_B1_PIN)))
    value += 7; // P5
  if(!(HARMELODIUM_BUTTON_BANK_B_PINS & _BV(HARMELODIUM_BUTTON_B2_PIN)))
    value += 5; // P4
  if(!(HARMELODIUM_BUTTON_BANK_A_PINS & _BV(HARMELODIUM_BUTTON_A1_PIN)))
    value += 4; // M3
  if(!(HARMELODIUM_BUTTON_BANK_A_PINS & _BV(HARMELODIUM_BUTTON_A2_PIN)))
    value += 2; // M2
  if(!(HARMELODIUM_BUTTON_BANK_A_PINS & _BV(HARMELODIUM_BUTTON_A3_PIN)))
    value -= 1; // Dim
  // octaves
  if(!(HARMELODIUM_BUTTON_BANK_B_PINS & _BV(HARMELODIUM_BUTTON_B3_PIN)))
    value += 12; // +1 octave
  if(!(HARMELODIUM_BUTTON_BANK_B_PINS & _BV(HARMELODIUM_BUTTON_B4_PIN)))
    value += 24; // +2 octaves
  if(!(HARMELODIUM_BUTTON_BANK_A_PINS & _BV(HARMELODIUM_BUTTON_A4_PIN)))
    value -= 12; // -1 octaves
  return value;
}

#define HARMELODIUM_PIEZO_THRESHOLD 800

void noteOff(int8_t pitch){
  midi.noteOff(pitch, 0);
}

void noteOn(int8_t pitch, int8_t velocity){
  midi.noteOn(pitch, velocity);
}

#define NO_NOTE -1
uint32_t lastbang;
int8_t lastnote = NO_NOTE;
uint16_t timeout = 40;
uint16_t duration = 200;

#define min(a,b) ((a)<(b)?(a):(b))

void loop(){
  uint32_t now = millis();
  uint16_t threshold = getAnalogValue(HARMELODIUM_FADER_CONTROL);
  uint16_t bang = getAnalogValue(HARMELODIUM_PIEZO_CONTROL);
  if(bang > threshold && now > lastbang + timeout){
    uint8_t pitch = getKeyValue();
    uint8_t velocity = min(127, 40+ (bang >> 5));
    lastbang = now;
    if(lastnote != NO_NOTE)
      noteOff(lastnote);
    noteOn(pitch, velocity);
    lastnote = pitch;
  }else if(lastnote != NO_NOTE && now > lastbang + duration){
    noteOff(lastnote);
    lastnote = NO_NOTE;
  }

  // debug
//   if(serialAvailable() > 0){
//     serialRead();
//     printString("status: ");
//     printString("piezo: ");
//     printInteger(getAnalogValue(HARMELODIUM_PIEZO_CONTROL));
//     printString(" fader: ");
//     printInteger(getAnalogValue(HARMELODIUM_FADER_CONTROL));
//     printString("\t\tkey: ");
//     printInteger(getKeyValue());
//     printNewline();
//     if(getAnalogValue(HARMELODIUM_PIEZO_CONTROL) > HARMELODIUM_PIEZO_THRESHOLD){
//       printString("\t\tbang!\n");
//     }
//   }

//   // debug
//   PORTB ^= _BV(PORTB5);
}
