#ifndef SOCKET_SERVER_H_INCLUDED
#define SOCKET_SERVER_H_INCLUDED

#include "wwd_constants.h"
#include "wwd_debug.h"

#define SOCKET_SERVER_STACK_SIZE      2048
#define SOCKET_SERVER_PORT            8008

#ifdef __cplusplus
extern "C" {
#endif

  void start_socket_server_thread( uint32_t bind_address_in );
  wiced_bool_t socket_server_is_running( void );
  void quit_socket_server( void );
  void send_socket_data(unsigned char * data, unsigned long length);


#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef SOCKET_SERVER_H_INCLUDED */
