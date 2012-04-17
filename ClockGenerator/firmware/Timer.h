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

#define CLOCKED_TIMER_MIN_FREQUENCY 0
#define CLOCKED_TIMER_MAX_FREQUENCY TIMER2_MAX_FREQUENCY
// #define CLOCKED_TIMER_FREQUENCY_MULTIPLIER 1024
#define CLOCKED_TIMER_FREQUENCY_MULTIPLIER (1024*8)

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
    r *= maximum;
    r = max(minimum, r);
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

class ClockedTimer : public Timer {
private:
  volatile uint16_t time;
  uint16_t period;
  uint16_t duration;
public:
  ClockedTimer() {
    minimum = CLOCKED_TIMER_MIN_FREQUENCY;
    maximum = CLOCKED_TIMER_MAX_FREQUENCY;
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
    if(frequency <= 0)
      frequency += 0.00001;
    period = (uint16_t)(CLOCKED_TIMER_FREQUENCY_MULTIPLIER/frequency);
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
