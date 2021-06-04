#include "spi.h"

#include <avr/io.h>

#define SCK_DDR  DDRB
#define SCK_PIN  PB5      // SCK clock pin
#define SCK_PORT PORTB
#define SDI_DDR  DDRB
#define SDI_PIN  PB3      // SDI MOSI pin: master out, slave in
#define SDI_PORT PORTB

void spi_init(){
  // set pins to output
  SCK_DDR |= _BV(SCK_PIN);
  SDI_DDR |= _BV(SDI_PIN);
  // Enable SPI, Master, set clock rate fck/16 
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}

static void spi_transfer(uint8_t value) {
  SPDR = value;
  while(!(SPSR & _BV(SPIF))); 
}

void spi_out(uint8_t high, uint8_t low) {
  spi_transfer(high);
  spi_transfer(low);
}
