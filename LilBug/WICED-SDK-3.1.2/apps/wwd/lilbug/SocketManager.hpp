/* check http://www.keil.com/pack/doc/mw/Network/html/using_network_sockets_bsd.html 
   https://github.com/yamyamyuo/CS118-Concurrent-Web-Server-using-BSD-Sockets/blob/master/serverFork.c
   http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/
   http://www.gnu.org/software/libc/manual/html_node/Server-Example.html#Server-Example
*/
/* purpose: 
   - accept connection without calling TcpClient copy ctor
   - allow for single threaded, delay-free monitoring and closing of connections
*/
#include "socket.h"

class Socket {
private:
public:
  int32_t sock;
  int16_t read(uint8_t* buf, size_t sz){
    return recv(sock, buf, sz, 0);
  }
  int16_t write(uint8_t* buf, size_t sz){
    return send(sock, buf, sz, 0);
  }
};

#define SOCKET_SERVICE_MAX_SOCKETS 6

class SocketService {
public:
  ~SocketService(){}
  virtual SocketService* process(Socket& sock);
  // SocketService& read(TcpClient& client); // returns the next handler, e.g. close, write
  // SocketService& write(TcpClient& client); // returns the next handler, e.g. close, write
  // void close(TcpClient& client);
};

class SocketManager {
private:
  uint16_t port;
  // long masterSocket;
  int maxSocket;
  timeval timeout;
  SocketService* services[SOCKET_SERVICE_MAX_SOCKETS];
  Socket sockets[SOCKET_SERVICE_MAX_SOCKETS];
  _types_fd_set_cc3000 activeSet;
public:
  SocketManager()
    : maxSocket(0) {
    timeout.tv_sec = 0;
    timeout.tv_usec = 5000; // 5ms is minimum timeout
    for(int i=0; i<SOCKET_SERVICE_MAX_SOCKETS; ++i){
      sockets[i].sock = MAX_SOCK_NUM;
      services[i] = NULL;
    }
  }

  // UDP
  bool udpService(int port, SocketService* service){
    sockaddr tUDPAddr;
    memset(&tUDPAddr, 0, sizeof(tUDPAddr));
    tUDPAddr.sa_family = AF_INET;
    tUDPAddr.sa_data[0] = (_port & 0xFF00) >> 8;
    tUDPAddr.sa_data[1] = (_port & 0x00FF);

    if(bind(_sock, (sockaddr*)&tUDPAddr, sizeof(tUDPAddr)) < 0)
      return false;
    Serial_printf("SocketManager listening on port %d\n", port);
    return true;
  }

  // UDP
  int beginPacket(IPAddress ip, uint16_t port){
    _remoteIP = ip;
    _remotePort = port;
    _remoteSockAddr.sa_family = AF_INET;
    _remoteSockAddr.sa_data[0] = (_remotePort & 0xFF00) >> 8;
    _remoteSockAddr.sa_data[1] = (_remotePort & 0x00FF);
    _remoteSockAddr.sa_data[2] = _remoteIP._address[0];
    _remoteSockAddr.sa_data[3] = _remoteIP._address[1];
    _remoteSockAddr.sa_data[4] = _remoteIP._address[2];
    _remoteSockAddr.sa_data[5] = _remoteIP._address[3];
    _remoteSockAddrLen = sizeof(_remoteSockAddr);
    return 1;
  }

  // UDP
  size_t write(const uint8_t *buffer, size_t size) {
    int rv =  sendto(_sock, buffer, size, 0, &_remoteSockAddr, _remoteSockAddrLen);
    return rv;
  }

  int endPacket(){
    return 1;
  }

  // TCP
  bool connect(int p, SocketService* service){
    port = p;
    services[0] = service;
    if(!WiFi.ready())
      return false;
    sockaddr tServerAddr;
    tServerAddr.sa_family = AF_INET;
    tServerAddr.sa_data[0] = (port & 0xFF00) >> 8;
    tServerAddr.sa_data[1] = (port & 0x00FF);
    tServerAddr.sa_data[2] = 0;
    tServerAddr.sa_data[3] = 0;
    tServerAddr.sa_data[4] = 0;
    tServerAddr.sa_data[5] = 0;
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
      return false;
    long optval = SOCK_ON;
    if(setsockopt(sock, SOL_SOCKET, SOCKOPT_ACCEPT_NONBLOCK, &optval, sizeof(optval)) < 0)
      return false;
    if(bind(sock, (sockaddr*)&tServerAddr, sizeof(tServerAddr)) < 0)
      return false;
    sockets[0].sock = sock;
    /* Initialize the set of active sockets. */
    FD_ZERO(&activeSet);
    FD_SET(sockets[0].sock, &activeSet);
    maxSocket = sock;
    if(listen(sockets[0].sock, 0) < 0)
      return false;
    Serial_printf("SocketManager listening on port %d\n", port);
    return true;
  }

  // class AcceptService : public SocketService {
  // public:
  //   SocketService* process(long sock){
  //   sockaddr tClientAddr;
  //   socklen_t tAddrLen = sizeof(tClientAddr);
  //   long newsock = accept(sockets[0], (sockaddr*)&tClientAddr, &tAddrLen);
  //   if(newsock > 0){
  //     Socket socket(newsock, tClientAddr);
  //     client.sock = sock;
  // }

