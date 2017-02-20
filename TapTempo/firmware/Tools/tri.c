#include "stdio.h"
#include "math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEFAULT_LENGTH 256
#define DEFAULT_OFFSET 0
#define DEFAULT_HEIGHT 256
#define DEFAULT_PHASE 0

int main(int argc, char **argv){
  int len = DEFAULT_LENGTH;
  int lim = DEFAULT_HEIGHT;
  int offset = DEFAULT_OFFSET;
  int phase = DEFAULT_PHASE;
  if(argc > 1)
    len = atoi(argv[1]);
  if(argc > 2)
    offset = atoi(argv[2]);
  if(argc > 3)
    lim = atoi(argv[3]);
  if(argc > 4)
    phase = atoi(argv[4]);
  int i;
  float incr = 2.0f*(lim-offset)/len;
  printf("/* triangle wavetable %d values [%d - %d] %d deg phase offset, %f increments */\n", len, offset, lim, phase, incr);
  phase *= len/360.0f;
  float value = (lim-offset)/2;
  printf("const uint16_t trianglewave[%d] = { ", len);
  for(i=0; i<len+phase; i++){
    if(i >= phase)
      printf("%d, ", (int)value);
    value += incr;
    if(value >= lim){
      incr *= -1;
      value += incr;
    }else if(value <= offset){
      incr *= -1;
      value += incr;
    }
  }
  printf(" };\n");
  return 0;
}
