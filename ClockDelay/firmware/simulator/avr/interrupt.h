#ifndef _AVR_INTERRUPT_H_
#define _AVR_INTERRUPT_H_

#include <stdio.h>
#include <avr/io.h>

#define __AVR_ATmega168__

#ifdef __cplusplus
extern "C" {
#endif

void sei(void);
void cli(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#define ISR(vector)					\
extern "C" void vector(void);				\
void vector (void)
#else
#define ISR(vector)					\
void vector (void)
#endif

#ifdef __cplusplus
#define SIGNAL(signame)					\
extern "C" void signame(void);				\
void signame (void)
#else
#define SIGNAL(signame)					\
void signame (void)
#endif

#ifdef __cplusplus
#define EMPTY_INTERRUPT(vector)                \
extern "C" void vector(void);                  \
void vector (void) __attribute__ ((naked));    \
void vector (void) {  __asm__ __volatile__ ("reti" ::); }
#else
#define EMPTY_INTERRUPT(vector)                \
void vector (void) __attribute__ ((naked));    \
void vector (void) { __asm__ __volatile__ ("reti" ::); }
#endif

#endif
