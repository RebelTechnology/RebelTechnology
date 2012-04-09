#ifndef _TIMER_H_
#define _TIMER_H_

#include "device.h"
#include <math.h>

#define FREQ_CONSTANT (F_CPU / 2)
static uint16_t prescalers[] = {1, 8, 32, 64, 128, 256, 1024};

class Timer {
public:
  virtual void init(){}
  virtual void setPrescaler(uint8_t divisor){}
  virtual void setTopLimit(uint16_t limit){}
  /* expects a value 0.0-1.0 */
  void setDutyCycle(float value){}

  uint8_t getPrescaler(float freq){
    float val = FREQ_CONSTANT / 255 / freq;
    for(int i=0; i<7; ++i)
      if(prescalers[i] > val)
	return i+1;
    return 0;
  }

  uint16_t getTopLimit(float freq, uint8_t pre){
    return round(FREQ_CONSTANT / prescalers[pre-1] / freq);
  }

  void setFrequency(float freq){
    uint8_t pre = getPrescaler(freq);
    uint16_t limit = getTopLimit(freq, pre);
    setPrescaler(pre);
    setTopLimit(limit);
  }

  float midiToFreq(uint8_t note){
    return 440.0 * pow(2, (note - 69) / 12.0); 
  }

  void setMidiNote(uint8_t note){
    setFrequency(midiToFreq(note));
  }
};

class Timer1 : public Timer {
public:
  void init(){
/*     pinMode(9, OUTPUT);  // OC1A */
/*     pinMode(10, OUTPUT); // OC1B */

    TIMER1_DDR_A |= _BV(TIMER1_OUTPUT_A);
    TIMER1_DDR_B |= _BV(TIMER1_OUTPUT_B);

    TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  }
  void setPrescaler(uint8_t divisor){
    TCCR1B = _BV(WGM13) | divisor;
  }
  void setTopLimit(uint16_t limit){
    OCR1A = limit;
  }
  void setDutyCycle(float value){
    OCR1B = (uint16_t)(OCR2A * value);
  }
};

class Timer2 : public Timer {
public:
  void init(){
/*     pinMode(11, OUTPUT); // OC2A */
/*     pinMode(3, OUTPUT);  // OC2B */

    TIMER2_DDR_A |= _BV(TIMER2_OUTPUT_A);
    TIMER2_DDR_B |= _BV(TIMER2_OUTPUT_B);

    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
  }
  void setPrescaler(uint8_t divisor){
    if(divisor > 7)
      return;
    TCCR2B = _BV(WGM22) | divisor;
  }
  void setTopLimit(uint16_t limit){
    OCR2A = limit;
  }
  void setDutyCycle(float value){
    OCR2B = (uint8_t)(OCR2A * value);
  }
};

#endif /* _TIMER_H_ */
