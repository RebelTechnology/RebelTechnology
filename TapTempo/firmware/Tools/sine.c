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
  float phase = DEFAULT_PHASE;
  if(argc > 1)
    len = atoi(argv[1]);
  if(argc > 2)
    offset = atoi(argv[2]);
  if(argc > 3)
    lim = atoi(argv[3]);
  if(argc > 4)
    phase = atoi(argv[4]);
  int i;
  printf("/* sine wavetable %d values [%d - %d] %d deg phase offset */\n", len, offset, lim, (int)phase);
  printf("const uint16_t sinewave[%d] = { ", len);
  phase = M_PI*atoi(argv[4])/180.0;
  for(i=0; i<len; i++){ 
    int s =(int)((sin(i*2*M_PI/(len-1)+phase)+1)*((lim-offset)/2));
    printf("%d, ", offset+s);
  }
  printf(" };\n");
  return 0;
}
