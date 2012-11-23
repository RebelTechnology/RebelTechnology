#include "spi.h"

#include <avr/io.h>

#define SCK_DDR  DDRB
#define SCK_PIN  PB5      // SCK clock pin
#define SCK_PORT PORTB
#define SDI_DDR  DDRB
#define SDI_PIN  PB3      // SDI MOSI pin: master out, slave in
#define SDI_PORT PORTB

static void spi_transfer(uint8_t value) {
  for(uint8_t i=0x80; i; i>>=1){
    if(value & i)
      SDI_PORT |= _BV(SDI_PIN);
    else
      SDI_PORT &= ~_BV(SDI_PIN);
    // clock
    SCK_PORT |= _BV(SCK_PIN); // HIGH
    SCK_PORT &= ~_BV(SCK_PIN); // LOW
  }
}

void spi_out(uint8_t high, uint8_t low) {
  spi_transfer(high);
  spi_transfer(low);
}

void spi_init(){
  // set pins to output
  SCK_DDR |= _BV(SCK_PIN);
  SDI_DDR |= _BV(SDI_PIN);
}
