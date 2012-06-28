#ifndef _EEPROM_H_
#define _EEPROM_H_ 1

#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t eeprom_read_byte (const uint8_t *addr);

uint16_t eeprom_read_word (const uint16_t *addr);

void eeprom_read_block (void *pointer_ram,
                   const void *pointer_eeprom,
                   size_t size);

void eeprom_write_byte (uint8_t *addr,uint8_t value);

void eeprom_write_word (uint16_t *addr,uint16_t value);

void eeprom_write_block (const void *pointer_ram,
                    void *pointer_eeprom,
                    size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _EEPROM_H_ */
