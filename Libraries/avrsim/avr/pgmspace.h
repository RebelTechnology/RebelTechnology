#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

#define __need_size_t
#include <inttypes.h>
#include <stddef.h>

#define PROGMEM

#ifdef __cplusplus
extern "C" {
#endif

typedef void PROGMEM prog_void;
typedef char PROGMEM prog_char;
typedef unsigned char PROGMEM prog_uchar;
typedef int8_t PROGMEM prog_int8_t;
typedef uint8_t PROGMEM prog_uint8_t;
typedef int16_t PROGMEM prog_int16_t;
typedef uint16_t PROGMEM prog_uint16_t;
typedef int32_t PROGMEM prog_int32_t;
typedef uint32_t PROGMEM prog_uint32_t;
typedef int64_t PROGMEM prog_int64_t;
typedef uint64_t PROGMEM prog_uint64_t;

uint8_t pgm_read_byte_near(prog_uchar* address);

  /*
#define PSTR(s) ((const PROGMEM char *)(s))
#define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))
#define pgm_read_word_near(address_short) __LPM_word((uint16_t)(address_short))
#define pgm_read_dword_near(address_short) 
#define pgm_read_byte_far(address_long)  __ELPM((uint32_t)(address_long))
#define pgm_read_word_far(address_long)  __ELPM_word((uint32_t)(address_long))
#define pgm_read_dword_far(address_long) __ELPM_dword((uint32_t)(address_long))
#define pgm_read_byte(address_short)    pgm_read_byte_near(address_short)
#define pgm_read_word(address_short)    pgm_read_word_near(address_short)
#define pgm_read_dword(address_short)   pgm_read_dword_near(address_short)
  */
#ifdef __cplusplus
}
#endif

#endif /* __PGMSPACE_H_ */
