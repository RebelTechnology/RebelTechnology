#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "adc_freerunner.h"
#include "ContinuousController.h"

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#define GENERATOR_TOP_FREQUENCY 31250
#define GENERATOR_TOP_FREQUENCY 15625

inline bool isChained(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_B));
}

inline bool isFree(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_A));
}

class FrequencyController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setFrequency(v<0?0:v*GENERATOR_TOP_FREQUENCY);
#ifdef SERIAL_DEBUG
    printByte('.');
#endif /* SERIAL_DEBUG */
  }
};

class DutyCycleController : public ContinuousController {
public:
  Timer* timer;
  virtual void hasChanged(float v){
    timer->setDutyCycle(v);
#ifdef SERIAL_DEBUG
    printByte('-');
#endif /* SERIAL_DEBUG */
  }
};

Timer1 timer1;
Timer2 timer2;

FrequencyController rateA;
DutyCycleController dutyA;
FrequencyController rateB;

#define GENERATOR_CONTROLLER_DELTA 0.001

void setup(){
  cli();

  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_B);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_B);

  timer2.start();

  rateA.timer = &timer2;
  dutyA.timer = &timer2;
  rateB.timer = &timer1;

  rateA.delta = GENERATOR_CONTROLLER_DELTA;
  dutyA.delta = GENERATOR_CONTROLLER_DELTA;
  rateB.delta = GENERATOR_CONTROLLER_DELTA;

  setup_adc();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

bool timer1stopped = true;

#define RATE_MIDPOINT

void loop(){

  rateA.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  dutyA.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));

  if(isChained()){
    rateB.update(getAnalogValue(GENERATOR_RATE_A_CONTROL)
		 +getAnalogValue(GENERATOR_RATE_B_CONTROL)
		 -ADC_VALUE_RANGE/2);
    if(timer1stopped){
      timer1.start();
      timer1.setDutyCycle(0.5);
      timer1stopped = false;
    }
  }else if(isFree()){
    rateB.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
    if(timer1stopped){
      timer1.start();
      timer1.setDutyCycle(0.5);
      timer1stopped = false;
    }
  }else if(!timer1stopped){
    timer1.stop();
    timer1stopped = true;
  }

#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("a: [");
    printInteger(rateA.value*GENERATOR_TOP_FREQUENCY);
    printString(", ");
    printInteger(dutyA.value*255);
    printString("] ");
    printString("b: [");
    printInteger(rateB.value*GENERATOR_TOP_FREQUENCY);
    printString("] ");
    if(isChained())
      printString(" chained ");
    if(isFree())
      printString(" free ");
    printNewline();
  }
#endif
}
