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
  if(argc > 1)
    len = atoi(argv[1]);
  if(argc > 1)
    lim = atoi(argv[2]);
  int sinwave[len];
  int i;
  FILE *sinmif,*cosmif,*trimif;
  for(i=0;i<len;i++){ 
    sinwave[i]=(int)((sin(i*2*M_PI/(lim-1))+1)*(lim/2));
    printf("%d:%d\n", i, sinwave[i]);
  }
}
