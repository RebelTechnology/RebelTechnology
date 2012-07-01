#ifndef _AVR_IO_H_
#define _AVR_IO_H_

#include <inttypes.h>
#include <avr/iomx8.h>
#include <avr/portpins.h>
#include <avr/sfr_defs.h>

#define _BV(bit) (1 << (bit))

#ifdef __cplusplus
extern "C" {
#endif

#define F_CPU 16000000

/* , ISC10, ISC01, INT1, INT0, WGM01, WGM00, CS01, CS00, TOIE0
, ADPS2, ADPS1, ADPS0, REFS0, ADATE, ADEN, ADSC, ADIE */
  extern uint8_t UBRR0H, UBRR0L, UCSR0B, UCSR0A, UDR0;
  extern uint8_t TCCR0A, TCCR0B, TIMSK0;
  extern uint8_t TIMSK1, TCCR1A, TCCR1B, OCR1A, OCR1B;
  extern uint8_t TIMSK2, TCCR2A, TCCR2B, OCR2A, OCR2B;
  extern uint8_t EICRA, EIMSK;
  extern uint8_t ADCSRA, ADMUX;
  extern uint8_t ADCL, ADCH;
  extern uint8_t DDRB, DDRC, DDRD;
  extern uint8_t PORTB, PORTC, PORTD;

  extern uint8_t SREG; // System Register

#define PINB PORTB
#define PINC PORTC
#define PIND PORTD

#ifdef __cplusplus
}
#endif

#endif /* _AVR_IO_H_ */
