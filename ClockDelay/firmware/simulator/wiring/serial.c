#include <stdio.h>
#include "../serial.h"

void beginSerial(long baud)
{
  printf("beginSerial %ld\n", baud);
}

void serialWrite(unsigned char c)
{
/*   printf("tx 0x%x\n", c); */
  putchar(c);
}

int serialAvailable(void){
  return 0;
}
int serialRead(void){
  return 0;
}

void serialFlush(void){}
void printByte(unsigned char c){
/*   printf("0x%x", c); */
  putchar(c);
}
void printNewline(void){
  putchar('\n');
}
void printString(const char *s){
  printf("%s", s);
}
void printInteger(long n){
  printf("%ld", n);
}
void printHex(unsigned long n){
  printf("0x%lx", n);
}
void printOctal(unsigned long n){
  printf("0%lo", n);
}
void printBinary(unsigned long n){
  printf("0x%lx", n);
}
void printIntegerInBase(unsigned long n, unsigned long base){}
