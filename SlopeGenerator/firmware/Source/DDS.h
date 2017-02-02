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

 // calculated zero points
#define DDS_SINE_ZERO_VALUE    2094
#define DDS_RAMP_ZERO_VALUE    3900

#define DDS_MAX_RAMP_VALUE     3700
#define DDS_MIN_RAMP_VALUE     610
#define DDS_RAMP_RANGE         (DDS_MAX_RAMP_VALUE-DDS_MIN_RAMP_VALUE)

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
  inline DDS_DATATYPE inc(){
    return tuning;
  }
  /* return 12-bit waveforms */
  static inline uint16_t getRisingRamp(DDS_DATATYPE accumulator){
    DDS_DATATYPE val = accumulator >> (DDS_ACCUMULATOR_WIDTH - 12);
    return DDS_RAMP_RANGE - (val * DDS_RAMP_RANGE)/4095 + DDS_MIN_RAMP_VALUE;
  }
  static inline uint16_t getFallingRamp(DDS_DATATYPE accumulator){
    DDS_DATATYPE val = accumulator >> (DDS_ACCUMULATOR_WIDTH - 12);
    return (val * DDS_RAMP_RANGE)/4095 + DDS_MIN_RAMP_VALUE;
  }
  /* inline uint16_t getTri(){ */
  /*   uint16_t tri = accumulator >> (DDS_ACCUMULATOR_WIDTH - 13); */
  /*   return 4095 - min(abs(4095 - tri), 4095); */
  /* } */
  static uint16_t getSine(DDS_DATATYPE accumulator);
  static uint16_t getTri(DDS_DATATYPE accumulator);

private:
  volatile DDS_DATATYPE tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
