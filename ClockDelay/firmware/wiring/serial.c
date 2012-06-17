#include <stdio.h>
#include "../serial.h"

void beginSerial(long baud)
{
  printf("beginSerial %ld\n", baud);
}

void serialWrite(unsigned char c)
{
  printf("tx 0x%x\n", c);
}

int serialAvailable(void){
  return 0;
}
int serialRead(void){
  return 0;
}

void serialFlush(void){}
void printByte(unsigned char c){}
void printNewline(void){}
void printString(const char *s){}
void printInteger(long n){}
void printHex(unsigned long n){}
void printOctal(unsigned long n){}
void printBinary(unsigned long n){}
void printIntegerInBase(unsigned long n, unsigned long base){}
