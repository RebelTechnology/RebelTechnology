#include <math.h>
#include "DDS.h"

// #define REFCLK (double)31372.549
#include "sinewave.h"
#include "trianglewave.h"

void DDS::init(){
  setPeriod(0);
  // setFrequency(1000.0);
}

// void DDS::setFrequency(double freq){
//   tuning = (uint32_t)(pow(2, 32)*freq/REFCLK); // calulate DDS new tuning word
// //   tword_m = (unsigned long)(pow(2,32)*freq/REFCLK); // calulate DDS new tuning word
// }

uint16_t DDS::getSine(DDS_DATATYPE accumulator){
  uint16_t icnt = accumulator >> (DDS_ACCUMULATOR_WIDTH - 12); // use upper bits of phase accumulator
  // read value from wave table
  return sinewave[icnt];
}

uint16_t DDS::getTri(DDS_DATATYPE accumulator){
  uint16_t icnt = accumulator >> (DDS_ACCUMULATOR_WIDTH - 12);
  return trianglewave[icnt];
}
