#include "uart.h"

#include "platform.h"
#include "platform_peripheral.h"

#define MIDI_UART         WICED_UART_1
#define RX_BUFFER_SIZE    64

wiced_uart_config_t uart_config = {
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
  return wiced_uart_init(MIDI_UART, &uart_config, &rx_buffer)  == WICED_SUCCESS;
}

int uart_transmit_bytes(const void* data, uint32_t size){
    /* Send a test string to the terminal */
  return wiced_uart_transmit_bytes(MIDI_UART, data, size) == WICED_SUCCESS;
}

int uart_receive_bytes(void* data, uint32_t size){
  return wiced_uart_receive_bytes(MIDI_UART, &c, 1, WICED_NEVER_TIMEOUT ) == WICED_SUCCESS;
}
