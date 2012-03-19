#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// #include "device.h"
// #include "adc_freerunner.h"
// #include "DiscreteController.h"

void setup();
void loop();
// debug
// #include "serial.h"
#include "wiring.h"

#ifndef __cplusplus
#error "wtf!"
#endif

#ifndef A0
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
#endif

void setup(){
  cli();
//   setup_adc();

//   SEQUENCER_CLOCK_DDR &= ~_BV(SEQUENCER_CLOCK_PIN);
//   SEQUENCER_CLOCK_PORT |= _BV(SEQUENCER_CLOCK_PIN); // enable pull-up resistor
//   SEQUENCER_CHAINED_SWITCH_DDR  &= ~_BV(SEQUENCER_CHAINED_SWITCH_PIN);
//   SEQUENCER_CHAINED_SWITCH_PORT |= _BV(SEQUENCER_CHAINED_SWITCH_PIN);

  pinMode(A5, INPUT);
  digitalWrite(A5, HIGH);
  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);
  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);

  sei();

  // debug
  beginSerial(9600);
  printString("hello\n");
//   serialWrite('h');
//   serialWrite('\n');
}

#define PIEZO_THRESHOLD 100

void loop(){
  if(serialAvailable() > 0){
    serialRead();
    printString("status: ");
    printString("A1: ");
    printHex(analogRead(1));
    printString(" A0: ");
    printHex(analogRead(0));
    if(digitalRead(A5) == LOW)
      printString(" A5!");
    if(digitalRead(A4) == LOW)
      printString(" A4!");
    if(digitalRead(A3) == LOW)
      printString(" A3!");
    if(digitalRead(A2) == LOW)
      printString(" A2!");
    printNewline();
  }

  if(analogRead(1) > PIEZO_THRESHOLD){
    printString("\t\tbang!\n");
  }
//   // debug
//   PORTB ^= _BV(PORTB5);
}
