#ifndef _DDS_H_
#define _DDS_H_

#include <stdint.h>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif /* min */
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif /* max */
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

#define DDS_ACCUMULATOR_PERIOD UINT64_MAX

class DDS {
public:
  void init();
  void setFrequency(double freq);
  inline uint64_t getPeriod(){
    return DDS_ACCUMULATOR_PERIOD/tuning - 1;
  }
  inline void setPeriod(uint64_t t){
    tuning = DDS_ACCUMULATOR_PERIOD/(t+1);
  }
  inline void tune(int32_t adj){
    tuning += adj;
  }
  inline void reset(){
    accumulator = 0;
  }
  /* increment phase accumulator */
  inline void clock(){
    accumulator += tuning;
  }
  /* return 12-bit waveforms */
  inline uint16_t getRamp(){
    return accumulator >> 52;
  }
  inline uint16_t getTri(){
    uint16_t tri = accumulator >> 51;
    return 4095 - min(abs(4095 - tri), 4095);
  }
  uint16_t getSine();

private:
  volatile uint64_t accumulator;   // phase accumulator
  volatile uint64_t tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
