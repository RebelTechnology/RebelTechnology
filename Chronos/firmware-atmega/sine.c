#include "stdio.h"
#include "math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEFAULT_LENGTH 256
#define DEFAULT_HEIGHT 256

int main(int argc, char **argv){
  int len = DEFAULT_LENGTH;
  int lim = DEFAULT_HEIGHT;
  float ph = 0;
  if(argc > 1)
    len = atoi(argv[1]);
  if(argc > 2)
    lim = atoi(argv[2]);
  if(argc > 3)
    ph = M_PI*atoi(argv[3])/4.0;
  int i;
  printf("/* sine wavetable %d x %d */\n", lim, len);
  printf("int sine[%d] = { ", len);
  for(i=0; i<len; i++){ 
    int s =(int)((sin(i*2*M_PI/(len-1)+ph)+1)*(lim/2));
    printf("%d, ", s);
  }
  printf(" };\n");
}
