#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "DeadbandController.h"
#include "TapTempo.hpp"

inline bool mulIsHigh(){
  return !(CLOCKMULTIPLIER_MULIN_PINS & _BV(CLOCKMULTIPLIER_MULIN_PIN));
}
inline bool durIsHigh(){
  return !(CLOCKMULTIPLIER_DURIN_PINS & _BV(CLOCKMULTIPLIER_DURIN_PIN));
}
inline bool repIsHigh(){
  return !(CLOCKMULTIPLIER_REPIN_PINS & _BV(CLOCKMULTIPLIER_REPIN_PIN));
}

class ClockMultiplier {
public:
  uint16_t riseMark;
  uint16_t fallMark;
  uint8_t muls;
  volatile uint16_t pos;
  ClockMultiplier(){
    reset();
  }
  inline uint16_t getPeriod(){
    return riseMark;
  }
  inline void reset(){
    riseMark = fallMark = pos = 0;
    off();
  }
  inline void rise(){
    riseMark = pos / muls;
  }
  inline void fall(){
    fallMark = riseMark+pos;
  }
  inline void clock(){
    if(++pos == riseMark){
      on();
    }else if(pos == fallMark){
      off();
    }
  }
  void setMultiplier(uint16_t value){
    value /= 64;
    if(value != muls){
      riseMark = riseMark*muls/value;
      fallMark = fallMark*muls/value
      muls = value;
    }
  }
  virtual void on(){
    CLOCKMULTIPLIER_MULOUT_PORT |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
  virtual void off(){
    CLOCKMULTIPLIER_MULOUT_PORT &= ~_BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
  virtual bool isOff(){
    return CLOCKMULTIPLIER_MULOUT_PORT & _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("rise ");
    printInteger(riseMark);
    printString(", fall ");
    printInteger(fallMark);
    printString(", pos ");
    printInteger(pos);
    if(isOff())
      printString(" off");
    else
      printString(" on");
  }
#endif
};

class ClockDuration {
public:
  uint16_t period;
  uint16_t fallMark;
  uint16_t duration;
  volatile uint16_t pos;
  ClockDuration(){
    reset();
  }
  inline void reset(){
    riseMark = fallMark = pos = 0;
    off();
  }
  inline void rise(){
    period = pos;
    fallMark = (period*duration)>>10; // todo: calculate overflow condition
    pos = 0;
    on();
  }
  inline void fall(){
  }
  inline void clock(){
    if(++pos == fallMark){
      off();
    }
  }
  void setDuration(uint16_t value){
    if(value != duration){
      // wait until next trigger to recalculate fallMark
      // fallMark = (period*duration)>>10;
      duration = value;
    }
  }
  virtual void on(){
    CLOCKMULTIPLIER_DUROUT_PORT |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  }
  virtual void off(){
    CLOCKMULTIPLIER_DUROUT_PORT &= ~_BV(CLOCKMULTIPLIER_DUROUT_PIN);
  }
  virtual bool isOff(){
    return CLOCKMULTIPLIER_DUROUT_PORT & _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("period ");
    printInteger(period);
    printString(", fall ");
    printInteger(fallMark);
    printString(", pos ");
    printInteger(pos);
    if(isOff())
      printString(" off");
    else
      printString(" on");
  }
#endif
};

class ClockRepeater {
public:
  ClockRepeater(ClockMultiplier& cm):
    multiplier(cm){
    reset();
  }
  ClockMultiplier& multiplier;
  uint16_t riseMark;
  uint16_t fallMark;
  uint8_t reps;
  volatile uint8_t times;
  volatile uint16_t pos;
  volatile bool running;
  inline void start(){
    pos = 0;
    times = 0;
    riseMark = multiplier.getPeriod();
    //    riseMark = multiplier.riseMark;
    fallMark = riseMark << 1;
    //    fallMark = multiplier.fallMark;
    running = true;
  }
  inline void stop(){
    running = false;
  }
  inline void reset(){
    stop();
    off();
  }
  inline void rise(){
    start();
    on();
  }
  inline void fall(){
    stop();
  }
  inline void clock(){
    if(running){
      if(++pos == riseMark){
	on();
      }else if(pos == fallMark){
	off();
	pos = 0;
	if(times++ >= reps)
	  stop();
      }
    }
  }
  void setRepetitions(uint16_t value){
    reps = value / 64;
    // value /= 64;
    // if(value != reps){
    //   reps = value;
    // }
  }
  virtual void on(){
    CLOCKMULTIPLIER_REPOUT_PORT |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);
  }
  virtual void off(){
    CLOCKMULTIPLIER_REPOUT_PORT &= ~_BV(CLOCKMULTIPLIER_REPOUT_PIN);
  }
  virtual bool isOff(){
    return CLOCKMULTIPLIER_REPOUT_PORT & _BV(CLOCKMULTIPLIER_REPOUT_PIN);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("rise ");
    printInteger(riseMark);
    printString(", fall ");
    printInteger(fallMark);
    printString(", pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
    if(running)
      printString(" running");
    else
      printString(" stopped");
    if(isOff())
      printString(" off");
    else
      printString(" on");
  }
#endif
};

ClockMultiplier mul;
ClockDuration dur;
ClockRepeater rep(mul);

void reset(){
  mul.reset();
  dur.reset();
  rep.reset();
}

void setup(){
  cli();

  // define hardware interrupts 0 and 1
//   EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // trigger int0 on rising edge
//  EICRA = (1<<ISC10) | (1<<ISC01);
  // trigger int0 on the falling edge, since input is inverted
  // trigger int1 on any logical change.

  // ISC01 ISC00 or ISC10 ISC11:
  //     0     0 low level triggers interrupt
  //     0     1 any logical change
  //     1     0 falling edge
  //     1     1 rising edge
  EICRA = (1<<ISC10) | (1<<ISC00); // trigger int0 and int1 on any logical change

  // pulses that last longer than one clock period will generate an interrupt.
  EIMSK =  (1<<INT1) | (1<<INT0); // enables INT0 and INT1
  CLOCKMULTIPLIER_MULIN_DDR &= ~_BV(CLOCKMULTIPLIER_MULIN_PIN);
  CLOCKMULTIPLIER_MULIN_PORT |= _BV(CLOCKMULTIPLIER_MULIN_PIN); // enable pull-up resistor
  CLOCKMULTIPLIER_DURIN_DDR &= ~_BV(CLOCKMULTIPLIER_DURIN_PIN);
  CLOCKMULTIPLIER_DURIN_PORT |= _BV(CLOCKMULTIPLIER_DURIN_PIN); // enable pull-up resistor
  CLOCKMULTIPLIER_REPIN_DDR &= ~_BV(CLOCKMULTIPLIER_REPIN_PIN);
  CLOCKMULTIPLIER_REPIN_PORT |= _BV(CLOCKMULTIPLIER_REPIN_PIN); // enable pull-up resistor

  CLOCKMULTIPLIER_MULOUT_DDR |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  CLOCKMULTIPLIER_DUROUT_DDR |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  CLOCKMULTIPLIER_REPOUT_DDR |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);

  CLOCKMULTIPLIER_MULOUT_PORT |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  CLOCKMULTIPLIER_DUROUT_PORT |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  CLOCKMULTIPLIER_REPOUT_PORT |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
//   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
  TCCR0B |= _BV(CS01);  // prescaler: 8
  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);

//   dividerControl.range = 33;
  dividerControl.value = -1;
//   counterControl.range = 33;
  counterControl.value = -1;

