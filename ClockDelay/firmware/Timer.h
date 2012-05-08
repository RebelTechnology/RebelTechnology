#ifndef _TIMER_H_
#define _TIMER_H_

#include "device.h"
#include "macros.h"
#include <math.h>
#include <inttypes.h>

#define CLOCKED_TIMER_FREQUENCY_MULTIPLIER 1024

class Timer {
public:
  float duty;
  float frequency;
  float minimum;
  float maximum;
  virtual void setFrequency(float f){
    frequency = f;
    updateFrequency();
    updateDutyCycle();
  }
  /* expects a value 0.0-1.0 */
  virtual void setDutyCycle(float d){
    duty = d;
    updateDutyCycle();
  }
  // set the frequency as a percentage of max speed, 0.0-1.0
  void setRate(float r){
    r *= (maximum-minimum);
    r += minimum;
    setFrequency(r);
  }
  float midiToFreq(uint8_t note){
    return 440.0 * pow(2, (note - 69) / 12.0); 
  }
  void setMidiNote(uint8_t note){
    setFrequency(midiToFreq(note));
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("f ");
    printInteger(frequency);
    printString(", d ");
    printInteger(duty*255);
  }
#endif
protected:
  virtual void updateFrequency(){}
  virtual void updateDutyCycle(){} 
};

/**
 * 16-bit manually triggered timer.
 * Has a range of 2ms to 32 seconds when triggered every millisecond.
 */
class ClockedTimer : public Timer {
private:
  volatile uint16_t time;
  uint16_t period;
  uint16_t duration;
public:
  ClockedTimer() {
/*     minimum = CLOCKED_TIMER_MIN_FREQUENCY; */
/*     maximum = CLOCKED_TIMER_MAX_FREQUENCY; */
  }
  void reset(){
    time = 0;
  }
  void clock(){
    if(++time > period){
      time = 0;
      on();
    }else if(time > duration){
      off();
    }else{
      on();
    }
  }
  void updateFrequency(){
    if(frequency <= 0){
      period = 2;
    }else{
      period = (uint16_t)(CLOCKED_TIMER_FREQUENCY_MULTIPLIER/frequency);
    }
  }
  void updateDutyCycle(){
    duration = period*duty;
  }
  virtual void on(){}
  virtual void off(){}
#ifdef SERIAL_DEBUG
  virtual void dump(){
    Timer::dump();
    printString(", t ");
    printInteger(time);
    printString(", p ");
    printInteger(period);
    printString(", d ");
    printInteger(duration);
  }
#endif
};

#endif /* _TIMER_H_ */
