#ifndef _AVR_IO_H_
#define _AVR_IO_H_

#include <inttypes.h>
#include <avr/iomx8.h>
#include <avr/portpins.h>

/* #elif defined (__AVR_ATmega168__) */
/* #  include <avr/iom168.h> */
/* #elif defined (__AVR_ATmega168P__) */
/* #  include <avr/iom168p.h> */
/* #elif defined (__AVR_ATmega328P__) */
/* #  include <avr/iom328p.h> */

#define _BV(bit) (1 << (bit))

#ifdef __cplusplus
extern "C" {
#endif

/* , ISC10, ISC01, INT1, INT0, WGM01, WGM00, CS01, CS00, TOIE0
, ADPS2, ADPS1, ADPS0, REFS0, ADATE, ADEN, ADSC, ADIE */
  extern uint8_t TCCR0A, TCCR0B, TIMSK0;
  extern uint8_t EICRA, EIMSK;
  extern uint8_t ADCSRA, ADMUX;
  extern uint8_t ADCL, ADCH;
  extern uint8_t DDRB, DDRC, DDRD;
  extern uint8_t PORTB, PORTC, PORTD;

/*   extern uint8_t PINB, PINC, PIND; */
#define PINB PORTB
#define PINC PORTC
#define PIND PORTD

/*   extern uint8_t UDR0; */
/*   extern uint8_t PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5, PORTB6, PORTB7; */
/*   extern uint8_t PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5, PORTC6, PORTC7; */
/*   extern uint8_t PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6, PORTD7; */

#ifdef __cplusplus
}
#endif

#endif /* _AVR_IO_H_ */
