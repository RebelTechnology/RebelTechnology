
#define ADC_CHANNELS                    3
#define ADC_OVERSAMPLING                4
#define ADC_VALUE_RANGE                 (1024*ADC_OVERSAMPLING)
#define CLOCKMULTIPLIER_DEADBAND_THRESHOLD  (ADC_VALUE_RANGE/32/4)

#define DURCV_ADC_CHANNEL              1
#define MULCV_ADC_CHANNEL              0
#define REPCV_ADC_CHANNEL              2
#define MULTIPLIER_ADC_CHANNEL          1

/*
  pin mappings
 */
#define CLOCKMULTIPLIER_MULIN_DDR            DDRD
#define CLOCKMULTIPLIER_MULIN_PORT           PORTD
#define CLOCKMULTIPLIER_MULIN_PINS           PIND
#define CLOCKMULTIPLIER_MULIN_PIN            PORTD3

#define CLOCKMULTIPLIER_DURIN_DDR            DDRD
#define CLOCKMULTIPLIER_DURIN_PORT           PORTD
#define CLOCKMULTIPLIER_DURIN_PINS           PIND
#define CLOCKMULTIPLIER_DURIN_PIN            PORTD2

#define CLOCKMULTIPLIER_REPIN_DDR            DDRD
#define CLOCKMULTIPLIER_REPIN_PORT           PORTD
#define CLOCKMULTIPLIER_REPIN_PINS           PIND
#define CLOCKMULTIPLIER_REPIN_PIN            PORTD4

#define CLOCKMULTIPLIER_MULOUT_DDR            DDRB
#define CLOCKMULTIPLIER_MULOUT_PORT           PORTB
#define CLOCKMULTIPLIER_MULOUT_PINS           PINB
#define CLOCKMULTIPLIER_MULOUT_PIN            PORTD1

#define CLOCKMULTIPLIER_DUROUT_DDR            DDRB
#define CLOCKMULTIPLIER_DUROUT_PORT           PORTB
#define CLOCKMULTIPLIER_DUROUT_PINS           PINB
#define CLOCKMULTIPLIER_DUROUT_PIN            PORTD0

#define CLOCKMULTIPLIER_REPOUT_DDR            DDRB
#define CLOCKMULTIPLIER_REPOUT_PORT           PORTB
#define CLOCKMULTIPLIER_REPOUT_PINS           PINB
#define CLOCKMULTIPLIER_REPOUT_PIN            PORTD2



