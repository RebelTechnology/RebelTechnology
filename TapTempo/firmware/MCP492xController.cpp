#include "MCP492xController.h"

#include "spi.h"
#include "device.h"
#include <avr/io.h>

// #define TRANSFER_BITS _BV(DAC_SHDN_BIT) // 2x gain
// #define TRANSFER_BITS (_BV(DAC_SHDN_BIT) | _BV(DAC_GA_BIT)) // 1x gain

void MCP492xController::init(uint8_t _cs, uint8_t _transfer_bits) {
  cs = _cs;
  transfer_bits = _transfer_bits;
  CS_DDR |= _BV(cs);
  // hold slave select 1 pin high, so that chip is not selected to begin with
  CS_PORT |= _BV(cs); // HIGH
  spi_init();
}

void MCP492xController::send(uint8_t data){
  send(0, data);
}

void MCP492xController::send(uint8_t high, uint8_t low){
  CS_PORT &= ~_BV(cs); // LOW - chip select
  spi_out(transfer_bits | (high & 0xf), low & 0xff);
  CS_PORT |= _BV(cs); // HIGH
}

void MCP492xController::send(uint16_t data){
  send(data >> 8 & 0xf, data & 0xff);
}
