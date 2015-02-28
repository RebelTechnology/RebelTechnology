#include "uart.h"

wiced_result_t wiced_uart_init( wiced_uart_t uart, const wiced_uart_config_t* config, wiced_ring_buffer_t* optional_rx_buffer )
{
#ifndef WICED_DISABLE_STDIO
    /* Interface is used by STDIO. Uncomment WICED_DISABLE_STDIO to overcome this */
    if ( uart == STDIO_UART )
    {
        return WICED_ERROR;
    }
#endif
    return (wiced_result_t) platform_uart_init( &platform_uart_drivers[uart], &platform_uart_peripherals[uart], config, optional_rx_buffer );
}

wiced_result_t wiced_uart_deinit( wiced_uart_t uart )
{
    return (wiced_result_t) platform_uart_deinit( &platform_uart_drivers[uart] );
}

wiced_result_t wiced_uart_transmit_bytes( wiced_uart_t uart, const void* data, uint32_t size )
{
    return (wiced_result_t) platform_uart_transmit_bytes( &platform_uart_drivers[uart], (const uint8_t*) data, size );
}

wiced_result_t wiced_uart_receive_bytes( wiced_uart_t uart, void* data, uint32_t size, uint32_t timeout )
{
    return (wiced_result_t) platform_uart_receive_bytes( &platform_uart_drivers[uart], (uint8_t*)data, size, timeout );
}

/* wiced_result_t wiced_watchdog_kick( void ) */
/* { */
/*     return (wiced_result_t) platform_watchdog_kick( ); */
/* } */
