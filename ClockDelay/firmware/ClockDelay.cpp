#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "adc_freerunner.h"
#include "DiscreteController.h"
#include "ContinuousController.h"

#define CLOCKDELAY_CONTROLLER_DELTA 0.001

#define CLOCKED_TIMER_MIN_FREQUENCY 0.0312 /* 0.0312Hz, period apprx 32 secs */
#define CLOCKED_TIMER_MAX_FREQUENCY 512 /* 512Hz, period apprx 2ms */

inline bool clockIsHigh(){
  return !(CLOCKDELAY_CLOCK_PINS & _BV(CLOCKDELAY_CLOCK_PIN));
}

inline bool resetIsHigh(){
  return !(CLOCKDELAY_RESET_PINS & _BV(CLOCKDELAY_RESET_PIN));
}

inline bool isCountMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

inline bool isDelayMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

enum OperatingMode {
  DISABLED_MODE                   = 0,
  DIVIDE_AND_DELAY_MODE           = 1,
  DIVIDE_AND_COUNT_MODE           = 2,
  SWING_MODE                      = 3
};

OperatingMode mode;

inline void updateMode(){
  if(isCountMode()){
    mode = DIVIDE_AND_COUNT_MODE;
  }else if(isDelayMode()){
    mode = DIVIDE_AND_DELAY_MODE;
  }else{
    mode = SWING_MODE;
  }
}

class ClockCounter {
public:
  inline void reset(){
    pos = 0;
  }
  bool next(){
    if(++pos >= value){
      pos = 0;
      return true;
    }
    return false;
  }
public:
  uint8_t pos;
  uint8_t value;
  void rise(){
    if(next())
      on();
    else
      off();
  }
  void fall(){
    off();
  }
  virtual void on(){
    DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN_A);
    DIVIDE_OUTPUT_PORT &= ~_BV(DIVIDE_OUTPUT_PIN_B);
  }
  void off(){
    DIVIDE_OUTPUT_PORT &= ~_BV(DIVIDE_OUTPUT_PIN_A);
    DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN_B);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
  }
#endif
};

ClockCounter counter;

class ClockDivider {
public:
  inline void reset(){
    pos = 0;
  }
  bool next(){
    if(++pos >= value){
      pos = 0;
      return true;
    }
    return false;
  }
public:
  uint8_t pos;
  uint8_t value;
  inline bool isLow(){
    return DIVIDE_OUTPUT_PINS & _BV(DIVIDE_OUTPUT_PIN_A);
  }
  inline bool isHigh(){
    return !(DIVIDE_OUTPUT_PINS & _BV(DIVIDE_OUTPUT_PIN_A));
  }
  void rise(){
    if(isLow() && next())
      on();
  }
  void fall(){
    if(isHigh() && next())
      off();
  }
  virtual void on(){
    DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN_A);
    DIVIDE_OUTPUT_PORT &= ~_BV(DIVIDE_OUTPUT_PIN_B);
  }
  void off(){
    DIVIDE_OUTPUT_PORT &= ~_BV(DIVIDE_OUTPUT_PIN_A);
    DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN_B);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
  }
#endif
};

ClockDivider divider;

class ClockDelay : public ClockedTimer {
public:
  void on(){
    DELAY_OUTPUT_PORT &= ~_BV(DELAY_OUTPUT_PIN_A);
    DELAY_OUTPUT_PORT |= _BV(DELAY_OUTPUT_PIN_B);
    if(mode != SWING_MODE || divider.pos == 0){
      COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN);
    }
  }
  void off(){
    DELAY_OUTPUT_PORT |= _BV(DELAY_OUTPUT_PIN_A);
    DELAY_OUTPUT_PORT &= ~_BV(DELAY_OUTPUT_PIN_B);
    if(mode != SWING_MODE || divider.pos == 0){
      COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
    }
  }
};

ClockDelay delay; // manually triggered from Timer0 interrupt

class FrequencyController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setRate(v);
  }
};

class CounterController : public DiscreteController {
public:
  ClockCounter* counter;
  virtual void hasChanged(int8_t v){
    counter->value = v;
  }
};

class DividerController : public DiscreteController {
public:
  ClockDivider* divider;
  virtual void hasChanged(int8_t v){
    divider->value = v;
  }
};

FrequencyController delayControl;
DividerController dividerControl;
CounterController counterControl;

void setup(){
  cli();

  // define interrupt 0 and 1
  EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00);
  // trigger int0 on the rising edge.
  // trigger int1 on any logical change.
  // pulses that last longer than one clock period will generate an interrupt.
  EIMSK =  (1<<INT1) | (1<<INT0);
  // enables INT0 and INT1
  CLOCKDELAY_CLOCK_DDR &= ~_BV(CLOCKDELAY_CLOCK_PIN);
  CLOCKDELAY_CLOCK_PORT |= _BV(CLOCKDELAY_CLOCK_PIN); // enable pull-up resistor

  CLOCKDELAY_RESET_DDR &= ~_BV(CLOCKDELAY_RESET_PIN);
  CLOCKDELAY_RESET_PORT |= _BV(CLOCKDELAY_RESET_PIN); // enable pull-up resistor

  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_B);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_B);

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
//   TCCR0B |= _BV(CS01);  // prescaler: 8
  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);

  delay.minimum = 1.0; // 1Hz
  delay.maximum = 512.0; // 512Hz, period apprx 2ms
  delay.setDutyCycle(0.5);

  delayControl.timer = &delay;
  delayControl.delta = CLOCKDELAY_CONTROLLER_DELTA;

  dividerControl.divider = &divider;
  dividerControl.range = 16;
  dividerControl.value = -1;

  counterControl.counter = &counter;
  counterControl.range = 16;
  counterControl.value = -1;

  setup_adc();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

void loop(){
  updateMode();
  dividerControl.update(getAnalogValue(DIVIDE_ADC_CHANNEL));
  counterControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  delayControl.update(getAnalogValue(DELAY_ADC_CHANNEL));

//   switch(mode){
//   case DIVIDE_AND_COUNT_MODE:
//     delay.stop();
//     break;
//   case DIVIDE_AND_DELAY_MODE:
//   case SWING_MODE:
//     break;
//   }
  
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("divider: [");
    divider.dump();
    printString("] ");
    printString("counter: [");
    counter.dump();
    printString("] ");
    printString("delay: [");
    delay.dump();
    printString("] ");
    if(isDelayMode())
      printString(" delay ");
    if(isCountMode())
      printString(" count ");
    printNewline();
  }
#endif
}

/* Timer 0 overflow interrupt */
ISR(TIMER0_OVF_vect){
  if(mode != DIVIDE_AND_COUNT_MODE)
    delay.clock();
}

/* Reset interrupt */
SIGNAL(INT0_vect){
  delay.reset();
  divider.reset();
  counter.reset();
  // hold everything until reset is released
  // todo: enable and test
//   while(resetIsHigh());
}

/* Clock interrupt */
SIGNAL(INT1_vect){
//   switch(mode){
//   case DIVIDE_AND_COUNT_MODE:
//     break;
//   case DIVIDE_AND_DELAY_MODE:
//   case SWING_MODE:
//     delay.clock();
//     break;
//   }
  if(clockIsHigh()){
    divider.rise();
    if(mode == DIVIDE_AND_COUNT_MODE)
      counter.rise();
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_C_PIN);
  }else{
    divider.fall();
    if(mode == DIVIDE_AND_COUNT_MODE)
      counter.fall();
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_C_PIN);
  }

//   if(clockIsHigh())
//     CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_C_PIN);
//   else
//     CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_C_PIN);
}
