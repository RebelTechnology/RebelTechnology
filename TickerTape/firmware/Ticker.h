#include <inttypes.h>
#include <string.h>
#include "device.h"

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#define TICKER_TAPE_BYTES 768
#else
#define TICKER_TAPE_BYTES 896
#endif

#define TICKER_TAPE_BITS (TICKER_TAPE_BYTES*8)

enum OperatingMode {
  RECORD_MODE                         = 0,
  PLAYBACK_MODE                       = 1
};

inline bool triggerIsHigh(){
  return !(TICKER_TAPE_TRIGGER_PINS & _BV(TICKER_TAPE_TRIGGER_PIN));
}

inline bool gateIsHigh(){
  return !(TICKER_TAPE_GATE_PINS & _BV(TICKER_TAPE_GATE_PIN));
}

inline bool isRecordMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

inline bool isFastMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

#define RETRIGGER_THRESHOLD 4

class TickerTape {
 private:
 public:
  uint8_t bits[TICKER_TAPE_BYTES];
  volatile uint16_t counter;
  volatile uint16_t limit;
  volatile OperatingMode mode;
  
 public:
 TickerTape() : counter(0), limit(TICKER_TAPE_BYTES) {
    memset(bits, 0, TICKER_TAPE_BYTES);
  }

  void updateMode(){
    if(isRecordMode()){
      if(mode == PLAYBACK_MODE && counter > RETRIGGER_THRESHOLD){
/*       if(mode == PLAYBACK_MODE){ */
	counter = 0;
	mode = RECORD_MODE;
      }
    }else{
      if(mode == RECORD_MODE && counter > RETRIGGER_THRESHOLD){
/*       if(mode == RECORD_MODE){ */
	limit = counter;
      }
      mode = PLAYBACK_MODE;
    }
  }

  void trigger(){
    switch(mode){
    case RECORD_MODE:
      bits[counter >> 3] |= _BV(counter & 0x07);
      break;
    case PLAYBACK_MODE:      
      break;
    }
  }

  void clock(){
    //     if(++counter == TICKER_TAPE_BITS)
    //       counter = 0;
    switch(mode){
    case RECORD_MODE:
      counter = (counter + 1) & (TICKER_TAPE_BITS - 1);
      if(gateIsHigh() | triggerIsHigh()){
	bits[counter >> 3] |= _BV(counter & 0x07);
	high();
      }else{
	bits[counter >> 3] &= ~_BV(counter & 0x07);
	low();
      }
      break;
    case PLAYBACK_MODE:
      if(++counter > limit)
	counter = 0;
      if(bits[counter >> 3] & _BV(counter & 0x07))
	high();
      else
	low();
      break;
    }
  }

  void reset(){
    low();
    counter = 0;
  }

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
    printString("cnt ");
    printInteger(counter);
    printString(" lim ");
    printInteger(limit);
    switch(mode){
    case RECORD_MODE:
      printString(" rec ");
      break;
    case PLAYBACK_MODE:
      printString(" play ");
      break;
    }
    if(isHigh())
      printString("high ");
    else
      printString("low ");
    for(uint16_t i=0; i<TICKER_TAPE_BITS; ++i){
/*     for(uint16_t i=0; i<limit; ++i){ */
      if(counter == i)
	printByte('>');
      if(limit == i){
	printByte('|');
	if(mode == PLAYBACK_MODE)
	  break;
      }
      if(bits[i>>3] & _BV(i & 0x07))
	printByte('+');
      else
	printByte('.');
    }
  }
#endif
};
