#include "lwip/opt.h"
#include "lwip/icmp.h"
#include "lwip/inet_chksum.h"
#include "lwip/sockets.h"
#include "lwip/mem.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include "ipv4/lwip/ip.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "wwd_network.h"
#include "wwd_management.h"
#include "wwd_wifi.h"
#include "wwd_debug.h"
#include "wwd_assert.h"
#include "platform/wwd_platform_interface.h"

#include "udp_server.h"

#include <string.h>

// #define PAYLOAD             "/hi\0" ",i\0\0" "\0\0\x04\xd2" /* osc message /hi i 1234 */

int lSocket;
struct sockaddr_in sLocalAddr, sDestAddr;
int udp_status = 0;

// int udp_get_local_addr(){
//   return sLocalAddr.sin_addr.s_addr;
// }

// void sendIp(){
//   // Get the local IP address and send it as an OSC Message
//   uint8_t ip[4] = {
//     (uint8_t) ( (htonl( sLocalAddr.sin_addr.s_addr ) >> 24 ) & 0xff ),
//     (uint8_t) ( ( htonl( sLocalAddr.sin_addr.s_addr ) >> 16 ) & 0xff ),
//     (uint8_t) ( ( htonl( sLocalAddr.sin_addr.s_addr ) >> 8 ) & 0xff ),
//     (uint8_t) ( ( htonl( sLocalAddr.sin_addr.s_addr ) >> 0 ) & 0xff ) };
//   OscMessage msg(OscCmd_ip);
// // msg.add(ip[0]).add(ip[1]).add(ip[2]).add(ip[3]);
//   char buf[16];
//   sprintf(buf, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
//   msg.add('s', (uint8_t*)buf, strlen(buf));
//   sendMessage(msg);
//   // Serial_print("Local IP: ");
//   // Serial_println(ip);
// }

void udp_send_packet(uint8_t* buffer, int size){
  if(udp_status == 1)
    sendto(lSocket, buffer, size, 0, (struct sockaddr *)&sDestAddr, sizeof(sDestAddr));
  // WPRINT_APP_INFO(("sent UDP message %s", buffer));
}

void udp_server_task(void*){
  // char reply[] = "/hi\0" ",i\0\0" "\0\0\x04\xd2";
  char reply[] = "/hi\0" ",\0\0\0";
  char buffer[1024];
  int nbytes;
  int err;
  lSocket = lwip_socket(AF_INET, SOCK_DGRAM, 0);
       
  memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
  memset((char *)&sDestAddr, 0, sizeof(sDestAddr));

  /*Destination*/
  sDestAddr.sin_family = AF_INET;
  sDestAddr.sin_len = sizeof(sDestAddr);
  sDestAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  sDestAddr.sin_port = htons(9000);
       
  /*Source*/
  sLocalAddr.sin_family = AF_INET;
  sLocalAddr.sin_len = sizeof(sLocalAddr);
  sLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  sLocalAddr.sin_port = htons(8000);

  err = bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr));
  if(err >= 0){
    // vTaskDelay( 200 );  //some delay!
    // sendIp();
    sendto(lSocket, reply, sizeof(reply), 0, (struct sockaddr *)&sDestAddr, sizeof(sDestAddr));
    udp_status = 1;

    for(;;){
      nbytes = recv(lSocket, buffer, sizeof(buffer), 8);
      if(nbytes>0){
	udp_recv_packet((uint8_t*)buffer, nbytes);
      }
      // sendto(lSocket, reply, sizeof(reply), 0, (struct sockaddr *)&sDestAddr, sizeof(sDestAddr));
      vTaskDelay( 200 );  //some delay!
    }
  }
  close(lSocket);
  for(;;);
}
