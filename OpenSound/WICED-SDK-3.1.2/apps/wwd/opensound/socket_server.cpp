#include <stdlib.h>
#include "wwd_wifi.h"
#include "wwd_management.h"
#include "wwd_network.h"
#include "network/wwd_buffer_interface.h"
#include "platform/wwd_platform_interface.h"
#include "lwip/opt.h"
#include "lwip/mem.h"
#include <string.h>
#include "lwip/init.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"  /* equivalent of <sys/socket.h> */
#include "lwip/inet.h"
#include "lwip/dhcp.h"
#include "wwd_wifi.h"
#include "wwd_management.h"
#include "network/wwd_buffer_interface.h"
#include "platform/wwd_platform_interface.h"
#include "RTOS/wwd_rtos_interface.h"
#include "socket_server.h"
#include "wwd_debug.h"
#include "wwd_assert.h"
#include "wiced_utilities.h"
#include "platform_toolchain.h"
#include "app.h"

#ifndef WEB_SERVER_NO_PRINT
#define WEB_SERVER_ERROR_PRINT( x )  WINFO_APP_ERROR( x )
#define WEB_SERVER_PRINT( x )        WINFO_APP( x )
#else
#define WEB_SERVER_ERROR_PRINT( x )  wiced_assert( "", 0!=0 )
#define WEB_SERVER_PRINT( x )
#endif

#define ETHER_PAYLOAD_MTU (1500)
#define IP_HEADER_SIZE    (20)
#define TCP_HEADER_SIZE   (20)
/* Using the full MTU for TCP causes issues with LwIP trying to chain buffers */
/* #define MAX_TCP_PAYLOAD   ( ETHER_PAYLOAD_MTU - IP_HEADER_SIZE - TCP_HEADER_SIZE ) */
#define MAX_TCP_PAYLOAD 1200

#include "SocketServer.hpp"

static xTaskHandle              socket_server_thread_handle;
static uint32_t                 server_local_addr;

static SocketServer sockserv(SOCKET_SERVER_PORT);

static void socket_server_proc( void * thread_input ){
  sockserv.run(server_local_addr);
  vTaskDelete( socket_server_thread_handle );
}

void start_socket_server_thread( uint32_t bind_address_in ){
  server_local_addr = bind_address_in;

  xTaskCreate( socket_server_proc, (signed char*)"SocketServer", SOCKET_SERVER_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, DEFAULT_THREAD_PRIO, &socket_server_thread_handle );
}

void quit_socket_server( void ){
  sockserv.quit();
}

void send_socket_data(unsigned char * data, unsigned long length){
  if(sockserv.isConnected())
    sockserv.send_data(data, length);
}





