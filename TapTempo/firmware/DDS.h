#ifndef _DDS_H_
#define _DDS_H_

#include <stdint.h>

#define DDS_ACCUMULATOR_PERIOD 4294967295LL

class DDS {
public:
  void init();
  uint16_t getValue();
  void setFrequency(double freq);
  inline void setPeriod(uint32_t t){
    tuning = DDS_ACCUMULATOR_PERIOD/t;
  }
  inline void reset(){
    accumulator = 0;
  }
private:
  volatile uint32_t accumulator;   // phase accumulator
  volatile uint32_t tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
