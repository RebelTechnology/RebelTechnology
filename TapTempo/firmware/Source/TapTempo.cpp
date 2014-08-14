#include "periph.h"

enum OperatingMode {
  MEDIUM_SPEED_MODE                   = 0,
  HIGH_SPEED_MODE                     = 1,
  LOW_SPEED_MODE                      = 2
};


inline bool isSlowMode(){
  return !getPin(TOGGLE_A_PORT, TOGGLE_A_PIN_A);
}

inline bool isFastMode(){
  return !getPin(TOGGLE_A_PORT, TOGGLE_A_PIN_B);
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

#define RAMP_LIMIT 4096L
#define TRIGGER_LIMIT 4294967295LL

class TapTempo {
private:
  volatile uint64_t counter;
  volatile uint64_t limit;
  volatile uint64_t trig;
  volatile uint32_t ramp;
public:
  volatile uint32_t threshold;
  
public:
  TapTempo() : counter(0), limit(4096L), trig(0), ramp(0), threshold(32) {}
  void trigger(){
    if(trig > threshold){
      high();
      // dds.setPeriod(trig);
      // dds.reset();
      limit = trig>>1; // toggle at period divided by 2
      trig = 0;
      counter = 0;
//       dds.setFrequency(DDS_FREQUENCY/limit);
    }
  }
  void clock(){
//     if(!++trig)
//       trig = TRIGGER_LIMIT;
    if(trig < TRIGGER_LIMIT)
      trig++;
    if(++counter > limit){
      toggle();
      counter = 0;
    }
    // dac1.send(dds.getValue());
//     dac1.send(ramp++);
//     if(ramp == RAMP_LIMIT)
//       ramp = 0;
//       if(ramp < RAMP_LIMIT){
// 	dac1.send(ramp++);
//       }
  }
  void low(){
    clearPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
    
  }
  void high(){
    setPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
//     ramp = 0;
  }
  void toggle(){
    if(isHigh())
      low();
    else
      high();
  }
  inline bool isHigh(){
    return getPin(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
  }
};

TapTempo tempo;

void setup(){
  ledSetup();
  setLed(RED);
  pushButtonSetup();

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  configureDigitalInput(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN, false);
  configureDigitalInput(TOGGLE_A_PORT, TOGGLE_A_PIN_A, true);
  configureDigitalInput(TOGGLE_A_PORT, TOGGLE_A_PIN_B, true);
  configureDigitalInput(TOGGLE_B_PORT, TOGGLE_A_PIN_A, true);
  configureDigitalInput(TOGGLE_B_PORT, TOGGLE_A_PIN_B, true);
  configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
}

bool triggerIsHigh(){
  return isPushButtonPressed() || !getPin(TRIGGER_INPUT_PORT, TRIGGER_INPUT_PIN);
}

void run(){
  int count = 0;
  for(;;){
    if(count++ % 0x200000 == 0)
      setLed(GREEN);
    else if(count % 0x100000 == 0){
      setLed(RED);
    }
  }
  tempo.clock();
  if(triggerIsHigh())
    tempo.trigger();
}
