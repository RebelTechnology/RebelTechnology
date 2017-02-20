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
    x = atof(argv[2]);
  if(argc > 3)
    y = atof(argv[3]);
  //  printf("from: %d to: %d steps: %d\n", from, to, n);
  printf("x: %f y: %f\n", x, y);
  int i;
  for(i=0 ; i < n ; i++){
    printf("%d, ", (int)x) ; 
    x *= y;
  } 

  return 0;
}

