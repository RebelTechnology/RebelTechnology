#include <stdlib.h>
#include "periph.h"

#include "DDS.h"

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

OperatingMode mode;
inline void updateMode(){
  if(isFastMode()){
    mode = HIGH_SPEED_MODE;
  }else if(isSlowMode()){
    mode = LOW_SPEED_MODE;
  }else{
    mode = MEDIUM_SPEED_MODE;
  }
}

DDS dds;

#define TRIGGER_LIMIT UINT64_MAX

enum TapTempoMode {
  OFF, SINE, TRIANGLE
};

class TapTempo {
private:
  volatile uint64_t counter;
  volatile uint64_t limit;
  volatile uint64_t trig;
  volatile uint32_t ramp;
  volatile uint32_t threshold;
  volatile bool isHigh;  
  volatile TapTempoMode mode;
  volatile uint32_t period;
public:
  TapTempo() : counter(0), limit(4096L), trig(0), ramp(0), threshold(32), isHigh(false), mode(SINE) {}
  void trigger(){
    if(trig > threshold && trig < TRIGGER_LIMIT){
      high();
      dds.setPeriod(trig);
      dds.reset();
      limit = trig>>1; // toggle at period divided by 2
      counter = 0;
//       dds.setFrequency(DDS_FREQUENCY/limit);
    }
    trig = 0;
  }
  void setPeriodBasis(uint32_t basis){
    int adjustment = basis - period;
    dds.tune(adjustment);
    period = basis;
  }
  void multiplyTempo(float factor){
    dds.setPeriod(factor*dds.getPeriod());
  }
  TapTempoMode getMode(){
    return mode;
  }
  void setMode(TapTempoMode m){
    mode = m;
    if(mode == OFF){
      counter = 0;
      dds.reset();
      DAC_SetDualChannelData(DAC_Align_12b_R, 0, 0);
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
	DAC_SetDualChannelData(DAC_Align_12b_R, dds.getSine(), dds.getRamp());
      }else{ // if(mode == TRIANGLE){
	DAC_SetDualChannelData(DAC_Align_12b_R, dds.getTri(), 4095-dds.getRamp());
      }
      dds.clock();
    }
    // setAnalogValue(0, dds.getValue());
    // setAnalogValue(1, dds.getRamp());
    // dac1.send(dds.getValue());
//     dac1.send(ramp++);
//     if(ramp == RAMP_LIMIT)
//       ramp = 0;
//       if(ramp < RAMP_LIMIT){
// 	dac1.send(ramp++);
//       }
  }
  void low(){
    isHigh = false;
    setPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(NONE);    
  }
  void high(){
    isHigh = true;
    clearPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    setLed(GREEN);
//     ramp = 0;
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
    setLed(RED);
  }else{
    setLed(NONE);
  }
}

void timerCallback(){
  tempo.clock();
  // togglePin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
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
  triggerInputSetup(triggerCallback);
  pushButtonSetup(buttonCallback);
  timerSetup(692, timerCallback);
  adcSetup();
  dacSetup();
}

bool triggerIsHigh(){
  // return isPushButtonPressed() || !getPin(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN);
  return isPushButtonPressed();
}

uint32_t period = 0;
void run(){
  // int count = 0;
  for(;;){
    // if(count++ % 0x200000 == 0)
    //   setLed(GREEN);
    // else if(count % 0x100000 == 0){
    //   setLed(RED);
    // }
    // updateMode();
    if(isTriangleMode()){
      if(tempo.getMode() != TRIANGLE)
	tempo.setMode(TRIANGLE);
    }else if(isSineMode()){
      if(tempo.getMode() != SINE)
	tempo.setMode(SINE);
    }else if(tempo.getMode() != OFF){
      tempo.setMode(OFF);
    }

    uint32_t p = (4095-getAnalogValue(0))*6+32;
    if(isFastMode()){
      p <<= 1;
    }else if(isSlowMode()){
      p >>= 1;
    }
    p += 1;
    if(abs(p-period) > 32){
      period = p;
      timerSet(period);
      // tempo.setPeriodBasis(period);
    }

    // 91Hz - 17kHz
    // tempo.clock();
    // if(triggerIsHigh())
    //   tempo.trigger();
  }
}
