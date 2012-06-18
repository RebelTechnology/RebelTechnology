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

void pulseClock(int times = 1){
  for(int i=0; i<times; ++i){
    PIND &= ~_BV(PORTD3); // clock high
    INT1_vect();
    PIND |= _BV(PORTD3); // clock low
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

BOOST_AUTO_TEST_CASE(testDivideControlRange){
  DefaultFixture fixture;
  setDivide(0.0);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 0);
  setDivide(1.0);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 15);
  setDivide(0.5);
  loop();
  BOOST_CHECK_EQUAL(divider.value, 7);
}

BOOST_AUTO_TEST_CASE(testCounterControlRange){
  DefaultFixture fixture;
  setDelay(0.0);
  loop();
  BOOST_CHECK_EQUAL(counter.value, 0);
  setDelay(1.0);
  loop();
  BOOST_CHECK_EQUAL(counter.value, 15);
  setDelay(0.5);
  loop();
  BOOST_CHECK_EQUAL(counter.value, 7);
}

BOOST_AUTO_TEST_CASE(testDelayControlRange){
  DefaultFixture fixture;
  setDelay(0.0);
  loop();
  BOOST_CHECK_EQUAL(delay.value, 1);
  setDelay(1.0);
  loop();
  BOOST_CHECK_EQUAL(delay.value, 1023);
  setDelay(0.5);
  loop();
  BOOST_CHECK_EQUAL(delay.value, 512);
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
  setDivide(0.5);
  setDelay(0.5);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 7);
  BOOST_CHECK(!divideIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  int i;
  for(i=0; !divideIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15); // first run doesn't include falling half-cycle
  BOOST_CHECK(divideIsHigh());
  BOOST_CHECK(clockIsHigh());
  for(i=0; divideIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 16);
  BOOST_CHECK(!divideIsHigh());
  BOOST_CHECK(clockIsHigh());
  for(i=0; !divideIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 16);
  for(i=0; divideIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 16);
}

void checkDivide(float div){
  setDivide(div);
  loop();
//   int pulses = div*16+1;
  int pulses = divider.value+1;
  int i;
  for(i=0; !divideIsHigh() && i<100; ++i)
    pulseClock();
  BOOST_CHECK_EQUAL(i, pulses);
  for(i=0; divideIsHigh() && i<100; ++i)
    pulseClock();
  BOOST_CHECK_EQUAL(i, pulses);
}

BOOST_AUTO_TEST_CASE(testDivideByAny){
  DefaultFixture fixture;
  for(float f=0.2; f<=1.0; f+=0.1)
    checkDivide(f);
}

BOOST_AUTO_TEST_CASE(testDivideByOne){
  DefaultFixture fixture;
  setDivide(0.0);
  loop();
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
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  int i;
  for(i=0; !delayIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
  BOOST_CHECK(delayIsHigh());
  toggleClock();
  for(i=0; !delayIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
  toggleClock();
  for(i=0; !delayIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
}

void checkCount(float cnt){
  setDelay(cnt);
  loop();
  int count = counter.value*2+1;
  int i;
  for(i=0; !delayIsHigh() && i<100; ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, count);
  toggleClock();
  for(i=0; !delayIsHigh() && i<100; ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, count);
  toggleClock();
}

BOOST_AUTO_TEST_CASE(testCountToAny){
  DefaultFixture fixture;
  setCountMode();
  for(float f=0.0; f<=1.0; f+=0.1)
    checkCount(f);
}

BOOST_AUTO_TEST_CASE(testDelayLongPulse){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.5);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(delay.value, 512);
  BOOST_CHECK(!delayIsHigh());
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_DELAY_MODE);
  callTimer(100);
  BOOST_CHECK(!delayIsHigh());
  int i;
  setClock(true);
  for(i=0; !delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 512);
  setClock(false);
  for(i=0; delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 512);
}

BOOST_AUTO_TEST_CASE(testDelaySlowPulse){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.5);
  setDelayMode();
  loop();
  int i;
  setClock(true);
  for(i=0; !delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 512);
  for(i=0; delayIsHigh() && i<1000; ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 1000);
  setClock(false);
  for(i=0; delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 512);
}

BOOST_AUTO_TEST_CASE(testZeroDelay){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.0);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(delay.value, 1);
  int i;
  for(i=0; (clockIsHigh() == delayIsHigh()) && i<100; ++i){
    toggleClock();
    callTimer();
  }
  BOOST_CHECK_EQUAL(i, 100);
}

