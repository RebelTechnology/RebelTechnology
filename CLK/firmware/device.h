/*
  pin mappings
counter  pin       schematic   function
OC1A     PORTB1    OUTA        TIMER1_OUTPUT_B  50% duty cycle
OC1B     PORTB2    LED2        TIMER1_OUTPUT_A  
OC2A     PORTB3    LED1        TIMER2_OUTPUT_A  50% duty cycle
OC2B     PORTD3    OUTB        TIMER2_OUTPUT_B
  TIMER0 = TIMER2

  Timer 0: 8 bit software interrupt every ~1ms, OUTB
  Timer 1: 16 bit hardware, OUTA
  Timer 2: 8 bit hardware, OUTB
 */

#define GENERATOR_OUTA_DDR                  DDRD
#define GENERATOR_OUTA_PORT                 PORTD
#define GENERATOR_OUTA_PIN                  PORTD6

#define GENERATOR_OUTB_DDR                  DDRB
#define GENERATOR_OUTB_PORT                 PORTB
#define GENERATOR_OUTB_PIN                  PORTB1

#define GENERATOR_OUTC_DDR                  DDRD
#define GENERATOR_OUTC_PORT                 PORTD
#define GENERATOR_OUTC_PIN                  PORTD3

#define GENERATOR_RATE_A_CONTROL            2
#define GENERATOR_RATE_B_CONTROL            1
#define GENERATOR_RATE_C_CONTROL            0

#define GENERATOR_SWITCH_DDR                DDRB
#define GENERATOR_SWITCH_PINS               PINB
#define GENERATOR_SWITCH_PORT               PORTB
#define GENERATOR_SWITCH_PIN_A              PORTB4
#define GENERATOR_SWITCH_PIN_B              PORTB5

#define TIMERA_DDR_A                        DDRB
#define TIMERA_PORT_A                       PORTB
#define TIMERA_OUTPUT_A                     PORTB3
#define TIMERA_DDR_B                        DDRB
#define TIMERA_PORT_B                       PORTB
#define TIMERA_OUTPUT_B                     PORTB1

#define TIMERB_DDR_A                        DDRB
#define TIMERB_PORT_A                       PORTB
#define TIMERB_OUTPUT_A                     PORTB2
#define TIMERB_DDR_B                        DDRD
#define TIMERB_PORT_B                       PORTD
#define TIMERB_OUTPUT_B                     PORTD3



