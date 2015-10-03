// #include <assert.h> causes undefined symbols in nanolib
#include "application.h"
#include "opensound.h"
#include <stdint.h>
// #include "TcpSocketServer.hpp"
// #include "WebSocketServer.hpp"
// #include "WebServer.hpp"
#include "SparkIntervalTimer.h"
#include "dac.h"

// #define debugMessage(x) if(0){}

SYSTEM_MODE(MANUAL);
// #define RX_BUFFER_LENGTH 64
#define TCP_SERVER_PORT       8888
#define HTTP_SERVER_PORT      80
#define WEBSOCKET_SERVER_PORT 8008
#define SERIAL_BAUD_RATE      57600
#define UDP_REMOTE_PORT       9000
#define UDP_LOCAL_PORT        8000

#define DEFAULT_ANTENNA ANT_AUTO

#define NETWORK_LOCAL_WIFI   0
#define NETWORK_ACCESS_POINT 1
#define BUTTON_DEBOUNCE_MS   100
#define BUTTON_TOGGLE_MS     2000

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
#define GREEN_LED_PIN        D4
#define RED_LED_PIN          D5
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

#include "osc.hpp"
#include "web.hpp"

// WebSocketServer websocketserver(WEBSOCKET_SERVER_PORT);
// TcpSocketServer tcpsocketserver(TCP_SERVER_PORT);

void setIpAddress(String ip){
#ifdef SERIAL_DEBUG
  Serial.print("Set remote IP: ");
  Serial.println(ip);
#endif
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
#ifdef SERIAL_DEBUG
  Serial.print("Remote IP: ");
  Serial.println(oscserver.remoteIPAddress);
#endif
}

int current_network = -1;
void connect(int iface){
  if(current_network != iface){
    debugMessage("wifi.disconnect");
    WiFi.disconnect();
    if(iface == NETWORK_LOCAL_WIFI){
      debugMessage("wifi.sta");
      if(current_network == NETWORK_ACCESS_POINT)
	WiFi.stopAccessPoint(); // SOS if not running?
    }else if(iface == NETWORK_ACCESS_POINT){
      debugMessage("wifi.ap");
      WiFi.startAccessPoint();
    }
    WiFi.selectNetworkInterface(iface);
    WiFi.connect();
    debugMessage("wifi.connect");
    current_network = iface;
  }
  setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_RED);
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

void readCredentials(Stream& port){
  port.setTimeout(10000);
  port.println("Enter SSID:");
  String ssid = port.readStringUntil('\r');
  ssid.trim();
  port.println("Enter password:");
  String pass = port.readStringUntil('\r');
  pass.trim();
  port.print("SSID: [");
  port.print(ssid);
  port.println("]");
  port.print("Password: [");
  port.print(pass);
  port.println("]");
  port.println("Type yes to confirm");
  String yes = port.readStringUntil('\r');
  port.setTimeout(1000);
  if(yes.equals("yes"))
    setCredentials(ssid, pass);
  else
    port.println("Cancelled");
}

void configureServers(){
  debugMessage("configure servers");
  configureWeb();
  configureOsc();
}

void startServers(){
  debugMessage("start servers");
  webserver.begin();
  oscserver.setRemoteIP(remoteIPAddress);
  oscserver.setRemotePort(remotePort);
  oscserver.begin(localPort);
  debugMessage("servers.begin");
}

void stopServers(){
  debugMessage("stop servers");
  //  tcpsocketserver.stop();
  //  websocketserver.stop();
  webserver.stop();
  oscserver.stop();
  debugMessage("servers.end");
}

void printInfo(Print& out){
  out.print("Device Status ");
  if(WiFi.connecting())
    out.println("Connecting");
  if(WiFi.listening())
    out.println("Listening");
  if(WiFi.ready())
    out.println("Ready");
  if(WiFi.hasCredentials())
    out.println("Has Credentials");

  out.print("Device ID: "); 
  out.println(Spark.deviceID());
  //  out.println(Particle.deviceID());

  out.print("SSID: "); 
  out.println(WiFi.SSID());

  out.print("Local IP: "); 
  out.println(WiFi.localIP());

  out.print("Gateway: "); 
  out.println(WiFi.gatewayIP());

  out.print("RSSI: "); 
  out.println(WiFi.RSSI());

  out.print("Local port: "); 
  out.println(localPort);

  out.print("Remote IP: "); 
  out.println(oscserver.remoteIP());

  out.print("Remote Port: "); 
  out.println(oscserver.remotePort());

  byte mac[6];
  WiFi.macAddress(mac);
  out.print("MAC Address: ");
  for(int i=0; i<6; i++){
    if(i)out.print(":");
    out.print(mac[i], HEX);
  }
  out.println();

  //  out.print("Free memory: "); 
  //  out.println(System.freeMemory());
}

unsigned long lastButtonPress;
uint16_t cvA, cvB;
bool triggerA, triggerB;
bool button;

