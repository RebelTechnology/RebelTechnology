/*
g++ -g -I../../../RebelTechnology/Libraries/wiring -I../../../RebelTechnology/Libraries/avrsim -I/opt/local/include -L/opt/local/lib -o TickerTest -lboost_unit_test_framework  TickerTest.cpp ../../../RebelTechnology/Libraries/avrsim/avr/io.c ../../../RebelTechnology/Libraries/wiring/serial.c  && ./TickerTest
*/
#define SERIAL_DEBUG
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include <avr/io.h>
#include "Ticker.h"

BOOST_AUTO_TEST_CASE(universeInOrder){
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(testDefaults){
  TickerTape tape;
  int res = 0;
  for(int i=0; i<TICKER_TAPE_BYTES; ++i)
    res |= tape.bits[i];
  BOOST_CHECK_EQUAL(res, 0);
  BOOST_CHECK_EQUAL(tape.counter, 0);
}
