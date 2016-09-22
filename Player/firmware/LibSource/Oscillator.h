#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "FloatArray.h"

class Oscillator {
public:
  Oscillator(){}
  virtual ~Oscillator(){}
  virtual float getNextSample() = 0;
  /* Fills @param output with samples */
  virtual void getSamples(FloatArray output){
    for(int i=0; i<output.getSize(); ++i)
      output[i] = getNextSample();
  }
  virtual void setSampleRate(float value){}
  virtual void setFrequency(float value){}
};

#endif /* OSCILLATOR_HPP */
