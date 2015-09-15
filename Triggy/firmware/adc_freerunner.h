#ifndef _ANALOGREADER_H_
#define _ANALOGREADER_H_

#include <inttypes.h>

#define ADC_CHANNELS 7
#define ADC_OVERSAMPLING 4
#ifdef ADC_OVERSAMPLING
#define ADC_VALUE_RANGE (1024*ADC_OVERSAMPLING)
#else
#define ADC_VALUE_RANGE 1024
#endif

#define ADC_PRESCALER 128

extern uint16_t volatile adc_values[ADC_CHANNELS];
extern uint32_t volatile adc_count;

void setup_adc();
#define getAnalogValue(i) (adc_values[i])

#endif /* _ANALOGREADER_H_ */
