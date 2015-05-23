#include "web_server.h"

#define DEBUG_USART

#ifdef DEBUG_USART
#define Serial_printf(fmt, ...) printf(fmt, __VA_ARGS__)
#define Serial_print(x) puts(x)
#define Serial_println(x) puts(x "\n")
#else // DEBUG_USART
#define Serial_printf(...) 
#define Serial_print(x) 
#define Serial_println(x) 
#endif // DEBUG_USART

#include "app.h"
#include "uart.h"
#include <string.h>
#include "udp_server.h"
// #include "socket_server.h"
#include "WebSocketServer.hpp"

WebSocketServer ws;
int process_websocket(void* socket){  
  ws.reset();
  return ws.process(socket);
}

void debug_message(const char* string){
  // do naught
}

void setup(void){
  debug_message("showtime");
}

void pollOpenSoundTask(void*){
  const uint8_t init_str[] = { 'x' };
  // todo:
    // Sampling rate: 500sps
    // Drift filter: On
    // Right leg drive: On
    // Gain: 12x
    // Continuous sampling: Off

  uart_transmit_bytes(init_str, sizeof(init_str));
  uint8_t buffer[11]; // one frame of data is 11 bytes
  for(;;){
    if(uart_receive_bytes(buffer, sizeof(buffer)) == 0){
      // send_socket_data(buffer, sizeof(buffer));
      ws.sendOpenSoundData(buffer, sizeof(buffer));
    }
  }
}

/* web handler todo: factor out */
#include <stdlib.h>

static const char no_content_header[] = "HTTP/1.1 204 No Content\r\n\r\n";  
static const char empty_page[] = "<html/>\n";
static const char empty_image[] = "\x00";
static const char pitch_param[] = "pitch";
static const char velocity_param[] = "velocity";

void udp_recv_packet(uint8_t* buffer, int size){
  // OscMessage msg;
  // msg.parse(buffer, size);
  // WPRINT_APP_INFO(("received UDP message %s", msg.getAddress()));  
  // char* address = msg.getAddress();
  // if(strcmp(OscCmd_status, address) == 0){
  //   oscStatus(msg);
  // }else if(strcmp(OscCmd_led, address) == 0){
  //   oscLed(msg);
  // }else if(strcmp(OscCmd_note_on, address) == 0){
  //   oscNoteOn(msg);
  // }else if(strcmp(OscCmd_note_off, address) == 0){
  //   oscNoteOff(msg);
  // }else if(strcmp(OscCmd_control_change, address) == 0){
  //   oscControlChange(msg);
  // }else if(strcmp(OscCmd_pitch_bend, address) == 0){
  //   oscPitchBend(msg);
  // }

  // WPRINT_APP_INFO(("sent UDP message %s", buffer));  
}

/* handle incoming data from web socket */
void process_opensound(uint8_t* data, size_t dataSize){
  uart_transmit_bytes(data, dataSize);
}
