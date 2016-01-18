//#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"

#ifndef UINT16_MAX
#define UINT16_MAX 65535
#endif

typedef uint32_t ClockTick;

inline bool mulIsHigh(){
  return !(CLOCKMULTIPLIER_MULIN_PINS & _BV(CLOCKMULTIPLIER_MULIN_PIN));
}
inline bool durIsHigh(){
  return !(CLOCKMULTIPLIER_DURIN_PINS & _BV(CLOCKMULTIPLIER_DURIN_PIN));
}
inline bool repIsHigh(){
  return !(CLOCKMULTIPLIER_REPIN_PINS & _BV(CLOCKMULTIPLIER_REPIN_PIN));
}

class ClockDuration {
public:
  ClockTick period;
  ClockTick fallMark;
  uint16_t duration;
  volatile ClockTick pos;
  ClockDuration(){
    reset();
  }
  inline void reset(){
    period = fallMark = pos = 0;
    off();
  }
  inline void rise(){
    period = pos;
    fallMark = ((uint32_t)period*duration)>>12;
    pos = 0;
    on();
  }
  inline void fall(){
  }
  inline void clock(){
    if(++pos >= fallMark){
      off();
    }
  }
  void setDuration(uint16_t value){
    if(value != duration){
      // wait until next trigger to recalculate fallMark
      // fallMark = (period*duration)>>11;
      duration = value;
    }
  }
  void on(){
    CLOCKMULTIPLIER_DUROUT_PORT &= ~_BV(CLOCKMULTIPLIER_DUROUT_PIN);
    CLOCKMULTIPLIER_LED1_PORT &= ~_BV(CLOCKMULTIPLIER_LED1_PIN);
  }
  void off(){
    CLOCKMULTIPLIER_DUROUT_PORT |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
    CLOCKMULTIPLIER_LED1_PORT |= _BV(CLOCKMULTIPLIER_LED1_PIN);
  }
  bool isOff(){
    return CLOCKMULTIPLIER_DUROUT_PORT & _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  }
#ifdef SERIAL_DEBUG
  void dump(){
    printString("period ");
    printInteger(period);
    printString(", duration ");
    printInteger(duration);
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

class ClockMultiplier {
public:
  ClockTick riseMark;
  ClockTick fallMark;
  uint8_t muls;
  volatile ClockTick pos;
  volatile ClockTick counter;
  ClockTick period;
  uint16_t duration;
  ClockMultiplier(){
    reset();
  }
  inline void reset(){
    riseMark = fallMark = pos = period = counter = 0;    
    off();
  }
  ClockTick getPeriod(){
    return riseMark;
  }
  inline void rise(){
    on();
    riseMark = counter / muls;
    pos = riseMark;
    //    fallMark = riseMark + (((uint32_t)riseMark*duration)>>11);
    fallMark = riseMark*2; // 50% pulse width
    period = counter;
    counter = 0;
  }
  inline void fall(){
  }
  inline void clock(){
    if(pos >= fallMark){
      off();
      pos = 0;
    }else if(++pos >= riseMark){
      on();
    }
    counter++;
  }
  void setDuration(uint16_t value){
    if(value != duration){
      duration = value;
      //      fallMark = riseMark + (((uint32_t)riseMark*duration)>>11);
    }
  }
  void setMultiplier(uint16_t value){
    value >>= 8; // range of 0 to 15
    value <<= 1; // multiply by two
    value += 2;
    if(value != muls){
      riseMark = riseMark*muls/value;
      fallMark = riseMark*2;
      //      fallMark = fallMark*muls/value;
      muls = value;
    }
  }
  void on(){
    CLOCKMULTIPLIER_MULOUT_PORT &= ~_BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
  void off(){
    CLOCKMULTIPLIER_MULOUT_PORT |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
  bool isOff(){
    return CLOCKMULTIPLIER_MULOUT_PORT & _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  }
#ifdef SERIAL_DEBUG
  void dump(){
    printString("mul ");
    printInteger(muls);
    printString(", rise ");
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

class ClockRepeater {
public:
  ClockRepeater(){
    reset();
  }
  ClockTick period;
  ClockTick riseMark;
  ClockTick fallMark;
  uint8_t reps;
  uint16_t duration;
  volatile uint8_t times;
  volatile ClockTick pos;
  volatile bool running;
  inline void start(){
    on();
    times = 0;
    riseMark = period;
    pos = riseMark;
    // fallMark = riseMark + (((uint32_t)riseMark*duration)>>11);
    fallMark = riseMark * 2;
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
      if(pos >= fallMark){
	off();
	pos = 0;
	if(++times >= reps)
	  stop();
      }else if(++pos == riseMark){
	on();
      }
    }
  }
  inline void setPeriod(ClockTick value){
    period = value;
  }
  void setDuration(uint16_t value){
    if(value != duration){
      duration = value;
      //      fallMark = riseMark + (((uint32_t)riseMark*duration)>>11);
    }
  }
  void setRepetitions(uint16_t value){
    value >>= 8; // range 0 to 15
    value += 1;
    if(value != reps){
      riseMark = riseMark*reps/value;
      //      fallMark = fallMark*reps/value;
      fallMark = riseMark * 2;
      reps = value;
    }
  }
  void on(){
    CLOCKMULTIPLIER_REPOUT_PORT &= ~_BV(CLOCKMULTIPLIER_REPOUT_PIN);
    CLOCKMULTIPLIER_LED2_PORT &= ~_BV(CLOCKMULTIPLIER_LED2_PIN);
  }
  void off(){
    CLOCKMULTIPLIER_REPOUT_PORT |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);
    CLOCKMULTIPLIER_LED2_PORT |= _BV(CLOCKMULTIPLIER_LED2_PIN);
  }
  bool isOff(){
    return CLOCKMULTIPLIER_REPOUT_PORT & _BV(CLOCKMULTIPLIER_REPOUT_PIN);
  }
#ifdef SERIAL_DEBUG
  void dump(){
    printString("reps ");
    printInteger(reps);
    printString(", rise ");
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

ClockDuration dur;
ClockMultiplier mul;
ClockRepeater rep;

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
  CLOCKMULTIPLIER_DURIN_PORT |= _BV(CLOCKMULTIPLIER_DURIN_PIN);
  CLOCKMULTIPLIER_REPIN_DDR &= ~_BV(CLOCKMULTIPLIER_REPIN_PIN);
  CLOCKMULTIPLIER_REPIN_PORT |= _BV(CLOCKMULTIPLIER_REPIN_PIN);

  CLOCKMULTIPLIER_MULOUT_DDR |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  CLOCKMULTIPLIER_DUROUT_DDR |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  CLOCKMULTIPLIER_REPOUT_DDR |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);
  CLOCKMULTIPLIER_LED1_DDR   |= _BV(CLOCKMULTIPLIER_LED1_PIN);
  CLOCKMULTIPLIER_LED2_DDR   |= _BV(CLOCKMULTIPLIER_LED2_PIN);

  CLOCKMULTIPLIER_MULOUT_PORT |= _BV(CLOCKMULTIPLIER_MULOUT_PIN);
  CLOCKMULTIPLIER_DUROUT_PORT |= _BV(CLOCKMULTIPLIER_DUROUT_PIN);
  CLOCKMULTIPLIER_REPOUT_PORT |= _BV(CLOCKMULTIPLIER_REPOUT_PIN);
  CLOCKMULTIPLIER_LED1_PORT   |= _BV(CLOCKMULTIPLIER_LED1_PIN);
  CLOCKMULTIPLIER_LED2_PORT   |= _BV(CLOCKMULTIPLIER_LED2_PIN);

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
//   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
  // TCCR0B |= _BV(CS01);  // prescaler: 8
  TCCR0B |= _BV(CS00);  // prescaler: 1
  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);

  setup_adc();
  reset();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\r\n");
#endif
}

/* Timer 0 overflow interrupt */
ISR(TIMER0_OVF_vect){
  mul.clock();
  dur.clock();
  rep.clock();
}

ISR(CLOCKMULTIPLIER_DURIN_INT){
  if(durIsHigh())
    dur.rise();
  else
    dur.fall();
}

ISR(CLOCKMULTIPLIER_MULIN_INT){
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
  mul.setDuration(getAnalogValue(DURCV_ADC_CHANNEL));
  rep.setPeriod(mul.getPeriod());
  rep.setDuration(getAnalogValue(DURCV_ADC_CHANNEL));
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
    case '<':
      adc_values[0] -= 100;
      adc_values[1] -= 100;
      adc_values[2] -= 100;
      break;
    case '>':
      adc_values[0] += 100;
      adc_values[1] += 100;
      adc_values[2] += 100;
      break;
    }
    printString("\r\ndur[");
    dur.dump();
    printString("]\r\nmul[");
    mul.dump();
    printString("]\r\nrep[");
    rep.dump();
    printString("]");
    printNewline();
  }
#endif
}
