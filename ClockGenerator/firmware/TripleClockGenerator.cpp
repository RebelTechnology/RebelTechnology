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
    if(++pos > period){
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
  GENERATOR_OUTB_PORT |= _BV(GENERATOR_OUTB_PIN);
}
template<> bool ClockGenerator<CLOCK_TYPE_B>::isOff(){
  return GENERATOR_OUTB_PORT & _BV(GENERATOR_OUTB_PIN);
}

template<> void ClockGenerator<CLOCK_TYPE_C>::on(){
  GENERATOR_OUTC_PORT &= ~_BV(GENERATOR_OUTC_PIN);
}
template<> void ClockGenerator<CLOCK_TYPE_C>::off(){
  GENERATOR_OUTC_PORT |= _BV(GENERATOR_OUTC_PIN);
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

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.

  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  // TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64
  // TCCR0B |= _BV(CS01);  // prescaler: 8
  TCCR0B |= _BV(CS00);  // prescaler: 1
  TIMSK0 |= _BV(TOIE0); // enable timer 0 overflow interrupt
  OCR0A = 0;

  setup_adc();

  sei();
}

ClockTick a, b, c;
const ClockTick FREQ_RANGE = 2666;
const ClockTick FREQ_MIN = 666;
const ClockTick FREQ_TICKS_PER_MILLIHZ = 1920L*1000L;
const int MULTIPLIERS[] = { 2, 4, 8, 16, 24 };
void loop(){
  a = (getAnalogValue(GENERATOR_RATE_A_CONTROL) * FREQ_RANGE)/ADC_VALUE_RANGE + FREQ_MIN;
  b = (getAnalogValue(GENERATOR_RATE_B_CONTROL) * 11) / ADC_VALUE_RANGE;
  if(b > 5)
    b = a*(b-4);
  else if(b < 5)
    b = a/(6-b);
  else
    b = a;
  c = (getAnalogValue(GENERATOR_RATE_C_CONTROL) * 11) / ADC_VALUE_RANGE;
  if(c > 5){
    c = MULTIPLIERS[c-6];
    c = a*c;
  }else if(c < 5){
    c = MULTIPLIERS[4-c];
    c = a/c;
  }else{
    c = a;
  }
  a = FREQ_TICKS_PER_MILLIHZ / a;
  b = FREQ_TICKS_PER_MILLIHZ / b;
  c = FREQ_TICKS_PER_MILLIHZ / c;
  clockA.period = a;
  clockB.period = b;
  clockC.period = c;
}

ISR(TIMER0_OVF_vect){
  clockA.clock();
  clockB.clock();
  clockC.clock();
}
