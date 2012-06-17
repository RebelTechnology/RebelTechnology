/*
g++ -I./simulator -I/opt/local/include -L/opt/local/lib -o ClockDelayTest -lboost_unit_test_framework  ClockDelayTest.cpp simulator/avr/io.c simulator/wiring/serial.c adc_freerunner.cpp simulator/avr/interrupt.c && ./ClockDelayTest
*/
// #define mcu atmega168
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include "ClockDelay.cpp"

struct PinFixture {
  PinFixture() {
    setup();
    PIND |= _BV(PORTD2);
    PIND |= _BV(PORTD3);
    PIND |= _BV(PORTD4);
    PIND |= _BV(PORTD5);
    PIND |= _BV(PORTD6);
    PIND |= _BV(PORTD7);
  }
};

// void updatePins(){
//   PINB = PORTB;
//   PINC = PORTC;
//   PIND = PORTD;
// }

void setCountMode(){
  PIND |= _BV(PORTD6);
  PIND &= ~_BV(PORTD7);
}

void setDelayMode(){
  PIND &= ~_BV(PORTD6);
  PIND |= _BV(PORTD7);
}

void setSwingMode(){
  PIND |= _BV(PORTD6);
  PIND |= _BV(PORTD7);
}

void setClock(bool high){
  if(high)
    PIND &= ~_BV(PORTD3);
  else
    PIND |= _BV(PORTD3);
  INT1_vect();
}

void toggleClock(int times = 1){
  for(int i=0; i<times; ++i){
    PIND ^= _BV(PORTD3);
    INT1_vect();
  }
}

void callTimer(int times = 1){
  for(int i=0; i<times; ++i)
    TIMER0_OVF_vect();
}

void setDivide(float value){
  adc_values[0] = value*ADC_VALUE_RANGE;
}

void setDelay(float value){
  adc_values[1] = value*ADC_VALUE_RANGE;
}

bool divideIsHigh(){
  return !(PORTB & _BV(PORTB0));
}

bool delayIsHigh(){
  return !(PORTB & _BV(PORTB1));
}

bool combinedIsHigh(){
  return !(PORTB & _BV(PORTB2));
}

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
  setDelayMode();
  updateMode();
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(isDelayMode());
  BOOST_CHECK(mode == DIVIDE_AND_DELAY_MODE);
  setCountMode();
  updateMode();
  BOOST_CHECK(mode == DIVIDE_AND_COUNT_MODE);
  BOOST_CHECK(isCountMode());
  BOOST_CHECK(!isDelayMode());  
  setSwingMode();
  updateMode();
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(!isDelayMode());  
  BOOST_CHECK(mode == SWING_MODE);
}

BOOST_AUTO_TEST_CASE(testClock){
  PinFixture fixture;
  setClock(true);
  BOOST_CHECK(clockIsHigh());
  setClock(false);
  BOOST_CHECK(!clockIsHigh());
  for(int i=0; i<10000; i++){
    toggleClock(10);
    loop();
  }
}

BOOST_AUTO_TEST_CASE(testDivide){
  PinFixture fixture;
  setDivide(0.5);
  setDelay(0.5);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 8);
  BOOST_CHECK(!divideIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  for(int i=0; i<14; ++i){
    toggleClock();
    BOOST_CHECK(!divideIsHigh());
  }
  for(int i=0; i<15; ++i){
    toggleClock();
    BOOST_CHECK(divideIsHigh());
  }
  for(int i=0; i<15; ++i){
    toggleClock();
    BOOST_CHECK(!divideIsHigh());
  }
  toggleClock();
  BOOST_CHECK(divideIsHigh());
}

BOOST_AUTO_TEST_CASE(testCount){
  PinFixture fixture;
  setDivide(0.5);
  setDelay(0.3);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(counter.value, 8);
  BOOST_CHECK(!delayIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  for(int i=0; i<14; ++i){
    toggleClock();
    BOOST_CHECK(!delayIsHigh());
    counter.dump();
    printNewline();
  }

  for(int i=0; i<14; ++i){
    toggleClock();
    BOOST_CHECK(!delayIsHigh());
    counter.dump();
    printNewline();
  }

}

BOOST_AUTO_TEST_CASE(testDelay){
  PinFixture fixture;
  setDelayMode();
  setDivide(0.3);
  setDelay(0.3);
  loop();
  BOOST_CHECK(!delayIsHigh());
  callTimer(100);
  BOOST_CHECK(!delayIsHigh());
  setClock(true);
  BOOST_CHECK(!delayIsHigh());
  callTimer(100);
  BOOST_CHECK(!delayIsHigh());
  callTimer(300);
  BOOST_CHECK(delayIsHigh());

  setClock(false);

//   toggleClock(100);
  
//   for(int i=0; i<10; i++){
//     doClock(5);
//     loop();
//     callTimer(9);
//     divider.dump();
//     printNewline();
//     counter.dump();
//     printNewline();
//     swinger.dump();
//     printNewline();
//   }
}