  void addSocket(long sock){
    Serial_print("adding socket ");
    Serial_print(sock);
    FD_SET(sock, &activeSet);
    if(sock > maxSocket)
      maxSocket = sock;
    for(int i=1; i<SOCKET_SERVICE_MAX_SOCKETS; ++i){
      if(sockets[i].sock == MAX_SOCK_NUM){
	sockets[i].sock = sock;
	services[i] = services[0];
	Serial_print(" [");
	Serial_print(i);
	Serial_println("]");
	break;
      }
    }
  }

  void removeSocket(long sock){
    Serial_print("removing socket ");
    Serial_print(sock);
    FD_CLR(sock, &activeSet);
    for(int i=1; i<SOCKET_SERVICE_MAX_SOCKETS; ++i){
      if(sockets[i].sock == sock){
	sockets[i].sock = MAX_SOCK_NUM;
	Serial_print(" [");
	Serial_print(i);
	Serial_println("]");
      }
    }
    if(maxSocket == sock){
      maxSocket = 0;
      for(int i=0; i<SOCKET_SERVICE_MAX_SOCKETS; ++i){
	if(sockets[i].sock != MAX_SOCK_NUM && sockets[i].sock > maxSocket)
	  maxSocket = sockets[i].sock;
      }
    }
  }

  void doAccept(){
    sockaddr tClientAddr;
    socklen_t tAddrLen = sizeof(tClientAddr);
    long sock = accept(sockets[0].sock, (sockaddr*)&tClientAddr, &tAddrLen);
    if(sock > 0)
      addSocket(sock);
  }
 
  void loop(){
    // call select to check for new connections and service any which are ready to read
    _types_fd_set_cc3000 readSet;
    _types_fd_set_cc3000 writeSet;
    _types_fd_set_cc3000 exceptSet;
    readSet = activeSet;
    writeSet = activeSet;
    exceptSet = activeSet;
    int ret = select(maxSocket+1, &readSet, &writeSet, &exceptSet, &timeout);
    if(ret < 0){
      Serial_printf("select error %d\n", ret);
    }
    if(ret > 0){
      if(FD_ISSET(sockets[0].sock, &readSet)){
	// never called
	Serial_println("master accept");
	doAccept();
      }
      for(int i=1; i<SOCKET_SERVICE_MAX_SOCKETS; ++i){
	if(sockets[i].sock != MAX_SOCK_NUM){
	  if(FD_ISSET(sockets[i].sock, &exceptSet)){
	    // never called
	    Serial_printf("socket except [%d]", i);
	    closesocket(sockets[i].sock);
	    removeSocket(sockets[i].sock);
	  }else if(FD_ISSET(sockets[i].sock, &readSet)){
	    Serial_printf("socket read [%d]", i);
	    // invoke callback to process request
	    if(services[i] == NULL){
	      closesocket(sockets[i].sock);
	      removeSocket(sockets[i].sock);
	    }else{
	      services[i] = services[i]->process(sockets[i]);
	      if(services[i] == NULL){
		closesocket(sockets[i].sock);
		removeSocket(sockets[i].sock);
	      }
	    }
	  }else if(FD_ISSET(sockets[i].sock, &writeSet)){
	    Serial_printf("socket write [%d]", i);
	    // invoke callback to process request
	    if(services[i] == NULL){
	      closesocket(sockets[i].sock);
	      removeSocket(sockets[i].sock);
	    }else{
	      services[i] = services[i]->process(sockets[i]);
	      if(services[i] == NULL){
		closesocket(sockets[i].sock);
		removeSocket(sockets[i].sock);
	      }
	    }
	  }
	}
      }
    }
  }

//     int ret = select(..., &readable, &writeable, &closed, 0);
//     //  Specify zero as the time (a struct timeval containing all zeros) if you want to find out which descriptors are ready without waiting if none are ready.
//     // The normal return value from select is the total number of ready file descriptors in all of the sets. Each of the argument sets is overwritten with information about the descriptors that are ready for the corresponding operation. Thus, to see if a particular descriptor desc has input, use FD_ISSET (desc, read-fds) after select returns.
//     // use two different fd_sets for active socks and readable, copy before select

//     for(int i=0; i<4; ++i){
//       if(FD_ISSET(callbacks[i].client.getSocket(), &readable)){

//       }


// 	callbacks[i].read(callbacks[i].client);
//     }
//   }
// private:
//   SocketCallback callbacks[4];
//   struct SocketCallback {
//     long sock;
//     SocketService& callback;
//   };
};
 
// class TcpClient {
// public:
//   int receive(uint8_t buf, size_t sz);
//   int send(uint8_t buf, size_t sz);
//   void close(){
//     if(isOpen())
//       closesocket(_sock);
//   }
//   bool isOpen(){
//     return _sock != MAX_SOCKET;
//   }
// };

// class SocketService {
// public:
//   SocketService* process(long sock);
//   SocketService& read(TcpClient& client); // returns the next handler, e.g. close, write
//   SocketService& write(TcpClient& client); // returns the next handler, e.g. close, write
//   void close(TcpClient& client);
// };
 
// class TcpConnectionCloser : public SocketService {
// private:
//   uint8_t buf[32]; // small buffer to empty data into
// public:
//   SocketService& receive(TcpClient& client){
//     client.receive(buf, sizeof(buf));
//     return this;
//   }
//   void close(TcpClient& client){
//     client.close();
//   }
// };
