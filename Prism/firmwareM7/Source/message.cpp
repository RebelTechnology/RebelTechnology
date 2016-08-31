#include "message.h"
#include <string.h>

static char buffer[64];
static const char hexnumerals[] = "0123456789abcdef";

#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

static char* itoa(int val, int base, int pad){
  static char buf[13] = {0};
  int i = 11;
  unsigned int part = abs(val);
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(i && (--pad > 0 || part));
  if(val < 0)
    buf[i--] = '-';
  return &buf[i+1];
}

static char* itoa(int val, int base){
  return itoa(val, base, 0);
}

static char* ftoa(float val, int base){
  static char buf[16] = {0};
  int i = 14;
  // print 4 decimal points
  unsigned int part = abs((int)((val-int(val))*10000));
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(i>10);
  buf[i--] = '.';
  part = abs(int(val));
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(part && i);
  if(val < 0.0f)
    buf[i--] = '-';
  return &buf[i+1];
}

static const char* debugmessage;
const char* getDebugMessage(){
  return debugmessage;
}

// semihosting
// static void put_char(char c){
//     asm (
//     "mov r0, #0x03\n"   /* SYS_WRITEC */
//     "mov r1, %[msg]\n"
//     "bkpt #0xAB\n"
//     :
//     : [msg] "r" (&c)
//     : "r0", "r1"
//     );
// }

void setDebugMessage(const char* msg){
  // size_t len = strnlen(msg, sizeof(buffer));
  // for(int i=0; i<len; ++i)
  //   put_char(msg[i]);
  debugmessage = msg;
}

void debugMessage(const char* msg){
  strlcpy(buffer, msg, 64);
}

void debugMessage(const char* msg, int a){
  char* p = buffer;
  p = stpncpy(p, msg, 48);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(a, 10));
  setDebugMessage(buffer);
}

void debugMessage(const char* msg, int a, int b){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(b, 10));
  setDebugMessage(buffer);
}

void debugMessage(const char* msg, int a, int b, int c){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(b, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, itoa(c, 10));
  setDebugMessage(buffer);
}

void debugMessage(const char* msg, float a){
  char* p = buffer;
  p = stpncpy(p, msg, 48);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(a, 10));
  setDebugMessage(buffer);
}

void debugMessage(const char* msg, float a, float b){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(b, 10));
  setDebugMessage(buffer);
}

void debugMessage(const char* msg, float a, float b, float c){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(b, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, ftoa(c, 10));
  setDebugMessage(buffer);
}

// void error(int8_t code, const char* reason){
//   ProgramVector* vec = getProgramVector();
//   if(vec != NULL){
//     vec->error = code;
//     vec->message = (char*)reason;
//     if(vec->programStatus != NULL)
//       vec->programStatus(AUDIO_ERROR_STATUS);
//   }
// }

// void assert_failed(const char* msg, const char* location, int line){
//   char* p = buffer;
//   p = stpncpy(p, msg, 32);
//   p = stpcpy(p, (const char*)" in ");
//   p = stpncpy(p, location, 32);
//   p = stpcpy(p, (const char*)" line ");
//   p = stpcpy(p, itoa(line, 10));
//   getDebugMessage() = buffer;
//   if(getProgramVector()->programStatus != NULL)
//     getProgramVector()->programStatus(AUDIO_ERROR_STATUS);
// }

// void assert_failed(uint8_t* location, uint32_t line){
//   assert_failed("Assertion Failed", (const char*)location, line);
// }

Debug debug;

void Debug::print(char arg){
  if(getDebugMessage() != buffer)
    pos = 0;
  if(pos < sizeof(buffer)-1)
    buffer[pos++] = arg;
  setDebugMessage(buffer);
}

void Debug::print(const char* arg){
  if(getDebugMessage() != buffer)
    pos = 0;
  char* p = buffer+pos;
  p = stpncpy(p, arg, sizeof(buffer)-pos);
  pos = p-buffer;
  setDebugMessage(buffer);
}

void Debug::print(float arg){
  if(getDebugMessage() != buffer)
    pos = 0;
  char* p = buffer+pos;
  p = stpncpy(p, ftoa(arg, 10), sizeof(buffer)-pos);
  pos = p-buffer;
  setDebugMessage(buffer);
}

void Debug::print(int arg){ 
  if(getDebugMessage() != buffer)
    pos = 0;
  char* p = buffer+pos;
  p = stpncpy(p, itoa(arg, 10), sizeof(buffer)-pos);
  pos = p-buffer;
  setDebugMessage(buffer);
}
