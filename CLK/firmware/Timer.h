#ifndef _TIMER_H_
#define _TIMER_H_

#include "device.h"
#include "macros.h"
#include <math.h>
#include <inttypes.h>

#define TIMER1_MAX_TOP_VALUE 65535
#define TIMER2_MAX_TOP_VALUE 255

#define TIMER1_MIN_FREQUENCY 0.12
#define TIMER1_MAX_FREQUENCY 15625.0 // artificial upper limit
#define TIMER2_MIN_FREQUENCY 30.64
#define TIMER2_MAX_FREQUENCY 8192.0 // artificial upperlimit
// #define TIMER2_MAX_FREQUENCY 15625.0 // artificial upperlimit

class Timer {
public:
  float duty;
  float frequency;
  float minimum;
  float maximum;
  bool running;
  virtual void start(){
    running = true;
  }
  virtual void stop(){
    running = false;
  }
  bool isStopped(){
    return !running;
  }
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
    if(isStopped())
      printString(" stopped");
  }
#endif
protected:
  virtual void updateFrequency(){}
  virtual void updateDutyCycle(){} 
};

template<typename T>
class ClockedTimer : public Timer {
private:
  volatile T time;
  T period;
  T duration;
public:
  T multiplier;
  ClockedTimer() {
  }
  void setMultiplier(T mult){
    multiplier = mult;
    updateFrequency();
    updateDutyCycle();
  }
  void start(){
    time = 0;
    running = true;
  }
  void clock(){
    if(running){
      if(++time > period){
	time = 0;
	on();
      }else if(time > duration){
	off();
      }else{
	on();
      }
    }else{
      off();
    }
  }
  void updateFrequency(){
    if(frequency <= 0){
      period = 2;
    }else{
      period = (T)(multiplier/frequency);
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
    printString(", m ");
    printInteger(multiplier);
  }
#endif
};

#endif /* _TIMER_H_ */
