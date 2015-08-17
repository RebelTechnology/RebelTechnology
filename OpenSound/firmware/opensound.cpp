// #include <assert.h> causes undefined symbols in nanolib
#include "application.h"
#include "opensound.h"
#include <stdint.h>
//#include "WebSocketServer.hpp"
// #include "WebServer.hpp"
#include "TcpSocketServer.hpp"
#include "UdpServer.hpp"
#include "dac.h"


#include "WebServer.h"

SYSTEM_MODE(MANUAL);
// #define RX_BUFFER_LENGTH 64
#define TCP_SERVER_PORT       8888
#define HTTP_SERVER_PORT      80
#define WEBSOCKET_SERVER_PORT 8008
#define SERIAL_BAUD_RATE      57600
#define UDP_REMOTE_PORT       9000
#define UDP_LOCAL_PORT        8000

#define DEFAULT_ANTENNA ANT_AUTO

int remotePort = UDP_REMOTE_PORT;
int localPort = UDP_LOCAL_PORT;
IPAddress remoteIPAddress(192,168,2,172);

const char* OPENSOUND_WIFI_SSID = "FortRebel";
const char* OPENSOUND_WIFI_PASSWORD = "notwhattheyseem";

#define ANALOG_PIN_A         A0
#define ANALOG_PIN_B         A1
/* SPI uses pins A2 to A5 */
#define DIGITAL_OUTPUT_PIN_A D0
#define DIGITAL_OUTPUT_PIN_B D1
#define DIGITAL_INPUT_PIN_A  D2
#define DIGITAL_INPUT_PIN_B  D3
#define BUTTON_PIN           D6
#define GREEN_LED_PIN        A6
#define RED_LED_PIN          A7
#define ANALOG_THRESHOLD     15

enum LedPin {
  LED_NONE,
  LED_GREEN,
  LED_RED,
  };

// LedPin getLed();

inline void setLed(LedPin led){
  if(led == LED_RED){
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }else if(led == LED_GREEN){
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }else{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}
inline void toggleLed(){
  digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN));
  digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN));
}

#if 1
#define PREFIX ""
WebServer webserver(PREFIX, HTTP_SERVER_PORT);
#else
WebServer webserver(HTTP_SERVER_PORT);
#endif

template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

void webIndex(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server << "<html><body>"
	   << "<form action='/settings' method='POST'>"
	   << "<p>Local IP: "
	   << WiFi.localIP()
	   << "</p><p>Local Port: <input type='text' name='localport' value='"
	   << localPort
	   << "'/></p>"
	   << "<p>Remote IP: <input type='text' name='remoteip' value='"
	   << remoteIPAddress
	   << "'/></p>"
	   << "<p>Remote Port: <input type='text' name='remoteport' value='"
	   << remotePort
	   << "'/></p>"
	   << "<input type='submit'/>"
	   << "</form>"
	   << "</body></html>\r\n";
  }
}

void webSettings(WebServer &server, WebServer::ConnectionType type, char* url_tail, bool tail_complete){
  if(type == WebServer::POST){
    bool repeat;
    char name[16], value[16];
    do{
      repeat = server.readPOSTparam(name, 16, value, 16);
      if(strcmp(name, "localport") == 0){
	localPort = strtoul(value, NULL, 10);
      }else if(strcmp(name, "remoteport") == 0){
	remotePort = strtoul(value, NULL, 10);
      }
    }while(repeat);
  }
  server.httpSeeOther(PREFIX "/index.html");
}

void webHello(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    const static char* helloMsg = "<h1>Hello, World!</h1>";
    server.print(helloMsg);
  }
}

// WebSocketServer websocketserver(WEBSOCKET_SERVER_PORT);
TcpSocketServer tcpsocketserver(TCP_SERVER_PORT);

#include "OscMessage.hpp"

char* OscCmd_status      = (char*)"/status";
char* OscCmd_a_trigger   = (char*)"/trigger_a";
char* OscCmd_b_trigger   = (char*)"/trigger_b";
char* OscCmd_cv          = (char*)"/cv";
char* OscCmd_a_cv        = (char*)"/cv_a";
char* OscCmd_b_cv        = (char*)"/cv_b";
char* OscCmd_led         = (char*)"/led";
char* OscCmd_ip          = (char*)"/localip";
char* OscCmd_port        = (char*)"/localport";
char* OscCmd_gain        = (char*)"/gain";
char* OscCmd_ping        = (char*)"/ping";

OscMessage osc_status_msg(OscCmd_status);
OscMessage osc_led_msg(OscCmd_led);
OscMessage osc_ping_msg(OscCmd_ping);
OscMessage osc_a_cv_msg(OscCmd_a_cv);
OscMessage osc_b_cv_msg(OscCmd_b_cv);
OscMessage osc_a_trigger_msg(OscCmd_a_trigger);
OscMessage osc_b_trigger_msg(OscCmd_b_trigger);

