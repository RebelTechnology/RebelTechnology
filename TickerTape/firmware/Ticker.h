#include <inttypes.h>
#include <string.h>
#include "device.h"

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#define TICKER_TAPE_BYTES 512

/* #ifdef SERIAL_DEBUG */
/* #define TICKER_TAPE_BYTES 768 */
/* #else */
/* #define TICKER_TAPE_BYTES 960 */
/* #endif */

#define TICKER_TAPE_BITS (TICKER_TAPE_BYTES*8)

enum OperatingMode {
  RECORD_MODE                         = 0,
  PLAYBACK_MODE                       = 1,
  THROUGH_MODE                        = 2
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

inline bool isThroughMode(){
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

  OperatingMode readMode(){
    if(isRecordMode())
      return RECORD_MODE;
    if(isThroughMode())
      return THROUGH_MODE;
    return PLAYBACK_MODE;
  }

  void updateMode(){
    OperatingMode current = readMode();
    if(mode != current && counter > RETRIGGER_THRESHOLD){
      if(mode == RECORD_MODE)
	limit = counter;
      counter = 0;
      mode = current;
    }
  }

/*   void trigger(){ */
/*     switch(mode){ */
/*     case RECORD_MODE: */
/*       bits[counter >> 3] |= _BV(counter & 0x07); */
/*       break; */
/*     case PLAYBACK_MODE:       */
/*       break; */
/*     } */
/*   } */

  void clock(){
    switch(mode){
    case RECORD_MODE:
      if(gateIsHigh() | triggerIsHigh()){
	bits[counter >> 3] |= _BV(counter & 0x07);
	high();
      }else{
	bits[counter >> 3] &= ~_BV(counter & 0x07);
	low();
      }
      counter = (counter + 1) & (TICKER_TAPE_BITS - 1);
      break;
    case PLAYBACK_MODE:
      if(bits[counter >> 3] & _BV(counter & 0x07))
	high();
      else
	low();
      if(++counter > limit)
	counter = 0;
      break;
    case THROUGH_MODE:
      if(gateIsHigh() | triggerIsHigh()){
	high();
      }else{
	low();
      }
      if(++counter > limit)
	counter = 0;
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
    case THROUGH_MODE:
      printString(" thru ");
      break;
    }
    if(isHigh())
      printString("high ");
    else
      printString("low ");
    for(uint16_t i=0; i<TICKER_TAPE_BITS; ++i){
      if(counter == i)
	printByte('>');
      if(limit == i){
	printByte('|');
	if(mode != RECORD_MODE)
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
