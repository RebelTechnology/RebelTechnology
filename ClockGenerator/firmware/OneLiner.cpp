#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"
#include "DiscreteController.h"

// #define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

static uint16_t timer0prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer1prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer2prescalers[] = {1, 8, 32, 64, 128, 256, 1024};


inline bool isSwitchUp(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_A));
}

inline bool isSwitchDown(){
  return !(GENERATOR_SWITCH_PINS & _BV(GENERATOR_SWITCH_PIN_B));
}

uint8_t index;
uint16_t toplimit;

void setPrescaler(uint8_t divisor){
  TCCR2B = (TCCR2B & 0xf8) | (divisor & 0x07);
}

class IndexController : public DiscreteController {
  void hasChanged(int8_t v){
    index = v;
  }
};

class PrescalerController : public DiscreteController {
  void hasChanged(int8_t v){
    setPrescaler(v);
  }
};

IndexController indexControl;
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

  indexControl.range = 13;
  prescalerControl.range = 8;
  index = 0;
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

uint32_t t = 0;
inline uint16_t calculate(){
  uint16_t out;
  switch(index){
  case 1:
    out = t * ((t>>12|t>>8) & 63 & t >> 4);
    break;
  case 2:
    out = (t*(t>>5|t>>8))>>(t>>16);
    break;
  case 3:
    out = t*((t>>9|t>>13)&25&t>>6);
    break;
  case 4:
    out = t*(t>>11&t>>8&&123&&t>>3);
    break;
  case 5:
    out = t * ((t>>3|t>>9)&82&t>>9);
//     out = (t*(t>>8*(t>>15|t>>8)&(20|(t>>19(*5>>t|t>>3);
    break;
  case 6:
    // probably too slow to run this
    out = ((-t&4095)*(255&t*(t&t>>13))>>12)+(127&t*(234&t>>8&t>>3)>>(3&t>>14));
    break;
  case 7:
    // probably too slow to run this
    out = t*(t>>((t>>9|t>>8))&63&t>>4);
    break;
  case 8:
    out = (t>>6|t|t>>(t>>16))*10+((t>>11)&7);
    break;
  case 9:
    out = (t|(t>>9|t>>7))*t&(t>>11|t>>9);
    break;
  case 10:
    out = t*5&(t>>7)|t*3&(t*4>>10);
    break;
  case 11:
    out = (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6);
    break;
  case 12:
    // probably too slow to run this
    out = ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t));
    break;
  case 13:
    out = (t*(t%255)|(t>>4))>>3;
    break;
  }
  ++t;
  return out;
}

void loop(){
  indexControl.update(getAnalogValue(GENERATOR_RATE_A_CONTROL));
  prescalerControl.update(getAnalogValue(GENERATOR_RATE_B_CONTROL));
  if(isSwitchUp()){
    t = 0;
  }else if(isSwitchDown()){
  }
#ifdef SERIAL_DEBUG
  if(serialAvailable() > 0){
    serialRead();
    printString("index ");
    printInteger(index);
    printString(" pre ");
    printInteger(prescalerControl.value)
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
  uint16_t out = calculate();
//   // make the LED blink
//   PORTB = out & 0x20;
  // convert from u-law to linear
  out = ~out;
  toplimit = ((out & 0x0f) << 3) + 0x84;
  toplimit <<= ((unsigned)out & 0x70) >> 4;
  toplimit = ((out & 0x80) ? (0x84 - toplimit) : (toplimit - 0x84));
  toplimit >>= 8;
}  
