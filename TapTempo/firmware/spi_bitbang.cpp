#include "spi.h"

#include <wiring.h>

#define CS_PIN   9       // CS slave select pin
#define SCK_PIN  13      // SCK clock pin
#define SDI_PIN  11      // SDI MOSI pin: master out, slave in

static void spi_transfer(uint8_t working) {
  // function to actually bit shift the data byte out
  for(int i = 1; i <= 8; i++) {
    if(working > 127)
      digitalWrite (SDI_PIN, HIGH); // if it is a 1 (ie. B1XXXXXXX), set the master out pin high
    else
      digitalWrite (SDI_PIN, LOW); // if it is not 1 (ie. B0XXXXXXX), set the master out pin low
    digitalWrite (SCK_PIN, HIGH); // set clock high, the pot IC will read the bit into its register
    working = working << 1;
    digitalWrite(SCK_PIN, LOW); // set clock low, the pot IC will stop reading and prepare for the next iteration (next significant bit
  }
}

static void spi_out(uint8_t high, uint8_t low) {
  digitalWrite(CS_PIN, LOW);
  spi_transfer(high);
  spi_transfer(low);
  digitalWrite(CS_PIN, HIGH);
}

static void spi_init() {
  pinMode(CS_PIN, OUTPUT); // set CS pin to output
  pinMode(SCK_PIN, OUTPUT); // set SCK pin to output
  pinMode(SDI_PIN, OUTPUT); // set MOSI pin to output
  digitalWrite(CS_PIN, HIGH); // hold slave select 1 pin high, so that chip is not selected to begin with
}
