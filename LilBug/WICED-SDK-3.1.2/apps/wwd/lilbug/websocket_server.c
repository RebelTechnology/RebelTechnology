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
#include "websocket_server.h"
#include "wwd_debug.h"
#include "wwd_assert.h"
#include "wiced_utilities.h"
#include "platform_toolchain.h"
#include "bug.h"

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

static int                      websocket_server_quit_flag = 1;
static xTaskHandle              websocket_server_thread_handle;
static uint32_t                 server_local_addr;

static void websocket_server_proc( void * thread_input )
{
    run_websocket_server( server_local_addr );

    /* Clean up this startup thread */
    vTaskDelete( websocket_server_thread_handle );
}

void start_websocket_server_thread( uint32_t bind_address_in )
{
    server_local_addr = bind_address_in;
    websocket_server_quit_flag = 0;

    xTaskCreate( websocket_server_proc, (signed char*)"Websockets", WEBSOCKET_SERVER_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, DEFAULT_THREAD_PRIO, &websocket_server_thread_handle );
}

void quit_websocket_server( void )
{
    websocket_server_quit_flag = 1;
}


wiced_bool_t websocket_server_is_running( void )
{
    return ( ( websocket_server_quit_flag != 1 )? WICED_TRUE : WICED_FALSE);
}

void run_websocket_server( uint32_t bind_address_in)
{
    int socket;
    struct sockaddr_in bind_address;
    bind_address.sin_addr.s_addr = (u32_t) bind_address_in;
    bind_address.sin_family = AF_INET;

    /* Create server socket */
    if ( 0 > ( socket = socket( AF_INET, SOCK_STREAM, 0 ) ) )
    {
        WEB_SERVER_ERROR_PRINT( ( "Failed to create server socket\n" ) );
        return;
    }

    /* Bind socket to port 8080 */
    bind_address.sin_port = htons( 8080 );

    if ( 0 > bind( socket, (struct sockaddr *) &bind_address,
            sizeof( struct sockaddr_in ) ) )
    {
        WEB_SERVER_ERROR_PRINT( ( "Failed bind server socket to port 80 (HTTP)\n" ) );
        return;
    }

    /* Listen for connections on server socket */
    int rc = listen( socket, 10 );
    if ( rc != 0 )
    {
        WEB_SERVER_ERROR_PRINT( ( "Failed to listen on server socket\n" ) );
        return;
    }

    /* set timeout for accepting connections - so that quit flag gets checked periodically */
    int recv_timeout = 500; /* milliseconds */
    setsockopt( socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof( recv_timeout ) );

    websocket_server_quit_flag = 0;

    /* Loop forever, serving pages */
    WEB_SERVER_PRINT(("Waiting for page requests\n"));
    while ( websocket_server_quit_flag == 0 )
    {
        struct sockaddr_in remote_address;
        u32_t addr_length;

        /* Wait until a connection on the server socket is received */
        int accepted_socket_hnd = accept( socket, (struct sockaddr *) &remote_address, &addr_length );
        if ( accepted_socket_hnd < 0 )
        {
            continue;
        }

        /* Receive at most 200 bytes from connected socket (enough for request path, query and fragment id) */
        recv_timeout = 2000;
        setsockopt( accepted_socket_hnd, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof( recv_timeout ) );

	websocket_server_quit_flag = process_websocket((void*)accepted_socket_hnd);

        /* End connection */
        close( accepted_socket_hnd );
    }
    websocket_server_quit_flag = 1;
    close( socket );
}

int recv_websocket_data( void * socket, unsigned char * data, unsigned long length ){
  return recv((int)socket, data, length, 200);
}

int send_websocket_data( void * socket, unsigned char * data, unsigned long length ){
    while ( length > 0 )
    {
        uint16_t packet_size = ( length > MAX_TCP_PAYLOAD ) ? MAX_TCP_PAYLOAD : length;
        /* Send the packet out! */
        int num_sent = send( (int)socket, data, packet_size, 0 );
        if ( num_sent < 0 )
        {
	  WPRINT_APP_INFO( ( "Error sending packet: %d", num_sent ) );
            /* WEB_SERVER_ERROR_PRINT( ( "Error sending packet\n" ) ); */
            return -1;
        }
        data += packet_size;
        length -= packet_size;
    }
    return length;
}






