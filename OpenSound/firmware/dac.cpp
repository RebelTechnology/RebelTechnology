#include "dac.h"
#include "application.h"

const int DAC_CS_PIN        = A2;
const int DAC_SCK_PIN       = A3;
const int DAC_SDI_PIN       = A5;

#define DAC_A_B_BIT   (1<<7) // 0=DAC A, 1=DAC b
#define DAC_BUF_BIT   (1<<6)
#define DAC_GA_BIT    (1<<5) // 0=2x, 1=1x gain
#define DAC_SHDN_BIT  (1<<4) // 0=shutdown, 1=normal
// uint8_t TRANSFER_BITS = (DAC_SHDN_BIT | DAC_GA_BIT | DAC_BUF_BIT);
uint8_t TRANSFER_BITS = (DAC_SHDN_BIT | DAC_BUF_BIT);

static void spi_transfer(uint8_t working) {
  // function to actually bit shift the data byte out
  for(int i = 1; i <= 8; i++) {
    if(working > 127)
      digitalWrite (DAC_SDI_PIN, HIGH); // if it is a 1 (ie. B1XXXXXXX), set the master out pin high
    else
      digitalWrite (DAC_SDI_PIN, LOW); // if it is not 1 (ie. B0XXXXXXX), set the master out pin low
    digitalWrite (DAC_SCK_PIN, HIGH); // set clock high, the pot IC will read the bit into its register
    working = working << 1;
    digitalWrite(DAC_SCK_PIN, LOW); // set clock low, the pot IC will stop reading and prepare for the next iteration (next significant bit
  }
}

static void spi_out(uint8_t high, uint8_t low) {
  digitalWrite(DAC_CS_PIN, LOW);
  spi_transfer(high);
  spi_transfer(low);
  digitalWrite(DAC_CS_PIN, HIGH);
}

void spi_init() {
  pinMode(DAC_CS_PIN, OUTPUT); // set CS pin to output
  pinMode(DAC_SCK_PIN, OUTPUT); // set SCK pin to output
  pinMode(DAC_SDI_PIN, OUTPUT); // set MOSI pin to output
  digitalWrite(DAC_CS_PIN, HIGH); // hold slave select 1 pin high, so that chip is not selected to begin with
}

void dac_set_a(int value){
  spi_out(TRANSFER_BITS | (value >> 8 & 0xf), value & 0xff);
}

void dac_set_b(int value){
  spi_out(TRANSFER_BITS | DAC_A_B_BIT | (value >> 8 & 0xf), value & 0xff);
}

