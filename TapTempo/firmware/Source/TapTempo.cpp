#include <stdlib.h>
#include "periph.h"
#include "DDS.h"

/* period 3000: 1kHz toggle
 *        1000: 3kHz
 *	   300: 10kHz
 *	   200: 15kHz
 *	    30: 45Hz 
 */
#define TIMER_PERIOD      300 // 20kHz sampling rate
#define TRIGGER_THRESHOLD 16  // 1250Hz at 20kHz sampling rate
#define TAP_THRESHOLD     256 // 78Hz at 20kHz sampling rate, or 16th notes at 293BPM
#define TRIGGER_LIMIT     INT32_MAX
/* At 20kHz sampling frequency (TIMER_PERIOD 300), a 32-bit counter will 
 * overflow every 59.65 hours. With 63 bits it overflows every 14623560 years.
 */

// tracking at 18Hz trigger input but not at 20Hz with threshold 1024
// tracking at 610Hz trigger input but not at 625Hz with threshold 32 (20k/32=625)

/* #define DEBOUNCE(nm, ms) if(true){static uint32_t nm ## Debounce = 0; \
if(getSysTicks() < nm ## Debounce+(ms)) return; nm ## Debounce = getSysTicks();} */

void setAnalogValue(uint8_t channel, uint16_t value){
  value = value & 0xfff;
  if(channel == 0)
    DAC_SetChannel1Data(DAC_Align_12b_R, value);
  else if(channel == 1)
    DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

inline bool isSlowMode(){
  return !getPin(TOGGLE_R_PORT, TOGGLE_R_PIN_B);
}

inline bool isFastMode(){
  return !getPin(TOGGLE_R_PORT, TOGGLE_R_PIN_A);
}

inline bool isSineMode(){
  return !getPin(TOGGLE_L_PORT, TOGGLE_L_PIN_B);
}

inline bool isTriangleMode(){
  return !getPin(TOGGLE_L_PORT, TOGGLE_L_PIN_A);
}

DDS dds;

enum SynchroniserMode {
  OFF, SINE, TRIANGLE
};

class Synchroniser {
private:
  int32_t trig;
  int32_t period;
  bool isHigh;  
  SynchroniserMode mode;
  uint16_t speed;
public:
  Synchroniser() : trig(TRIGGER_LIMIT), period(0),
	       isHigh(false), mode(OFF), speed(4095) {
    dds.setPeriod(period);
  }
  void reset(){
    trig = TRIGGER_LIMIT;
    dds.reset();
    DAC_SetDualChannelData(DAC_Align_12b_R, DDS_RAMP_ZERO_VALUE, DDS_SINE_ZERO_VALUE);
  }
  void trigger(){
    if(trig < TRIGGER_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      period = trig;
      dds.setPeriod(period);
    }
    trig = 0;
  }
  void setSpeed(int16_t s){
    if(abs(speed-s) > 16){
      int64_t delta = (int64_t)period*(speed-s)/1024;
      period = max(1, period+delta);
      dds.setPeriod(period);
      speed = s;
    }
  }
  void setMode(SynchroniserMode m){
    if(m == OFF && mode != OFF)
      reset();
    mode = m;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    if(mode == SINE){
      DAC_SetDualChannelData(DAC_Align_12b_R, dds.getRisingRamp(), dds.getSine());
      dds.clock();
    }else if(mode == TRIANGLE){
      DAC_SetDualChannelData(DAC_Align_12b_R, dds.getFallingRamp(), dds.getTri());
      dds.clock();
    }
  }
};

class TapTempo {
private:
  int32_t counter;
  int32_t limit;
  int32_t trig;
  bool isHigh;  
  bool on;
  uint16_t speed;
public:
  TapTempo() : counter(0), limit(TRIGGER_LIMIT/2), trig(TRIGGER_LIMIT), 
	       isHigh(false), on(false), speed(4095) {}
  void reset(){
    counter = 0;
    low();
  }
  void trigger(){
    if(trig < TAP_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      high();
      limit = trig>>1; // toggle at period divided by 2
      counter = 0;
    }
    trig = 0;
  }
  void setSpeed(int16_t s){
    if(abs(speed-s) > 16){
      int64_t delta = (int64_t)limit*(speed-s)/2048;
      limit = max(1, limit+delta);
      speed = s;
    }
  }
  void setStatus(bool enable){
    if(!enable && on)
      reset();
    on = enable;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    if(on && ++counter > limit){
      counter = 0;
      toggle();
    }
  }
  void low(){
    isHigh = false;
    setPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(NONE);    
  }
  void high(){
    isHigh = true;
    clearPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(RED);
  }
  void toggle(){
    if(isHigh)
      low();
    else
      high();
  }
};

Synchroniser synchro;
TapTempo tempo;

// todo: proper debouncing with systick counter
void buttonCallback(){
  if(isPushButtonPressed()){
    tempo.trigger();
    // toggleLed();
  }else{
    tempo.low();
  }
}

void triggerCallback(){
  if(isTriggerHigh()){
    synchro.trigger();
  }
}

void timerCallback(){
  tempo.clock();
  synchro.clock();
#ifdef DEBUG_PINS
  togglePin(GPIOB, GPIO_Pin_10); // debug
#endif
}

void updateMode(){
  if(isSineMode()){
    synchro.setMode(SINE);
    tempo.setStatus(true);
  }else if(isTriangleMode()){
    synchro.setMode(TRIANGLE);
    tempo.setStatus(true);
  }else{
    synchro.setMode(OFF);
    tempo.setStatus(false);
  }
}

void updateSpeed(){
  int16_t p = getAnalogValue(0);
  synchro.setSpeed(p);
  tempo.setSpeed(p);
}

void setup(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_A, true);
  configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(TOGGLE_R_CLOCK, ENABLE);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_B, true);
  configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
#ifdef DEBUG_PINS
  configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
#endif
  ledSetup();
  setLed(RED);
  adcSetup();
  dacSetup();
  triggerInputSetup(triggerCallback);
  pushButtonSetup(buttonCallback);
  timerSetup(TIMER_PERIOD, timerCallback);
}

void run(){
  for(;;){
    updateMode();
    updateSpeed();
  }
}
