#ifndef _TIMER_H_
#define _TIMER_H_

#include "device.h"
#include "macros.h"
#include <math.h>
#include <inttypes.h>

#define FREQ_CONSTANT (F_CPU / 2)
static uint16_t timer1prescalers[] = {1, 8, 64, 256, 1024};
static uint16_t timer2prescalers[] = {1, 8, 32, 64, 128, 256, 1024};

#define TIMER1_MAX_TOP_VALUE 65535
#define TIMER2_MAX_TOP_VALUE 255

#define TIMER1_MIN_FREQUENCY 0.12
#define TIMER1_MAX_FREQUENCY 15625.0 // artificial upper limit
#define TIMER2_MIN_FREQUENCY 30.64
#define TIMER2_MAX_FREQUENCY 15625.0 // artificial upperlimit

#define CLOCKED_TIMER_MIN_FREQUENCY 0
#define CLOCKED_TIMER_MAX_FREQUENCY 1000.0
#define CLOCKED_TIMER_FREQUENCY_MULTIPLIER 1000

class Timer {
public:
  float duty;
  float frequency;
  float minimum;
  float maximum;
  virtual void start(){}
  virtual void stop(){}
//   virtual bool isStopped(){return true;}
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
protected:
  virtual void updateFrequency(){}
  virtual void updateDutyCycle(){} 
};

// enum ClockedTimerState {
//   STOPPED_LOW = 0,
//   STOPPED_HIGH = 1,
//   RUNNING_LOW = 2,
//   RUNNING_HIGH = 3
// };

class ClockedTimer : public Timer {
private:
  int running;
  uint16_t time;
  uint16_t period;
  uint16_t duration;
public:
  ClockedTimer() : running(false) {
    minimum = CLOCKED_TIMER_MIN_FREQUENCY;
    maximum = CLOCKED_TIMER_MAX_FREQUENCY;
  }
  virtual void start(){
    time = 0;
    running = true;
  }
  virtual void stop(){
    running = false;
  }
  virtual bool isStopped(){
    return running;
  }
  void clock(){
//     state = (ClockedTimerState)(state | isOn());
//     switch(state){
//     }    
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
    period = (uint16_t)(CLOCKED_TIMER_FREQUENCY_MULTIPLIER/frequency);
  }
  void updateDutyCycle(){
    duration = period*duty;
  }
  virtual void on(){}
  virtual void off(){}
  // set the frequency as a percentage of max speed, 0.0-1.0
//   virtual void setRate(float r){
//     r *= CLOCKED_TIMER_MAX_FREQUENCY;
//     r = max(CLOCKED_TIMER_MIN_FREQUENCY, r);
//     setFrequency(r);    
//   }
};

#endif /* _TIMER_H_ */
