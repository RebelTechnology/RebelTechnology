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
// #include "ContinuousController.h"

#define GENERATOR_CONTROLLER_DELTA 0.001
typedef uint32_t ClockTick;

// #define FAST_MULTIPLIER        (F_CPU / (64*16ull))
#define FAST_MULTIPLIER        (F_CPU / (64*64ull))
#define MEDIUM_MULTIPLIER      (F_CPU / (64*256ull))
#define SLOW_MULTIPLIER        (F_CPU / (64*4096ull))

// FrequencyController rateA;
// FrequencyController rateB;
// FrequencyController rateC;

#define CLOCK_TYPE_A 1
#define CLOCK_TYPE_B 2
#define CLOCK_TYPE_C 3

template<uint8_t TYPE>
class ClockGenerator {
private:
public:
  ClockTick period;
  ClockTick pos;
  void clock(){
    if(pos++ > period){
      toggle();
      pos = 0;
    }
  }
  void toggle(){
    if(isOff())
      on();
    else
      off();
  }
  void on();
  void off();
  bool isOff();
};

template<> void ClockGenerator<CLOCK_TYPE_A>::on(){
  GENERATOR_OUTA_PORT &= ~_BV(GENERATOR_OUTA_PIN);
}
template<> void ClockGenerator<CLOCK_TYPE_A>::off(){
  GENERATOR_OUTA_PORT |= _BV(GENERATOR_OUTA_PIN);
}
template<> bool ClockGenerator<CLOCK_TYPE_A>::isOff(){
  return GENERATOR_OUTA_PORT & _BV(GENERATOR_OUTA_PIN);
}

template<> void ClockGenerator<CLOCK_TYPE_B>::on(){
  GENERATOR_OUTB_PORT &= ~_BV(GENERATOR_OUTB_PIN);
}
template<> void ClockGenerator<CLOCK_TYPE_B>::off(){
  GENERATOR_OUTB_PORT |= _BV(GENERATOR_OUTA_PIN);
}
template<> bool ClockGenerator<CLOCK_TYPE_B>::isOff(){
  return GENERATOR_OUTB_PORT & _BV(GENERATOR_OUTB_PIN);
}

template<> void ClockGenerator<CLOCK_TYPE_C>::on(){
  GENERATOR_OUTC_PORT &= ~_BV(GENERATOR_OUTC_PIN);
}
template<> void ClockGenerator<CLOCK_TYPE_C>::off(){
  GENERATOR_OUTC_PORT |= _BV(GENERATOR_OUTA_PIN);
}
template<> bool ClockGenerator<CLOCK_TYPE_C>::isOff(){
  return GENERATOR_OUTC_PORT & _BV(GENERATOR_OUTC_PIN);
}

// class ClockController : public ContinuousController {
// public:
//   virtual void hasChanged(float v){
//     // timer->setRate(v);
//   }
// };

ClockGenerator<CLOCK_TYPE_A> clockA;
ClockGenerator<CLOCK_TYPE_B> clockB;
ClockGenerator<CLOCK_TYPE_C> clockC;

void setup(){
  cli();

  GENERATOR_OUTA_DDR |= _BV(GENERATOR_OUTA_PIN);
  GENERATOR_OUTB_DDR |= _BV(GENERATOR_OUTB_PIN);
  GENERATOR_OUTC_DDR |= _BV(GENERATOR_OUTC_PIN);

  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64
//   TCCR0B |= _BV(CS01);  // prescaler: 8
  TIMSK0 |= _BV(TOIE0); // enable timer 0 overflow interrupt
//   OCR0A = 0;

  // rateA.delta = GENERATOR_CONTROLLER_DELTA;
  // rateB.delta = GENERATOR_CONTROLLER_DELTA;
  // rateC.delta = GENERATOR_CONTROLLER_DELTA;

  setup_adc();

  sei();
}

void loop(){
  // rateA.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  // rateB.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  // rateC.update(getAnalogValue(GENERATOR_RATE_C_CONTROL));
  clockA.period = getAnalogValue(GENERATOR_RATE_A_CONTROL);
  clockB.period = getAnalogValue(GENERATOR_RATE_B_CONTROL);
  clockC.period = getAnalogValue(GENERATOR_RATE_C_CONTROL);
}

ISR(TIMER0_OVF_vect){
  clockA.clock();
  clockB.clock();
  clockC.clock();
}
