#include "web_server.h"
#include "platform/wwd_platform_interface.h"

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
#include "OscMessage.hpp"
#include "WebSocketServer.hpp"
#include "spi.h"
#include "gpio.h"

char* OscCmd_trigger_a   = (char*)"/trigger_a";
char* OscCmd_trigger_b   = (char*)"/trigger_b";
char* OscCmd_status      = (char*)"/status";
char* OscCmd_cv_a        = (char*)"/cv_a";
char* OscCmd_cv_b        = (char*)"/cv_b";
char* OscCmd_cv_ab       = (char*)"/cv";
char* OscCmd_led         = (char*)"/led";
char* OscCmd_ip          = (char*)"/localip";
char* OscCmd_port        = (char*)"/localport";
char* OscCmd_gain        = (char*)"/gain";
char* OscCmd_ping        = (char*)"/ping"; // todo

OscMessage trigger_a_msg(OscCmd_trigger_a);
OscMessage trigger_b_msg(OscCmd_trigger_b);
OscMessage cv_a_msg(OscCmd_cv_a);
OscMessage cv_b_msg(OscCmd_cv_b);
OscMessage cv_ab_msg(OscCmd_cv_ab);

void sendMessage(OscMessage& msg){
  uint8_t buf[64];
  int len = msg.copy(buf, sizeof(buf));
  if(len > 0)
    udp_send_packet(buf, len);
  else
    WPRINT_APP_INFO(("Failed to send osc message: %d", len));
}

void setTrigger(int ch){
  if(ch)
    clearPin(OPENSOUND_TRIG_OUT_B_PORT, OPENSOUND_TRIG_OUT_B_PIN);
  else
    clearPin(OPENSOUND_TRIG_OUT_A_PORT, OPENSOUND_TRIG_OUT_A_PIN);
}

void clearTrigger(int ch){
  if(ch)
    setPin(OPENSOUND_TRIG_OUT_B_PORT, OPENSOUND_TRIG_OUT_B_PIN);
  else
    setPin(OPENSOUND_TRIG_OUT_A_PORT, OPENSOUND_TRIG_OUT_A_PIN);
}

void setCv(int ch, int value){
  if(ch)
    dac_set_a(value);
  else
    dac_set_b(value);
}

void sendOscTrigger(int ch){
  if(ch)
    sendMessage(trigger_a_msg);
  else
    sendMessage(trigger_b_msg);
}

WebSocketServer ws;
int process_websocket(void* socket){  
  ws.reset();
  return ws.process(socket);
}

void debug_message(const char* string){
  // do naught
}

void setup(void){
  dac_setup();

  // todo: enable clocks
  configureDigitalOutput(OPENSOUND_TRIG_OUT_A_PORT, OPENSOUND_TRIG_OUT_A_PIN);
  configureDigitalOutput(OPENSOUND_TRIG_OUT_B_PORT, OPENSOUND_TRIG_OUT_B_PIN);
  configureDigitalInput(OPENSOUND_TRIG_IN_A_PORT, OPENSOUND_TRIG_IN_A_PIN, GPIO_PuPd_UP);
  configureDigitalInput(OPENSOUND_TRIG_IN_B_PORT, OPENSOUND_TRIG_IN_B_PIN, GPIO_PuPd_UP);

  cv_a_msg.add((int32_t)0);
  cv_b_msg.add((int32_t)0);
  cv_ab_msg.add((int32_t)0);
  cv_ab_msg.add((int32_t)0);

  debug_message("showtime");
}

void pollOpenSoundTask(void*){
  bool triggerStateA, triggerStateB = false;
  for(;;){
// #if 0
  if(getPin(OPENSOUND_TRIG_IN_A_PORT, OPENSOUND_TRIG_IN_A_PIN) != triggerStateA){
    triggerStateA = !triggerStateA;
    sendOscTrigger(0);
  }
  if(getPin(OPENSOUND_TRIG_IN_B_PORT, OPENSOUND_TRIG_IN_B_PIN) != triggerStateB){
    triggerStateB = !triggerStateB;
    sendOscTrigger(1);
  }
// #endif
    vTaskDelay( 200 );  //some delay!
  }
  // todo: poll CV inputs
}

/* web handler todo: factor out */
#include <stdlib.h>

// static const char no_content_header[] = "HTTP/1.1 204 No Content\r\n\r\n";  
// static const char empty_page[] = "<html/>\n";
// static const char empty_image[] = "\x00";
// static const char pitch_param[] = "pitch";
// static const char velocity_param[] = "velocity";

void handleOscTrigger(OscMessage &message, int ch){
  if(message.size() > 0 && message.getInt(0)){
    setTrigger(ch);
  }else{
    clearTrigger(ch);
  }
}

void handleOscCv(OscMessage &message, int ch){
  if(message.size() == 1){
    int value = message.getInt(0);
    setCv(ch, value);
  }
}

void handleOscStatus(OscMessage &message){
  // todo: send ip and port details
}

void handleOscLed(OscMessage &message){
  // todo: toggle led
}

void udp_recv_packet(uint8_t* buffer, int size){
  OscMessage msg;
  msg.parse(buffer, size);
  WPRINT_APP_INFO(("received UDP message %s", msg.getAddress()));  
  char* address = msg.getAddress();
  if(strcmp(OscCmd_trigger_a, address) == 0){
    handleOscTrigger(msg, 0);
  }else if(strcmp(OscCmd_trigger_b, address) == 0){
    handleOscTrigger(msg, 1);
  }else if(strcmp(OscCmd_cv_a, address) == 0){
    handleOscCv(msg, 0);
  }else if(strcmp(OscCmd_cv_b, address) == 0){
    handleOscCv(msg, 1);
  }else if(strcmp(OscCmd_status, address) == 0){
    handleOscStatus(msg);
  }else if(strcmp(OscCmd_led, address) == 0){
    handleOscLed(msg);
  }
}

/* handle incoming data from web socket */
void process_opensound(uint8_t* data, size_t dataSize){
  uart_transmit_bytes(data, dataSize);
}
