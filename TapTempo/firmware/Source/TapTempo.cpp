#include <stdlib.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "DDS.h"
#include "gpio.h"
#include "periph.h"

// #define DEBUG_PINS

extern "C"{
  void setup();
  void loop();
  extern DAC_HandleTypeDef hdac;
  extern ADC_HandleTypeDef hadc1;
  extern TIM_HandleTypeDef htim1; // LED1
  extern TIM_HandleTypeDef htim2; // internal clock
  extern TIM_HandleTypeDef htim3; // LED2
  extern TIM_HandleTypeDef htim6; // DAC trigger
}

#define NOF_ADC_VALUES 2
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
      return DOWN;
    else if(!getPin(SW1B_GPIO_Port, SW1B_Pin))
      return UP;
    else
      return OFF;
  case CH2:
    if(!getPin(SW2A_GPIO_Port, SW2A_Pin))
      return DOWN;
    else if(!getPin(SW2B_GPIO_Port, SW2B_Pin))
      return UP;
    else
      return OFF;
  }
  return OFF;
}

// void setClock(uint16_t value){
//   TIM2->CCR1 = value;
// }

uint16_t dac_values[4];
void setAnalogValue(Channel ch, uint16_t value){
  value &= 0xfff;
  if(ch == CH1)
    dac_values[0] = value;
  else if(ch == CH2)
    dac_values[1] = value;
  // if(ch == CH1)
  //   HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
  //   // DAC_SetChannel1Data(DAC_Align_12b_R, value);
  // else if(ch == CH2)
  //   HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, value);
  //   // DAC_SetChannel2Data(DAC_Align_12b_R, value);
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


DDS dds;

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
  volatile OperatingMode mode;
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
#ifndef DEBUG_PINS
  setPin(TR1_GPIO_Port, TR1_Pin);
#endif
  setLed1(0);    
}
template<>
void TapTempo<CH1>::setHigh(){
  isHigh = true;
#ifndef DEBUG_PINS
  clearPin(TR1_GPIO_Port, TR1_Pin);
#endif
  setLed1(LED_FULL);
}
template<>
void TapTempo<CH1>::setValue(uint16_t value){
  setLed1(value);  
}

template<>
void TapTempo<CH2>::setLow(){
  isHigh = false;
#ifndef DEBUG_PINS
  setPin(TR2_GPIO_Port, TR2_Pin);
#endif
  setLed2(0);    
}
template<>
void TapTempo<CH2>::setHigh(){
  isHigh = true;
#ifndef DEBUG_PINS
  clearPin(TR2_GPIO_Port, TR2_Pin);
#endif
  setLed2(LED_FULL);
}
template<>
void TapTempo<CH2>::setValue(uint16_t value){
  setLed2(value);  
}

template<Channel CH>
class Synchroniser {
private:
  volatile uint32_t trig;
  volatile uint32_t ticks;
  volatile uint32_t period;
  volatile uint32_t phase;
  volatile uint32_t tuning;
  volatile OperatingMode mode;
  OperatingMode previousMode;
public:
  uint16_t speed;
  Synchroniser() : 
    trig(TRIGGER_LIMIT), ticks(0), period(TRIGGER_LIMIT), mode(OFF), speed(4095) {
    setPeriod(period);
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
  void setMode(OperatingMode op){
    if(op != mode && op == OFF){
      previousMode = mode;
      reset();
    }
    mode = op;
  }
  void trigger(){
    switch(mode){
    case OFF: // one shot mode
      ticks = 1; // start period
      if(CH == CH2) // reset ramp phase on trigger
	phase = 0;
      break;
    default:
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
  }
  void reset(){
    setZeroValue();
    trig = TRIGGER_LIMIT; // really?
    phase = 0;
    ticks = 0; // stop ping
  }
  void clock(){
    switch(mode){
    case UP:
      setUpValue(phase);
      phase += tuning; 
      if(trig < TRIGGER_LIMIT)
	trig++;
     break;
    case DOWN:
      setDownValue(phase);
      phase += tuning;
      if(trig < TRIGGER_LIMIT)
	trig++;
      break;
    case OFF:
      if(ticks){ // one shot mode
	switch(previousMode){
	case UP:
	  setUpValue(phase);
	  phase += tuning;
	  break;
	case DOWN:
	  setDownValue(phase);
	  phase += tuning;
	  break;
	default:
	  break;
	}
	if(ticks++ >= period)
	  reset();
      }
    }
  }
  void setUpValue(uint32_t phase);
  void setDownValue(uint32_t phase);
  void setZeroValue();
};

template<>
void Synchroniser<CH1>::setUpValue(uint32_t phase){
  setAnalogValue(CH1, dds.getSine(phase));
}
template<>
void Synchroniser<CH1>::setDownValue(uint32_t phase){
  setAnalogValue(CH1, dds.getTri(phase));
}
template<>
void Synchroniser<CH1>::setZeroValue(){
  setAnalogValue(CH1, DDS_SINE_ZERO_VALUE);
}
template<>
void Synchroniser<CH2>::setUpValue(uint32_t phase){
  setAnalogValue(CH2, dds.getRisingRamp(phase));
}
template<>
void Synchroniser<CH2>::setDownValue(uint32_t phase){
  setAnalogValue(CH2, dds.getFallingRamp(phase));
}
template<>
void Synchroniser<CH2>::setZeroValue(){
  setAnalogValue(CH2, DDS_RAMP_ZERO_VALUE);
}

Synchroniser<CH1> synchro1;
Synchroniser<CH2> synchro2;

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
#ifdef DEBUG_PINS
    clearPin(TR2_GPIO_Port, TR2_Pin);
#endif
    tempo1.clock();
    synchro1.clock();
    tempo2.clock();
    synchro2.clock();
#ifdef DEBUG_PINS
    setPin(TR2_GPIO_Port, TR2_Pin);
#endif
  }

  void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    assert_param(0);
  }
  // void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  // }

  void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }

  void HAL_DAC_ErrorCallbackCh2(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }
}

void updateMode(){
  OperatingMode mode = getMode(CH1);
  synchro1.setMode(mode);
  tempo1.setMode(mode);
  mode = getMode(CH2);
  synchro2.setMode(mode);
  tempo2.setMode(mode);
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
  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)&dac_values[0], 1, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)&dac_values[1], 1, DAC_ALIGN_12B_R);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 2);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);

  HAL_TIM_Base_Start(&htim1); 
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim3); 
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  setLed1(0);
  setLed2(0);

  synchro1.reset();
  synchro2.reset();
  tempo1.reset();
  tempo2.reset();

  synchro1.speed = getAnalogValue(0);
  tempo1.speed = getAnalogValue(0);
  synchro2.speed = getAnalogValue(1);
  tempo2.speed = getAnalogValue(1);

  updateMode();

  // setClock(300);
}

void loop(){
#ifdef DEBUG_PINS
  clearPin(TR1_GPIO_Port, TR1_Pin);
#endif
  updateMode();
  updateSpeed();
#ifdef DEBUG_PINS
  setPin(TR1_GPIO_Port, TR1_Pin);
#endif
}
