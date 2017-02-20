#include <stdlib.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "periph.h"
#include "qint.h"

#define ATTACK1  2
#define ATTACK2  3
#define RELEASE1 4
#define RELEASE2 5
#define SHAPE1   0
#define SHAPE2   1

// #define DEBUG_PINS_CLOCK
// #define DEBUG_PINS_MAIN

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif /* min */
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif /* max */
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

extern "C"{
  void setup();
  void loop();
  extern DAC_HandleTypeDef hdac;
  extern ADC_HandleTypeDef hadc1;
  extern TIM_HandleTypeDef htim1; // LED1
  extern TIM_HandleTypeDef htim2; // internal clock
  extern TIM_HandleTypeDef htim3; // LED2
  extern TIM_HandleTypeDef htim4; // TEMPO_OUT
  extern TIM_HandleTypeDef htim6; // DAC trigger
}

enum Channel {
  CH1, CH2
};

enum OperatingMode {
  CYCLE_MODE, GATE_MODE, TRIGGER_MODE
};

OperatingMode getMode(Channel ch){  
  switch(ch){
  case CH1:
    if(!getPin(SW1A_GPIO_Port, SW1A_Pin))
      return CYCLE_MODE;
    else if(!getPin(SW1B_GPIO_Port, SW1B_Pin))
      return TRIGGER_MODE;
    else
      return GATE_MODE;
  case CH2:
    if(!getPin(SW2A_GPIO_Port, SW2A_Pin))
      return CYCLE_MODE;
    else if(!getPin(SW2B_GPIO_Port, SW2B_Pin))
      return TRIGGER_MODE;
    else
      return GATE_MODE;
  }
  return GATE_MODE;
}

uint16_t adc_values[6];
uint16_t dac_values[2];

uint16_t getAnalogValue(uint8_t index){
  return adc_values[index];
}

void setAnalogValue(Channel ch, uint16_t value){
  value &= 0xfff;
  if(ch == CH1)
    dac_values[0] = value;
  else if(ch == CH2)
    dac_values[1] = value;
}

// template<Channel CH>
// void setLed(uint16_t brightness);

void setLed(Channel ch, uint16_t brightness){
  switch(ch){
  case CH1:
    setLed1(brightness);
    break;
  case CH2:
    setLed2(brightness);
    break;
  }
}

// template<Channel CH>
// bool isTriggerHigh();

bool isTriggerHigh(Channel ch){
  if(ch == CH1)
    return !getPin(TR1_GPIO_Port, TR1_Pin);
  return !getPin(TR2_GPIO_Port, TR2_Pin);
}

bool isTriggerLow(Channel ch){
  if(ch == CH1)
    return getPin(TR1_GPIO_Port, TR1_Pin);
  return getPin(TR2_GPIO_Port, TR2_Pin);
}

#define TAP_THRESHOLD     256 // 78Hz at 20kHz sampling rate, or 16th notes at 293BPM
#define TRIGGER_LIMIT     UINT32_MAX

enum Stage {
  ATTACK_STAGE, SUSTAIN_STAGE, RELEASE_STAGE, END_STAGE
};

// #define DAC_SCALAR 18
// #define LED_SCALAR 22
// #define MAX_LEVEL (3960<<18) // 3960 appears to be at DAC maximum excursion
// #define MIN_LEVEL (1<<10)

int32_t ADC_RANGE = 4040;
int32_t DAC_RANGE = 3968;
// #define DAC_SCALAR 6
int32_t DAC_SCALAR =  6;
// #define ADC_SCALAR (DAC_SCALAR-6)
int32_t ADC_SCALAR =  (DAC_SCALAR-4);
#define LED_SCALAR (DAC_SCALAR+5)
// #define SKEW_SCALAR 21
int32_t SKEW_SCALAR = 10+DAC_SCALAR;
#define MAX_LEVEL (DAC_RANGE<<DAC_SCALAR)
#define MIN_LEVEL 0
// #define MID_LEVEL (MAX_LEVEL>>1)
int32_t MID_LEVEL = MAX_LEVEL>>1;
#define MIN_SLOPE 1

