// #define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "adc_freerunner.h"
#include "ContinuousController.h"

#define GENERATOR_CONTROLLER_DELTA 0.001

class TimerA : public ClockedTimer<uint32_t> {
  void on(){
    TIMERA_PORT_B &= ~_BV(TIMERA_OUTPUT_B); // clock inverted
    TIMERA_PORT_A |= _BV(TIMERA_OUTPUT_A); // LED on
  }
  void off(){
    TIMERA_PORT_B |= _BV(TIMERA_OUTPUT_B);
    TIMERA_PORT_A &= ~_BV(TIMERA_OUTPUT_A);
  }
};

class TimerB : public ClockedTimer<uint32_t> {
  void on(){
    TIMERB_PORT_B &= ~_BV(TIMERB_OUTPUT_B); // clock inverted
    TIMERB_PORT_A |= _BV(TIMERB_OUTPUT_A); // LED on
  }
  void off(){
    TIMERB_PORT_B |= _BV(TIMERB_OUTPUT_B);
    TIMERB_PORT_A &= ~_BV(TIMERB_OUTPUT_A);
  }
};

inline bool isChained(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_A));
}

inline bool isFree(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_B));
}

class FrequencyController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setRate(v);
  }
};

class DutyCycleController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setDutyCycle(v);
  }
};

TimerA timerA;
TimerB timerB;

FrequencyController rateA;
DutyCycleController dutyA;
FrequencyController rateB;
DutyCycleController dutyB;

void setup(){
  cli();

  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_B);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_B);

  TIMERA_DDR_A |= _BV(TIMERA_OUTPUT_A);
  TIMERA_DDR_B |= _BV(TIMERA_OUTPUT_B);
  TIMERB_DDR_A |= _BV(TIMERB_OUTPUT_A);
  TIMERB_DDR_B |= _BV(TIMERB_OUTPUT_B);

  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64
//   TCCR0B |= _BV(CS01);  // prescaler: 8
  TIMSK0 |= _BV(TOIE0); // enable timer 0 overflow interrupt
//   OCR0A = 0;

  rateA.timer = &timerA;
  dutyA.timer = &timerA;
  rateB.timer = &timerB;
  dutyB.timer = &timerB;

//   uint32_t multiplier = F_CPU / (2*64*(1+0xff)); // MCU clock frequency divided by prescaler;
  // see Datasheet Section 14.7.4
  uint32_t multiplier = F_CPU / (64*256); // MCU clock frequency divided by prescaler times 256 
    
  timerA.setDutyCycle(0.5);
  timerA.minimum = 0.001;
  timerA.maximum = 20;
  timerA.multiplier = multiplier;

  timerB.setDutyCycle(0.5);
  timerB.minimum = 0.001;
  timerB.maximum = 20;
  timerB.multiplier = multiplier;

  rateA.delta = GENERATOR_CONTROLLER_DELTA;
  dutyA.delta = GENERATOR_CONTROLLER_DELTA;
  rateB.delta = GENERATOR_CONTROLLER_DELTA;
  dutyB.delta = GENERATOR_CONTROLLER_DELTA;

  setup_adc();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif

  timerA.start();
  timerB.start();
}

// #define FAST_PRESCALER      (CS01)
// #define MEDIUM_PRESCALER    (CS01|CS00)
// #define SLOW_PRESCALER      (CS02|CS00)

#define FAST_MULTIPLIER        (F_CPU / (64*16ull))
#define MEDIUM_MULTIPLIER      (F_CPU / (64*256ull))
#define SLOW_MULTIPLIER        (F_CPU / (64*4096ull))

void loop(){
  rateA.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  rateB.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  dutyA.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));
  dutyB.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));

  if(isFree() && (timerA.multiplier != FAST_MULTIPLIER)){
    timerA.multiplier = FAST_MULTIPLIER;
    timerA.updateFrequency();
    timerA.updateDutyCycle();
  }else if(isChained() && (timerA.multiplier != SLOW_MULTIPLIER)){
    timerA.multiplier = SLOW_MULTIPLIER;
    timerA.updateFrequency();
    timerA.updateDutyCycle();
  }else if(timerA.multiplier != MEDIUM_MULTIPLIER){
    timerA.multiplier = MEDIUM_MULTIPLIER;
    timerA.updateFrequency();
    timerA.updateDutyCycle();
  }

//   static int prescaler = MEDIUM_PRESCALER;
//   if(isFree() && (prescaler != FAST_PRESCALER)){
//     TCCR0B = prescaler = FAST_PRESCALER;
//   }else if(isChained() && (prescaler != SLOW_PRESCALER)){
//     TCCR0B = prescaler = SLOW_PRESCALER;
//   }else if(prescaler != MEDIUM_PRESCALER){
//     TCCR0B = prescaler = MEDIUM_PRESCALER;
//   }

#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("0: [");
    timerA.dump();
    printString("] ");
    printString("1: [");
    timerB.dump();
    printString("] ");
    if(isChained())
      printString(" chained ");
    if(isFree())
      printString(" free ");
    printNewline();
  }
#endif
}

ISR(TIMER0_OVF_vect){
  timerA.clock();
  timerB.clock();
}
