#include "pgmspace.h"

/* extern prog_uchar typeface[]; */

uint8_t pgm_read_byte_near(prog_uchar* address){
  return *address;
}
