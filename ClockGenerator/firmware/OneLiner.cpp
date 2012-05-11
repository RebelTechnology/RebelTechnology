#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "DiscreteController.h"
#include "OneLineFormulas.h"

// #define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

static uint16_t timer0prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer1prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer2prescalers[] = {1, 8, 32, 64, 128, 256, 1024};


inline bool isSwitchUp(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_B));
}

inline bool isSwitchDown(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_A));
}

uint8_t bank;
uint8_t program;
uint8_t index;
uint16_t toplimit;
uint32_t time = 0;

void updateIndex(){
  index = bank*8+program+1;
}

void setPrescaler(uint8_t divisor){
  TCCR2B = (TCCR2B & 0xf8) | (divisor & 0x07);
}

class BankController : public DiscreteController {
  void hasChanged(int8_t v){
    bank = v;
    updateIndex();
  }
};

class ProgramController : public DiscreteController {
  void hasChanged(int8_t v){
    program = v;
    updateIndex();
  }
};

class PrescalerController : public DiscreteController {
  void hasChanged(int8_t v){
    setPrescaler(v+1);
  }
};

BankController bankControl;
ProgramController programControl;
PrescalerController prescalerControl;

void setup(){
  cli();

  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_A);
  GENERATOR_SWITCH_DDR &= ~_BV(GENERATOR_SWITCH_PIN_B);
  GENERATOR_SWITCH_PORT |= _BV(GENERATOR_SWITCH_PIN_B);
  TIMER1_DDR_A |= _BV(TIMER1_OUTPUT_A);
  TIMER1_DDR_B |= _BV(TIMER1_OUTPUT_B);
  TIMER2_DDR_A |= _BV(TIMER2_OUTPUT_A);
  TIMER2_DDR_B |= _BV(TIMER2_OUTPUT_B);

  bankControl.range = 8;
  programControl.range = 8;
  prescalerControl.range = 7;
  index = 0;
  bank = 0;
  program = 0;
  toplimit = 0;
  setPrescaler(0);
  // Set WGM to mode 1, prescaler to 1:1
  // and PWM output on pin 11
//   TCCR2A = 0x81;
//   TCCR2A = _BV(COM2A1) | _BV(WGM20);
  // also toggle OC2B
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
//   TCCR2B = 0x01;
  TCCR2B = _BV(CS20);
  // disable timer 0 interrupt, now delay() won't work
  TIMSK0 = 0x00;
  // enable timer 2 overflow interrupt only
  TIMSK2 = 0x01;
//   // WGM20 | WGM22 : PWM, Phase Correct, OCRA top
//   TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
//   TCCR2B = _BV(WGM22) | divisor;

  setup_adc();
  sei();

#ifdef SERIAL_DEBUG
  beginSerial(9600);
  printString("hello\n");
#endif
}

void loop(){
  bankControl.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  programControl.update(getAnalogValue(GENERATOR_DUTY_A_CONTROL));
  prescalerControl.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  if(isSwitchUp()){
    time = 0;
  }else if(isSwitchDown()){
    time = 0;
    index = 1;
    cli();
    while(isSwitchDown()); // wait
    sei();
  }
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("index ");
    printInteger(index);
    printString(" pre ");
    printInteger(prescalerControl.value);
    printString(" top ");
    printInteger(toplimit);
    if(isSwitchUp())
      printString(" up ");
    if(isSwitchDown())
      printString(" down ");
    printNewline();
  }
#endif
}

ISR(TIMER2_OVF_vect) {
  // set top limit
  OCR2A = toplimit;
  OCR2B = toplimit;
  uint16_t out = calculate(index, time++);
//   // make the LED blink
//   PORTB = out & 0x20;
  // convert from u-law to linear
  out = ~out;
  toplimit = ((out & 0x0f) << 3) + 0x84;
  toplimit <<= ((unsigned)out & 0x70) >> 4;
  toplimit = ((out & 0x80) ? (0x84 - toplimit) : (toplimit - 0x84));
  toplimit >>= 8;
}  
