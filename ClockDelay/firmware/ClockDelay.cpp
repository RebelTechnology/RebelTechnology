//#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "DiscreteController.h"

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
  DIVIDE_MODE                     = 1,
  DELAY_MODE                      = 2
};

class ClockCounter {
public:
  inline void reset(){
    pos = 0;
  }
  bool next(){
    if(++pos > value){
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
  virtual bool isOff(){
    return DELAY_OUTPUT_PINS & _BV(DELAY_OUTPUT_PIN);
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
    printString("pos ");
    printInteger(pos);
    printString(", value ");
    printInteger(value);
    if(isOff())
      printString(" off");
    else
      printString(" on");
  }
#endif
};

class ClockDivider {
public:
  inline void reset(){
    pos = 0;
    toggled = false;
  }
  bool next(){
    if(++pos > value){
      pos = 0;
      return true;
    }
    return false;
  }
public:
  uint8_t pos;
  uint8_t value;
  bool toggled;
  inline bool isOff(){
    return DIVIDE_OUTPUT_PINS & _BV(DIVIDE_OUTPUT_PIN);
  }
  void rise(){
    if(next()){
      toggle();
      toggled = true;
    }
  }
  void fall(){
    if(value == 0)
      off();
  }
  void toggle(){
    DIVIDE_OUTPUT_PORT ^= _BV(DIVIDE_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT ^= _BV(CLOCKDELAY_LED_2_PIN);
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
    if(isOff())
      printString(" off");
    else
      printString(" on");
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
    fallMark = 0;
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
  inline void clock(){
    if(running){
      if(++pos == riseMark){
	on();
      }else if(pos == fallMark){
	off();
	stop(); // one-shot
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
  virtual bool isOff(){
    return DELAY_OUTPUT_PINS & _BV(DELAY_OUTPUT_PIN);
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

class ClockSwing : public ClockDelay {
public:
  void on(){
    COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_1_PIN);
  }
 void off(){
    COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_1_PIN);
  }
  bool isOff(){
    return COMBINED_OUTPUT_PINS & _BV(COMBINED_OUTPUT_PIN);
  }
};

class DividingCounter : public ClockCounter {
public:
  void on(){
    COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_1_PIN);
  }
 void off(){
    COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
    CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_1_PIN);
  }
  bool isOff(){
    return COMBINED_OUTPUT_PINS & _BV(COMBINED_OUTPUT_PIN);
  }
};

ClockCounter counter;
ClockDivider divider;
ClockDelay delay; // manually triggered from Timer0 interrupt
ClockSwing swinger;
DividingCounter divcounter;

class DelayController {
public:
  void update(uint16_t value){
    value = (value>>2)+1; // divide by 4, add 1
    delay.value = value;
    swinger.value = value;
  }
};

class CounterController : public DiscreteController {
public:
  void hasChanged(int8_t v){
    counter.value = v;
    divcounter.value = v;
  }
};

class DividerController : public DiscreteController {
public:
  void hasChanged(int8_t v){
    divider.value = v;
  }
};

DelayController delayControl;
DividerController dividerControl;
CounterController counterControl;

void reset(){
  divider.reset();
  counter.reset();
  divcounter.reset();
  delay.reset();
  swinger.reset();
  DIVIDE_OUTPUT_PORT   |= _BV(DIVIDE_OUTPUT_PIN);
  DELAY_OUTPUT_PORT    |= _BV(DELAY_OUTPUT_PIN);
  COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
  CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_1_PIN);
  CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_2_PIN);
  CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_3_PIN);
}

volatile OperatingMode mode;

inline void updateMode(){
  if(isCountMode()){
    mode = DIVIDE_MODE;
  }else if(isDelayMode()){
    cli();
    reset();
    while(isDelayMode());
    sei();
  }else{
    mode = DELAY_MODE;
  }
}

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

  DIVIDE_OUTPUT_PORT |= _BV(DIVIDE_OUTPUT_PIN);
  DELAY_OUTPUT_PORT |= _BV(DELAY_OUTPUT_PIN);
  COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN);
  CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_1_PIN);
  CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_2_PIN);
  CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_3_PIN);

  // At 16MHz CPU clock and prescaler 64, Timer 0 should run at 1024Hz.
  // configure Timer 0 to Fast PWM, 0xff top.
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
//   TCCR0B |= _BV(CS01) | _BV(CS00); // prescaler: 64.
  TCCR0B |= _BV(CS01);  // prescaler: 8
  // enable timer 0 overflow interrupt
  TIMSK0 |= _BV(TOIE0);

  dividerControl.range = 16;
  dividerControl.value = -1;
  counterControl.range = 16;
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
  delay.clock();
  swinger.clock();
}

/* Reset interrupt */
ISR(INT0_vect){
  reset();  
  // hold everything until reset is released
  while(resetIsHigh());
}

/* Clock interrupt */
ISR(INT1_vect){
  if(clockIsHigh()){
    divider.rise();
    switch(mode){
    case DELAY_MODE:
      delay.rise();
      if(divider.toggled){
	swinger.rise();
      }else{
	COMBINED_OUTPUT_PORT &= ~_BV(COMBINED_OUTPUT_PIN); // pass through clock
	CLOCKDELAY_LEDS_PORT |= _BV(CLOCKDELAY_LED_1_PIN);
      }
      break;
    case DIVIDE_MODE:
      counter.rise();
      if(divider.toggled){
	divcounter.rise();
	if(!divcounter.isOff())
	  divider.toggled = false;
      }
      break;
    }
  }else{
    switch(mode){
    case DELAY_MODE:
      delay.fall();
      if(divider.toggled){
	swinger.fall();
	divider.toggled = false;
      }else{
	COMBINED_OUTPUT_PORT |= _BV(COMBINED_OUTPUT_PIN); // pass through clock
	CLOCKDELAY_LEDS_PORT &= ~_BV(CLOCKDELAY_LED_1_PIN);
      }
      break;
    case DIVIDE_MODE:
      counter.fall();
      divcounter.fall();
      break;
    }
    divider.fall();
  }
}

void loop(){
  updateMode();
  dividerControl.update(getAnalogValue(DIVIDE_ADC_CHANNEL));
  counterControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  delayControl.update(getAnalogValue(DELAY_ADC_CHANNEL));
  
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
    case DIVIDE_MODE:
      printString(" count ");
      break;
    case DELAY_MODE:
      printString(" delay ");
      break;
    }
    printNewline();
  }
#endif
}