template<Channel CH>
class Envelope {
public:
  int32_t level;
  int32_t linear;
  volatile OperatingMode mode;  
  volatile int32_t attack;
  volatile int32_t release;
  volatile int32_t attack_skew;
  volatile int32_t release_skew;
  volatile Stage stage;
  Envelope() :
    level(MIN_LEVEL), linear(-MID_LEVEL), mode(GATE_MODE), attack(0), release(0), attack_skew(0), release_skew(0), stage(END_STAGE) {}
  void setAttack(int32_t value, int32_t skew){
    value = min(ADC_RANGE-1, value);
    attack = max(MIN_SLOPE, MAX_LEVEL/((ADC_RANGE - value)<<ADC_SCALAR));
    attack_skew = (attack*skew)>>11;
  }
  void setRelease(int32_t value, int32_t skew){
    value = min(ADC_RANGE-1, value);
    release = max(MIN_SLOPE,  MAX_LEVEL/((ADC_RANGE - value)<<ADC_SCALAR));
    release_skew = (release*skew)>>11;
  }
  void clock(){
    switch(stage){
    case ATTACK_STAGE:
      level += max(1, attack + ((linear*attack_skew)>>SKEW_SCALAR));
      linear += attack;
      if(linear >= MID_LEVEL){
	linear = MID_LEVEL;
	stage = SUSTAIN_STAGE;
      }
      break;
    case SUSTAIN_STAGE:
      if(mode != GATE_MODE || isTriggerLow(CH))
	stage = RELEASE_STAGE;
      break;
    case RELEASE_STAGE:
      level -= max(1, release - ((linear*release_skew)>>SKEW_SCALAR));
      linear -= release;
      if(linear <= -MID_LEVEL){
	linear = -MID_LEVEL;
	level = MIN_LEVEL;
	stage = END_STAGE;
      }
      break;
    case END_STAGE:
      if(mode == CYCLE_MODE)
	stage = ATTACK_STAGE;
    }
    level = max(0, min(MAX_LEVEL, level));
    setAnalogValue(CH, level>>DAC_SCALAR);
    setLed(CH, (level>>LED_SCALAR)&0x7f);
  }
  void trigger(){
    stage = ATTACK_STAGE;
    // level = MIN_LEVEL;
  }
};

class TapTempo {
private:
  uint32_t trig;
public:
  uint32_t period;
  TapTempo() : trig(0), period(TRIGGER_LIMIT>>1) {}
  void trigger(){
    if(trig < TAP_THRESHOLD)
      return;
    if(trig < TRIGGER_LIMIT){
      period = trig;
      trig = 0;
    }else{
      trig = 0;
    }
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
  }
};

TapTempo tempo;
Envelope<CH1> env1;
Envelope<CH2> env2;

extern "C"{
  void HAL_GPIO_EXTI_Callback(uint16_t pin){
    switch(pin){
    case TR1_Pin:
      env1.trigger();
      break;
    case TR2_Pin:
      env2.trigger();
      break;
    case TEMPOIN_Pin:
      tempo.trigger();
      break;
    }
  }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
#ifdef DEBUG_PINS_CLOCK
  setPin(TEMPOOUT_GPIO_Port, TEMPOOUT_Pin);
#endif
  tempo.clock();
  env1.clock();
  env2.clock();
#ifdef DEBUG_PINS_CLOCK
  clearPin(TEMPOOUT_GPIO_Port, TEMPOOUT_Pin);
#endif
}

  // void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  // }

  void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    assert_param(0);
  }
  void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }
  void HAL_DAC_ErrorCallbackCh2(DAC_HandleTypeDef *hdac){
    assert_param(0);
  }
}

void updateMode(){
  env1.mode = getMode(CH1);
  env2.mode = getMode(CH2);
}

#define NOMINAL_PERIOD 9000 // 1.33Hz, 80BPM, at 12kHz
void updateParameters(){
  int32_t skew = 2048 - getAnalogValue(SHAPE1);
  int32_t period = tempo.period;
  int32_t value = (getAnalogValue(ATTACK1)*period)/NOMINAL_PERIOD;
  env1.setAttack(value, skew);
  value = (getAnalogValue(RELEASE1)*period)/NOMINAL_PERIOD;
  env1.setRelease(value, skew);
  skew = 2048 - getAnalogValue(SHAPE2);
  value = (getAnalogValue(ATTACK2)*period)/NOMINAL_PERIOD;
  env2.setAttack(value, skew);
  value = (getAnalogValue(RELEASE2)*period)/NOMINAL_PERIOD;
  env2.setRelease(value, skew);
}

void setup(){
  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)&dac_values[0], 1, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)&dac_values[1], 1, DAC_ALIGN_12B_R);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 6);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);

  HAL_TIM_Base_Start(&htim1); 
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim3); 
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim4); 
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

  setLed1(LED_FULL/2);
  setLed2(LED_FULL/2);

  updateMode();
  updateParameters();
}

void loop(){
#ifdef DEBUG_PINS_MAIN
  setPin(TEMPOOUT_GPIO_Port, TEMPOOUT_Pin);
#endif
  updateMode();
  updateParameters();
#ifdef DEBUG_PINS_MAIN
  clearPin(TEMPOOUT_GPIO_Port, TEMPOOUT_Pin);
#endif
}
