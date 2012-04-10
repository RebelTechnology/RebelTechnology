#ifndef _TIMER_H_
#define _TIMER_H_

#include "device.h"
#include "macros.h"
#include <math.h>

#define FREQ_CONSTANT (F_CPU / 2)
static uint16_t timer1prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer2prescalers[] = {1, 8, 32, 64, 128, 256, 1024};

#define TIMER1_MAX_TOP_VALUE 65535
#define TIMER2_MAX_TOP_VALUE 255

#define TIMER1_MIN_FREQUENCY 0.12
#define TIMER1_MAX_FREQUENCY 15625.0 // artificial upper limit
#define TIMER2_MIN_FREQUENCY 30.64
#define TIMER2_MAX_FREQUENCY 15625.0 // artificial upperlimit

class Timer {
public:
  float duty;
  float frequency;
  virtual void start(){}
  virtual void stop(){}
  virtual void setPrescaler(uint8_t divisor){}
  virtual void setTopLimit(uint16_t limit){}
  /* expects a value 0.0-1.0 */
  void setDutyCycle(float value){
    duty = value;
    updateDutyCycle();
  }
  void setFrequency(float freq){
    frequency = freq;
    uint8_t pre = getPrescaler(freq);
    uint16_t limit = getTopLimit(freq, pre);
    setPrescaler(pre);
    setTopLimit(limit);
    updateDutyCycle();
  }
  float midiToFreq(uint8_t note){
    return 440.0 * pow(2, (note - 69) / 12.0); 
  }

  void setMidiNote(uint8_t note){
    setFrequency(midiToFreq(note));
  }
  // set the frequency as a percentage of max speed, 0.0-1.0
  virtual void setRate(float r){}
  virtual bool isStopped(){return true;}
protected:
  virtual void updateDutyCycle();
  virtual uint8_t getPrescaler(float freq);
  virtual uint16_t getTopLimit(float freq, uint8_t pre);
};

/** 16-bit Timer/Counter 1 */
class Timer1 : public Timer {
public:
  void start(){
    TIMER1_DDR_A |= _BV(TIMER1_OUTPUT_A);
    TIMER1_DDR_B |= _BV(TIMER1_OUTPUT_B);
    // WGM10 | WGM11 | WGM13 : PWM, Phase Correct, OCR1A top
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  }
  void stop(){
    TCCR1A = 0;
    TIMER1_PORT_A &= ~_BV(TIMER1_OUTPUT_A);
    TIMER1_PORT_B &= ~_BV(TIMER1_OUTPUT_B);    
  }
  bool isStopped(){
    return !(TCCR1A & (_BV(COM1A1) | _BV(COM1B1)));
  }
  void setRate(float r){
    r *= TIMER1_MAX_FREQUENCY;
    r = max(TIMER1_MIN_FREQUENCY, r);
    setFrequency(r);
  }
  void setPrescaler(uint8_t divisor){
    TCCR1B = _BV(WGM13) | divisor;
  }
  void setTopLimit(uint16_t limit){
    OCR1A = limit;
  }
  void updateDutyCycle(){
    OCR1B = (uint16_t)(OCR2A * duty);
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

/** 8-bit Timer/Counter 1 */
class Timer2 : public Timer {
public:
  void start(){
    TIMER2_DDR_A |= _BV(TIMER2_OUTPUT_A);
    TIMER2_DDR_B |= _BV(TIMER2_OUTPUT_B);
    // WGM20 | WGM22 : PWM, Phase Correct, OCRA top
    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
  }
  void stop(){
    TCCR2A = 0;
    TIMER2_PORT_A &= ~_BV(TIMER2_OUTPUT_A);
    TIMER2_PORT_B &= ~_BV(TIMER2_OUTPUT_B);
  }
  bool isStopped(){
    return !(TCCR2A & (_BV(COM2A0) | _BV(COM2B1)));
  }
  void setRate(float r){
    r *= TIMER2_MAX_FREQUENCY;
    r = max(TIMER2_MIN_FREQUENCY, r);
    setFrequency(r);
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

#endif /* _TIMER_H_ */
