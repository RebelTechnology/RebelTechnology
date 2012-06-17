/*
g++ -I. -I/opt/local/include -L/opt/local/lib -o test -lboost_unit_test_framework  test.cpp avr/io.c wiring/serial.c adc_freerunner.cpp avr/interrupt.c 
*/
// #define mcu atmega168
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include "ClockDelay.cpp"

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

BOOST_AUTO_TEST_CASE(universeInOrder)
{
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(testDefaults){
  PinFixture fixture;
  updateMode();
  BOOST_CHECK(!resetIsHigh());
  BOOST_CHECK(!clockIsHigh());
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(!isDelayMode());  
}

BOOST_AUTO_TEST_CASE(testModes){
  PinFixture fixture;
  PIND &= ~_BV(PORTD6);
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(isDelayMode());  
  updateMode();
  BOOST_CHECK(mode == DIVIDE_AND_DELAY_MODE);
  PIND |= _BV(PORTD6);
  PIND &= ~_BV(PORTD7);
  updateMode();
  BOOST_CHECK(mode == DIVIDE_AND_COUNT_MODE);
  BOOST_CHECK(isCountMode());
  BOOST_CHECK(!isDelayMode());  
  PIND |= _BV(PORTD6);
  PIND |= _BV(PORTD7);
  updateMode();
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(!isDelayMode());  
  BOOST_CHECK(mode == SWING_MODE);
}
