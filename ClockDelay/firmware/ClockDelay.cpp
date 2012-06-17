#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "DiscreteController.h"
#include "ContinuousController.h"

#define CLOCKDELAY_CONTROLLER_DELTA 0.001

inline bool clockIsHigh(){
  return !(CLOCKDELAY_CLOCK_PINS & _BV(CLOCKDELAY_CLOCK_PIN));
}

inline bool resetIsHigh(){
  return !(CLOCKDELAY_RESET_PINS & _BV(CLOCKDELAY_RESET_PIN));
}

inline bool isCountMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

inline bool isDelayMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

enum OperatingMode {
  DISABLED_MODE                   = 0,
  DIVIDE_AND_DELAY_MODE           = 1,
  DIVIDE_AND_COUNT_MODE           = 2,
  SWING_MODE                      = 3
};

volatile OperatingMode mode;

inline void updateMode(){
  if(isCountMode()){
    mode = DIVIDE_AND_COUNT_MODE;
  }else if(isDelayMode()){
    mode = DIVIDE_AND_DELAY_MODE;
  }else{
    mode = SWING_MODE;
  }
}

class ClockCounter {
public:
  inline void reset(){
    pos = 0;
  }
  bool next(){
    if(++pos >= value){
      pos = 0;
      return true;
    }
    return false;
  }
public:
  uint8_t pos;
  uint8_t value;
  void rise(){
    if(next())
      on();
    else
      off();
  }
  inline void fall(){
    off();
  }
  inline bool isOff(){
    return DELAY_OUTPUT_PINS & _BV(DELAY_OUTPUT_PIN);
  }
  inline void on(){
    DELAY_OUTPUT_PORT &= ~_BV(DELAY_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_3_PIN);
  }
  inline void off(){
    DELAY_OUTPUT_PORT |= _BV(DELAY_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_3_PIN);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
  }
#endif
};

ClockCounter counter;

class ClockDivider {
public:
  inline void reset(){
    pos = value;
  }
  bool next(){
    if(++pos >= value){
      pos = 0;
      return true;
    }
    return false;
  }
public:
  uint8_t pos;
  uint8_t value;
  inline bool isOff(){
    return DIVIDE_OUTPUT_PINS & _BV(DIVIDE_OUTPUT_PIN);
  }
  void rise(){
    if(isOff() && next())
      on();
  }
  void fall(){
    if(!isOff() && next())
      off();
  }
  void on(){
    DIVIDE_OUTPUT_PORT &= ~_BV(DIVIDE_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_2_PIN);
  }
  void off(){
    DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_2_PIN);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
  }
#endif
};

class ClockDelay {
public:
  uint16_t riseMark;
  uint16_t fallMark;
  uint16_t value;
  volatile uint16_t pos;
  volatile bool running;
  inline void start(){
    pos = 0;
    running = true;
  }
  inline void stop(){
    running = false;
  }
  inline void reset(){
    stop();
  }
  inline void rise(){
    riseMark = value;
    start();
  }
  inline void fall(){
    fallMark = riseMark+pos;
  }
  inline bool isOff(){
    return DELAY_OUTPUT_PINS & _BV(DELAY_OUTPUT_PIN);
  }
  inline void clock(){
    if(running){
      if(pos > fallMark){
	off();
	stop(); // one-shot
      }else if(++pos > riseMark){
	on();
      }
    }
  }
  virtual void on(){
    DELAY_OUTPUT_PORT &= ~_BV(DELAY_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_3_PIN);
  }
  virtual void off(){
    DELAY_OUTPUT_PORT |= _BV(DELAY_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_3_PIN);
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
  }
#endif
};

class ClockSwing : public ClockDelay {
  void on(){
    COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN);
  }
 void off(){
    COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
  }
};

ClockDivider divider;
ClockDelay delay; // manually triggered from Timer0 interrupt
ClockSwing swinger;

class DelayController : public ContinuousController {
public:
  ClockDelay* delay;
  void hasChanged(float v){
    delay->value = v*1023;
  }
};

class CounterController : public DiscreteController {
public:
  ClockCounter* counter;
  void hasChanged(int8_t v){
    counter->value = v;
  }
};

class DividerController : public DiscreteController {
public:
  ClockDivider* divider;
  void hasChanged(int8_t v){
    divider->value = v+1;
  }
};

DelayController delayControl;
DelayController swingControl;
DividerController dividerControl;
CounterController counterControl;

