/*
  pin mappings
counter  pin       schematic   function
OC1A     PORTB1    OUTA        TIMER2_OUTPUT_B  50% duty cycle
OC1B     PORTB2    LED2        TIMER2_OUTPUT_A  
OC2A     PORTB3    LED1        TIMER1_OUTPUT_A  50% duty cycle
OC2B     PORTD3    OUTB        TIMER1_OUTPUT_B
  TIMER0 = TIMER2

  Timer 0: 8 bit software interrupt every ~1ms, OUTB
  Timer 1: 16 bit hardware, OUTA
  Timer 8: 8 bit hardware, OUTB
 */

#define GENERATOR_RATE_A_CONTROL            2
#define GENERATOR_DUTY_A_CONTROL            1
#define GENERATOR_RATE_B_CONTROL            0

#define GENERATOR_SWITCH_DDR                DDRB
#define GENERATOR_SWITCH_PINS               PINB
#define GENERATOR_SWITCH_PORT               PORTB
#define GENERATOR_SWITCH_PIN_A              PORTB4
#define GENERATOR_SWITCH_PIN_B              PORTB5

#define TIMER1_DDR_A                        DDRB
#define TIMER1_PORT_A                       PORTB
#define TIMER1_OUTPUT_A                     PORTB3
#define TIMER1_DDR_B                        DDRD
#define TIMER1_PORT_B                       PORTD
#define TIMER1_OUTPUT_B                     PORTD3

#define TIMER2_DDR_A                        DDRB
#define TIMER2_PORT_A                       PORTB
#define TIMER2_OUTPUT_A                     PORTB2
#define TIMER2_DDR_B                        DDRB
#define TIMER2_PORT_B                       PORTB
#define TIMER2_OUTPUT_B                     PORTB1

#define TIMER0_DDR_A                        DDRB
#define TIMER0_PORT_A                       PORTB
#define TIMER0_OUTPUT_A                     PORTB1
#define TIMER0_DDR_B                        DDRB
#define TIMER0_PORT_B                       PORTB
#define TIMER0_OUTPUT_B                     PORTB2


