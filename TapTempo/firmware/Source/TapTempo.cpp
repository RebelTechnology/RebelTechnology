#include <stdlib.h>
#include "periph.h"
#include "DDS.h"

/* period 3000: 1kHz toggle
 *        1000: 3kHz
 *	   300: 10kHz
 *	   200: 15kHz
 *	    30: 45Hz 
 */
#define TIMER_PERIOD      300
#define TRIGGER_THRESHOLD 32
// #define TIMER_PERIOD      450
// #define TRIGGER_THRESHOLD 24
#define TRIGGER_LIMIT     INT32_MAX
/* At 20kHz sampling frequency (TIMER_PERIOD 300), a 32-bit counter will 
 * overflow every 59.65 hours. With 63 bits it overflows every 14623560 years.
 */

// tracking at 18Hz trigger input but not at 20Hz with threshold 1024
// tracking at 610Hz trigger input but not at 625Hz with threshold 32

void setAnalogValue(uint8_t channel, uint16_t value);

void setAnalogValue(uint8_t channel, uint16_t value){
  value = value & 0xfff;
  if(channel == 0)
    DAC_SetChannel1Data(DAC_Align_12b_R, value);
  else if(channel == 1)
    DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

/* #define DEBOUNCE(nm, ms) if(true){static uint32_t nm ## Debounce = 0; \
if(getSysTicks() < nm ## Debounce+(ms)) return; nm ## Debounce = getSysTicks();} */

enum OperatingMode {
  MEDIUM_SPEED_MODE                   = 0,
  HIGH_SPEED_MODE                     = 1,
  LOW_SPEED_MODE                      = 2
};

inline bool isSlowMode(){
  return !getPin(TOGGLE_A_PORT, TOGGLE_A_PIN_B);
}

inline bool isFastMode(){
  return !getPin(TOGGLE_A_PORT, TOGGLE_A_PIN_A);
}

inline bool isSineMode(){
  return !getPin(TOGGLE_B_PORT, TOGGLE_B_PIN_B);
}

inline bool isTriangleMode(){
  return !getPin(TOGGLE_B_PORT, TOGGLE_B_PIN_A);
}

DDS dds;

enum TapTempoMode {
  OFF, SINE, TRIANGLE
};

class TapTempo {
private:
  volatile uint32_t counter;
  volatile uint32_t limit;
  volatile uint32_t trig;
  volatile uint32_t period;
  volatile uint16_t threshold;
  volatile bool isHigh;  
  volatile TapTempoMode mode;
  volatile uint16_t speed;
public:
  TapTempo() : counter(0), limit(TRIGGER_LIMIT), trig(TRIGGER_LIMIT), period(TRIGGER_LIMIT), 
	       threshold(TRIGGER_THRESHOLD), isHigh(false), mode(SINE), speed(0) {}
  void trigger(){
    if(trig > threshold){
      if(trig < TRIGGER_LIMIT){
	high();
	period = trig;
	dds.setPeriod(period);
	dds.reset();
	limit = trig>>1; // toggle at period divided by 2
	counter = 0;
	//       dds.setFrequency(DDS_FREQUENCY/limit);
      }
      trig = 0;
    }
  }
  void setSpeed(int16_t s){
    if(abs(speed-s)>32){
      int64_t delta = (int64_t)period*(speed-s)/1024;
      period = period+delta;
      dds.setPeriod(period);
      limit = period>>1;
      speed = s;
      // without overflow handling, actual accumulator depth is less
    }
  }
  TapTempoMode getMode(){
    return mode;
  }
  void setMode(TapTempoMode m){
    mode = m;
    if(mode == OFF){
      counter = 0;
      trig = TRIGGER_LIMIT;
      dds.reset();
      low();
      DAC_SetDualChannelData(DAC_Align_12b_R, 0, 2047);
    }
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    if(mode != OFF){
      if(++counter > limit){
	counter = 0;
	toggle();
      }
      if(mode == SINE){
	DAC_SetDualChannelData(DAC_Align_12b_R, dds.getRamp(), dds.getSine());
      }else{ // if(mode == TRIANGLE){
	DAC_SetDualChannelData(DAC_Align_12b_R, 4095-dds.getRamp(), dds.getTri());
      }
      dds.clock();
    }
  }
  void low(){
    isHigh = false;
    clearPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(NONE);    
  }
  void high(){
    isHigh = true;
    setPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(GREEN);
  }
  void toggle(){
    if(isHigh)
      low();
    else
      high();
  }
};

TapTempo tempo;

void buttonCallback(){
  tempo.trigger();
  toggleLed();
}

void triggerCallback(){
  // DEBOUNCE(trigger, 100);
  if(getPin(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN)){
    tempo.trigger();
    // setLed(RED);
  }else{
    setLed(NONE);
  }
}

void timerCallback(){
  tempo.clock();
  // togglePin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
  togglePin(GPIOB, GPIO_Pin_10); // debug
}

void setup(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  configureDigitalInput(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN, false);
  configureDigitalInput(TOGGLE_A_PORT, TOGGLE_A_PIN_A, true);
  configureDigitalInput(TOGGLE_A_PORT, TOGGLE_A_PIN_B, true);
  configureDigitalInput(TOGGLE_B_PORT, TOGGLE_A_PIN_A, true);
  configureDigitalInput(TOGGLE_B_PORT, TOGGLE_A_PIN_B, true);
  configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
  ledSetup();
  setLed(RED);
  adcSetup();
  dacSetup();
  triggerInputSetup(triggerCallback);
  pushButtonSetup(buttonCallback);
  timerSetup(TIMER_PERIOD, timerCallback);

  configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
}

bool triggerIsHigh(){
  // return isPushButtonPressed() || !getPin(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN);
  return isPushButtonPressed();
}

void run(){
  for(;;){
    switch(tempo.getMode()){
    case SINE:
      if(!isSineMode()){
	if(isTriangleMode())
	  tempo.setMode(TRIANGLE);
	else
	  tempo.setMode(OFF);
      }
      break;
    case TRIANGLE:
      if(!isTriangleMode()){
	if(isSineMode())
	  tempo.setMode(SINE);
	else
	  tempo.setMode(OFF);
      }
      break;
    case OFF:
      if(isSineMode())
	tempo.setMode(SINE);
      else if(isTriangleMode())
	tempo.setMode(TRIANGLE);
      break;
    }
    int16_t p = getAnalogValue(0);
    // if(isFastMode()){
    //   p *= 2;
    // }else if(isSlowMode()){
    //   p /= 2;
    // }
    tempo.setSpeed(p);
  }
}
