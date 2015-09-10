// #define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#include "serial.h"
#endif // SERIAL_DEBUG

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "device.h"
#include "adc_freerunner.h"

#define TEST_CLK() !(CLK_INPUT_PINS & _BV(CLK_INPUT_PIN))
/* use pre-processor concatenation with ## in macros */
#define TEST_TRG(nm) (adc_values[ADC ## nm] < limit)
#define SET_TRG(nm) TRG ## nm ## _OUTPUT_PORT &= ~_BV(TRG ## nm ## _OUTPUT_PIN)
#define CLR_TRG(nm) TRG ## nm ## _OUTPUT_PORT |= _BV(TRG ## nm ## _OUTPUT_PIN)
#define CLR_LED(nm) LED ## nm ## _OUTPUT_PORT &= ~_BV(LED ## nm ## _OUTPUT_PIN)
#define SET_LED(nm) LED ## nm ## _OUTPUT_PORT |= _BV(LED ## nm ## _OUTPUT_PIN)

class Triggy {
private:
  volatile uint16_t limit;
public:
};

void setup(){
  cli();
  CLK_INPUT_DDR &= ~_BV(CLK_INPUT_PIN);
  CLK_INPUT_PORT |= _BV(CLK_INPUT_PIN); // enable pull-up resistor

  TRG0_OUTPUT_DDR |= _BV(TRG0_OUTPUT_PIN);
  TRG1_OUTPUT_DDR |= _BV(TRG1_OUTPUT_PIN);
  TRG2_OUTPUT_DDR |= _BV(TRG2_OUTPUT_PIN);
  TRG3_OUTPUT_DDR |= _BV(TRG3_OUTPUT_PIN);
  TRG4_OUTPUT_DDR |= _BV(TRG4_OUTPUT_PIN);
  TRG5_OUTPUT_DDR |= _BV(TRG5_OUTPUT_PIN);

  LED0_OUTPUT_DDR |= _BV(LED0_OUTPUT_PIN);
  LED1_OUTPUT_DDR |= _BV(LED1_OUTPUT_PIN);
  LED2_OUTPUT_DDR |= _BV(LED2_OUTPUT_PIN);
  LED3_OUTPUT_DDR |= _BV(LED3_OUTPUT_PIN);
  LED4_OUTPUT_DDR |= _BV(LED4_OUTPUT_PIN);
  LED5_OUTPUT_DDR |= _BV(LED5_OUTPUT_PIN);
  LED6_OUTPUT_DDR |= _BV(LED6_OUTPUT_PIN);

  CLR_TRG(0);
  CLR_TRG(1);
  CLR_TRG(2);
  CLR_TRG(3);
  CLR_TRG(4);
  CLR_TRG(5);

  CLR_LED(0);
  CLR_LED(1);
  CLR_LED(2);
  CLR_LED(3);
  CLR_LED(4);
  CLR_LED(5);
  SET_LED(6);

  setup_adc();

  sei();
}

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6

// #define CHECK_TRG(nm) if(TEST_TRG(nm) && TEST_CLK()){
/*
#define CHECK_TRG(nm) if(TEST_TRG(nm)){	\
    SET_TRG(nm);\
    SET_LED(nm);\  
  }else{\
    CLR_TRG(nm);\
    CLR_LED(nm);\
  }
*/
#define CHECK_TRG(nm)\
	if(TEST_TRG(nm)){\
	  if(adc_count > onsets[nm]*2){\
	    onsets[nm] = adc_count;\
	    SET_TRG(nm);\
	    SET_LED(nm);\
	  }\
	}else{\
	  CLR_TRG(nm);\
	  CLR_LED(nm);\
	}

void loop(){
  uint16_t limit = adc_values[ADC6];
  static uint32_t onsets[6] = {0};  
  if(TEST_CLK())
    SET_LED(6);
  else
    CLR_LED(6);

  /*
  if(TEST_CLK()){
    SET_LED(6);
    for(int i=0; i<6; ++i){
      if(adc_count > onsets[i]){
	if(TEST_TRG(i)){
	  if(adc_count > onsets[i]*2){
	    onsets[i] = adc_count;
	    SET_TRG(nm);
	    SET_LED(nm);
	  }
	}else{
	  CLR_TRG(nm);
	  CLR_LED(nm);
	}
      }
    }
  }else{
    CLR_LED(6);   
  }
  */

  CHECK_TRG(0);
  CHECK_TRG(1);
  CHECK_TRG(2);
  CHECK_TRG(3);
  CHECK_TRG(4);
  CHECK_TRG(5);

	/*
  for(int i=0; i<6; ++i){
    if(adc_values[i] < limit)      
  }
	*/
}
