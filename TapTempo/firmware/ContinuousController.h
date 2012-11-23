#ifndef _CONTINUOUS_CONTROLLER_H_
#define _CONTINUOUS_CONTROLLER_H_

#include "macros.h"
#include "adc_freerunner.h"

class ContinuousController {
 public:
  float value;
  float delta;
  virtual void hasChanged(float v){}
  void update(uint16_t x){
    float v = (float)x/ADC_VALUE_RANGE;
    if(abs(v-value) > delta){
      value = v;
      hasChanged(value);
    }
  }
};

#endif /* _CONTINUOUS_CONTROLLER_H_ */
