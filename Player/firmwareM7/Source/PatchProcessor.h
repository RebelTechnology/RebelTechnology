#ifndef __PatchProcessor_h__
#define __PatchProcessor_h__

#include <stdint.h>
#include "StompBox.h"
#include "SampleBuffer.hpp"
#include "device.h"

class PatchProcessor {
public:  
  PatchProcessor();
  ~PatchProcessor();
  void clear();
  void setPatch(Patch* patch);
  void run();
  float getParameterValue(PatchParameterId pid);
  void setParameterValues(int16_t *parameters);
  Patch* patch;
private:
  SampleBuffer buffer;
  int16_t parameterValues[NOF_ADC_VALUES];
};

#endif // __PatchProcessor_h__
