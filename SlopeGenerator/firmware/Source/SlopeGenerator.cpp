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
  dac_values[ch] = value;
}

#define TAP_THRESHOLD     256 // 78Hz at 20kHz sampling rate, or 16th notes at 293BPM
#define TRIGGER_LIMIT     MAX_PERIOD

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
int32_t DAC_SCALAR = 16;
// #define ADC_SCALAR (DAC_SCALAR-6)
int32_t ADC_SCALAR =  (DAC_SCALAR-4);
#define LED_SCALAR (DAC_SCALAR+5)
// #define SKEW_SCALAR 21
int32_t SKEW_SCALAR = 10+DAC_SCALAR;
int32_t SKEW_SHIFT = 11;
// #define MAX_LEVEL (DAC_RANGE<<DAC_SCALAR)
int32_t MAX_LEVEL = (DAC_RANGE<<DAC_SCALAR);
#define MIN_LEVEL 0
// #define MID_LEVEL (MAX_LEVEL>>1)
int32_t MID_LEVEL = MAX_LEVEL>>1;
int32_t MAX_SLOPE = MAX_LEVEL;// ADC_RANGE*3;
int32_t MIN_SLOPE = 3;
// #define MIN_SLOPE 3

void setConstants(int range = DAC_SCALAR){
 DAC_SCALAR = range;
 ADC_SCALAR =  (DAC_SCALAR-4);
 SKEW_SCALAR = 10+DAC_SCALAR;
 MAX_LEVEL = (DAC_RANGE<<DAC_SCALAR);
 MID_LEVEL = MAX_LEVEL>>1;
 MAX_SLOPE = MAX_LEVEL;// ADC_RANGE*3;
}

#define MIN_PERIOD     720               // 16.66Hz, 1000 BPM
#define MAX_PERIOD (12000*600)           // 0.0016Hz, 0.1 BPM
#define NOMINAL_PERIOD 9000              // 1.33Hz, 80 BPM, at 12kHz

// int32_t ADC_MUL = 15; // 1<<ADC_SCALAR;
int32_t ADC_DIV = 8; // 1<<ADC_SCALAR;

#include "exptable.h"
template<Channel CH>
class Envelope {
public:
  int32_t level;
  int64_t linear;
  volatile OperatingMode mode;
  volatile int32_t attack;
  volatile int32_t release;
  volatile int32_t attack_skew;
  volatile int32_t release_skew;
  volatile Stage stage;
  Envelope() :
    level(MIN_LEVEL), linear(-MID_LEVEL), mode(GATE_MODE), attack(0), release(0), attack_skew(0), release_skew(0), stage(END_STAGE) {}

  int32_t compute(int32_t value, int32_t period){
    value = exptable[value];
    value = ((int64_t)value*NOMINAL_PERIOD)/period;
    value = min(MAX_LEVEL/3, max(1, value));
    return value;
  }  
  void setAttack(int32_t value, int32_t period){
    attack = compute(value, period);
  }
  void setRelease(int32_t value, int32_t period){
    release = compute(value, period);
  }
  void setSkew(int64_t skew){
    release_skew = (release*skew)>>SKEW_SHIFT;
    attack_skew = (attack*skew)>>SKEW_SHIFT;
    factor = skew > 0 ? -COMPENSATION_FACTOR : COMPENSATION_FACTOR;
  }
  float factor = 0.0;
  float COMPENSATION_FACTOR = 2.5;
  /* compensate for skew to ensure that level will reach target in the right time */
  int32_t compensateNonLinear(int32_t lin, int32_t exp){
    return max(-MID_LEVEL, min(MID_LEVEL, lin - factor*(lin + MID_LEVEL - exp)));
  }
  void clock(){
    switch(stage){
    case ATTACK_STAGE:
      level += max(0, attack + ((linear*attack_skew)>>SKEW_SCALAR));
      linear += attack;
      if(linear >= MID_LEVEL){
	linear = MID_LEVEL;
	stage = SUSTAIN_STAGE;
      }else if(mode == GATE_MODE && isTriggerLow()){
	linear = compensateNonLinear(linear, level);
	stage = RELEASE_STAGE;
      }
      break;
    case SUSTAIN_STAGE:
      if(mode != GATE_MODE || isTriggerLow())
	stage = RELEASE_STAGE;
      break;
    case RELEASE_STAGE:
      level -= max(0, release - ((linear*release_skew)>>SKEW_SCALAR));
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
    level = max(MIN_LEVEL, min(MAX_LEVEL, level));
    setAnalogValue(level>>DAC_SCALAR);
    setLed((level>>LED_SCALAR)&0x7f);
  }
  void trigger(){
    if(stage == RELEASE_STAGE)
      linear = compensateNonLinear(linear, level);
    stage = ATTACK_STAGE;
  }
  
  bool isTriggerHigh();
  bool isTriggerLow();
  void setLed(uint16_t brightness);
  void setAnalogValue(uint16_t value);
};

template<>
bool Envelope<CH1>::isTriggerHigh(){
    return !getPin(TR1_GPIO_Port, TR1_Pin);
}
template<>
bool Envelope<CH2>::isTriggerHigh(){
  return !getPin(TR2_GPIO_Port, TR2_Pin);
}
template<>
bool Envelope<CH1>::isTriggerLow(){
    return getPin(TR1_GPIO_Port, TR1_Pin);
}
template<>
bool Envelope<CH2>::isTriggerLow(){
  return getPin(TR2_GPIO_Port, TR2_Pin);
}
template<>
void Envelope<CH1>::setLed(uint16_t brightness){
  setLed1(brightness);
}
template<>
void Envelope<CH2>::setLed(uint16_t brightness){
  setLed2(brightness);
}
template<>
void Envelope<CH1>::setAnalogValue(uint16_t value){
  dac_values[CH1] = value & 0xfff;
}
template<>
void Envelope<CH2>::setAnalogValue(uint16_t value){
  dac_values[CH2] = value & 0xfff;
}

class TapTempo {
private:
  uint32_t trig;
public:
  uint32_t period;
  TapTempo() : trig(MAX_PERIOD), period(NOMINAL_PERIOD) {}
  void trigger(){
    if(trig < MIN_PERIOD)
      return;
    if(trig < MAX_PERIOD){
      period = trig;
      trig = 0;
    }else{
      trig = 0;
    }
  }
  void clock(){
    if(trig < MAX_PERIOD) // prevents overflow
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

void updateParameters(){
  static int32_t period = NOMINAL_PERIOD;
  period = (period + period + period + tempo.period) >> 2;
  period = max(MIN_PERIOD, min(MAX_PERIOD, period));
  env1.setAttack(getAnalogValue(ATTACK1), period);
  env1.setRelease(getAnalogValue(RELEASE1), period);
  env1.setSkew(2048 - getAnalogValue(SHAPE1));
  env2.setAttack(getAnalogValue(ATTACK2), period);
  env2.setRelease(getAnalogValue(RELEASE2), period);
  env2.setSkew(2048 - getAnalogValue(SHAPE2));
}

void setup(){
  setConstants();
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
