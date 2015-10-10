#include "opensound.h"
#include "OscMessage.hpp"
#include "OscSender.h"
#include "OscServer.h"

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
  bool broadcast = oscserver.isBroadcastMode();
  oscserver.setBroadcastMode(true);
  IPAddress ip = WiFi.localIP();
  char buf[24];
  sprintf(buf, "%d.%d.%d.%d:%d", ip[0], ip[1], ip[2], ip[3], networkSettings.localPort);
  sendOscStatus(buf);
  oscserver.setBroadcastMode(broadcast);
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
      setLed(LED_YELLOW);
    else
      setLed(LED_GREEN);
  }else if(msg.getDataType(0) == 'i'){
    if(msg.getInt(0) > 0)
      setLed(LED_YELLOW);
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
    a = msg.getFloat(0)*2047 + 2047;
  else // if(msg.getDataType(0) == 'i')
    a = msg.getInt(0);
  setCVA(a);
  if(msg.getDataType(1) == 'f')
    b = msg.getFloat(1)*2047 + 2047;
  else // if(msg.getDataType(1) == 'i')
    b = msg.getInt(1);
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
    a = msg.getFloat(0)*2047 + 2047;
  else if(msg.getDataType(0) == 'i')
    a = msg.getInt(0);
  setCVA(a);
}

void oscCvB(OscServer& server, OscMessage& msg){
  debugMessage("osc cv b");
  int b = 0;
  if(msg.getDataType(0) == 'f')
    b = msg.getFloat(0)*2047 + 2047;
  else if(msg.getDataType(0) == 'i')
    b = msg.getInt(0);
  setCVB(b);
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
  setTriggerA(value);
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
  setTriggerB(value);
}

void sendCvA(uint16_t value){
  oscsender.send(OscSender::CV_A, (float)value/2048.0f - 1.0f);
}

void sendCvB(uint16_t value){
  oscsender.send(OscSender::CV_B, (float)value/2048.0f - 1.0f);
}

void sendTriggerA(bool value){
  oscsender.send(OscSender::TRIGGER_A, (int)value);
}

void sendTriggerB(bool value){
  oscsender.send(OscSender::TRIGGER_B, (int)value);
}

void configureOsc(){
  oscsender.init();
  oscserver.init();
  oscserver.addCommand(addressSettings.inputAddress[0], &oscStatus);
  oscserver.addCommand(addressSettings.inputAddress[1], &oscCvA, 1);
  oscserver.addCommand(addressSettings.inputAddress[2], &oscCvB, 1);
  oscserver.addCommand(addressSettings.inputAddress[3], &oscTriggerA);
  oscserver.addCommand(addressSettings.inputAddress[4], &oscTriggerB);
  oscserver.addCommand("/osm/cv", &oscCv, 2);
  oscserver.addCommand("/osm/led", &oscLed);
}
