#ifndef WEBSOCKET_SERVER_H_INCLUDED
#define WEBSOCKET_SERVER_H_INCLUDED

#include "wwd_constants.h"
#include "wwd_debug.h"

#define WEBSOCKET_SERVER_STACK_SIZE      2048

#ifdef __cplusplus
extern "C" {
#endif

int send_websocket_data( void * socket, unsigned char * data, unsigned long length );

int recv_websocket_data( void * socket, unsigned char * data, unsigned long length );

void run_websocket_server( uint32_t bind_address_in );

void start_websocket_server_thread( uint32_t bind_address_in );
wiced_bool_t websocket_server_is_running( void );
void quit_websocket_server( void );


#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef WEBSOCKET_SERVER_H_INCLUDED */
