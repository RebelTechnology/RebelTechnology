#include <stdlib.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "DDS.h"
#include "gpio.h"
#include "periph.h"

extern "C"{
  void setup();
  void loop();
  extern DAC_HandleTypeDef hdac;
}

/* period 3000: 1kHz toggle
 *        1000: 3kHz
 *	   300: 10kHz
 *	   200: 15kHz
 *	    30: 45Hz 
 */
#define TIMER_PERIOD      300 // 20kHz sampling rate
#define TRIGGER_THRESHOLD 16  // 1250Hz at 20kHz sampling rate
#define TAP_THRESHOLD     256 // 78Hz at 20kHz sampling rate, or 16th notes at 293BPM
#define TRIGGER_LIMIT     UINT32_MAX
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
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
    // DAC_SetChannel1Data(DAC_Align_12b_R, value);
  else if(channel == 1)
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
    // DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

inline bool isSlowMode(){
  return !getPin(TOGGLE1A_GPIO_Port, TOGGLE1A_Pin);
}

inline bool isFastMode(){
  return !getPin(TOGGLE1B_GPIO_Port, TOGGLE1B_Pin);
}

inline bool isSineMode(){
  return !getPin(TOGGLE2A_GPIO_Port, TOGGLE2A_Pin);
}

inline bool isTriangleMode(){
  return !getPin(TOGGLE2B_GPIO_Port, TOGGLE2B_Pin);
}

enum SynchroniserMode {
  OFF, SINE, TRIANGLE
};

class Synchroniser {
private:
  volatile uint32_t trig;
  uint32_t period;
  bool isHigh;  
  SynchroniserMode mode;
public:
  uint16_t speed;
  DDS dds;
  uint32_t sine, saw;
public:
  Synchroniser() : trig(TRIGGER_LIMIT), period(0),
	       isHigh(false), mode(OFF), speed(4095) {
    dds.setPeriod(period);
  }
  void reset(){
    trig = TRIGGER_LIMIT;
    sine = saw = 0; // reset phase accumulators
    setAnalogValue(0, DDS_RAMP_ZERO_VALUE);
    setAnalogValue(1, DDS_SINE_ZERO_VALUE);
    // DAC_SetDualChannelData(DAC_Align_12b_R, DDS_RAMP_ZERO_VALUE, DDS_SINE_ZERO_VALUE);
  }
  void trigger(){
    if(trig < TRIGGER_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      period = trig;
      dds.setPeriod(period);
    }
    trig = 0;
    saw = 0; // phase reset
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
      setAnalogValue(0, dds.getRisingRamp(saw));
      setAnalogValue(1, dds.getSine(sine));
      // DAC_SetDualChannelData(DAC_Align_12b_R, dds.getRisingRamp(saw), dds.getSine(sine));
      saw += dds.inc();
      sine += dds.inc();
    }else if(mode == TRIANGLE){
      setAnalogValue(0, dds.getFallingRamp(saw));
      setAnalogValue(1, dds.getTri(sine));
      // DAC_SetDualChannelData(DAC_Align_12b_R, dds.getFallingRamp(saw), dds.getTri(sine));
      saw += dds.inc();
      sine += dds.inc();
    }
  }
};

class TapTempo {
private:
  volatile uint32_t counter;
  uint32_t goLow;
  uint32_t goHigh;
  uint32_t trig;
  bool isHigh;  
  bool on;
public:
  uint16_t speed;
  TapTempo() : counter(0), goLow(TRIGGER_LIMIT>>2), goHigh(TRIGGER_LIMIT>>1), 
	       trig(0), isHigh(false), on(false), speed(4095) {}	       
  void reset(){
    counter = 0;
    setLow();
  }
  void trigger(bool high){
    if(trig < TAP_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      if(high){
	setHigh();
	goHigh = trig;
	goLow = trig>>1;
	counter = 0;
	trig = 0;
      }else{
	setLow();
      }
    }else if(high){
      trig = 0;
    }
  }
  void setSpeed(int16_t s){
    if(abs(speed-s) > 16){
      // int64_t delta = (int64_t)goLow*(speed-s)/2048;
      // goLow = max(1, goLow+delta);
      int64_t delta = (int64_t)goHigh*(speed-s)/2048;
      goHigh = max(1, goHigh+delta);
      goLow = goHigh >> 1;
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
    if(on){
      if(++counter >= goHigh){
	setHigh();
	counter = 0;
      }else if(counter >= goLow && isHigh){
	setLow();
      }
      if(isSineMode())
	setLed(LED_FULL*(goHigh-counter)/(goHigh+1));
      else
	setLed(LED_FULL*counter/(goHigh+1));
    }
  }
  void setLow(){
    isHigh = false;
    setPin(TR1_GPIO_Port, TR1_Pin);
    setLed(0);    
  }
  void setHigh(){
    isHigh = true;
    clearPin(TR1_GPIO_Port, TR1_Pin);
    setLed(LED_FULL);
  }
  void toggle(){
    if(isHigh)
      setLow();
    else
      setHigh();
  }
};

Synchroniser synchro;
TapTempo tempo;

// todo: proper debouncing with systick counter
void buttonCallback(){
  tempo.trigger(isPushButtonPressed());
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
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(TOGGLE_R_CLOCK, ENABLE);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_B, true);
//   configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
// #ifdef DEBUG_PINS
//   configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
// #endif
//   ledSetup();
  setLed(0);
  // adcSetup();
  // dacSetup();
  // triggerInputSetup(triggerCallback);
  // pushButtonSetup(buttonCallback);
  // timerSetup(TIMER_PERIOD, timerCallback);
  updateSpeed();
  synchro.speed = getAnalogValue(0);
  tempo.speed = getAnalogValue(0);
}


void loop(){
  updateMode();
  updateSpeed();
}
