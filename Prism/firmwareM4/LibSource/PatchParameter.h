#ifndef __PatchParameter_h__
#define __PatchParameter_h__


#include "SmoothValue.h"

class PatchParameter {
public:
  virtual void update(uint16_t value){}
};

template<type T, type V>
class GenericParameter : public PatchParameter {
private:
  PatchParameterId pid;
  T min, max;
  V value;
public:
  PatchParameter(){}
  PatchParameter(PatchParameterId pid, T min, T max, V initialValue);
  // called when requestParameter() returns to patch constructor
  PatchParameter(const PatchParameter<T>& other);
  void update(uint16_t value);
  /*
  void update(T newValue){
    value = newValue;
  } */
  operator V(){
    return value;
  }
};

template<type T, type V>
GenericParameter<T, V> Patch::requestParameter(const char* name, T min, T max, V defaultValue = V()){
  int pid = 0;
  if(nextPid < 5){
    pid = nextPid++;
    registerParameter(pid, name);
  }
  return GenericParameter<T, V>(PatchParameterId(pid), min, max, defaultValue);
}

template<type T>
GenericParameter<T, SmoothValue<T>> Patch::requestParameter(const char* name, T min, T max, T defaultValue, T lambda){
  requestParameter(name, min, max, SmoothValue<T>(defaultValue, lambda));
}

// Patch {
// FloatParameter requestParameter(const char* name, float min, float max, float defaultValue);
// SmoothFloatParameter requestParameter(const char* name, float min, float max, float defaultValue, float lambda); // lambda between 0.5 and 0.99 - compensate for rate/blocksize
// IntParameter requestParameter(const char* name, int min, int max, int defaultValue);
// StiffIntParameter requestParameter(const char* name, int min, int max, int defaultValue, float delta); // delta between 0 and 1 for 0 to 4095
// };

// exponentially averaged float parameter with hysteresis:
// won't work!
// StiffSmoothFloatParameter spread; spread = requestParameter("spread", 0.0, 1.0, 0.5, 0.9); // how to set stiff delta?
// should be GenericParameter<float, SmoothValue<StiffFloat>> but whole of stiff gets assigned to value of smooth
// typedef StiffSmoothFloatParameter GenericParameter<float, SmoothValue<StiffFloat>>

// default in patch processor to StiffSmoothIntParameter

typedef IntParameter GenericParameter<int, int>;
typedef StiffIntParameter GenericParameter<int, StiffInt>;
typedef SmoothIntParameter GenericParameter<int, SmoothInt>;
typedef FloatParameter GenericParameter<float, float;
typedef StiffFloatParameter GenericParameter<float, StiffFloat>;
typedef SmoothFloatParameter GenericParameter<float, SmoothFloat>;
//FloatParameter spread = requestParameter("Spread", 0.0, 1.0, 0.5);
//SmoothFloatParameter spread = requestParameter("Spread", 0.0, 1.0, SmoothFloat(0.9, 0.5));
//SmoothFloatParameter spread = requestParameter("Spread", 0.0, 1.0, 0.5, 0.9);

template<type T, type V>
GenericParameter<T,V>::GenericParameter<T,V>(PatchParameterId p, T mn, T mx, T v)
: pid(p), min(mn), max(mx), value(v) {}

template<type T, type V>
GenericParameter(const GenericParameter<T,V>& other){
  // register for update callback in copy constructor
  if(pid != NO_PID)
    getCurrentPatchProcessor()->setPatchParameter(pid, this);
}

template<V>
void GenericParameter<int,V>::update(uint16_t newValue){
  value = (newValue*(max-min)+min)/4095;
}

template<V>
void GenericParameter<float,V>::update(uint16_t value){
  value = newValue/4096.0f;
  // should work for <float, float>, <float, SmoothFloat>, and <float, StiffFloat>
}

#endif /* __PatchParameter_h__ */
