/*
g++ -I../../Libraries/wiring -I../../Libraries/avrsim -I/opt/local/include -L/opt/local/lib -o ClockGeneratorTest -lboost_unit_test_framework  ClockGeneratorTest.cpp ../../Libraries/avrsim/avr/io.c adc_freerunner.cpp ../../Libraries/avrsim/avr/interrupt.c serial.c && ./ClockGeneratorTest
*/
// #define mcu atmega168
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include "ClockGenerator.cpp"

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

  // PD3 out b
  // PB1 out a
};

void callTimer(int times = 1){
  for(int i=0; i<times; ++i)
    TIMER0_OVF_vect();
}

void setDuty(float value){
  adc_values[1] = ADC_VALUE_RANGE-1-value*1023*4;
}

void setRateA(float value){
  adc_values[2] = ADC_VALUE_RANGE-1-value*1023*4;
}

void setRateB(float value){
  adc_values[0] = ADC_VALUE_RANGE-1-value*1023*4;
}

struct DefaultFixture {
  PinFixture pins;
  DefaultFixture(){
    loop();
    setDuty(0.5);
    setRateA(0.5);
    setRateB(0.5);
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
}

float margin = 0.5; // percentage tolerance

BOOST_AUTO_TEST_CASE(testDutyCycleControlRange){
  DefaultFixture fixture;
  setDuty(0.0);
  loop();
  BOOST_CHECK_CLOSE(timer0.duty, 0, margin);
  BOOST_CHECK_CLOSE(timer1.duty, 0, margin);
  setDuty(0.5);
  loop();
  BOOST_CHECK_CLOSE(timer0.duty, 0.5, margin);
  BOOST_CHECK_CLOSE(timer1.duty, 0.5, margin);
  setDuty(1.0);
  loop();
  BOOST_CHECK_CLOSE(timer0.duty, 1.0, margin);
  BOOST_CHECK_CLOSE(timer1.duty, 1.0, margin);
}

BOOST_AUTO_TEST_CASE(testRateControlRange){
  DefaultFixture fixture;
  setRateA(0.0);
  setRateB(0.0);
  loop();
  BOOST_CHECK_CLOSE(timer0.frequency, 0, margin);
  BOOST_CHECK_CLOSE(timer1.frequency, 0, margin);
  setRateA(0.5);
  setRateB(0.5);
  loop();
  BOOST_CHECK_CLOSE(timer0.frequency, 1200, margin);
  BOOST_CHECK_CLOSE(timer1.frequency, 1200, margin);  
  setRateA(1.0);
  setRateB(1.0);
  loop();
  BOOST_CHECK_CLOSE(timer0.frequency, 120000, margin);
  BOOST_CHECK_CLOSE(timer1.frequency, 120000, margin);  
}
