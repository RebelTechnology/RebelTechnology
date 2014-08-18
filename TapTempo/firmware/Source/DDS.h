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

#define DDS_ACCUMULATOR_PERIOD UINT32_MAX
#define DDS_ACCUMULATOR_WIDTH  32
#define DDS_DATATYPE           uint32_t

class DDS {
public:
  void init();
  void setFrequency(double freq);
  inline DDS_DATATYPE getPeriod(){
    return DDS_ACCUMULATOR_PERIOD/tuning - 1;
  }
  inline void setPeriod(DDS_DATATYPE t){
    tuning = DDS_ACCUMULATOR_PERIOD/(t+1);
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
    return accumulator >> (DDS_ACCUMULATOR_WIDTH - 12);
  }
  inline uint16_t getTri(){
    uint16_t tri = accumulator >> (DDS_ACCUMULATOR_WIDTH - 13);
    return 4095 - min(abs(4095 - tri), 4095);
  }
  uint16_t getSine();

private:
  volatile DDS_DATATYPE accumulator;   // phase accumulator
  volatile DDS_DATATYPE tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
