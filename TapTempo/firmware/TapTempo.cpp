// #define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "ContinuousController.h"
#include "MCP492xController.h"

MCP492xController dac1;

/*
notes:

TapTempo Rev 01:
DAC SDI connected to PB4 MISO pin 16, should be PB3 MOSI pin 15 ->
bridge IC pins with solder, configure PB4 as high impedance input.

SS is on PB2, connects to CLKOUT
PC5 connects to DAC CS

*/

inline bool triggerIsHigh(){
  return !(TAPTEMPO_TRIGGER_PINS & _BV(TAPTEMPO_TRIGGER_PIN));
}

inline bool gateIsHigh(){
  return !(TAPTEMPO_GATE_PINS & _BV(TAPTEMPO_GATE_PIN));
}

inline bool isCountMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

inline bool isDelayMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

enum OperatingMode {
  DISABLED_MODE                   = 0,
  DIVIDE_MODE                     = 1,
  DELAY_MODE                      = 2
};

// #define SHIFT_LIMIT 2147483648L
#define SHIFT_LIMIT 65536L
#define RAMP_LIMIT 4096L
// #define STEP_RATIO 12
#define STEP_RATIO 1

#define RETRIGGER_THRESHOLD 4

class TapTempo {
private:
  volatile uint32_t counter;
  volatile uint32_t limit;
  volatile uint16_t ramp;
//   volatile uint32_t step;
  volatile uint32_t trig;
  
public:
  TapTempo() : counter(0), limit(4096L), ramp(0), trig(0) {}
//   void shiftLimit(float amount){
//     setLimit(limit + SHIFT_LIMIT*amount);
//   }
  void setLimit(uint32_t l){
    limit = l;
//     step = limit >> STEP_RATIO;
  }
  void trigger(){
    if(trig > RETRIGGER_THRESHOLD){
      high();
      setLimit(trig);
      trig = 0;
    }
  }
  void clock(){
    trig++;
    if(++counter > limit){
      toggle();
      counter = 0;
    }
//     dac1.send(ramp++);
//     if(counter % step == 0){
      if(ramp < RAMP_LIMIT){
	dac1.send(ramp++);
      }
//     }
  }
  void low(){
    TAPTEMPO_GATE_OUTPUT_PORT |= _BV(TAPTEMPO_GATE_OUTPUT_PIN);
  }
  void high(){
    TAPTEMPO_GATE_OUTPUT_PORT &= ~_BV(TAPTEMPO_GATE_OUTPUT_PIN);
    ramp = 0;
  }
  void toggle(){
    if(isHigh())
      low();
    else
      high();
  }
  inline bool isHigh(){
    return !(TAPTEMPO_GATE_OUTPUT_PINS & _BV(TAPTEMPO_GATE_OUTPUT_PIN));
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("trg ");
    printInteger(trig);
    printString(" cnt ");
    printInteger(counter);
    printString(", lim ");
    printInteger(limit);
//     printString(", stp ");
//     printInteger(step);
    if(isHigh())
      printString(" high");
    else
      printString(" low");
  }
#endif
};

TapTempo tempo;

// class TempoController : public ContinuousController {
// private:
//   float last;
// public:
//   void hasChanged(float v){
//     tempo.shiftLimit(last - v);
//     last = v;
//   }
// };

// TempoController tempoControl;

void reset(){
  tempo.low();
}

volatile OperatingMode mode;

inline void updateMode(){
  if(isCountMode()){
    mode = DIVIDE_MODE;
  }else if(isDelayMode()){
    mode = DELAY_MODE;
//     cli();
//     reset();
//     while(isDelayMode());
//     sei();
  }else{
    mode = DISABLED_MODE;
  }
}

