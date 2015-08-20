#include "OscMessage.hpp"

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

#define MAX_OSC_COMMANDS 8
class OscServer : public UdpServer {
  typedef void OscCommand(OscServer &server, OscMessage& msg);
  struct OscCommandMap {
    char* address;
    uint8_t addressLen;
    uint8_t minArgs;
    OscCommand* cmd;
    bool matches(OscMessage& msg){
      return strncmp(msg.getAddress(), address, addressLen) == 0 && msg.size() >= minArgs;
    }
  };
  int commandCount = 0;
  OscCommandMap commands[MAX_OSC_COMMANDS];
public:
  OscServer() : commandCount(0) {}

  void reset(){
    commandCount = 0;
  }

  void addCommand(char* address, OscCommand* cmd, int minArgs = 0){
    if(commandCount < MAX_OSC_COMMANDS){
      commands[commandCount].address = address;
      commands[commandCount].addressLen = strlen(address);
      commands[commandCount].minArgs = minArgs;
      commands[commandCount].cmd = cmd;    
      commandCount++;
    }
  }

  void udp_recv_packet(uint8_t* buffer, int size){
    OscMessage msg;
    msg.parse(buffer, size);
    for(int i=0; i<commandCount; ++i)
      if(commands[i].matches(msg)){
	commands[i].cmd(*this, msg);
	break;
      }
  }

  void sendMessage(OscMessage& msg){
    UdpServer::beginPacket();
    msg.write(*this);
    UdpServer::endPacket();
  }

  void setBroadcastMode(){
    remoteIPAddress = WiFi.localIP();
    remoteIPAddress[3] = 255;
    Serial.print("Remote IP (broadcast): ");
    Serial.println(remoteIPAddress);
  }
};

OscServer oscserver;

class Osc {
public:
  enum OscMessageId {
    STATUS = 0,
    CV_A,
    CV_B,
    TRIGGER_A,
    TRIGGER_B,
    MESSAGE_COUNT
  };
  OscMessage messages[MESSAGE_COUNT];

  Osc(){
    messages[STATUS].setAddress(OscCmd_status);
    messages[STATUS].addString();
    messages[CV_A].setAddress(OscCmd_a_cv);
    messages[CV_A].addFloat(.0f);
    messages[CV_B].setAddress(OscCmd_b_cv);
    messages[CV_B].addFloat(.0f);
    messages[TRIGGER_A].setAddress(OscCmd_a_trigger);
    messages[TRIGGER_A].addInt(0);
    messages[TRIGGER_B].setAddress(OscCmd_b_trigger);
    messages[TRIGGER_B].addInt(0);
    // osc_status_msg.addString();
    // osc_a_cv_msg.addFloat(.0f);
    // osc_b_cv_msg.addFloat(.0f);
    // osc_a_trigger_msg.addInt(0);
    // osc_b_trigger_msg.addInt(0);
  // note_on_msg.add((int32_t)0);
  // note_on_msg.add((int32_t)0);
  // note_on_msg.add((int32_t)0);
  // note_off_msg.add((int32_t)0);
  // note_off_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // pitch_bend_msg.add((int32_t)0);
  // pitch_bend_msg.add((int32_t)0);
  }

  void setAddress(OscMessageId mid, char* address){
    if(mid < MESSAGE_COUNT)
      messages[mid].setAddress(address);
  }

  char* getAddress(OscMessageId mid){
    if(mid < MESSAGE_COUNT)
      return messages[mid].getAddress();
    return NULL;
  }

  void send(OscMessageId mid, float value){
    if(mid < MESSAGE_COUNT){
      messages[mid].setFloat(0, value);
      oscserver.beginPacket();
      messages[mid].write(oscserver);
      oscserver.endPacket();
    }
  }

  void send(OscMessageId mid, const char* value){
    if(mid < MESSAGE_COUNT){
      messages[mid].setString(0, value);
      oscserver.beginPacket();
      messages[mid].write(oscserver);
      oscserver.endPacket();
    }
  }
};

Osc osc;

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
  osc.send(Osc::STATUS, status);
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
  dac_set_a(a);
  Serial.print("DAC transfer A: ");
  Serial.println(a);
  if(msg.getDataType(1) == 'f')
    b = msg.getFloat(1)*4096;
  else // if(msg.getDataType(1) == 'i')
    b = msg.getInt(1);
  b = 4095 - max(0, min(4095, b));
  dac_set_b(b);
  Serial.print("DAC transfer B: ");
  Serial.println(b);
}

void oscCvA(OscServer& server, OscMessage& msg){
  debugMessage("osc cv a");
  int a = 0;
  if(msg.getDataType(0) == 'f')
    a = msg.getFloat(0)*4096;
  else if(msg.getDataType(0) == 'i')
    a = msg.getInt(0);
  a = 4095 - max(0, min(4095, a));
  dac_set_a(a);
  Serial.print("DAC transfer A: ");
  Serial.println(a);
}

void oscCvB(OscServer& server, OscMessage& msg){
  debugMessage("osc cv b");
  int b = 0;
  if(msg.getDataType(0) == 'f')
    b = msg.getFloat(0)*4096;
  else if(msg.getDataType(0) == 'i')
    b = msg.getInt(0);
  b = 4095 - max(0, min(4095, b));
  dac_set_b(b);
  Serial.print("DAC transfer B: ");
  Serial.println(b);
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
  Serial.print("trigger A: ");
  Serial.println(value);
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
  Serial.print("trigger B: ");
  Serial.println(value);
}

void sendCvA(uint16_t value){
  osc.send(Osc::CV_A, value/4096.0);
  //  osc_a_cv_msg.setFloat(0, (float)value/4096.0);
  //  sendMessage(osc_a_cv_msg);
}

void sendCvB(uint16_t value){
  osc.send(Osc::CV_B, value/4096.0);
  //  osc_b_cv_msg.setFloat(0, (float)value/4096.0);
  //  sendMessage(osc_b_cv_msg);
}

void sendTriggerA(bool value){
  osc.send(Osc::TRIGGER_A, (int)value);
  //  osc_a_trigger_msg.setInt(0, value);
  //  sendMessage(osc_a_trigger_msg);  
}

void sendTriggerB(bool value){
  osc.send(Osc::TRIGGER_B, (int)value);
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
