#ifndef __SOCKET_SERVER_H_
#define __SOCKET_SERVER_H_

#include "wwd_constants.h"
#include "wwd_debug.h"

#include "app.h"
#define BUF_LEN 32
  
class SocketServer {
private:
  enum SocketStatus {
    DISCONNECTED,
    LISTENING,
    CONNECTED,
    ERROR
  };
  SocketStatus status;
  int port;
  uint8_t buffer[BUF_LEN];
  int readLength;
  void* socket;
  int quit_flag;

public:
  SocketServer(int p) : status(DISCONNECTED), port(p), quit_flag(1) {
    reset();
  }

  void quit(){
    quit_flag = 1;
  }

  void reset(){
    memset(buffer, 0, BUF_LEN);
    readLength = 0;
    status = DISCONNECTED;
  }

  bool isConnected(){
    return status == CONNECTED;
  }

  void sendOpenSoundData(uint8_t* data, size_t dataSize){
    if(status == CONNECTED)
      send_data(data, dataSize);
  }

  void run( uint32_t bind_address_in){
    int sock;
    struct sockaddr_in bind_address;
    bind_address.sin_addr.s_addr = (u32_t) bind_address_in;
    bind_address.sin_family = AF_INET;

    /* Create server socket */
    if ( 0 > ( sock = socket( AF_INET, SOCK_STREAM, 0 ) ) ){
        WEB_SERVER_ERROR_PRINT( ( "Failed to create server socket\n" ) );
        return;
    }

    /* Bind socket to port */
    bind_address.sin_port = htons( port );

    if ( 0 > bind( sock, (struct sockaddr *) &bind_address,
            sizeof( struct sockaddr_in ) ) ){
        WEB_SERVER_ERROR_PRINT( ( "Failed bind server socket to port 80 (HTTP)\n" ) );
        return;
    }

    /* Listen for connections on server socket */
    int rc = listen( sock, 10 );
    if ( rc != 0 ){
        WEB_SERVER_ERROR_PRINT( ( "Failed to listen on server socket\n" ) );
        return;
    }

    status = LISTENING;

    /* set timeout for accepting connections - so that quit flag gets checked periodically */
    int recv_timeout = 500; /* milliseconds */
    setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof( recv_timeout ) );

    quit_flag = 0;

    /* Loop forever, reading from socket */
    WEB_SERVER_PRINT(("Waiting for socket requests\n"));
    while ( quit_flag == 0 ){
        struct sockaddr_in remote_address;
        u32_t addr_length;

        /* Wait until a connection on the server socket is received */
        int accepted_socket_hnd = accept( sock, (struct sockaddr *) &remote_address, &addr_length );
        if ( accepted_socket_hnd < 0 ){
            continue;
        }
        recv_timeout = 2000;
        setsockopt( accepted_socket_hnd, SOL_SOCKET, SO_RCVTIMEO, (char*)&recv_timeout, sizeof( recv_timeout ) );
	status = CONNECTED;
	// todo: process connection in separate thread
	quit_flag = process_socket((void*)accepted_socket_hnd);
	status = LISTENING;
        /* End connection */
        close( accepted_socket_hnd );
    }
    quit_flag = 1;
    close( sock );
  }

  int process_socket(void* sock){
    socket = sock;
    int readLength = 0;
    // wait for data
    while(quit_flag == 0){
      readLength = recv_data(buffer, BUF_LEN);
      if(readLength > 0){
	// WPRINT_APP_INFO(("socket recv %d bytes", readLength));
	process_opensound(buffer, readLength);
	if(memrchr(buffer, EOF, readLength) != NULL)
	// if(buffer[readLength-1] == EOF)
	  return 0;
      }
    }
    return 0;
  }

  int recv_data( unsigned char * data, unsigned long length ){
    return recv((int)socket, data, length, 200);
  }

  int send_data( unsigned char * data, unsigned long length ){
    while ( length > 0 ){
      uint16_t packet_size = ( length > MAX_TCP_PAYLOAD ) ? MAX_TCP_PAYLOAD : length;
      /* Send the packet out! */
      int num_sent = send( (int)socket, data, packet_size, 0 );
      if ( num_sent < 0 ){
	WPRINT_APP_INFO( ( "Error sending packet: %d", num_sent ) );
	/* WEB_SERVER_ERROR_PRINT( ( "Error sending packet\n" ) ); */
            return -1;
      }
      data += packet_size;
      length -= packet_size;
    }
    return length;
  }

};

#endif /* __SOCKET_SERVER_H_ */
