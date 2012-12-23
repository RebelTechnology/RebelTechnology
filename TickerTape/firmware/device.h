/*
  pin mappings
 */

#define TEMPO_ADC_CHANNEL               0

#define MODE_SWITCH_DDR                 DDRD
#define MODE_SWITCH_PINS                PIND
#define MODE_SWITCH_PORT                PORTD
#define MODE_SWITCH_PIN_A               PORTD6
#define MODE_SWITCH_PIN_B               PORTD4

#define TICKER_TAPE_TRIGGER_DDR            DDRD
#define TICKER_TAPE_TRIGGER_PORT           PORTD
#define TICKER_TAPE_TRIGGER_PINS           PIND
#define TICKER_TAPE_TRIGGER_PIN            PORTD2

#define TICKER_TAPE_GATE_DDR            DDRD
#define TICKER_TAPE_GATE_PORT           PORTD
#define TICKER_TAPE_GATE_PINS           PIND
#define TICKER_TAPE_GATE_PIN            PORTD3

#define TICKER_TAPE_GATE_OUTPUT_DDR             DDRB
#define TICKER_TAPE_GATE_OUTPUT_PINS            PINB
#define TICKER_TAPE_GATE_OUTPUT_PORT            PORTB
#define TICKER_TAPE_GATE_OUTPUT_PIN             PORTB2

#define TICKER_TAPE_LEDS_DDR        DDRB
#define TICKER_TAPE_LEDS_PORT       PORTB
#define TICKER_TAPE_LEDS_PINS       PINB
#define TICKER_TAPE_LED_1_PIN       PORTB3
#define TICKER_TAPE_LED_2_PIN       PORTB4
#define TICKER_TAPE_LED_3_PIN       PORTB5

#define CS_DDR        DDRC
#define CS_PORT       PORTC
#define DAC1_CS_PIN   PORTC5       // CS slave select pin