#define MAX_OSC_COMMANDS 12
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

// void sendMessage(OscMessage& msg){
//   uint8_t buf[64];
//   int len = msg.copy(buf, sizeof(buf));
//   if(len > 0)
//     udp_send_packet(buf, len);
//   else
//     debugMessage("Failed to send osc message");
// }
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

void sendMessage(OscMessage& msg){
  oscserver.beginPacket();
  msg.write(oscserver);
  oscserver.endPacket();
}

void sendOscStatus(const char* status){
  debugMessage("sending osc status");
  debugMessage(status);
  osc_status_msg.setString(0, status);
  oscserver.sendMessage(osc_status_msg);
}

void oscStatus(OscServer& server, OscMessage& msg){
    debugMessage("osc status");
    if(msg.getDataType(0) == 's')
      debugMessage(msg.getString(0));
    sendOscStatus("fine");
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
  osc_a_cv_msg.setFloat(0, (float)value/4096.0);
  sendMessage(osc_a_cv_msg);
}

void sendCvB(uint16_t value){
  osc_b_cv_msg.setFloat(0, (float)value/4096.0);
  sendMessage(osc_b_cv_msg);
}

void sendTriggerA(bool value){
  osc_a_trigger_msg.setInt(0, value);
  sendMessage(osc_a_trigger_msg);  
}

void sendTriggerB(bool value){
  osc_b_trigger_msg.setInt(0, value);
  sendMessage(osc_b_trigger_msg);  
}

void setIpAddress(String ip){
  Serial.print("Set remote IP: ");
  Serial.println(ip);
  ip.toLowerCase();
  if(ip.startsWith("auto")){
    oscserver.autoRemoteIPAddress = true;
    return;
  }
  if(ip.equalsIgnoreCase("broadcast")){
    oscserver.autoRemoteIPAddress = false;
    oscserver.setBroadcastMode();
    return;
  }
  oscserver.autoRemoteIPAddress = false;
  int pos = 0;
  int idx = ip.indexOf('.');
  for(int i=0; i<3; ++i){
    oscserver.remoteIPAddress[i] = ip.substring(pos, idx).toInt();
    pos = idx+1;
    idx = ip.indexOf('.', pos);
  }
  oscserver.remoteIPAddress[3] = ip.substring(pos).toInt();
  Serial.print("Remote IP: ");
  Serial.println(oscserver.remoteIPAddress);
}

void setCredentials(String ssid, String passwd){
  debugMessage("setting ssid "+ssid+" password "+passwd);
  WiFi.disconnect();
  WiFi.setCredentials(ssid, passwd, WPA2);
  WiFi.connect();
  debugMessage("wifi.connect");
}

void clearCredentials(){
  debugMessage("clearing credentials");
  WiFi.clearCredentials();
}

void setupServers(){
  // tcp = TCPServer(TCP_SERVER_PORT);
  // webserver = WebServer(HTTP_SERVER_PORT);
  // websocketserver = WebSocketServer(WEBSOCKET_SERVER_PORT);
  // websocketserver.begin();
  tcpsocketserver.begin();

  webserver.setDefaultCommand(&webHello);
  webserver.addCommand("index.html", &webIndex);
  webserver.addCommand("settings", &webSettings);
  webserver.begin();

  oscserver.addCommand(OscCmd_a_cv, &oscCvA, 1);
  oscserver.addCommand(OscCmd_b_cv, &oscCvB, 1);
  oscserver.addCommand(OscCmd_a_trigger, &oscTriggerA);
  oscserver.addCommand(OscCmd_b_trigger, &oscTriggerB);
  oscserver.addCommand(OscCmd_status, &oscStatus);
  oscserver.addCommand(OscCmd_cv, &oscCv, 2);
  oscserver.addCommand(OscCmd_led, &oscLed);

  oscserver.begin(localPort);
  oscserver.remoteIPAddress = remoteIPAddress;
  oscserver.remotePort = remotePort;
  debugMessage("servers.begin");
  sendOscStatus("servers.begin");  
}

void printInfo(Print& out){
  out.print("Device ID: "); 
  out.println(Spark.deviceID());

  out.print("SSID: "); 
  out.println(WiFi.SSID());

  out.print("Local IP: "); 
  out.println(WiFi.localIP());

  out.print("RSSI: "); 
  out.println(WiFi.RSSI());

  out.print("Local port: "); 
  out.println(localPort);

  out.print("Remote IP: "); 
  out.println(oscserver.remoteIPAddress);

  out.print("Remote Port: "); 
  out.println(oscserver.remotePort);

  byte mac[6];
  WiFi.macAddress(mac);
  out.print("MAC Address: ");
  for(int i=0; i<6; i++){
    if(i)out.print(":");
    out.print(mac[i], HEX);
  }
  out.println();
}

