// #define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "Twister.h"

/*
  prescaler 8
  1.880 Hz saw at fastest setting
  timer overflow called each 0.129mS (smallest overflow limit = 256).

  27.78 mHz saw at middle
  overflow called each 8.788mS

  14.88 mHz at slowest
  overflow called each 16.4mS
*/

inline bool triggerIsHigh(){
  return !(TICKER_TAPE_TRIGGER_PINS & _BV(TICKER_TAPE_TRIGGER_PIN));
}

inline bool gateIsHigh(){
  return !(TICKER_TAPE_GATE_PINS & _BV(TICKER_TAPE_GATE_PIN));
}

inline bool isTriggerMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

inline bool isClockMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

inline bool isGateMode(){
  return !isClockMode() && isTriggerMode();
}

inline bool isExternalClockMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

inline bool isInternalClockMode(){
  return !isExternalClockMode();
}

MersenneTwister random;

void reset(){
  random.reset();
}

void setup(){
  cli();

  // define hardware interrupts 0 and 1
//   EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // trigger int0 on rising edge, int1 on any change
//   EICRA = _BV(ISC11) | _BV(ISC01); // falling edge triggers INT1 and INT0
  // let's do not enable int0 and int1
//   EIMSK =  _BV(INT1) | _BV(INT0); // enables INT0 and INT1

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
//   TICKER_TAPE_LEDS_DDR |= _BV(TICKER_TAPE_LED_2_PIN);
//   TICKER_TAPE_LEDS_DDR |= _BV(TICKER_TAPE_LED_3_PIN);

  TICKER_TAPE_GATE_PORT |= _BV(TICKER_TAPE_GATE_OUTPUT_PIN);
  TICKER_TAPE_LEDS_PORT |= _BV(TICKER_TAPE_LED_1_PIN);
//   TICKER_TAPE_LEDS_PORT &= ~_BV(TICKER_TAPE_LED_2_PIN);
//   TICKER_TAPE_LEDS_PORT &= ~_BV(TICKER_TAPE_LED_3_PIN);

//   TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B); // Enable Interrupt Timer/Counter1, Output Compare A & B (SIG_OUTPUT_COMPARE1A/SIG_OUTPUT_COMPARE1B)
//   TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12);    // Clock/1024, 0.001024 seconds per tick, Mode=CTC

  TIMSK1 = _BV(OCIE1A); // Enable Interrupt Timer/Counter1, Output Compare A
  // Set timer mode and prescaler
//   TCCR1B = _BV(CS10) | _BV(WGM12);                       // Clock/1, Mode=CTC
//   TCCR1B = _BV(CS11) | _BV(WGM12);                       // Clock/8, Mode=CTC
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);           // Clock/64, Mode=CTC
//   TCCR1B = _BV(CS12) | _BV(WGM12);                       // Clock/256, Mode=CTC
  OCR1A = 8; // 31250Hz with prescaler=8

  // prescale = 8 means 250Khz / OCR1A overflow interrupt rate?
//   // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
//   // configure Timer 0 to Fast PWM, 0xff top.
//   TCCR0A |= _BV(WGM01) | _BV(WGM00);
// //   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
//   TCCR0B |= _BV(CS01);  // prescaler: 8
//   // enable timer 0 overflow interrupt
//   TIMSK0 |= _BV(TOIE0);

  setup_adc();

  uint32_t seed = 5489;
  for(uint8_t i=0; i<ADC_CHANNELS; ++i)
    seed ^= getAnalogValue(i);
  random.seed(seed);

  reset();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

ISR(SIG_OUTPUT_COMPARE1A){
//   ledOn();
  if(isClockMode())
    random.trigger();
//   ledOff();
}

// ISR(SIG_OUTPUT_COMPARE1B){
// }

/* Timer 0 overflow interrupt */
// ISR(TIMER0_OVF_vect){
//   tempo.clock();
// }

/* Trigger interrupt */
ISR(INT0_vect){  
  if(isTriggerMode())
    random.trigger();
}

/* Gate interrupt */
ISR(INT1_vect){
  if(isGateMode())
    random.trigger();
}

#define MINIMUM_PERIOD 128
#define MAXIMUM_PERIOD (MINIMUM_PERIOD + ADC_VALUE_RANGE)

void loop(){
  uint16_t period = getAnalogValue(TEMPO_ADC_CHANNEL);
  period |= 0xf;
  period <<= 3;
  // with prescaler=8, period=[1016-65528], interrupt should run at ~ 2kHz - 30Hz, 512 bytes in 0.26s to 17s.
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
    printString(" twister[");
    random.dump();
    printString("]");
    printNewline();
  }
#endif
}
