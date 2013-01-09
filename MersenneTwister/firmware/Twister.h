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
  uint32_t		random_value;
/*   static mt_state	state; */
  MCP492xController dac1;
  mt_state state;
//   uint8_t bitshift;

 public:
 MersenneTwister()
//   : bitshift(0) {
  {
    dac1.init(DAC1_CS_PIN, DAC_SHDN_BIT);
  }

  void seed(uint32_t seed){
    mts_seed32new(&state, seed);
  }

  void trigger(){
    ledOn();
    random_value = mts_lrand(&state);
//     uint16_t cv = 0x0fff & (random_value << bitshift);
    uint16_t cv = 0x0fff & random_value;
    dac1.send(cv);
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
