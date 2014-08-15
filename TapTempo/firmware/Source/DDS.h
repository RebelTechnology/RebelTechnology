#ifndef _DDS_H_
#define _DDS_H_

#include <stdint.h>

/* #define DDS_ACCUMULATOR_PERIOD 4294967295LL */
#define DDS_ACCUMULATOR_PERIOD UINT64_MAX

class DDS {
public:
  void init();
  uint16_t getValue();
  void setFrequency(double freq);
  inline void setPeriod(uint64_t t){
    tuning = DDS_ACCUMULATOR_PERIOD/t+1;
  }
  inline void reset(){
    accumulator = 0;
  }
  inline uint16_t getRamp(){
    return accumulator >> 52;
  }

private:
  volatile uint64_t accumulator;   // phase accumulator
  volatile uint64_t tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
