#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"

/* swapped dur and mul so that order from top is:
   Modulate (pulse width modulation)
   Multiply
   Repeat
*/
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
    }else if(pos >= fallMark){
      off();
      pos = 0;
    }
  }
  void setMultiplier(uint16_t value){
    value >>= 6; // value /= 64;
    if(value != muls){
      riseMark = riseMark*muls/value;
      fallMark = fallMark*muls/value;
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
    period = fallMark = pos = 0;
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
  ClockRepeater(uint16_t* p):
    period(p){
    reset();
  }
  uint16_t* period;
  uint16_t riseMark;
  uint16_t fallMark;
  uint8_t reps;
  volatile uint8_t times;
  volatile uint16_t pos;
  volatile bool running;
  inline void start(){
    on();
    times = 0;
    riseMark = *period;
    pos = riseMark;
    fallMark = riseMark << 1; // riseMark * 2;
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
  }
  inline void fall(){
    //    stop();
  }
  inline void clock(){
    if(running){
      if(++pos == riseMark){
	on();
      }else if(pos >= fallMark){
	off();
	pos = 0;
	if(times++ >= reps)
	  stop();
      }
    }
  }
  void setRepetitions(uint16_t value){
    reps = value >> 6; // value / 64;
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
    printString(", period ");
    printInteger(*period);
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
ClockRepeater rep(&mul.riseMark);

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

  setup_adc();
  reset();

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
}

/* INT0/PD2 interrupt */
ISR(INT0_vect){
  if(durIsHigh())
    dur.rise();
  else
    dur.fall();
}

/* INT1/PD3 interrupt */
ISR(INT1_vect){
  if(mulIsHigh()){
    mul.rise();
  }else{
    mul.fall();
  }
}

void loop(){
  // todo: use StiffValue for hysteresis
  dur.setDuration(getAnalogValue(DURCV_ADC_CHANNEL));
  mul.setMultiplier(getAnalogValue(MULCV_ADC_CHANNEL));
  rep.setRepetitions(getAnalogValue(REPCV_ADC_CHANNEL));

  static int repstate = 0;
  int isrep = repIsHigh();
  if(isrep != repstate){
    if(isrep)
      rep.rise();
    else
      rep.fall();
    repstate = isrep;
  }

#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    switch(serialRead()){
    case ',':
      CLOCKMULTIPLIER_DURIN_PORT ^= _BV(CLOCKMULTIPLIER_DURIN_PIN);
      INT0_vect();
      break;
    case '.':
      CLOCKMULTIPLIER_MULIN_PORT ^= _BV(CLOCKMULTIPLIER_MULIN_PIN);
      INT1_vect();
      break;
    case '/':
      CLOCKMULTIPLIER_REPIN_PORT ^= _BV(CLOCKMULTIPLIER_REPIN_PIN);
      break;
    }
    printString("dur[");
    dur.dump();
    printString("] mul[");
    mul.dump();
    printString("] rep[");
    rep.dump();
    printString("]");
    printNewline();
  }
#endif
}
