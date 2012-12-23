#include <inttypes.h>
#include <string.h>
#include "device.h"

#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG


#define TICKER_TAPE_BYTES 512L
#define TICKER_TAPE_BITS (TICKER_TAPE_BYTES*8-1)

enum OperatingMode {
  MEDIUM_SPEED_MODE                   = 0,
  HIGH_SPEED_MODE                     = 1,
  LOW_SPEED_MODE                      = 2,

  RECORD_MODE                         = 3,
  PLAYBACK_MODE                       = 4
};

inline bool triggerIsHigh(){
  return !(TAPTEMPO_TRIGGER_PINS & _BV(TAPTEMPO_TRIGGER_PIN));
}

inline bool gateIsHigh(){
  return !(TAPTEMPO_GATE_PINS & _BV(TAPTEMPO_GATE_PIN));
}

inline bool isRecordMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_B));
}

inline bool isPlayMode(){
  return !(MODE_SWITCH_PINS & _BV(MODE_SWITCH_PIN_A));
}

class TickerTape {
private:
public:
  uint8_t bits[TICKER_TAPE_BYTES];
  volatile uint16_t counter;
  volatile OperatingMode mode;
  
public:
  TickerTape() : counter(0) {
    memset(bits, 0, TICKER_TAPE_BYTES);
  }

  void updateMode(){
    if(isRecordMode()){
      mode = RECORD_MODE;
    }else{
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
    counter = (counter + 1) & TICKER_TAPE_BITS;
//     if(++counter == TICKER_TAPE_BITS)
//       counter = 0;
    switch(mode){
    case RECORD_MODE:
      if(gateIsHigh() | triggerIsHigh())
	bits[counter >> 3] |= _BV(counter & 0x07);
      else
	bits[counter >> 3] &= ~_BV(counter & 0x07);
      break;
    case PLAYBACK_MODE:
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
    TAPTEMPO_GATE_OUTPUT_PORT |= _BV(TAPTEMPO_GATE_OUTPUT_PIN);
  }
  void high(){
    TAPTEMPO_GATE_OUTPUT_PORT &= ~_BV(TAPTEMPO_GATE_OUTPUT_PIN);
  }
  void toggle(){
    if(isHigh())
      low();
    else
      high();
  }
  inline bool isHigh(){
    return !(TAPTEMPO_GATE_OUTPUT_PINS & _BV(TAPTEMPO_GATE_OUTPUT_PIN));
  }
#ifdef SERIAL_DEBUG
  virtual void dump(){
    printString("cnt ");
    printInteger(counter);
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
      if(bits[i>>3] & _BV(i & 0x07))
	printByte('+');
      else
	printByte('.');
    }
  }
#endif
};
