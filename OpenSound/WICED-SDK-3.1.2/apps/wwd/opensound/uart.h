#ifndef INCLUDED_UART_H
#define INCLUDED_UART_H

#include <stdint.h>

#define UART_BAUD_RATE 57600
/* #define UART_BAUD_RATE 115200 */

#ifdef __cplusplus
extern "C" {
#endif

  int uart_init();
  int uart_transmit_bytes(const void* data, uint32_t size);
  int uart_receive_bytes(void* data, uint32_t size);

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_UART_H */