void setup(){
  cli();

  dac1.init(DAC1_CS_PIN, DAC_SHDN_BIT);

  // define hardware interrupts 0 and 1
//   EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // trigger int0 on rising edge
  EICRA = _BV(ISC11) | _BV(ISC01); // falling edge triggers INT1 and INT0

//   EICRA = (1<<ISC10) | (1<<ISC01);
  // trigger int0 on the falling edge, since input is inverted
  // trigger int1 on any logical change.
  // pulses that last longer than one clock period will generate an interrupt.
  EIMSK =  (1<<INT1) | (1<<INT0); // enables INT0 and INT1
  TAPTEMPO_TRIGGER_DDR &= ~_BV(TAPTEMPO_TRIGGER_PIN);
  TAPTEMPO_TRIGGER_PORT |= _BV(TAPTEMPO_TRIGGER_PIN); // enable pull-up resistor

  TAPTEMPO_GATE_DDR &= ~_BV(TAPTEMPO_GATE_PIN);
  TAPTEMPO_GATE_PORT |= _BV(TAPTEMPO_GATE_PIN); // enable pull-up resistor

  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_B);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_B);

  TAPTEMPO_RAMP_OUTPUT_DDR |= _BV(TAPTEMPO_RAMP_OUTPUT_PIN);
  TAPTEMPO_GATE_OUTPUT_DDR |= _BV(TAPTEMPO_GATE_OUTPUT_PIN);
  TAPTEMPO_LEDS_DDR |= _BV(TAPTEMPO_LED_1_PIN);
  TAPTEMPO_LEDS_DDR |= _BV(TAPTEMPO_LED_2_PIN);
  TAPTEMPO_LEDS_DDR |= _BV(TAPTEMPO_LED_3_PIN);

  TAPTEMPO_RAMP_OUTPUT_PORT |= _BV(TAPTEMPO_RAMP_OUTPUT_PIN);
  TAPTEMPO_GATE_PORT |= _BV(TAPTEMPO_GATE_OUTPUT_PIN);
  TAPTEMPO_LEDS_PORT |= _BV(TAPTEMPO_LED_1_PIN);
  TAPTEMPO_LEDS_PORT &= ~_BV(TAPTEMPO_LED_2_PIN);
  TAPTEMPO_LEDS_PORT &= ~_BV(TAPTEMPO_LED_3_PIN);

  //
//   TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B); // Enable Interrupt Timer/Counter1, Output Compare A & B (SIG_OUTPUT_COMPARE1A/SIG_OUTPUT_COMPARE1B)
//   TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12);    // Clock/1024, 0.001024 seconds per tick, Mode=CTC
//   OCR1A = 1954;                       // 0.001024*1954 ~= 2 SIG_OUTPUT_COMPARE1A will be triggered every 2 seconds
//     OCR1B = 1929;                       // 0.001024*1929 ~= 1.975 SIG_OUTPUT_COMPARE1B will be triggered 25ms before SIG_OUTPUT_COMPARE1A

  TIMSK1 = _BV(OCIE1A); // Enable Interrupt Timer/Counter1, Output Compare A
  TCCR1B = _BV(CS11) | _BV(WGM12);    // Clock/8, Mode=CTC
//   TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);    // Clock/64, Mode=CTC
//   TCCR1B = _BV(CS12) | _BV(WGM12);    // Clock/256, Mode=CTC
  OCR1A = 4096L;

//   // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
//   // configure Timer 0 to Fast PWM, 0xff top.
//   TCCR0A |= _BV(WGM01) | _BV(WGM00);
// //   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
//   TCCR0B |= _BV(CS01);  // prescaler: 8
//   // enable timer 0 overflow interrupt
//   TIMSK0 |= _BV(TOIE0);

  setup_adc();
  reset();
  updateMode();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

ISR(SIG_OUTPUT_COMPARE1A){
  tempo.clock();
}

// ISR(SIG_OUTPUT_COMPARE1B){

// }

/* Timer 0 overflow interrupt */
// ISR(TIMER0_OVF_vect){
//   tempo.clock();
// }

/* Trigger interrupt */
ISR(INT0_vect){  
  tempo.trigger();
//   // hold everything until released
//   while(triggerIsHigh());
//   output.low();
}

/* Gate interrupt */
ISR(INT1_vect){
  tempo.trigger();
  // hold everything until released
//   while(gateIsHigh());
}

// #define MAX_OVERFLOW_LIMIT 65535L
// #define MAX_OVERFLOW_LIMIT 32767L
#define MAX_OVERFLOW_LIMIT 36864

void loop(){
  updateMode();

  uint16_t tempi = getAnalogValue(TEMPO_ADC_CHANNEL) << 3;
  OCR1A = MAX_OVERFLOW_LIMIT - tempi;

//   tempoControl.update(getAnalogValue(TEMPO_ADC_CHANNEL));
  
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){

//     // test dac
//     static uint8_t dactest;
//     dac1.send(dactest++);

    serialRead();
    printString("tempo[");
    tempo.dump();
    printString("] ");
    printInteger(OCR1A);
    switch(mode){
    case DIVIDE_MODE:
      printString(" divide ");
      break;
    case DELAY_MODE:
      printString(" delay ");
      break;
    }
    if(gateIsHigh())
      printString(" gate ");
    if(triggerIsHigh())
      printString(" trigger ");
    printNewline();
  }
#endif
}