BOOST_AUTO_TEST_CASE(testZeroSwing){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.0);
  setSwingMode();
  loop();
  int i;
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
  BOOST_CHECK(clockIsHigh());
  BOOST_CHECK(!combinedIsHigh());
  callTimer(20);
  toggleClock();
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 1);
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
}

BOOST_AUTO_TEST_CASE(testDelayShortPulse){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.2);
  setDelayMode();
  loop();
  BOOST_CHECK_EQUAL(delay.value, 205);
  int i;
  setClock(true);
  callTimer(100);
  setClock(false);
  for(i=0; !delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 105);
  for(i=0; delayIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 100);
}

void checkSwing(float div, float del){
  setDivide(div);
  setDelay(del);
  setSwingMode();
  loop();
//   int cycles = (divider.value-1)*2+1;
//   int cycles = divider.value;
  int cycles = divider.value*2+1;
  int time = delay.value/2+1;
  int ticks = delay.value-time;
  int i;
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, cycles);
  BOOST_CHECK(swinger.running == true);
  BOOST_CHECK(clockIsHigh());
  callTimer(time);
  setClock(false);
  for(i=0; !combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, ticks);
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, time);
}

BOOST_AUTO_TEST_CASE(testSwingRepeat){
  DefaultFixture fixture;
  for(int i=0; i<10; ++i)
    checkSwing(0.2, 0.2);
}

BOOST_AUTO_TEST_CASE(testSwingChangeRepeat){
  DefaultFixture fixture;
  for(int i=0; i<20; ++i)
    checkSwing(i/19.0, i/19.0);
}

BOOST_AUTO_TEST_CASE(testSwing){
  DefaultFixture fixture;
  setDivide(0.2);
  setDelay(0.2);
  setSwingMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 2);
  BOOST_CHECK_EQUAL(delay.value, 205);
  BOOST_CHECK_EQUAL(mode, SWING_MODE);
  int i;
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 5);
  BOOST_CHECK(swinger.running == true);
  BOOST_CHECK(clockIsHigh());
  callTimer(80);
  setClock(false);
  for(i=0; !combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 205-80);
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
  // repeat
  callTimer(80);
  setClock(false);
  for(i=0; !combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 205-80);
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 80);
  for(i=0; clockIsHigh() == combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 5);
}

BOOST_AUTO_TEST_CASE(testDivideAndCount){
  DefaultFixture fixture;
  setDivide(0.5);
  setDelay(0.3);
  setCountMode();
  loop();
  BOOST_CHECK_EQUAL(divider.value, 7);
  BOOST_CHECK_EQUAL(divcounter.value, 4);
  BOOST_CHECK_EQUAL(mode, DIVIDE_AND_COUNT_MODE);
  int i;
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  // the first pulse is delayed: divcounter.value*2
  // following pulses are offset with the same period as the divider: divider.value*2+1
  BOOST_CHECK_EQUAL(i, 15+8);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, 15);
}

void checkDivideAndCount(float div, float cnt){
  setDivide(div);
  setDelay(cnt);
  loop();
  reset();
  int count = counter.value;
  int pulses = divider.value;
  BOOST_CHECK(pulses > count/2);
  int cycles = pulses*2+count*2+1;
  int i;
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, cycles);
  toggleClock();
  for(i=0; !combinedIsHigh(); ++i)
    toggleClock();
  BOOST_CHECK_EQUAL(i, pulses*2+1);
  toggleClock();
}

BOOST_AUTO_TEST_CASE(testDivideAndCountToAny){
  DefaultFixture fixture;
  setCountMode();
  for(float f=0.2; f<=1.0; f+=0.1)
    checkDivideAndCount(f, f/2);
}

BOOST_AUTO_TEST_CASE(testDivideByOneAndCount){
  DefaultFixture fixture;
  setDivide(0.0);
  setDelay(0.5);
  setCountMode();
  loop();
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
  BOOST_CHECK_EQUAL(delay.value, 103);
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
  BOOST_CHECK_EQUAL(i, 103-60);
  for(i=0; combinedIsHigh(); ++i)
    callTimer();
  BOOST_CHECK_EQUAL(i, 60);
}

BOOST_AUTO_TEST_CASE(testDivideByOneAndDelay){
  DefaultFixture fixture;
  setDivide(0.0);
  setDelay(0.3);
  setDelayMode();
  loop();
  int i;
  for(i=0; delayIsHigh() == combinedIsHigh() && i<1000; ++i){
    toggleClock();
    callTimer(1000);
  }
  BOOST_CHECK_EQUAL(i, 1000);  
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