void setup(){
  cli();

  // define hardware interrupts 0 and 1
//   EICRA = (1<<ISC10) | (1<<ISC01) | (1<<ISC00); // trigger int0 on rising edge
  EICRA = (1<<ISC10) | (1<<ISC01);
  // trigger int0 on the falling edge, since input is inverted
  // trigger int1 on any logical change.
  // pulses that last longer than one clock period will generate an interrupt.
  EIMSK =  (1<<INT1) | (1<<INT0); // enables INT0 and INT1
  CLOCKDELAY_CLOCK_DDR &= ~_BV(CLOCKDELAY_CLOCK_PIN);
  CLOCKDELAY_CLOCK_PORT |= _BV(CLOCKDELAY_CLOCK_PIN); // enable pull-up resistor

  CLOCKDELAY_RESET_DDR &= ~_BV(CLOCKDELAY_RESET_PIN);
  CLOCKDELAY_RESET_PORT |= _BV(CLOCKDELAY_RESET_PIN); // enable pull-up resistor

  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_A);
  MODE_SWITCH_DDR &= ~_BV(MODE_SWITCH_PIN_B);
  MODE_SWITCH_PORT |= _BV(MODE_SWITCH_PIN_B);

  DIVIDE_OUTPUT_DDR |= _BV(DIVIDE_OUTPUT_PIN);
  DELAY_OUTPUT_DDR |= _BV(DELAY_OUTPUT_PIN);
  COMBINED_OUTPUT_DDR |= _BV(COMBINED_OUTPUT_PIN);
  CLOCKDELAY_LEDS_DDR |= _BV(CLOCKDELAY_LED_1_PIN);
  CLOCKDELAY_LEDS_DDR |= _BV(CLOCKDELAY_LED_2_PIN);
  CLOCKDELAY_LEDS_DDR |= _BV(CLOCKDELAY_LED_3_PIN);

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
//   TCCR0B |= _BV(CS01);  // prescaler: 8
  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);

//   delay.minimum = 1.0; // 1Hz
//   delay.maximum = 512.0; // 512Hz, period apprx 2ms
//   delay.setDutyCycle(0.5);

  delayControl.delay = &delay;
  delayControl.delta = CLOCKDELAY_CONTROLLER_DELTA;

  swingControl.delay = &swinger;
  swingControl.delta = CLOCKDELAY_CONTROLLER_DELTA;

  dividerControl.divider = &divider;
  dividerControl.range = 16;
  dividerControl.value = -1;

  counterControl.counter = &counter;
  counterControl.range = 16;
  counterControl.value = -1;

  setup_adc();

  divider.reset();
  counter.reset();
  delay.reset();
  swinger.reset();
  updateMode();

  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

/* Timer 0 overflow interrupt */
ISR(TIMER0_OVF_vect){
//   if(mode != DIVIDE_AND_COUNT_MODE)
  delay.clock();
  swinger.clock();
}

/* Reset interrupt */
ISR(INT0_vect){
  divider.reset();
  counter.reset();
  delay.reset();
  swinger.reset();
  // hold everything until reset is released
  while(resetIsHigh());
}

/* Clock interrupt */
ISR(INT1_vect){
  if(clockIsHigh()){
    divider.rise();
    switch(mode){
    case SWING_MODE:
      if(divider.pos == 0)
	swinger.rise();
      else
	COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN); // pass through clock
      break;
    case DIVIDE_AND_COUNT_MODE:
      counter.rise();
      if(!divider.isOff() && !counter.isOff())
	COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN);
      break;
    case DIVIDE_AND_DELAY_MODE:
      delay.rise();
      if(!divider.isOff())
	swinger.rise();
      break;
    }
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_1_PIN);
  }else{
    switch(mode){
    case SWING_MODE:
      if(divider.pos == 0)
	swinger.fall();
      else
	COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN); // pass through clock
      break;
    case DIVIDE_AND_COUNT_MODE:
      counter.fall();
      COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
      break;
    case DIVIDE_AND_DELAY_MODE:
      delay.fall();
      if(!divider.isOff())
	swinger.fall();
      break;
    }
    divider.fall();
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_1_PIN);
  }
}

void loop(){
  updateMode();
  dividerControl.update(getAnalogValue(DIVIDE_ADC_CHANNEL));
  counterControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  delayControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  swingControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    switch(serialRead()){
    case '.':
      CLOCKDELAY_CLOCK_PORT ^= ~_BV(CLOCKDELAY_CLOCK_PIN);
      INT1_vect();
//       CLOCKDELAY_CLOCK_PORT &= ~_BV(CLOCKDELAY_CLOCK_PIN);
//       INT1_vect();
//       CLOCKDELAY_CLOCK_PORT |= _BV(CLOCKDELAY_CLOCK_PIN);
//       INT1_vect();
      break;
    case ':':
      CLOCKDELAY_RESET_PORT &= ~_BV(CLOCKDELAY_RESET_PIN);
      TIMER0_OVF_vect();
      CLOCKDELAY_RESET_PORT |= _BV(CLOCKDELAY_RESET_PIN);
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
    delay.dump();
    printString("] ");
    printString("swing[");
    swinger.dump();
    printString("] ");
    printBinary(DELAY_OUTPUT_PINS);
    switch(mode){
    case DIVIDE_AND_COUNT_MODE:
      printString(" count ");
      break;
    case DIVIDE_AND_DELAY_MODE:
      printString(" delay ");
      break;
    case SWING_MODE:
      printString(" swing ");
      break;
    }
    printNewline();
  }
#endif
}
