// #define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "Ticker.h"

/*
  prescaler 8
  1.880 Hz saw at fastest setting
  timer overflow called each 0.129mS (smallest overflow limit = 256).

  27.78 mHz saw at middle
  overflow called each 8.788mS

  14.88 mHz at slowest
  overflow called each 16.4mS
*/

TickerTape tape;

void reset(){
  tape.reset();
}

void setup(){
  cli();

  // define hardware interrupts 0 and 1
//   EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // trigger int0 on rising edge, int1 on any change
  EICRA = _BV(ISC11) | _BV(ISC01); // falling edge triggers INT1 and INT0

  // pulses that last longer than one clock period will generate an interrupt.
  EIMSK =  _BV(INT1) | _BV(INT0); // enables INT0 and INT1
  TICKER_TAPE_TRIGGER_DDR &= ~_BV(TICKER_TAPE_TRIGGER_PIN);
  TICKER_TAPE_TRIGGER_PORT |= _BV(TICKER_TAPE_TRIGGER_PIN); // enable pull-up resistor

  TICKER_TAPE_GATE_DDR &= ~_BV(TICKER_TAPE_GATE_PIN);
  TICKER_TAPE_GATE_PORT |= _BV(TICKER_TAPE_GATE_PIN); // enable pull-up resistor

  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_B);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_B);

  TICKER_TAPE_GATE_OUTPUT_DDR |= _BV(TICKER_TAPE_GATE_OUTPUT_PIN);
  TICKER_TAPE_LEDS_DDR |= _BV(TICKER_TAPE_LED_1_PIN);
  TICKER_TAPE_LEDS_DDR |= _BV(TICKER_TAPE_LED_2_PIN);
  TICKER_TAPE_LEDS_DDR |= _BV(TICKER_TAPE_LED_3_PIN);

  TICKER_TAPE_GATE_PORT |= _BV(TICKER_TAPE_GATE_OUTPUT_PIN);
  TICKER_TAPE_LEDS_PORT |= _BV(TICKER_TAPE_LED_1_PIN);
  TICKER_TAPE_LEDS_PORT &= ~_BV(TICKER_TAPE_LED_2_PIN);
  TICKER_TAPE_LEDS_PORT &= ~_BV(TICKER_TAPE_LED_3_PIN);

  //
//   TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B); // Enable Interrupt Timer/Counter1, Output Compare A & B (SIG_OUTPUT_COMPARE1A/SIG_OUTPUT_COMPARE1B)
//   TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12);    // Clock/1024, 0.001024 seconds per tick, Mode=CTC

  TIMSK1 = _BV(OCIE1A); // Enable Interrupt Timer/Counter1, Output Compare A
//   TCCR1B = _BV(CS10) | _BV(WGM12);  // Clock/1, Mode=CTC
  TCCR1B = _BV(CS11) | _BV(WGM12);  // Clock/8, Mode=CTC
  // prescale = 8 means 250Khz / OCR1A overflow interrupt rate?
//   TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);    // Clock/64, Mode=CTC
//   TCCR1B = _BV(CS12) | _BV(WGM12);    // Clock/256, Mode=CTC
  OCR1A = 8; // 31250Hz with prescaler=8

//   // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
//   // configure Timer 0 to Fast PWM, 0xff top.
//   TCCR0A |= _BV(WGM01) | _BV(WGM00);
// //   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
//   TCCR0B |= _BV(CS01);  // prescaler: 8
//   // enable timer 0 overflow interrupt
//   TIMSK0 |= _BV(TOIE0);

  setup_adc();
  reset();
  tape.updateMode();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

ISR(SIG_OUTPUT_COMPARE1A){
  tape.clock();
}

// ISR(SIG_OUTPUT_COMPARE1B){
// }

/* Timer 0 overflow interrupt */
// ISR(TIMER0_OVF_vect){
//   tempo.clock();
// }

/* Trigger interrupt */
ISR(INT0_vect){  
  tape.trigger();
//   // hold everything until released
//   while(triggerIsHigh());
//   output.low();
}

/* Gate interrupt */
ISR(INT1_vect){
  tape.trigger();
  // hold everything until released
//   while(gateIsHigh());
}

#define MINIMUM_PERIOD 1024
#define MAXIMUM_PERIOD (MINIMUM_PERIOD + ADC_VALUE_RANGE)

void loop(){
  tape.updateMode();
  uint16_t period = getAnalogValue(TEMPO_ADC_CHANNEL);
  period += MINIMUM_PERIOD;
  if(!isFastMode())
    period <<= 1;
//   period |= 0x01; // minimum 1
  OCR1A = period;
  
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
//     // test dac
//     static uint8_t dactest;
//     dac1.send(dactest++);
    printString("cnt ");    
    printInteger(OCR1A);
    if(gateIsHigh())
      printString(" gate");
    if(triggerIsHigh())
      printString(" trigger");
    serialRead();
    printString(" tape[");
    tape.dump();
    printString("]");
    printNewline();
  }
#endif
}
