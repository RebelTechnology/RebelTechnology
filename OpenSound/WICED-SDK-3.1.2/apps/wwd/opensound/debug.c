#include "debug.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

void debug_printf(const char* fmt, ...) {
  const uint16_t bufsize = 128;
   char buff[bufsize];
   va_list args;
   va_start(args, fmt);
   vsnprintf(buff, bufsize, fmt, args);
   va_end(args);
   debug_message(buff);
}
