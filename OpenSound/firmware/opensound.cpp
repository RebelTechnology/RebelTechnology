// #include <assert.h> causes undefined symbols in nanolib
#include "application.h"
#include "opensound.h"
#include <stdint.h>
// #include "TcpSocketServer.hpp"
// #include "WebServer.hpp"
#include "dac.h"
#include "ApplicationSettings.h"

// #define debugMessage(x) if(0){}

SYSTEM_MODE(MANUAL);
// #define RX_BUFFER_LENGTH 64
#define TCP_SERVER_PORT       8888
#define HTTP_SERVER_PORT      80
#define WEBSOCKET_SERVER_PORT 8008
#define SERIAL_BAUD_RATE      57600

#define DEFAULT_ANTENNA       ANT_AUTO

#define BUTTON_DEBOUNCE_MS    100
#define BUTTON_TOGGLE_MS      2000

NetworkSettings networkSettings;
AddressSettings addressSettings;

const char* OPENSOUND_WIFI_SSID = "BTHub3-FQG6";
const char* OPENSOUND_WIFI_PASSWORD = "2eb3f324af";
const char* OPENSOUND_WIFI_SECURITY = "3";
#define OSM_AP_SSID "OpenSoundAli"
#define OSM_AP_PASSWD "cbe83c9c"
#define OSM_AP_AUTH "3"

#define ANALOG_PIN_A         A0
#define ANALOG_PIN_B         A1
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
  LED_YELLOW,
};

// LedPin getLed();

static WLanConfig wlan_config;
IPAddress getDefaultGateway(){
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucDefaultGateway);
  return ip;
}

int getRSSI(){
  return wlan_connected_rssi();
}

IPAddress getSubnetMask(){
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucSubnetMask);
  return ip;
}

const char* getSSID(){
  if(getCurrentNetwork() == NETWORK_ACCESS_POINT){
    return getAccessPointSSID();
  }else{
    wlan_fetch_ipconfig(&wlan_config);
    return (const char*)wlan_config.uaSSID;
  }
}

void printMacAddress(Print& out){
  wlan_fetch_ipconfig(&wlan_config);
  for(int i=0; i<6; i++){
    if(i)out.write(':');      
    out.print(wlan_config.nw.uaMacAddr[i], HEX);
  }
}

IPAddress getLocalIPAddress(){
      /*
struct {
    uint16_t size;
    NetworkConfig nw;
    uint8_t uaSSID[33];
} WLanConfig;
struct {
    HAL_IPAddress aucIP;             // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucSubnetMask;     // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDefaultGateway; // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDHCPServer;     // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDNSServer;      // byte 0 is MSB, byte 3 is LSB
    uint8_t uaMacAddr[6];
} NetworkConfig;
      */
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucIP);
  return ip;
}

