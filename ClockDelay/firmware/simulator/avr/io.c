#include "io.h"

/* uint8_t TCCR0A; */
/* uint8_t TCCR0B; */
/* uint8_t WGM01; */
/* uint8_t WGM00; */
/* uint8_t CS01; */
/* uint8_t CS00; */
/* uint8_t TIMSK0; */
/* uint8_t TOIE0; */
/* uint8_t EICRA, ISC10, ISC01, EIMSK, INT1, INT0; */
/* uint8_t ADCSRA, ADPS2, ADPS1, ADPS0, ADMUX, REFS0; */
/* uint8_t ADCL, ADCH, ADATE, ADEN, ADSC, ADIE; */
/* uint8_t UDR0; */
 uint8_t TCCR0A, TCCR0B, TIMSK0;
 uint8_t EICRA, EIMSK;
 uint8_t ADCSRA, ADMUX;
 uint8_t ADCL, ADCH;

uint8_t DDRB, DDRC, DDRD;
/* uint8_t PINB, PINC, PIND; */
uint8_t PORTB, PORTC, PORTD;

/* uint8_t PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5, PORTB6, PORTB7; */
/* uint8_t PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5, PORTC6, PORTC7; */
/* uint8_t PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6, PORTD7; */
