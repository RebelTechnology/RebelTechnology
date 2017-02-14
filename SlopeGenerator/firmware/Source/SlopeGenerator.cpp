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
  extern TIM_HandleTypeDef htim1; // LED1
  extern TIM_HandleTypeDef htim2; // internal clock
  extern TIM_HandleTypeDef htim3; // LED2
  extern TIM_HandleTypeDef htim6; // DAC trigger
}

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
  }
  return OFF;
}

#define NOF_ADC_VALUES 12
uint16_t adc_values[NOF_ADC_VALUES];
uint16_t dac_values[4];
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


inline bool isSlowMode(){
  return !getPin(SW1A_GPIO_Port, SW1A_Pin);
}

inline bool isFastMode(){
  return !getPin(SW1B_GPIO_Port, SW1B_Pin);
}

inline bool isSineMode(){
  return !getPin(SW2A_GPIO_Port, SW2A_Pin);
}

inline bool isTriangleMode(){
  return !getPin(SW2B_GPIO_Port, SW2B_Pin);
}

class Synchroniser {
private:
  volatile uint32_t trig;
  uint32_t period;
  bool isHigh;  
  OperatingMode mode;
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
    setAnalogValue(CH1, DDS_RAMP_ZERO_VALUE);
    setAnalogValue(CH2, DDS_SINE_ZERO_VALUE);
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
  void setMode(OperatingMode m){
    if(m == OFF && mode != OFF)
      reset();
    mode = m;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
    if(mode == UP){
      setAnalogValue(CH1, dds.getRisingRamp(saw));
      setAnalogValue(CH2, dds.getSine(sine));
      // DAC_SetDualChannelData(DAC_Align_12b_R, dds.getRisingRamp(saw), dds.getSine(sine));
      saw += dds.inc();
      sine += dds.inc();
    }else if(mode == DOWN){
      setAnalogValue(CH1, dds.getFallingRamp(saw));
      setAnalogValue(CH2, dds.getTri(sine));
      // DAC_SetDualChannelData(DAC_Align_12b_R, dds.getFallingRamp(saw), dds.getTri(sine));
      saw += dds.inc();
      sine += dds.inc();
    }
  }
};

class SlopeGenerator {
private:
  volatile uint32_t counter;
  uint32_t goLow;
  uint32_t goHigh;
  uint32_t trig;
  bool isHigh;  
  bool on;
public:
  uint16_t speed;
  SlopeGenerator() : counter(0), goLow(TRIGGER_LIMIT>>2), goHigh(TRIGGER_LIMIT>>1), 
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
	setLed1(LED_FULL*(goHigh-counter)/(goHigh+1));
      else
	setLed1(LED_FULL*counter/(goHigh+1));
    }
  }
  void setLow(){
    isHigh = false;
    setPin(TR1_GPIO_Port, TR1_Pin);
    setLed1(0);    
  }
  void setHigh(){
    isHigh = true;
    clearPin(TR1_GPIO_Port, TR1_Pin);
    setLed1(LED_FULL);
  }
  void toggle(){
    if(isHigh)
      setLow();
    else
      setHigh();
  }
};

Synchroniser synchro;
SlopeGenerator tempo;

// todo: proper debouncing with systick counter
// void buttonCallback(){
//   tempo.trigger(isPushButtonPressed());
// }

// void triggerCallback(){
//   if(isTriggerHigh()){
//     synchro.trigger();
//   }
// }

extern "C"{
  void HAL_GPIO_EXTI_Callback(uint16_t pin){
    switch(pin){
    case TR1_Pin:
      break;
    case TR2_Pin:
      break;
    case TEMPOIN_Pin:
      break;
    }
  }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
// void timerCallback(){
  tempo.clock();
  synchro.clock();
#ifdef DEBUG_PINS
  togglePin(GPIOB, GPIO_Pin_10); // debug
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
  if(isSineMode()){
    synchro.setMode(UP);
    tempo.setStatus(true);
  }else if(isTriangleMode()){
    synchro.setMode(DOWN);
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

  setLed1(LED_FULL/2);
  setLed2(LED_FULL/2);

  updateSpeed();
  synchro.speed = getAnalogValue(0);
  tempo.speed = getAnalogValue(0);
}


void loop(){
  updateMode();
  updateSpeed();
}
