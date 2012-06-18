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
  adc_values[0] = ADC_VALUE_RANGE-1-value*1023*4;
// ADC_VALUE_RANGE-1-value*(ADC_VALUE_RANGE-1);
}

void setDelay(float value){
  adc_values[1] = ADC_VALUE_RANGE-1-value*1023*4;
// ADC_VALUE_RANGE-1-value*(ADC_VALUE_RANGE-1);
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

struct DefaultFixture {
  PinFixture pins;
  DefaultFixture(){
    loop();
    setDivide(0.0);
    setDelay(0.0);
    loop();
  }
};

BOOST_AUTO_TEST_CASE(universeInOrder)
{
    BOOST_CHECK(2+2 == 4);
}

BOOST_AUTO_TEST_CASE(testDefaults){
  PinFixture fixture;
  loop();
  BOOST_CHECK(!resetIsHigh());
  BOOST_CHECK(!clockIsHigh());
  BOOST_CHECK(!isCountMode());
  BOOST_CHECK(!isDelayMode());  
}

BOOST_AUTO_TEST_CASE(testControlRanges){
  DefaultFixture fixture;
  setDelay(0.0);
  setDivide(0.0);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 1);
  BOOST_CHECK_EQUAL(counter.value, 0);
  BOOST_CHECK_EQUAL(delay.value, 0);
  setDelay(1.0);
  setDivide(1.0);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 16);
  BOOST_CHECK_EQUAL(counter.value, 15);
  BOOST_CHECK_EQUAL(delay.value, 1022);
  setDelay(0.5);
  setDivide(0.5);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 8);
  BOOST_CHECK_EQUAL(counter.value, 7);
  BOOST_CHECK_EQUAL(delay.value, 511);
}

BOOST_AUTO_TEST_CASE(testModes){
  DefaultFixture fixture;
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
  DefaultFixture fixture;
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
  DefaultFixture fixture;
  loop();
  setDivide(0.0);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 1);
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

BOOST_AUTO_TEST_CASE(testDivideByOne){
  DefaultFixture fixture;
  setDivide(0.0);
  setDelay(0.5);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 1);
  int i;
  for(i=0; clockIsHigh() == divideIsHigh() && i<1000; ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 1000);
}

BOOST_AUTO_TEST_CASE(testCount){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.5);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(counter.value, 7);
  BOOST_CHECK(!delayIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  for(int i=0; i<14; ++i){
    toggleClock();
    BOOST_CHECK(!delayIsHigh());
  }
  toggleClock();
  BOOST_CHECK(delayIsHigh());
  for(int i=0; i<15; ++i){
    toggleClock();
    BOOST_CHECK(!delayIsHigh());
  }
  toggleClock();
  BOOST_CHECK(delayIsHigh());
}

BOOST_AUTO_TEST_CASE(testDelayLongPulse){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.5);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(delay.value, 511);
  BOOST_CHECK(!delayIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_DELAY_MODE);
  callTimer(100);
  BOOST_CHECK(!delayIsHigh());
  int i;
  setClock(true);
  for(i=0; !delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 511);
  setClock(false);
  for(i=0; delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 511);
}

BOOST_AUTO_TEST_CASE(testDelayShortPulse){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.2);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(delay.value, 204);
  int i;
  setClock(true);
  callTimer(100);
  setClock(false);
  for(i=0; !delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 104);
  for(i=0; delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 100);
}

BOOST_AUTO_TEST_CASE(testSwing){
  DefaultFixture fixture;
  setDivide(0.2);
  setDelay(0.2);
  setSwingMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 3);
  BOOST_CHECK_EQUAL(delay.value, 204);
  BOOST_CHECK_EQUAL(mode, SWING_MODE);
  int i;
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 5);
  BOOST_CHECK(swinger.running == true);
  callTimer(80);
  setClock(false);
  for(i=0; !combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 204-80);
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 80);
  BOOST_CHECK(swinger.running == false);
  BOOST_CHECK(clockIsHigh() == false);
  BOOST_CHECK(combinedIsHigh() == false);
  BOOST_CHECK(divideIsHigh() == true);
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 5);
}

BOOST_AUTO_TEST_CASE(testDivideAndCount){
  DefaultFixture fixture;
  setDivide(0.6);
  setDelay(0.3);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 10);
  BOOST_CHECK_EQUAL(counter.value, 4);
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  int i;
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 2*10+4);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 2*10+4);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 2*10+4);
}

BOOST_AUTO_TEST_CASE(testDivideByOneAndCount){
  DefaultFixture fixture;
  setDivide(0.0);
  setDelay(0.5);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 1);
  BOOST_CHECK_EQUAL(counter.value, 7);
  int i;
  for(i=0; delayIsHigh() == combinedIsHigh() && i<1000; ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 1000);  
}

BOOST_AUTO_TEST_CASE(testDivideAndDelay){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.1);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 8);
  BOOST_CHECK_EQUAL(delay.value, 102);
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_DELAY_MODE);
  int i;
  for(i=0; !combinedIsHigh() && i<15; ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);  
  BOOST_CHECK(divideIsHigh());  
  BOOST_CHECK(clockIsHigh());  
  for(i=0; !combinedIsHigh() && i<60; ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 60);
  setClock(false);
  for(i=0; !combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 102-60);
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 60);
}

// BOOST_AUTO_TEST_CASE(testDummy){
//   DefaultFixture fixture;
//   setDivide(0.6);
//   setDelay(0.2);
//   setCountMode();
//   loop();
//   for(int i=0; i<20; ++i){
//     toggleClock();
//     printString(clockIsHigh() ? "in  high " : "in  low ");
//     divider.dump();
//     printNewline();
//     printString(combinedIsHigh() ? "out high " : "out low ");
//     counter.dump();
//     printNewline();
//   }
// }
