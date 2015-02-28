#include "uart.h"

#include "platform.h"
#include "platform_peripheral.h"

#define MIDI_UART         WICED_UART_1
#define RX_BUFFER_SIZE    64
#define WICED_NEVER_TIMEOUT   (0xFFFFFFFF)

/* Externed from platforms/<Platform>/platform.c */
extern const platform_uart_t       platform_uart_peripherals[];
extern platform_uart_driver_t      platform_uart_drivers[];

platform_uart_config_t uart_config = {
    .baud_rate    = 115200,
    .data_width   = DATA_WIDTH_8BIT,
    .parity       = NO_PARITY,
    .stop_bits    = STOP_BITS_1,
    .flow_control = FLOW_CONTROL_DISABLED,
};

wiced_ring_buffer_t rx_buffer;
uint8_t             rx_data[RX_BUFFER_SIZE];

int uart_init(){
  /* Initialise ring buffer */
  ring_buffer_init(&rx_buffer, rx_data, RX_BUFFER_SIZE );

  /* Initialise UART. A ring buffer is used to hold received characters */
  return platform_uart_init( &platform_uart_drivers[MIDI_UART], &platform_uart_peripherals[MIDI_UART], &uart_config, &rx_buffer ) == PLATFORM_SUCCESS ? 0 : -1;

  /* return wiced_uart_init(MIDI_UART, &uart_config, &rx_buffer)  == WICED_SUCCESS; */
}

int uart_transmit_bytes(const void* data, uint32_t size){
    /* Send a test string to the terminal */
  platform_uart_transmit_bytes( &platform_uart_drivers[MIDI_UART], (const uint8_t*) data, size) == PLATFORM_SUCCESS ? 0 : -1;
  /* return wiced_uart_transmit_bytes(MIDI_UART, data, size) == WICED_SUCCESS; */
}

int uart_receive_bytes(void* data, uint32_t size){
  platform_uart_receive_bytes(&platform_uart_drivers[MIDI_UART], (uint8_t*)data, size, WICED_NEVER_TIMEOUT) == PLATFORM_SUCCESS ? 0 : -1;
  /* return wiced_uart_receive_bytes(MIDI_UART, &c, 1, WICED_NEVER_TIMEOUT ) == WICED_SUCCESS; */
}