  setup_adc();
  reset();
  updateMode();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

/* Timer 0 overflow interrupt */
ISR(TIMER0_OVF_vect){
  mul.clock();
  dur.clock();
  rep.clock();
  tempo.clock();
}

/* INT0/PD2 interrupt */
ISR(INT0_vect){
  if(mulIsHigh()){
    mul.rise();
    tempo.trigger(true);
  }else{
    mul.fall();
    tempo.trigger(false);
  }
}

/* INT1/PD3 interrupt */
ISR(INT1_vect){
  if(durIsHigh())
    dur.rise();
  else
    dur.fall();
}

void loop(){
  mul.setMultiplier(getAnalogValue(MULCV_ADC_CHANNEL));
  dur.setDuration(getAnalogValue(DURCV_ADC_CHANNEL));
  rep.setRepetitions(getAnalogValue(REPCV_ADC_CHANNEL));

  static int durstate = 0;
  int isdur = durIsHigh();
  if(isdur != durstate){
    if(isdur)
      dur.rise();
    else
      dur.fall();
    durstate = isdur;
  }
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    switch(serialRead()){
    case '.':
      CLOCKMULTIPLIER_CLOCK_PORT ^= _BV(CLOCKMULTIPLIER_CLOCK_PIN);
      INT1_vect();
      break;
    case ':':
      CLOCKMULTIPLIER_RESET_PORT &= ~_BV(CLOCKMULTIPLIER_RESET_PIN);
      TIMER0_OVF_vect();
      CLOCKMULTIPLIER_RESET_PORT |= _BV(CLOCKMULTIPLIER_RESET_PIN);
      TIMER0_OVF_vect();
      break;
    }      
    printString("div[");
    divider.dump();
    printString("] ");
    printString("cnt[");
    counter.dump();
    printString("] ");
    printString("del[");
    multiplier.dump();
    printString("] ");
    printString("swing[");
    swinger.dump();
    printString("] ");
    printBinary(MULTIPLIER_OUTPUT_PINS);
    switch(mode){
    case DIVIDE_MODE:
      printString(" count ");
      break;
    case MULTIPLIER_MODE:
      printString(" multiplier ");
      break;
    }
    printNewline();
  }
#endif
}
