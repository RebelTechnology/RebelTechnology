#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "HardwareTimer.h"
#include "adc_freerunner.h"
#include "ContinuousController.h"

#define GENERATOR_CONTROLLER_DELTA 0.001

class Timer0 : public ClockedTimer {
  void on(){
    TIMER0_PORT_B &= ~_BV(TIMER0_OUTPUT_B); // clock inverted
    TIMER0_PORT_A |= _BV(TIMER0_OUTPUT_A); // LED on
  }
  void off(){
    TIMER0_PORT_B |= _BV(TIMER0_OUTPUT_B);
    TIMER0_PORT_A &= ~_BV(TIMER0_OUTPUT_A);
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

class RelativeFrequencyController : public ContinuousController {
public:
  Timer* timer;
  ContinuousController* other;
  virtual void hasChanged(float v){
    v = other->value*v*2;
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

Timer1 timer1; // 16-bit Timer/Counter 1
Timer0 timer0; // manually triggered from Timer0 interrupt

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

  TIMER0_DDR_A |= _BV(TIMER0_OUTPUT_A);
  TIMER0_DDR_B |= _BV(TIMER0_OUTPUT_B);
  TIMER1_DDR_A |= _BV(TIMER1_OUTPUT_A);
  TIMER1_DDR_B |= _BV(TIMER1_OUTPUT_B);

  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64
//   TCCR0B |= _BV(CS01);  // prescaler: 8
  TIMSK0 |= _BV(TOIE0); // enable timer 0 overflow interrupt

  TIMSK1 |= _BV(TOIE1); // enable timer 1 overflow interrupt

  timer0.setDutyCycle(0.5);
  timer0.minimum = 1;
  timer0.maximum = 16384;
  timer0.multiplier = 65535;
  timer1.setDutyCycle(0.5);

  rateA.timer = &timer1;
  dutyA.timer = &timer1;
  rateB.timer = &timer0;
  dutyB.timer = &timer0;

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

  timer0.start();
  timer1.start();
}

void loop(){
  rateA.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  rateB.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  dutyA.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));
  dutyB.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));

#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("0: [");
    timer0.dump();
    printString("] ");
    printString("1: [");
    timer1.dump();
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
  timer0.clock();
}
