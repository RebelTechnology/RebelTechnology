#include "DDS.h"

#ifdef DDS_PGMSPACE
#include "avr/pgmspace.h"
#endif

// #include "avr/math.h"
#include <math.h>

#define REFCLK (double)31372.549

#ifdef DDS_PGMSPACE
PROGMEM prog_uchar wavetable[]  = {
#else
uint8_t wavetable[256] = {
#endif
  0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 15, 16, 18, 20, 21, 23, 25, 27, 29, 31, 33, 35, 37, 40, 42, 44, 47, 49, 52, 54, 57, 59, 62, 65, 68, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 113, 116, 119, 122, 125, 128, 131, 135, 138, 141, 144, 147, 150, 153, 156, 159, 163, 166, 169, 172, 174, 177, 180, 183, 186, 189, 192, 194, 197, 200, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 236, 238, 240, 241, 242, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 242, 241, 240, 238, 236, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 214, 212, 210, 207, 205, 202, 200, 197, 194, 191, 189, 186, 183, 180, 177, 174, 172, 169, 166, 163, 159, 156, 153, 150, 147, 144, 141, 138, 135, 131, 128, 125, 122, 119, 116, 113, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 76, 73, 70, 68, 65, 62, 59, 57, 54, 52, 49, 47, 44, 42, 40, 37, 35, 33, 31, 29, 27, 25, 23, 21, 20, 18, 16, 15, 13, 12, 11, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0
};

void DDS::init(){
  setFrequency(1000.0);
}

void DDS::setFrequency(double freq){
//   tuning = (uint16_t)(pow(2,32)*freq/REFCLK); // calulate DDS new tuning word
  tuning = (uint16_t)(pow(2,16)*freq/REFCLK); // calulate DDS new tuning word
//   tword_m = (unsigned long)(pow(2,32)*freq/REFCLK); // calulate DDS new tuning word
//   tword_m = (unsigned long)((1<<32)*freq/REFCLK); // calulate DDS new tuning word
}

uint8_t DDS::getValue(){
  accumulator += tuning; // soft DDS, phase accu with 32 bits
  uint8_t icnt = accumulator >> 8;     // use upper 8 bits for phase accu as frequency
  //   icnt = phaccu >> 24;     // use upper 8 bits for phase accu as frequency information
  // read value from wave table
#ifdef DDS_PGMSPACE
  return pgm_read_byte_near(wavetable + icnt);
#else
  return wavetable[icnt];
#endif
}
