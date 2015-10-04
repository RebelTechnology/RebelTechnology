#include "OscMessage.hpp"
#include "OscSender.h"
#include "OscServer.h"

void setCVA(uint16_t cv);
void setCVB(uint16_t cv);

char OscCmd_status[]      = "/status";
char OscCmd_a_trigger[]   = "/trigger_a";
char OscCmd_b_trigger[]   = "/trigger_b";
char OscCmd_cv[]          = "/cv";
char OscCmd_a_cv[]        = "/cv_a";
char OscCmd_b_cv[]        = "/cv_b";
char OscCmd_led[]         = "/led";
char OscCmd_ip[]          = "/localip";
char OscCmd_port[]        = "/localport";
char OscCmd_gain[]        = "/gain";
char OscCmd_ping[]        = "/ping";
/*
OscMessage osc_status_msg(OscCmd_status);
// OscMessage osc_led_msg(OscCmd_led);
// OscMessage osc_ping_msg(OscCmd_ping);
OscMessage osc_a_cv_msg(OscCmd_a_cv);
OscMessage osc_b_cv_msg(OscCmd_b_cv);
OscMessage osc_a_trigger_msg(OscCmd_a_trigger);
OscMessage osc_b_trigger_msg(OscCmd_b_trigger);
*/

OscServer oscserver;
OscSender oscsender;

/*
void sendMessage(OscMessage& msg){
  oscserver.beginPacket();
  msg.write(oscserver);
  oscserver.endPacket();
}
*/

void sendOscStatus(const char* status){
  debugMessage("sending osc status");
  debugMessage(status);
  oscsender.send(OscSender::STATUS, status);
  //  osc_status_msg.setString(0, status);
  //  oscserver.sendMessage(osc_status_msg);
}

void broadcastStatus(){
  oscserver.setBroadcastMode();
  IPAddress ip = WiFi.localIP();
  char buf[24];
  sprintf(buf, "%d.%d.%d.%d:%d", ip[0], ip[1], ip[2], ip[3], localPort);
  sendOscStatus(buf);
}

void oscStatus(OscServer& server, OscMessage& msg){
    debugMessage("osc status");
    if(msg.getDataType(0) == 's')
      debugMessage(msg.getString(0));
    sendOscStatus("hi");
    broadcastStatus();
}

void oscLed(OscServer& server, OscMessage& msg){
  debugMessage("osc led");
  if(msg.getDataType(0) == 'f'){
    if(msg.getFloat(0) > 0.5)
      setLed(LED_RED);
    else
      setLed(LED_GREEN);
  }else if(msg.getDataType(0) == 'i'){
    if(msg.getInt(0) > 0)
      setLed(LED_RED);
    else
      setLed(LED_GREEN);
  }else{
    toggleLed();
  }
}

void oscCv(OscServer& server, OscMessage& msg){
  debugMessage("osc cv");
  int a = 0, b = 0;
  if(msg.getDataType(0) == 'f')
    a = msg.getFloat(0)*4096;
  else // if(msg.getDataType(0) == 'i')
    a = msg.getInt(0);
  a = 4095 - max(0, min(4095, a));
  setCVA(a);
#ifdef SERIAL_DEBUG
  Serial.print("DAC transfer A: ");
  Serial.println(a);
#endif
  if(msg.getDataType(1) == 'f')
    b = msg.getFloat(1)*4096;
  else // if(msg.getDataType(1) == 'i')
    b = msg.getInt(1);
  b = 4095 - max(0, min(4095, b));
  setCVB(b);
#ifdef SERIAL_DEBUG
  Serial.print("DAC transfer B: ");
  Serial.println(b);
#endif
}

void oscCvA(OscServer& server, OscMessage& msg){
  debugMessage("osc cv a");
  int a = 0;
  if(msg.getDataType(0) == 'f')
    a = msg.getFloat(0)*4096;
  else if(msg.getDataType(0) == 'i')
    a = msg.getInt(0);
  a = 4095 - max(0, min(4095, a));
  setCVA(a);
#ifdef SERIAL_DEBUG
  Serial.print("DAC transfer A: ");
  Serial.println(a);
#endif
}

void oscCvB(OscServer& server, OscMessage& msg){
  debugMessage("osc cv b");
  int b = 0;
  if(msg.getDataType(0) == 'f')
    b = msg.getFloat(0)*4096;
  else if(msg.getDataType(0) == 'i')
    b = msg.getInt(0);
  b = 4095 - max(0, min(4095, b));
  setCVB(b);
#ifdef SERIAL_DEBUG
  Serial.print("DAC transfer B: ");
  Serial.println(b);
#endif
}

void oscTriggerA(OscServer& server, OscMessage& msg){
  debugMessage("osc trigger a");
  bool value = digitalRead(DIGITAL_OUTPUT_PIN_A);
  if(msg.getDataType(0) == 'T')
    value = true;
  else if(msg.getDataType(0) == 'F')
    value = false;
  else if(msg.getDataType(0) == 'i')
    value = msg.getInt(0) != 0;
  else if(msg.getDataType(0) == 'f')
    value = msg.getFloat(0) >= 0.5;
  digitalWrite(DIGITAL_OUTPUT_PIN_A, value ? LOW : HIGH);
#ifdef SERIAL_DEBUG
  Serial.print("trigger A: ");
  Serial.println(value);
#endif
}

void oscTriggerB(OscServer& server, OscMessage& msg){
  debugMessage("osc trigger b");
  bool value = digitalRead(DIGITAL_OUTPUT_PIN_B);
  if(msg.getDataType(0) == 'T')
    value = true;
  else if(msg.getDataType(0) == 'F')
    value = false;
  else if(msg.getDataType(0) == 'i')
    value = msg.getInt(0) != 0;
  else if(msg.getDataType(0) == 'f')
    value = msg.getFloat(0) >= 0.5;
  digitalWrite(DIGITAL_OUTPUT_PIN_B, value ? LOW : HIGH);
#ifdef SERIAL_DEBUG
  Serial.print("trigger B: ");
  Serial.println(value);
#endif
}

void sendCvA(uint16_t value){
  oscsender.send(OscSender::CV_A, (float)value/4096.0f);
  //  osc_a_cv_msg.setFloat(0, (float)value/4096.0);
  //  sendMessage(osc_a_cv_msg);
}

void sendCvB(uint16_t value){
  oscsender.send(OscSender::CV_B, (float)value/4096.0f);
  //  osc_b_cv_msg.setFloat(0, (float)value/4096.0);
  //  sendMessage(osc_b_cv_msg);
}

void sendTriggerA(bool value){
  oscsender.send(OscSender::TRIGGER_A, (int)value);
  //  osc_a_trigger_msg.setInt(0, value);
  //  sendMessage(osc_a_trigger_msg);  
}

void sendTriggerB(bool value){
  oscsender.send(OscSender::TRIGGER_B, (int)value);
  //  osc_b_trigger_msg.setInt(0, value);
  //  sendMessage(osc_b_trigger_msg);  
}

void configureOsc(){
  oscserver.addCommand(OscCmd_a_cv, &oscCvA, 1);
  oscserver.addCommand(OscCmd_b_cv, &oscCvB, 1);
  oscserver.addCommand(OscCmd_a_trigger, &oscTriggerA);
  oscserver.addCommand(OscCmd_b_trigger, &oscTriggerB);
  oscserver.addCommand(OscCmd_status, &oscStatus);
  oscserver.addCommand(OscCmd_cv, &oscCv, 2);
  oscserver.addCommand(OscCmd_led, &oscLed);
}
