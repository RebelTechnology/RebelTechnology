#include "WavetableOscillator.h"
#include "basicmaths.h"
#include <stdint.h>

WavetableOscillator* WavetableOscillator::create(float sr, int size) {
  FloatArray wave = FloatArray::create(size);
  for(int i=0; i<size; ++i)
    wave[i] = sin(2*M_PI*i/(size-1));    
  return new WavetableOscillator(sr, wave);
}

WavetableOscillator::WavetableOscillator(float sr, const FloatArray wavetable): 
  multiplier(1.0/sr),
  wave(wavetable),
  acc(0.0), inc(0.1)
{}

void WavetableOscillator::setSampleRate(float value){
  multiplier = 1.0/value;
}

void WavetableOscillator::setFrequency(float freq){
  //    inc = max(0.0, min(0.5, freq*multiplier));
  inc = freq*multiplier;  
}

float WavetableOscillator::getSample(float phase){
  uint32_t size = wave.getSize();
  uint32_t index = phase*(size-1);
  index = min(index, size-1);
  return wave[index];
}

float WavetableOscillator::getNextSample(){
  float s = getSample(acc);
  acc += inc;
  if(acc > 1.0)
    acc -= 1.0;
  return s;
}

void WavetableOscillator::getSamples(FloatArray samples){
  for(int i=0; i<samples.getSize();++i)
    samples[i] = getNextSample();
}
