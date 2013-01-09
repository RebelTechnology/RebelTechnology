#include <inttypes.h>
#include "device.h"

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include "MCP492xController.h"

#include "mtwist.h"

void ledOn(){
  TICKER_TAPE_LEDS_PORT |= _BV(TICKER_TAPE_LED_1_PIN);
}

void ledOff(){
  TICKER_TAPE_LEDS_PORT &= ~_BV(TICKER_TAPE_LED_1_PIN);
}

void ledToggle(){
  TICKER_TAPE_LEDS_PORT ^= _BV(TICKER_TAPE_LED_1_PIN);
}

class MersenneTwister {
 private:
 public:
  uint16_t counter;
  uint16_t limit;
  uint16_t random;
  MCP492xController dac1;
  mt_state state;
//   uint8_t bitshift;

 public:
 MersenneTwister()
//   : bitshift(0) {
   : counter(0), random(0xff)
  {
    dac1.init(DAC1_CS_PIN, DAC_SHDN_BIT);
  }

  void seed(uint32_t seed){
    mts_seed32new(&state, seed);
  }

  void clock(){
    if(++counter > limit){
      toggle();
      limit = random;
      counter = 0;
    }
  }

  void trigger(){
    ledOn();
    random = mts_lrand(&state) & 0x0fff; // 12-bit random number
//     uint16_t cv = 0x0fff & (random_value << bitshift);
    dac1.send(random);
    ledOff();
  }

//   void reset(){
//   }

  void low(){
    TICKER_TAPE_GATE_OUTPUT_PORT |= _BV(TICKER_TAPE_GATE_OUTPUT_PIN);
  }

  void high(){
    TICKER_TAPE_GATE_OUTPUT_PORT &= ~_BV(TICKER_TAPE_GATE_OUTPUT_PIN);
  }

  void toggle(){
    if(isHigh())
      low();
    else
      high();
  }

  inline bool isHigh(){
    return !(TICKER_TAPE_GATE_OUTPUT_PINS & _BV(TICKER_TAPE_GATE_OUTPUT_PIN));
  }

#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("rnd ");
    printInteger(random_value);
//     printString(" sft ");
//     printInteger(bitshift);
  }
#endif
};
