/*
  pin mappings
 */

#define TEMPO_ADC_CHANNEL               0

#define MODE_SWITCH_DDR                 DDRD
#define MODE_SWITCH_PINS                PIND
#define MODE_SWITCH_PORT                PORTD
#define MODE_SWITCH_PIN_A               PORTD6
#define MODE_SWITCH_PIN_B               PORTD7

#define TAPTEMPO_TRIGGER_DDR            DDRD
#define TAPTEMPO_TRIGGER_PORT           PORTD
#define TAPTEMPO_TRIGGER_PINS           PIND
#define TAPTEMPO_TRIGGER_PIN            PORTD3

#define TAPTEMPO_GATE_DDR            DDRD
#define TAPTEMPO_GATE_PORT           PORTD
#define TAPTEMPO_GATE_PINS           PIND
#define TAPTEMPO_GATE_PIN            PORTD2

#define TAPTEMPO_RAMP_OUTPUT_DDR                DDRB
#define TAPTEMPO_RAMP_OUTPUT_PINS               PINB
#define TAPTEMPO_RAMP_OUTPUT_PORT               PORTB
#define TAPTEMPO_RAMP_OUTPUT_PIN                PORTB1

#define TAPTEMPO_GATE_OUTPUT_DDR             DDRB
#define TAPTEMPO_GATE_OUTPUT_PINS            PINB
#define TAPTEMPO_GATE_OUTPUT_PORT            PORTB
#define TAPTEMPO_GATE_OUTPUT_PIN             PORTB2

#define TAPTEMPO_LEDS_DDR        DDRB
#define TAPTEMPO_LEDS_PORT       PORTB
#define TAPTEMPO_LEDS_PINS       PINB
#define TAPTEMPO_LED_1_PIN       PORTB3
#define TAPTEMPO_LED_2_PIN       PORTB4
#define TAPTEMPO_LED_3_PIN       PORTB5

#define CS_DDR        DDRC
#define CS_PORT       PORTC
#define DAC1_CS_PIN   PC5       // CS slave select pin