extern "C" void wwd_management_wifi_off( );
extern "C" void vPortYield();
void setup(){
  vPortYield();
  wwd_management_wifi_off( );

  setLed(LED_RED);
  osc_status_msg.addString();
  osc_a_cv_msg.addFloat(.0f);
  osc_b_cv_msg.addFloat(.0f);
  osc_a_trigger_msg.addInt(0);
  osc_b_trigger_msg.addInt(0);
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
  pinMode(ANALOG_PIN_A, INPUT);
  pinMode(ANALOG_PIN_B, INPUT);
  pinMode(DIGITAL_INPUT_PIN_A, INPUT);
  pinMode(DIGITAL_INPUT_PIN_B, INPUT);
  pinMode(DIGITAL_OUTPUT_PIN_A, OUTPUT);
  pinMode(DIGITAL_OUTPUT_PIN_B, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(SERIAL_BAUD_RATE);
  //  Serial1.begin(SERIAL_BAUD_RATE);
  debugMessage("Serial.go");
  //  Serial1.print("Serial1.go");

  spi_init();
  debugMessage("spi init");

  WiFi.selectAntenna(DEFAULT_ANTENNA);
  WiFi.on();
  debugMessage("wifi.on");

  setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD);
  // WiFi.setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD, WPA2);

  //  WiFi.connect();
  // debugMessage("wifi.connect");

  setupServers();
  oscserver.setBroadcastMode();
  printInfo(Serial);

  // RGB.control(true);
  // RGB.color(RGB_COLOR_GREEN);
  setLed(LED_GREEN);

}

uint16_t cvA, cvB;
bool triggerA, triggerB;
bool button;
char web_buf[64];
int web_buf_len = 64;
void loop(){
  int cv = analogRead(ANALOG_PIN_A);
  if(abs(cv - cvA) > ANALOG_THRESHOLD){
    cvA = cv;
    sendCvA(4095-cvA);
  }
  cv = analogRead(ANALOG_PIN_B);
  if(abs(cv - cvB) > ANALOG_THRESHOLD){
    cvB = cv;
    sendCvB(4095-cvB);
  }
  bool btn = digitalRead(BUTTON_PIN);
  if(btn != button){
    button = btn;
    if(button)
      setLed(LED_GREEN);
    else
      setLed(LED_RED);
    sendOscStatus("button");
  }

  btn = digitalRead(DIGITAL_INPUT_PIN_A);
  if(btn != triggerA){
    triggerA = btn;
    sendTriggerA(btn);
  }
  btn = digitalRead(DIGITAL_INPUT_PIN_B);
  if(btn != triggerB){
    triggerB = btn;
    sendTriggerB(btn);
  }

  /* process incoming connections one at a time forever */
  webserver.processConnection(web_buf, &web_buf_len);
  //  webserver.loop();

  // websocketserver.loop();
  tcpsocketserver.loop();

  if(Serial.available() > 0){
    int c = Serial.read();
    switch(c){
    case '?':
      printInfo(Serial);
      break;
    case 's':
      sendOscStatus("hi");
      break;
    case '!':
      debugMessage("clear credentials");
      clearCredentials();
      printInfo(Serial);
      break;
    case 'd':
      debugMessage("default credentials");
      setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD);
      printInfo(Serial);
      break;
    case 'b':
      debugMessage("broadcast");
      oscserver.setBroadcastMode();
      break;
    case '=': {
      debugMessage("set credentials");
      Serial.setTimeout(10000);
      Serial.println("Enter SSID:");
      String ssid = Serial.readStringUntil('\r');
      ssid.trim();
      Serial.println("Enter password:");
      String pass = Serial.readStringUntil('\r');
      pass.trim();
      Serial.print("SSID: [");
      Serial.print(ssid);
      Serial.println("]");
      Serial.print("Password: [");
      Serial.print(pass);
      Serial.println("]");
      Serial.println("Type yes to confirm");
      String yes = Serial.readStringUntil('\r');
      Serial.setTimeout(1000);
      if(yes.equals("yes"))
	setCredentials(ssid, pass);
      else
	Serial.println("Cancelled");
      break;
    }
    case 'l':
      debugMessage("toggle led");
      toggleLed();
      break;
    case '0':
      debugMessage("internal antenna");
      WiFi.selectAntenna(ANT_INTERNAL);
      break;
    case '1':
      debugMessage("auto antenna");
      WiFi.selectAntenna(ANT_AUTO);
      break;
    case '2':
      debugMessage("external antenna");
      WiFi.selectAntenna(ANT_EXTERNAL);
      break;
    }
  }
  oscserver.loop();
}

void process_opensound(uint8_t* data, size_t size){
  Serial.print(size);
  Serial.println(" bytes: process data");
}
