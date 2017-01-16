#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "Timer.h"
#include "adc_freerunner.h"
// #include "ContinuousController.h"

#define GENERATOR_CONTROLLER_DELTA 0.001
typedef uint32_t ClockTick;

const ClockTick FREQ_RANGE = 2666;
const ClockTick FREQ_MIN = 666;
const ClockTick FREQ_TICKS_PER_MILLIHZ = 1920L*1000L*2;
const ClockTick FREQ_TICKS_MAX_DUTY = 384*2;
const int B_MULTIPLIERS[] = { 48/6, 48/5, 48/4, 48/3, 48/2, 48*1, 48*2, 48*3, 48*4, 48*5, 48*6 };
const int C_MULTIPLIERS[] = { 48/24, 48/16, 48/8, 48/4, 48/2, 48*1, 48*2, 48*4, 48*8, 48*16, 48*24 };

// #define FAST_MULTIPLIER        (F_CPU / (64*16ull))
#define FAST_MULTIPLIER        (F_CPU / (64*64ull))
#define MEDIUM_MULTIPLIER      (F_CPU / (64*256ull))
#define SLOW_MULTIPLIER        (F_CPU / (64*4096ull))

#define CLOCK_TYPE_A 1
#define CLOCK_TYPE_B 2
#define CLOCK_TYPE_C 3

void reset();

template<uint8_t TYPE>
class ClockGenerator {
private:
public:
  volatile ClockTick period;
  volatile ClockTick duty;
  volatile ClockTick pos;
  void setPeriod(ClockTick ticks){
    duty = ticks>>1;
    period = ticks-1;
  }
  void resetPhase(){
    pos = -1;
    on();
  }
  void clock(){
    if(++pos == duty){
      off();
    }
    if(pos > period){
      pos = 0;
      on();
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
  reset();
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

class MasterClock {
private:
public:
volatile bool resetB = false;
volatile bool resetC = false;
  volatile ClockTick period;
  const ClockTick duty = FREQ_TICKS_MAX_DUTY; // max 100mS (2*1920 / 10)
  ClockTick pos;
  ClockTick uptime;
  void setPeriod(ClockTick ticks){
    period = ticks;
  }
  void off(){
    clockA.off();
    clockB.off();
    clockC.off();
  }
  void clock(){
    // if(uptime++ == duty){
    //   uptime = pos;
    //   off();
    // }
    if(++pos > period){
      pos = 0;
      clockA.clock();
      clockB.clock();
      clockC.clock();
    }
  }
  void reset(){
    if(resetB){
      clockB.resetPhase();
      resetB = false;
    }
    if(resetC){
      clockC.resetPhase();
      resetC = false;
    }
  }
};

MasterClock master;

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

  clockA.setPeriod(48);
  setup_adc();

  sei();
}

ClockTick mulB = 5;
ClockTick mulC = 5;
void loop(){
  ClockTick a, b, c;
  a = (getAnalogValue(GENERATOR_RATE_A_CONTROL) * FREQ_RANGE)/ADC_VALUE_RANGE + FREQ_MIN;
  b = (getAnalogValue(GENERATOR_RATE_B_CONTROL) * 11) / ADC_VALUE_RANGE;
  if(b != mulB){
    mulB = b;
    master.resetB = true;
  }
  // if(b > 5)
  //   b = a*(b-4);
  // else if(b < 5)
  //   b = a/(6-b);
  // else
  //   b = a;
  c = (getAnalogValue(GENERATOR_RATE_C_CONTROL) * 11) / ADC_VALUE_RANGE;
  if(c != mulC){
    mulC = c;
    master.resetC = true;
  }
  // if(c > 5){
  //   c = MULTIPLIERS[c-6];
  //   c = a*c;
  // }else if(c < 5){
  //   c = MULTIPLIERS[4-c];
  //   c = a/c;
  // }else
  //   c = a;
  a = FREQ_TICKS_PER_MILLIHZ / (a*48);
  // b = FREQ_TICKS_PER_MILLIHZ / b;
  // c = FREQ_TICKS_PER_MILLIHZ / c;
  b = B_MULTIPLIERS[10-b];
  c = C_MULTIPLIERS[10-c];

  master.setPeriod(a);
  clockB.setPeriod(b);
  clockC.setPeriod(c);
}

ISR(TIMER0_OVF_vect){
  master.clock();
}

void reset(){
  master.reset();
}
