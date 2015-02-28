#ifndef INCLUDED_UART_H
#define INCLUDED_UART_H

#include "platform.h"
#include "platform_peripheral.h"

#define MIDI_UART WICED_UART_1

#ifdef __cplusplus
extern "C" {
#endif

/* Externed from platforms/<Platform>/platform.c */
/* extern const platform_gpio_t       platform_gpio_pins[]; */
/* extern const platform_adc_t        platform_adc_peripherals[]; */
/* extern const platform_i2c_t        platform_i2c_peripherals[]; */
/* extern const platform_pwm_t        platform_pwm_peripherals[]; */
/* extern const platform_spi_t        platform_spi_peripherals[]; */
extern const platform_uart_t       platform_uart_peripherals[];
extern platform_uart_driver_t      platform_uart_drivers[];
/* extern platform_spi_slave_driver_t platform_spi_slave_drivers[]; */

typedef platform_uart_config_t                  wiced_uart_config_t;

/** Initialises a UART interface
 *
 * Prepares an UART hardware interface for communications
 *
 * @param  uart     : the interface which should be initialised
 * @param  config   : UART configuration structure
 * @param  optional_rx_buffer : Pointer to an optional RX ring buffer
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred with any step
 */
wiced_result_t wiced_uart_init( wiced_uart_t uart, const wiced_uart_config_t* config, wiced_ring_buffer_t* optional_rx_buffer );


/** Deinitialises a UART interface
 *
 * @param  uart : the interface which should be deinitialised
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred with any step
 */
wiced_result_t wiced_uart_deinit( wiced_uart_t uart );


/** Transmit data on a UART interface
 *
 * @param  uart     : the UART interface
 * @param  data     : pointer to the start of data
 * @param  size     : number of bytes to transmit
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred with any step
 */
wiced_result_t wiced_uart_transmit_bytes( wiced_uart_t uart, const void* data, uint32_t size );


/** Receive data on a UART interface
 *
 * @param  uart     : the UART interface
 * @param  data     : pointer to the buffer which will store incoming data
 * @param  size     : number of bytes to receive
 * @param  timeout  : timeout in milisecond
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred with any step
 */
wiced_result_t wiced_uart_receive_bytes( wiced_uart_t uart, void* data, uint32_t size, uint32_t timeout );

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_UART_H */