//IntervalTimer dacTimer;
uint16_t cvOutA;
uint16_t cvOutB;
void setCVA(uint16_t cv){
  cvOutA = cv;
}

void setCVB(uint16_t cv){
  cvOutB = cv;
}

uint16_t smooth = 3; 
void dacCallback(){
  static uint16_t a = 0;
  static uint16_t b = 0;
  a = (a*smooth + cvOutA)/(smooth+1);
  dac_set_a(a);
  b = (b*smooth + cvOutB)/(smooth+1);
  dac_set_b(b);
}

bool isButtonPressed(){
  //  return false;
  return !digitalRead(BUTTON_PIN);
}

void setup(){
  setLed(LED_RED);
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

  if(!WiFi.hasCredentials())
    WiFi.setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD);

  if(WiFi.hasCredentials())
    connect(NETWORK_LOCAL_WIFI);
  else
    connect(NETWORK_ACCESS_POINT);

  configureServers();
  startServers();

  oscserver.setBroadcastMode();
  printInfo(Serial);

  lastButtonPress = 0;
  button = isButtonPressed();
  cvA = analogRead(ANALOG_PIN_A);
  cvB = analogRead(ANALOG_PIN_B);

  //  dacTimer.begin(dacCallback, 400, hmSec);

  setLed(LED_GREEN);
}

#include "Scanner.hpp"
Scanner scanner;

char web_buf[64];
int web_buf_len = sizeof(web_buf);
void loop(){
  dacCallback();
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

  bool btn = isButtonPressed();
  if(btn != button && (millis() > lastButtonPress+BUTTON_DEBOUNCE_MS)){
    button = btn;
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_RED);
    if(button){
      lastButtonPress = millis();
      toggleLed();
      broadcastStatus();
    }else{
      lastButtonPress = 0;
    }    
  }

  if(lastButtonPress && (millis() > lastButtonPress+BUTTON_TOGGLE_MS)){
    debugMessage("toggle?");
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_RED);
    delay(BUTTON_TOGGLE_MS);
    if(isButtonPressed()){
      setLed(LED_NONE);
      debugMessage("toggle network");
      stopServers();
      if(current_network == NETWORK_LOCAL_WIFI)
	connect(NETWORK_ACCESS_POINT);
      else
	connect(NETWORK_LOCAL_WIFI);
      startServers();
    }
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_RED);
    lastButtonPress = 0;
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
  //  tcpsocketserver.loop();

  if(Serial.available() > 0){
    int c = Serial.read();
    switch(c){
    case '?':
      debugMessage("?: print info");
      printInfo(Serial);
      break;
    case 's':
      debugMessage("s: scan wifi");
      scanner.start();
      //      sendOscStatus("hi");
      break;
    case '!':
      debugMessage("!: clear credentials");
      clearCredentials();
      printInfo(Serial);
      break;
    case 'd':
      debugMessage("d: default credentials");
      setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD);
      printInfo(Serial);
      break;
    case 'b':
      debugMessage("b: broadcast mode");
      broadcastStatus();
      //oscserver.setBroadcastMode();
      break;
    case '=':
      debugMessage("=: set credentials");
      readCredentials(Serial);
      break;
    case 'l':
      debugMessage("l: toggle led");
      toggleLed();
      break;
    case '0':
      debugMessage("0: internal antenna");
      WiFi.selectAntenna(ANT_INTERNAL);
      break;
    case '1':
      debugMessage("1: auto antenna");
      WiFi.selectAntenna(ANT_AUTO);
      break;
    case '2':
      debugMessage("2: external antenna");
      WiFi.selectAntenna(ANT_EXTERNAL);
      break;
    case '<':
      debugMessage("<: stop servers");
      stopServers();
      break;
    case '>':
      debugMessage(">: start servers");
      startServers();
      break;
    case 'a':
      debugMessage("a: access point connect");
      //stopServers();
      connect(NETWORK_ACCESS_POINT);
      //startServers();
      break;
    case 'w':
      debugMessage("w: wifi connect");
      //stopServers();
      connect(NETWORK_LOCAL_WIFI);
      //startServers();
      break;
    case '+':
      debugMessage("+: start access point");
      WiFi.startAccessPoint();
      break;
    case '-':
      debugMessage("-: stop access point");
      WiFi.stopAccessPoint();
      break;
    case '*': {
      debugMessage("*: print local IP address");
      WLanConfig ip_config;
      wlan_fetch_ipconfig(&ip_config);
      IPAddress ip(ip_config.nw.aucIP);
      Serial.print("local IP: ");
      Serial.println(ip);
      break;
    }
    case '[':
      debugMessage("[: dac 0");
      setCVA(0);
      setCVB(0);
      break;
    case '|':
      debugMessage("|: dac 1/2");
      setCVA(2047);
      setCVB(2047);
      break;
    case ']':
      debugMessage("]: dac full");
      setCVA(4095);
      setCVB(4095);
      break;
    }
  }
  oscserver.loop();
}