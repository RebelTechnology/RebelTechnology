/*
g++ -g -I../../../RebelTechnology/Libraries/wiring -I../../../RebelTechnology/Libraries/avrsim -I/opt/local/include -L/opt/local/lib -o TickerTest -lboost_unit_test_framework  TickerTest.cpp ../../../RebelTechnology/Libraries/avrsim/avr/io.c ../../../RebelTechnology/Libraries/wiring/serial.c  && ./TickerTest
*/
#define SERIAL_DEBUG
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include <avr/io.h>
#include "Ticker.h"

struct PinFixture {
  PinFixture() {
    PIND |= _BV(PORTD2);
    PIND |= _BV(PORTD3);
    PIND |= _BV(PORTD4);
    PIND |= _BV(PORTD5);
    PIND |= _BV(PORTD6);
    PIND |= _BV(PORTD7);
  }
};

void setRecordMode(TickerTape& tape){
  PIND |= _BV(PORTD6);
  PIND &= ~_BV(PORTD4);
  tape.updateMode();
}

void setPlaybackMode(TickerTape& tape){
  PIND |= _BV(PORTD4);
  PIND &= ~_BV(PORTD6);
  tape.updateMode();
}

void setGate(bool high = true){
  if(high)
    PIND &= ~_BV(PORTD3);
  else
    PIND |= _BV(PORTD3);
}

void setTrigger(bool high = true){
  if(high)
    PIND &= ~_BV(PORTD2);
  else
    PIND |= _BV(PORTD2);
}

void callClock(TickerTape& tape, int times = 1){
  for(int i=0; i<times; ++i)
    tape.clock();
}

bool outputGateIsHigh(){
  return PINB & ~_BV(PORTB2);
}

int countSetBits(TickerTape& tape){
  int res = 0;
  for(int i=0; i<TICKER_TAPE_BYTES; ++i)
    for(int j=0; j<8; ++j)
      if(tape.bits[i] & _BV(j))
	res++;
  return res;
}

struct DefaultFixture {
  PinFixture pins;
  TickerTape tape;
  DefaultFixture(){
    setPlaybackMode(tape);
  }
};

BOOST_AUTO_TEST_CASE(universeInOrder){
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(testDefaults){
  DefaultFixture fixture;
  int res = 0;
  for(int i=0; i<TICKER_TAPE_BYTES; ++i)
    res |= fixture.tape.bits[i];
  BOOST_CHECK_EQUAL(res, 0);
  BOOST_CHECK_EQUAL(fixture.tape.counter, 0);
  BOOST_CHECK_EQUAL(fixture.tape.mode, PLAYBACK_MODE);
}

BOOST_AUTO_TEST_CASE(testTrigger){
  DefaultFixture fixture;
  TickerTape& tape = fixture.tape;
  setRecordMode(tape);
  callClock(tape, 23);
  setTrigger(true);
  tape.trigger();
  setTrigger(false);
  callClock(tape, 23);
  BOOST_CHECK_EQUAL(countSetBits(tape), 1);  
  setPlaybackMode(tape);
  callClock(tape, 10000);
  BOOST_CHECK_EQUAL(countSetBits(tape), 1);  
}

BOOST_AUTO_TEST_CASE(testTriggerAndClock){
  DefaultFixture fixture;
  TickerTape& tape = fixture.tape;
  setRecordMode(tape);
  callClock(tape, 77);
  setTrigger(true);
  callClock(tape, 1);
  setTrigger(false);
  callClock(tape, 17);
  BOOST_CHECK_EQUAL(countSetBits(tape), 1);
  setTrigger(true);
  callClock(tape, 59);
  setTrigger(false);
  callClock(tape, 42);
  BOOST_CHECK_EQUAL(countSetBits(tape), 60);
  setPlaybackMode(tape);
  callClock(tape, 10000);
  BOOST_CHECK_EQUAL(countSetBits(tape), 60);
}

BOOST_AUTO_TEST_CASE(testRecordPlaybackAndErase){
  DefaultFixture fixture;
  TickerTape& tape = fixture.tape;
  setRecordMode(tape);
  for(int i=0; i<12434; ++i){
    setTrigger(i%4);
    callClock(tape);
  }
  BOOST_CHECK_EQUAL(countSetBits(tape), 3*TICKER_TAPE_BITS/4);
  int cnt = countSetBits(tape);
  setPlaybackMode(tape);
  callClock(tape, 10000);
  tape.dump();
  BOOST_CHECK_EQUAL(countSetBits(tape), cnt);
  setRecordMode(tape);
  setTrigger(false);
  callClock(tape, 10000);
  BOOST_CHECK_EQUAL(countSetBits(tape), 0);
}