inline void setLed(LedPin led){
  if(led == LED_YELLOW){
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

void setRemoteIpAddress(const char* address){
  String ip(address);
#ifdef SERIAL_DEBUG
  Serial.print("Set remote IP: ");
  Serial.println(ip);
#endif
  ip.toLowerCase();
  if(ip.startsWith("auto")){
    oscserver.autoRemoteIPAddress = true;
    return;
  }
  if(ip.equals("broadcast")){
    oscserver.autoRemoteIPAddress = false;
    oscserver.setBroadcastMode(true);
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
  networkSettings.remoteIPAddress = oscserver.remoteIPAddress;
#ifdef SERIAL_DEBUG
  Serial.print("Remote IP: ");
  Serial.println(oscserver.remoteIPAddress);
#endif
}

static int current_network = -1;
int getCurrentNetwork(){
  return current_network;
}

void connect(int iface){
  /*  if(current_network != -1)
    stopServers();
  */
  if(current_network != iface){
    if(wlan_reset_credentials_store_required())
      wlan_reset_credentials_store();
    if(iface == NETWORK_LOCAL_WIFI){
      debugMessage("wifi.sta");
      if(current_network == NETWORK_ACCESS_POINT)
	wlan_stop_ap();
    }else if(iface == NETWORK_ACCESS_POINT){
      debugMessage("wifi.ap");
      wlan_start_ap();
    }
    current_network = iface;
    wlan_select_interface(iface);
    wlan_connect_init();
    wlan_connect_finalize();
    /*
    int ret = wlan_connect_init();
    wlan_result_t result = wlan_connect_finalize() 
    */
      /*
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
      */
  }
  setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
}

void setCredentials(const char* ssid, const char* passwd, const char* auth){
  debug << "setting credentials for ssid[" << ssid << "] auth[" << auth << "]\n";
  int sec = atol(auth);
  if(sec >= 0 && sec <= 3){
    //    WiFi.disconnect();
    WiFi.setCredentials(ssid, passwd, sec);
    //    WiFi.connect();
  }
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
  port.println("Enter AP security (0=Open, 1=WEP, 2=WPA, 3=WPA2):");
  String auth = port.readStringUntil('\r');
  auth.trim();
  port.println("Enter password:");
  String pass = port.readStringUntil('\r');
  pass.trim();
  port.print("SSID: [");
  port.print(ssid);
  port.print("] Auth: [");
  port.print(auth);
  port.print("] Password: [");
  port.print(pass);
  port.println("]");
  port.println("Type yes to confirm");
  String yes = port.readStringUntil('\r');
  port.setTimeout(1000);
  if(yes.equals("yes"))
    setCredentials(ssid.c_str(), pass.c_str(), auth.c_str());
  else
    port.println("Cancelled");
}

void readAccessPointCredentials(Stream& port){
  port.setTimeout(10000);
  port.println("Enter AP SSID:");
  String ssid = port.readStringUntil('\r');
  ssid.trim();
  port.println("Enter AP security (0=Open, 1=WEP, 2=WPA, 3=WPA2):");
  String auth = port.readStringUntil('\r');
  auth.trim();
  port.println("Enter AP password:");
  String pass = port.readStringUntil('\r');
  pass.trim();
  port.print("SSID: [");
  port.print(ssid);
  port.print("] Auth: [");
  port.print(auth);
  port.print("] Password: [");
  port.print(pass);
  port.println("]");
  port.println("Type yes to confirm");
  String yes = port.readStringUntil('\r');
  port.setTimeout(1000);
  if(yes.equals("yes")){
    setAccessPointCredentials(ssid.c_str(), pass.c_str(), auth.c_str());
    port.println("Done");
  }else
    port.println("Cancelled");
}

void startServers(){
  debugMessage("start servers");
  if(!WiFi.ready())
    debugMessage("wifi not ready");
  if(WiFi.connecting())
    debugMessage("wifi connecting");
  configureWeb();
  configureOsc();
  if(WiFi.ready() || getCurrentNetwork() == NETWORK_ACCESS_POINT){
    debugMessage("webserver.begin");
    webserver.begin();
    debugMessage("oscserver.begin");
    oscserver.begin(networkSettings.localPort);
    debugMessage("startServers done");
  }
}

void stopServers(){
  debugMessage("stopServers");
  if(current_network == -1)
    return;
  //  tcpsocketserver.stop();
  //  websocketserver.stop();
  debugMessage("webserver.stop");
  webserver.stop();
  debugMessage("oscserver.stop");
  oscserver.stop();
  debugMessage("stopServers done");
}

void printInfo(Print& out){
  out.println("Device Status");
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
  out.println(getSSID());
  out.print("Local IP: "); 
  out.println(getLocalIPAddress());
  out.print("Gateway: "); 
  out.println(getDefaultGateway());
  out.print("RSSI: "); 
  out.println(getRSSI());
  out.print("Local port: "); 
  out.println(networkSettings.localPort);
  out.print("Remote IP: "); 
  out.println(oscserver.remoteIP());
  out.print("Remote Port: "); 
  out.println(oscserver.remotePort());
  out.print("MAC Address: ");
  printMacAddress(out);
  out.println();
  //  out.print("Free memory: "); 
  //  out.println(System.freeMemory());
}

unsigned long lastButtonPress;
uint16_t cvA, cvB;
bool triggerA, triggerB;
bool button;

//IntervalTimer dacTimer;
static uint16_t cvOutA = 2047;
static uint16_t cvOutB = 2047;
uint16_t getCVA(){
  return cvOutA;
}

uint16_t getCVB(){
  return cvOutB;
}

void setCVA(uint16_t cv){
#ifdef SERIAL_DEBUG
  Serial.print("cv A: ");
  Serial.println(cv);
#endif
  cvOutA = cv;
}

void setCVB(uint16_t cv){
#ifdef SERIAL_DEBUG
  Serial.print("cv B: ");
  Serial.println(cv);
#endif
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

void setTriggerA(int value){
  digitalWrite(DIGITAL_OUTPUT_PIN_A, value == 0 ? HIGH : LOW);
#ifdef SERIAL_DEBUG
  Serial.print("trigger A: ");
  Serial.println(value);
#endif
}

void setTriggerB(int value){
  digitalWrite(DIGITAL_OUTPUT_PIN_B, value == 0 ? HIGH : LOW);
#ifdef SERIAL_DEBUG
  Serial.print("trigger B: ");
  Serial.println(value);
#endif
}

void toggleTriggerA(){
  bool value = digitalRead(DIGITAL_OUTPUT_PIN_A);
  setTriggerA(value);
}

void toggleTriggerB(){
  bool value = digitalRead(DIGITAL_OUTPUT_PIN_B);
  setTriggerB(value);
}

bool isButtonPressed(){
  //  return false;
  return !digitalRead(BUTTON_PIN);
}

void setup(){
  setLed(LED_GREEN);
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

  networkSettings.init();
  addressSettings.init();

  dac_init();
  debugMessage("dac init");

  WiFi.selectAntenna(DEFAULT_ANTENNA);
  // wwd_wifi_select_antenna(WICED_ANTENNA_AUTO);  
  //  WiFi.on();
  wlan_activate();

  debugMessage("wifi.on");

  /*
  if(!WiFi.hasCredentials())
    setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD, OPENSOUND_WIFI_SECURITY);
  */

  /*
  if(WiFi.hasCredentials())
    connect(NETWORK_LOCAL_WIFI);
  else
    connect(NETWORK_ACCESS_POINT);

  startServers();
  */

  lastButtonPress = 0;
  button = isButtonPressed();
  cvA = analogRead(ANALOG_PIN_A);
  cvB = analogRead(ANALOG_PIN_B);

  //  dacTimer.begin(dacCallback, 400, hmSec);
  //  setLed(LED_GREEN);
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
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
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
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
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
    setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
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
  //  webserver.processConnection(web_buf, &web_buf_len);
  //  webserver.loop();

  // websocketserver.loop();
  //  tcpsocketserver.loop();

  if(Serial.available() > 0){
    int c = Serial.read();
    switch(c){
    case 'f':
      debugMessage("f: factory reset");
      factoryReset();
      connect(NETWORK_ACCESS_POINT);
      break;
    case '?':
      debugMessage("?: print info");
      printInfo(Serial);
      break;
    case 's':
      debugMessage("s: scan wifi");
      scanner.start();
      break;
    case '!':
      debugMessage("!: clear credentials");
      clearCredentials();
      printInfo(Serial);
      break;
    case 'd':
      debugMessage("d: default credentials");
      setCredentials(OPENSOUND_WIFI_SSID, OPENSOUND_WIFI_PASSWORD, OPENSOUND_WIFI_SECURITY);
      printInfo(Serial);
      break;
    case 'b':
      debugMessage("b: broadcast mode");
      oscserver.setBroadcastMode(true);
      break;
    case '+':
      debugMessage("+: add credentials");
      readCredentials(Serial);
      break;
    case '=':
      debugMessage("=: set access point credentials");
      readAccessPointCredentials(Serial);
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
    case '*': {
      debugMessage("*: print local IP address");
      Serial.println(getLocalIPAddress());
      break;
    }
    case ':': {
      debugMessage("System Admin");
      while(Serial.available() < 1); // wait
      c = Serial.read();
      switch(c){      
      case '+':
	debugMessage("+: activate wlan");
	wlan_activate();
	break;
      case '-':
	debugMessage("-: deactivate wlan");
	wlan_deactivate();
	break;
      case '0':
	debugMessage("0: select STA");
	wlan_select_interface(NETWORK_LOCAL_WIFI);
	current_network = NETWORK_LOCAL_WIFI;
	break;
      case '1':
	debugMessage("1: select AP");
	wlan_select_interface(NETWORK_ACCESS_POINT);
	current_network = NETWORK_ACCESS_POINT;
	break;
      case 'i':
	debugMessage("i: connect init");
	wlan_connect_init();
	break;
      case 'f':
	debugMessage("f: connect finalise");
	wlan_connect_finalize();
	break;
      case 'd':
	debugMessage("d: disconnect");
	wlan_disconnect_now();
	break;
      case '>':
	debugMessage(">: start access point");
	WiFi.startAccessPoint();
	break;
      case '<':
	debugMessage("<: stop access point");
	WiFi.stopAccessPoint();
	break;
      }
      break;
    }
    case '[':
      debugMessage("[: dac 0");
      setCVA(0);
      setCVB(0);
      dac_set_a(0);
      dac_set_b(0);
      break;
    case '|':
      debugMessage("|: dac 1/2");
      setCVA(2047);
      setCVB(2047);
      dac_set_a(2047);
      dac_set_b(2047);
      break;
    case ']':
      debugMessage("]: dac full");
      setCVA(4095);
      setCVB(4095);
      dac_set_a(4095);
      dac_set_b(4095);
      break;
    }
  }
  oscserver.loop();
}

void reload(){
  oscserver.stop();
  configureOsc();
  oscserver.begin(networkSettings.localPort);
}

#include "dct.h"

void factoryReset(){
  networkSettings.reset();
  networkSettings.clearFlash();
  addressSettings.reset();
  addressSettings.clearFlash();
  clearCredentials();
  setAccessPointCredentials(OSM_AP_SSID, OSM_AP_PASSWD, OSM_AP_AUTH);
}

const int MAX_SSID_PREFIX_LEN = 25;
void setAccessPointPrefix(char* prefix){
  wiced_ssid_t ssid;
  ssid.length = strnlen(prefix, MAX_SSID_PREFIX_LEN);
  strncpy((char*)ssid.value, prefix, ssid.length);
  dct_write_app_data(&ssid, DCT_SSID_PREFIX_OFFSET, ssid.length+1);
}

const char* getAccessPointSSID(){
  wiced_config_soft_ap_t* ap;
  wiced_result_t result = wiced_dct_read_lock((void**)&ap, WICED_FALSE, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t));
  int len = min(ap->SSID.length+1, min(33, MAX_SSID_PREFIX_LEN));
  memcpy(wlan_config.uaSSID, ap->SSID.value, len);
  wlan_config.uaSSID[len] = '\0';
  wiced_dct_read_unlock(&ap, WICED_FALSE);
  return result == WICED_SUCCESS ? (const char*)wlan_config.uaSSID : NULL;
}

int setAccessPointCredentials(const char* ssid, const char* passwd, const char* auth){
  //void setAccessPoint(char* prefix, char* auth){
  wiced_config_soft_ap_t ap;
  ap.SSID.length = strnlen(ssid, MAX_SSID_PREFIX_LEN);
  strncpy((char*)ap.SSID.value, ssid, ap.SSID.length);
  ap.channel = 11;
  ap.details_valid = WICED_TRUE;
  int sec = atol(auth);
  switch(sec){
  case 0: // Open
    ap.security = WICED_SECURITY_OPEN;
    break;
  case 1: // WEP
    ap.security = WICED_SECURITY_WEP_PSK;
    break;
  case 2: // WPA
    ap.security = WICED_SECURITY_WPA_TKIP_PSK;
    break;
  case 3: // WPA2
    ap.security = WICED_SECURITY_WPA2_AES_PSK;
    break;
  default:
    return false;
  }
  if(sec == 3 && ap.SSID.length < 8)
    return false; // password too short for WPA2
  ap.security_key_length = strnlen(passwd, SECURITY_KEY_SIZE);
  strncpy(ap.security_key, passwd, ap.security_key_length);
  wiced_result_t result = wiced_dct_write(&ap, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t));
  return result == WICED_SUCCESS;
}
