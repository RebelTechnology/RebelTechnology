
/**
 * pin macros 
 */
#define TEST_CLK() !(CLK_INPUT_PINS & _BV(CLK_INPUT_PIN))
/* use pre-processor concatenation with ## in macros */
#define TEST_TRG(nm) (adc_values[ADC ## nm] < limit)
#define SET_TRG(nm) TRG ## nm ## _OUTPUT_PORT &= ~_BV(TRG ## nm ## _OUTPUT_PIN)
#define CLR_TRG(nm) TRG ## nm ## _OUTPUT_PORT |= _BV(TRG ## nm ## _OUTPUT_PIN)
#define CLR_LED(nm) LED ## nm ## _OUTPUT_PORT &= ~_BV(LED ## nm ## _OUTPUT_PIN)
#define SET_LED(nm) LED ## nm ## _OUTPUT_PORT |= _BV(LED ## nm ## _OUTPUT_PIN)
#define TGL_LED(nm) LED ## nm ## _OUTPUT_PORT ^= _BV(LED ## nm ## _OUTPUT_PIN)

/**
 * device pin mappings
 */
#define TRG0_OUTPUT_DDR                 DDRD
#define TRG1_OUTPUT_DDR                 DDRD
#define TRG2_OUTPUT_DDR                 DDRD
#define TRG3_OUTPUT_DDR                 DDRD
#define TRG4_OUTPUT_DDR                 DDRD
#define TRG5_OUTPUT_DDR                 DDRD

#define TRG0_OUTPUT_PORT                PORTD
#define TRG1_OUTPUT_PORT                PORTD
#define TRG2_OUTPUT_PORT                PORTD
#define TRG3_OUTPUT_PORT                PORTD
#define TRG4_OUTPUT_PORT                PORTD
#define TRG5_OUTPUT_PORT                PORTD

#define TRG0_OUTPUT_PIN                 PORTD0
#define TRG1_OUTPUT_PIN                 PORTD1
#define TRG2_OUTPUT_PIN                 PORTD2
#define TRG3_OUTPUT_PIN                 PORTD3
#define TRG4_OUTPUT_PIN                 PORTD4
#define TRG5_OUTPUT_PIN                 PORTD5

#define CLK_INPUT_DDR                   DDRD
#define CLK_INPUT_PORT                  PORTD
#define CLK_INPUT_PIN                   PORTD6
#define CLK_INPUT_PINS                  PIND

#define LED0_OUTPUT_DDR                 DDRB
#define LED1_OUTPUT_DDR                 DDRB
#define LED2_OUTPUT_DDR                 DDRB
#define LED3_OUTPUT_DDR                 DDRB
#define LED4_OUTPUT_DDR                 DDRB
#define LED5_OUTPUT_DDR                 DDRB
#define LED6_OUTPUT_DDR                 DDRD

#define LED0_OUTPUT_PORT                PORTB
#define LED1_OUTPUT_PORT                PORTB
#define LED2_OUTPUT_PORT                PORTB
#define LED3_OUTPUT_PORT                PORTB
#define LED4_OUTPUT_PORT                PORTB
#define LED5_OUTPUT_PORT                PORTB
#define LED6_OUTPUT_PORT                PORTD

#define LED0_OUTPUT_PIN                 PORTB0
#define LED1_OUTPUT_PIN                 PORTB1
#define LED2_OUTPUT_PIN                 PORTB2
#define LED3_OUTPUT_PIN                 PORTB3
#define LED4_OUTPUT_PIN                 PORTB4
#define LED5_OUTPUT_PIN                 PORTB5
#define LED6_OUTPUT_PIN                 PORTD7
