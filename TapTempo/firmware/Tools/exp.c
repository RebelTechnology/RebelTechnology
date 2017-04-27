#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
  double x = 1;
  double y = 1.01;
  int n = 0;
  if(argc > 1)
    n = atol(argv[1]);
  if(argc > 2)
    x = strtod(argv[2], NULL);
  if(argc > 3)
    y = strtod(argv[3], NULL);
  //  printf("from: %d to: %d steps: %d\n", from, to, n);
  /* printf("x: %f y: %f\n", x, y); */
  printf("/* exp table %d values from %d, step %f */\n", n, (int)x, y);
  printf("const int32_t exptable[%d] = { ", n);
  int i;
  for(i=0 ; i < n ; i++){
    printf("%d, ", (int)x) ; 
    x *= y;
  } 
  printf(" };\n");
  return 0;
}

