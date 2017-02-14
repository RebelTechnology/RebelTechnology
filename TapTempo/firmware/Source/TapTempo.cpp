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
  extern ADC_HandleTypeDef hadc1;
  extern TIM_HandleTypeDef htim1;
  extern TIM_HandleTypeDef htim2;
  extern TIM_HandleTypeDef htim3;
}

#define NOF_ADC_VALUES 4
uint16_t adc_values[NOF_ADC_VALUES];

uint16_t getAnalogValue(uint8_t index){
  return adc_values[index];
}

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif /* min */
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif /* max */
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

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

enum Channel {
  CH1, CH2
};

enum OperatingMode {
  OFF, UP, DOWN
};

OperatingMode getMode(Channel ch){  
  switch(ch){
  case CH1:
    if(!getPin(SW1A_GPIO_Port, SW1A_Pin))
      return UP;
    else if(!getPin(SW1B_GPIO_Port, SW1B_Pin))
      return DOWN;
    else
      return OFF;
  case CH2:
    if(!getPin(SW2A_GPIO_Port, SW2A_Pin))
      return UP;
    else if(!getPin(SW2B_GPIO_Port, SW2B_Pin))
      return DOWN;
    else
      return OFF;
  default:
    return OFF;
  }
}

void setPeriod(uint16_t value){
  TIM2->CCR1 = value;
}

void setAnalogValue(Channel ch, uint16_t value){
  value &= 0xfff;
  if(ch == CH1)
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
    // DAC_SetChannel1Data(DAC_Align_12b_R, value);
  else if(ch == CH2)
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
    // DAC_SetChannel2Data(DAC_Align_12b_R, value);
}

inline bool isPushButton1Pressed(){
  return !getPin(PUSH1_GPIO_Port, PUSH1_Pin); 
}

inline bool isPushButton2Pressed(){
  return !getPin(PUSH2_GPIO_Port, PUSH2_Pin); 
}

inline bool isTrigger1High(){
  return !getPin(TEMPO1_GPIO_Port, TEMPO1_Pin);
}

inline bool isTrigger2High(){
  return !getPin(TEMPO2_GPIO_Port, TEMPO2_Pin);
}

class Waveform {
public:
  virtual void reset() = 0;
  virtual void output(uint32_t phase) = 0;
};

#include "sinewave.h"
#include "trianglewave.h"

DDS dds;

class SineWave : public Waveform {
public:
  void reset(){
    setAnalogValue(CH1, DDS_SINE_ZERO_VALUE);
  }
  void output(uint32_t phase){
    setAnalogValue(CH1, dds.getSine(phase));
  }
};

class TriangleWave : public Waveform {
public:
  void reset(){
    setAnalogValue(CH1, DDS_SINE_ZERO_VALUE);
  }
  void output(uint32_t phase){
    setAnalogValue(CH1, dds.getTri(phase));
  }
};

class RisingRampWave : public Waveform {
public:
  void reset(){
    setAnalogValue(CH2, DDS_RAMP_ZERO_VALUE);
  }
  void output(uint32_t phase){
    setAnalogValue(CH2, dds.getRisingRamp(phase));
  }
};

class FallingRampWave : public Waveform {
public:
  void reset(){
    setAnalogValue(CH2, DDS_RAMP_ZERO_VALUE);
  }
  void output(uint32_t phase){
    setAnalogValue(CH2, dds.getFallingRamp(phase));
  }
};

/*
Synchronised LFO
- trigger: update period
- clock: increment phase
- convert phase to wave: 
  sine / triangle
  rising / falling saw
- occasional: update period from speed

*/

template<Channel CH>
class TapTempo {
private:
  volatile uint32_t counter;
  uint32_t goLow;
  uint32_t goHigh;
  uint32_t trig;
  bool isHigh;  
  OperatingMode mode;
public:
  uint16_t speed;
  TapTempo() : counter(0), goLow(TRIGGER_LIMIT>>2), goHigh(TRIGGER_LIMIT>>1), 
	       trig(0), isHigh(false), mode(OFF), speed(4095) {}	       
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
  void setMode(OperatingMode op){
    if(op != mode && op == OFF)
      reset();
    mode = op;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    switch(mode){
    case UP:
      if(++counter >= goHigh){
	setHigh();
	counter = 0;
      }else if(counter >= goLow && isHigh){
	setLow();
      }else{
	setValue(LED_FULL*(goHigh-counter)/(goHigh+1));
      }
      break;
    case DOWN:
      if(++counter >= goHigh){
	setHigh();
	counter = 0;
      }else if(counter >= goLow && isHigh){
	setLow();
      }else{
	setValue(LED_FULL*counter/(goHigh+1));
      }
      break;
    case OFF:
      counter = 0;
      break;
    }
  }
  void toggle(){
    if(isHigh)
      setLow();
    else
      setHigh();
  }
  void setLow();
  void setHigh();
  void setValue(uint16_t value);
};

