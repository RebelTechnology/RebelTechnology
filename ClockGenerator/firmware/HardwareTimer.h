#ifndef _HARDWARE_TIMER_H_
#define _HARDWARE_TIMER_H_

#include "Timer.h"
#include "device.h"
#include "avr/io.h"

#define FREQ_CONSTANT (F_CPU / 2)
static uint16_t timer0prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer1prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer2prescalers[] = {1, 8, 32, 64, 128, 256, 1024};

class HardwareTimer : public Timer {
public:
  virtual void setPrescaler(uint8_t divisor){}
  virtual void setTopLimit(uint16_t limit){}
  void updateFrequency(){
    uint8_t pre = getPrescaler(frequency);
    uint16_t limit = getTopLimit(frequency, pre);
    setPrescaler(pre);
    setTopLimit(limit);
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    Timer::dump();
    printString(", p ");
    printInteger(getPrescaler(frequency));
  }
#endif
protected:
  virtual uint8_t getPrescaler(float freq){};
  virtual uint16_t getTopLimit(float freq, uint8_t pre){};
};

/** 16-bit Timer/Counter 1 */
class Timer1 : public HardwareTimer {
private:
public:
  Timer1() {
    minimum = TIMER1_MIN_FREQUENCY;
    maximum = TIMER1_MAX_FREQUENCY;
  }
  void start(){
    // WGM10 | WGM11 | WGM13 : PWM, Phase Correct, OCR1A top, mode 11
//     TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11) | _BV(WGM10);
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
    running = true;
  }
  void stop(){
    TCCR1A = 0;
    TIMER1_PORT_A &= ~_BV(TIMER1_OUTPUT_A);
    TIMER1_PORT_B &= ~_BV(TIMER1_OUTPUT_B);    
    running = false;
  }
  void setPrescaler(uint8_t divisor){
    TCCR1B = _BV(WGM13) | divisor;
  }
  void setTopLimit(uint16_t limit){
    OCR1A = limit;
  }
  void updateDutyCycle(){
    OCR1B = (uint16_t)(OCR1A * duty);
  }
  uint8_t getPrescaler(float freq){
    float val = FREQ_CONSTANT / TIMER1_MAX_TOP_VALUE / freq;
    for(int i=0; i<5; ++i)
      if(timer1prescalers[i] > val)
	return i+1;
    return 5;
  }
  uint16_t getTopLimit(float freq, uint8_t pre){
    return round(FREQ_CONSTANT / timer1prescalers[pre-1] / freq);
  }
};

/** 8-bit Timer/Counter 2 */
class Timer2 : public HardwareTimer {
public:
  Timer2() {
    minimum = TIMER2_MIN_FREQUENCY;
    maximum = TIMER2_MAX_FREQUENCY;
  }
  void start(){
    // WGM20 | WGM22 : PWM, Phase Correct, OCRA top
    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
    running = true;
  }
  void stop(){
    TCCR2A = 0;
    TIMER2_PORT_A &= ~_BV(TIMER2_OUTPUT_A);
    TIMER2_PORT_B &= ~_BV(TIMER2_OUTPUT_B);
    running = false;
  }
  void setPrescaler(uint8_t divisor){
    if(divisor > 7)
      return;
    TCCR2B = _BV(WGM22) | divisor;
  }
  void setTopLimit(uint16_t limit){
    OCR2A = limit;
  }
  void updateDutyCycle(){
    OCR2B = (uint8_t)(OCR2A * duty);
  }
  uint8_t getPrescaler(float freq){
    float val = FREQ_CONSTANT / TIMER2_MAX_TOP_VALUE / freq;
    for(int i=0; i<7; ++i)
      if(timer2prescalers[i] > val)
	return i+1;
    return 7;
  }
  uint16_t getTopLimit(float freq, uint8_t pre){
    return round(FREQ_CONSTANT / timer2prescalers[pre-1] / freq);
  }
};

#endif /* _HARDWARE_TIMER_H_ */
