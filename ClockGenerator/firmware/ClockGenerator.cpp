#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "HardwareTimer.h"
#include "adc_freerunner.h"
#include "ContinuousController.h"

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

// #define GENERATOR_TOP_FREQUENCY 31250
#define GENERATOR_TOP_FREQUENCY 15625

#define GENERATOR_CONTROLLER_DELTA 0.001

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
#ifdef SERIAL_DEBUG
    printByte('|');
#endif
  }
};

class RelativeFrequencyController : public ContinuousController {
public:
  Timer* timer;
  ContinuousController* other;
  virtual void hasChanged(float v){
    v = other->value*v*2;
    timer->setRate(v);
#ifdef SERIAL_DEBUG
    printByte('*');
#endif
  }
};

class DutyCycleController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setDutyCycle(v);
#ifdef SERIAL_DEBUG
    printByte('-');
#endif
  }
};

Timer1 timer1; // 16-bit Timer/Counter 1
Timer2 timer2; // 8-bit Timer/Counter 2

FrequencyController rateA;
DutyCycleController dutyA;
FrequencyController rateB;
RelativeFrequencyController rateAB;

void setup(){
  cli();

  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_B);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_B);

  timer1.setDutyCycle(0.5);
  timer2.setDutyCycle(0.5);

  rateA.timer = &timer1;
  dutyA.timer = &timer1;
  rateB.timer = &timer2;
  rateAB.timer = &timer1;
  rateAB.other = &rateB;

  rateA.delta = GENERATOR_CONTROLLER_DELTA;
  dutyA.delta = GENERATOR_CONTROLLER_DELTA;
  rateB.delta = GENERATOR_CONTROLLER_DELTA;
  rateAB.delta = GENERATOR_CONTROLLER_DELTA;

  setup_adc();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif

  timer1.start();
  timer2.start();
}

void loop(){
  rateB.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  if(isChained()){
    rateAB.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
    if(timer1.isStopped())
      timer1.start();
  }else if(isFree()){
    rateA.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
    if(timer1.isStopped())
      timer1.start();
  }else if(!timer1.isStopped()){
    timer1.stop();
    rateA.value = -1.0;
    rateAB.value = -1.0;
  }

  dutyA.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));

#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("a: [");
    printInteger(timer1.frequency);
    printString(", ");
    printInteger(timer1.duty*255);
    if(timer1.isStopped())
      printString(" stopped");
    printString("] ");
    printString("b: [");
    printInteger(timer2.frequency);
    printString(", ");
    printInteger(timer2.duty*255);
    if(timer2.isStopped())
      printString(" stopped");
    printString("] ");
    if(isChained())
      printString(" chained ");
    if(isFree())
      printString(" free ");
    printNewline();
  }
#endif
}