template<>
void TapTempo<CH1>::setLow(){
  isHigh = false;
  setPin(TR1_GPIO_Port, TR1_Pin);
  setLed1(0);    
}
template<>
void TapTempo<CH1>::setHigh(){
  isHigh = true;
  clearPin(TR1_GPIO_Port, TR1_Pin);
  setLed1(LED_FULL);
}
template<>
void TapTempo<CH1>::setValue(uint16_t value){
  setLed1(value);  
}

template<>
void TapTempo<CH2>::setLow(){
  isHigh = false;
  setPin(TR2_GPIO_Port, TR2_Pin);
  setLed2(0);    
}
template<>
void TapTempo<CH2>::setHigh(){
  isHigh = true;
  clearPin(TR2_GPIO_Port, TR2_Pin);
  setLed2(LED_FULL);
}
template<>
void TapTempo<CH2>::setValue(uint16_t value){
  setLed2(value);  
}

SineWave sine;
TriangleWave triangle;
RisingRampWave risingRamp;
FallingRampWave fallingRamp;


template<Channel CH>
class Synchroniser {
private:
  Waveform* wave;
  volatile uint32_t trig;
  uint32_t period;
  uint32_t phase;
  uint32_t tuning;
  OperatingMode mode;
public:
  uint16_t speed;
  Synchroniser(Waveform* wv) : 
    wave(wv), trig(TRIGGER_LIMIT), period(0), mode(OFF), speed(4095) {
    setPeriod(period);
  }
  void setWaveform(Waveform* wv){
    wave = wv;
  }
  void setSpeed(int16_t s){
    if(abs(speed-s) > 16){
      int64_t delta = (int64_t)period*(speed-s)/1024;
      period = max(1, period+delta);
      setPeriod(period);
      speed = s;
    }
  }
  void setPeriod(uint32_t t){
    tuning = UINT32_MAX/(t+1);
  }
  void reset(){
    trig = TRIGGER_LIMIT;
    phase = 0;
    wave->reset();
  }
  void setMode(OperatingMode op){
    if(mode != op){
      mode = op;
      if(mode == UP && CH == CH1)
	wave = &sine;
      else if(mode == DOWN && CH == CH1)
	wave = &triangle;
      else if(mode == UP && CH == CH2)
	wave = &risingRamp;
      else if(mode == DOWN && CH == CH2)
	wave = &fallingRamp;
    }
  }
  void trigger(){
    if(trig < TRIGGER_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      period = trig;
      setPeriod(period);
    }
    trig = 0;
    if(CH == CH2) // reset ramp phase on trigger
      phase = 0;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    wave->output(phase);
    phase += tuning;
  }
};

Waveform* waves[] = {&sine, &triangle, &risingRamp, &fallingRamp };
Synchroniser<CH1> synchro1(waves[0]);
Synchroniser<CH2> synchro2(waves[2]);

TapTempo<CH1> tempo1;
TapTempo<CH2> tempo2;

extern "C"{
  void HAL_GPIO_EXTI_Callback(uint16_t pin){
    switch(pin){
    case PUSH1_Pin:
      tempo1.trigger(isPushButton1Pressed());
      break;
    case PUSH2_Pin:
      tempo2.trigger(isPushButton2Pressed());
      break;
    case TEMPO1_Pin:
      synchro1.trigger();
      break;
    case TEMPO2_Pin: 
      synchro2.trigger();
     break;
    }
  }

  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    tempo1.clock();
    synchro1.clock();
    tempo2.clock();
    synchro2.clock();
#ifdef DEBUG_PINS
    togglePin(GPIOB, GPIO_Pin_10); // debug
#endif
  }

  void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    assert_param(0);
  }
  void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  }
}

void updateMode(){
  OperatingMode mode1 = getMode(CH1);
  OperatingMode mode2 = getMode(CH2);
  synchro1.setMode(mode1);
  synchro2.setMode(mode2);
  tempo1.setMode(mode1);
  tempo2.setMode(mode2);
}

void updateSpeed(){
  int16_t p = getAnalogValue(0);
  synchro1.setSpeed(p);
  tempo1.setSpeed(p);
  p = getAnalogValue(1);
  synchro2.setSpeed(p);
  tempo2.setSpeed(p);
}

void setup(){
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 2);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);

  HAL_TIM_Base_Start(&htim1); 
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim3); 
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // configureDigitalInput(SW_L_PORT, SW_R_PIN_A, true);
  // configureDigitalInput(SW_L_PORT, SW_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(SW_R_CLOCK, ENABLE);
  // configureDigitalInput(SW_R_PORT, SW_R_PIN_A, true);
  // configureDigitalInput(SW_R_PORT, SW_R_PIN_B, true);
//   configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
// #ifdef DEBUG_PINS
//   configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
// #endif
//   ledSetup();
  setLed1(0);
  setLed2(0);
  // adcSetup();
  // dacSetup();
  // triggerInputSetup(triggerCallback);
  // pushButtonSetup(buttonCallback);
  // timerSetup(TIMER_PERIOD, timerCallback);
  updateSpeed();
  // synchro1.speed = getAnalogValue(0);
  // tempo1.speed = getAnalogValue(1);
  synchro1.reset();
  synchro2.reset();
  tempo1.reset();
  tempo2.reset();
  setPeriod(300);
}

void loop(){
  updateMode();
  updateSpeed();
}
