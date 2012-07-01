#include "interrupt.h"
#include "io.h"

void sei(void){
  // enable global interrupts: set Status Register flag I
  SREG |= _BV(7);
}

void cli(void){
  SREG &= ~_BV(7);
}
