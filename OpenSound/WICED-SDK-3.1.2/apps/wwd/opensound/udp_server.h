#ifndef INCLUDED_UDP_SERVER_H
#define INCLUDED_UDP_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

  void udp_server_task(void*);
  void udp_recv_packet(uint8_t* buffer, int size);
  void udp_send_packet(uint8_t* buffer, int size);

#ifdef __cplusplus
} /*extern "C" */
#endif


#endif /* ifndef INCLUDED_UDP_SERVER_H */
