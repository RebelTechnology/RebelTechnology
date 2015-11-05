// #include <assert.h> causes undefined symbols in nanolib
#include "application.h"
#include "biscuit.h"
#include "web.hpp"
#include <stdint.h>
#include "ApplicationSettings.h"
#include "ConnectionManager.h"

SYSTEM_MODE(MANUAL);
// #define RX_BUFFER_LENGTH 64
#define HTTP_SERVER_PORT      80
#define SERIAL_BAUD_RATE      57600

#define DEFAULT_ANTENNA       ANT_AUTO

ConnectionManager connection;
NetworkSettings networkSettings;

const char* BISCUIT_WIFI_SSID = "FortRebel";
const char* BISCUIT_WIFI_PASSWORD = "notwhattheyseem";
// const char* BISCUIT_WIFI_SSID = "BTHub3-FQG6";
// const char* BISCUIT_WIFI_PASSWORD = "2eb3f324af";
const char* BISCUIT_WIFI_SECURITY = "3";
#define OSM_AP_SSID                   "BiscuitModule"
#define OSM_AP_PASSWD                 "dadac0de"
#define OSM_AP_AUTH                   "3"
#define OSM_AP_HOSTNAME               "BiscuitModule"

class AnalogFrontEnd {
private:
  int currentPage;
private:
  // settings
  static const uint32_t AFE_TIMEOUT    = 512; // 128; // serial time out is 128 ms
  static const uint8_t REGISTER_READ   = 0x00;
  static const uint8_t REGISTER_WRITE  = 0x40;
  static const uint8_t PAGE_SELECT     = 0x80;
  static const uint8_t INSTRUCTION     = 0xc0;

public:
  // instructions
  static const uint8_t SOFTWARE_RESET  = 0x01;
  static const uint8_t STANDBY         = 0x02;
  static const uint8_t WAKEUP          = 0x03;
  static const uint8_t SINGLE_CONV     = 0x14;
  static const uint8_t CONTINUOUS_CONV = 0x15;
  static const uint8_t HALT_CONV       = 0x16;

  void writeSlow(uint8_t c){
    //int periodMicroSecs = 104; //1/9600  interval
    // int periodMicroSecs = 26;  //1/38400 interval
    int periodMicroSecs = 1666;  //1/600 interval
    // 1666.666uS
    //         writePin(LOW);
    pinResetFast(CS_RX);
    delayMicroseconds(periodMicroSecs);
    for(uint8_t b = 0; b < 8; b++){
      digitalWriteFast(CS_RX, c & 0x01);
      c >>= 1;
      delayMicroseconds(periodMicroSecs);
    }         
    //stop bit
    pinSetFast(CS_RX);
    //writePin(HIGH);
    delayMicroseconds(periodMicroSecs*2);
  };

  struct Measurements {
    uint32_t voltage;
    uint32_t current;
    uint32_t power;
    uint32_t rmsVoltage;
    uint32_t rmsCurrent;
    uint32_t rmsPower;
    uint32_t peakVoltage;
    uint32_t peakCurrent;
    uint32_t reactivePower;
    uint32_t apparentPower;
    uint32_t powerFactor;
  };
  Measurements ch1, ch2;
  void update(){
    ch1.voltage = readRegister(16, 2);
    ch1.current = readRegister(16, 3);
  }

public:
  AnalogFrontEnd() : currentPage(-1) {}
  void init(){
    //    pinMode(CS_TX, INPUT);
    pinMode(CS_RST, OUTPUT);
    pinMode(CS_D3, INPUT);
    setupSerial();
  }
  void setupSerial(){
    pinMode(CS_RX, OUTPUT);
    digitalWrite(CS_RST, HIGH);
    // after chip reset, the default baud rate is 600, if MCLK is 4096MHz
    static const int RX_CSUM_OFF = (1<<17);
    static float multiplier = (524288 / (4.096 * 1000000));
    // SerialCtrl: Page 0, Address 7
    int speed = 9600;
    int value = RX_CSUM_OFF | (int)(speed * multiplier);
    writeSlow(PAGE_SELECT);
    delay(10);
    writeSlow(REGISTER_WRITE | 7);
    delay(10);
    writeSlow((uint8_t)(value & 0xFF));
    value >>= 8;
    writeSlow((uint8_t)(value & 0xFF));
    value >>= 8;
    writeSlow((uint8_t)(value & 0xFF));
    delay(100);
    Serial1.begin(9600);
  }
  void reset(bool rst){
    if(rst)
      digitalWrite(CS_RST, LOW);
    else
      digitalWrite(CS_RST, HIGH);
    //    Serial1.end();
    //    Serial1.begin(600);
  }
  void reset(){
    Serial1.end();
    digitalWrite(CS_RST, LOW);
    delay(100);
    digitalWrite(CS_RST, HIGH);
    setupSerial();
  }
  void write(uint8_t data){    
    Serial1.write(data);
    // debug << "serial write [" << data << "/" << ret << "]\r\n";    
  }
  int read(){
    // blocking read
    int timeout = AFE_TIMEOUT;
    // debug << "available [" << Serial1.available() << "]\r\n";
    while(Serial1.available() < 1 && --timeout)
      delayMicroseconds(2000);
    int data = Serial1.read();
    if(!timeout)
      debugMessage("serial read timeout");
    return data;
  }
  void selectPage(uint8_t page){
    if(currentPage != page){
      write(PAGE_SELECT|page);
      currentPage = page;
    }
  }
  void sendInstruction(uint8_t instn){
    write(INSTRUCTION|instn);
  }
  int readRegister(int pg, uint8_t reg){
    selectPage(pg);
    write(REGISTER_READ|reg);
    // afe sends 3 bytes
    int timeout = AFE_TIMEOUT;
    while(Serial1.available() < 3){
      if(timeout-- == 0){
	// debug << "available [" << Serial1.available() << "][" << Serial1.peek() << "]\r\n";
	debugMessage("serial read timeout");
	return -1;
      }
      delay(1);
    }
    uint32_t data = Serial1.read();
    data |= Serial1.read() << 8;
    data |= Serial1.read() << 16;
    // debug << "register read [" << reg << "][" << data << "]\r\n";
    return data;
  }
  void writeRegister(uint8_t reg, int value){
    write(REGISTER_WRITE|reg);
    write((uint8_t)(value & 0xFF));
    value >>= 8;
    write((uint8_t)(value & 0xFF));
    value >>= 8;
    write((uint8_t)(value & 0xFF));
  }
  void setSerialSpeed(long speed){
    static const int RX_PU_OFF = (1<<18);
    static const int RX_CSUM_OFF = (1<<17);
    static float multiplier = (524288 / (4.096 * 1000000));
    // SerialCtrl: Page 0, Address 7
    int value = RX_CSUM_OFF | (int)(speed * multiplier);
    selectPage(0);
    writeRegister(7, value);
    // speed = reg / multiplier;
    debug << "set serial speed [" << speed << "]\r\n";
    Serial1.end();
    Serial1.begin(speed);
  }
  // a register write command must be followed by 3 bytes of data
  void softreset(){
    sendInstruction(SOFTWARE_RESET);
  }
  void setLed(bool on){
    debug << "afe set led [" << on << "]\r\n";
    // CONFIG1 page 0, address 1
    int value = readRegister(0, 1);
    // DO2MODE are bits 5 to 7
    static const uint8_t DO2MODE_MASK = 0x70;
    writeRegister(1, value);
  }
  int getStatus0(){
    return readRegister(0, 23);
  }
  int getStatus1(){
    // Chip status 1 (Status1): Page 0, Address 24
    selectPage(0);
    return readRegister(0, 24);
  }
  int getStatus2(){
    return readRegister(0, 25);
  }
  float getTemperature(){
    // Temperature (T): Page 16, Address 27
    selectPage(16);
    int temp = readRegister(27);
    if(temp == -1)
      return -1.0f;
    return temp / 65536.0f;
  }
  void setGain(int ch, int value){
    // todo
    // see System Calibration
  }
  void setOffset(int ch, int value){
    // todo
  }
  void setSampleCount(int count){
    // todo
    // averaging period for RMS is count / 4000
    // default 4000
    // todo: enable line frequency measurement, set line-cycle synchronised averaging
  }
  float getTotalActivePower(){
    selectPage(16);
    int data = readRegister(29);
    return data/8388608.0f;
  }
  void print(Print& out){
    out.print("AFE Status 0: 0x");
    out.println(getStatus0(), HEX);
    out.print("Status 1: 0x");
    out.println(getStatus1(), HEX);
    out.print("Status 2: 0x");
    out.println(getStatus2(), HEX);
    out.print("Temperature: ");
    out.println(getTemperature());
    out.print("Total Active Power: ");
    out.println(getTotalActivePower());
    out.print("serial [");
    out.print(Serial1.available());
    out.println("]");
    out << "reset [" << digitalRead(CS_RST) << "]\r\n";
    out << "DO3 [" << digitalRead(CS_D3) << "]\r\n";
  }
};

AnalogFrontEnd afe;

void printInfo(Print& out){
  out.println("Device Status");
  if(connection.isWiFiConnected())
    out.println("WiFi Connected");
  if(connection.isIpConnected())
    out.println("IP Connected");
  out.print("Device ID: "); 
  out.println(Particle.deviceID());
  out.print("SSID: "); 
  out.println(connection.getSSID());
  out.print("Local IP: "); 
  out.println(connection.getLocalIPAddress());
  out.print("Gateway: "); 
  out.println(connection.getDefaultGateway());
  out.print("RSSI: "); 
  out.println(connection.getRSSI());
  out.print("Local port: "); 
  out.println(networkSettings.localPort);
  out.print("MAC Address: ");
  connection.printMacAddress(out);
  out.println();
  /*
  out.print("Hostname: "); 
  out.println(connection.getHostname());
  */
  out.print("Accesspoint: "); 
  out.println(connection.getAccessPointSSID());
  out.print("Free memory: "); 
  out.println(System.freeMemory());
  out << "PIR [" << analogRead(PIR_SIG) << "]\r\n";
  afe.print(out);
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
    connection.setCredentials(ssid.c_str(), pass.c_str(), auth.c_str());
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
    connection.setAccessPointCredentials(ssid.c_str(), pass.c_str(), auth.c_str());
    port.println("Done");
  }else
    port.println("Cancelled");
}

void startServers(){
  debugMessage("start servers");
  /*
  if(!WiFi.ready())
    debugMessage("wifi not ready");
  if(WiFi.connecting())
    debugMessage("wifi connecting");
  */
  configureWeb();
  debugMessage("webserver.begin");
  bool success = webserver.begin();
  if(success)
    debugMessage("webserver success");
  else
    debugMessage("webserver fail");
  debugMessage("startServers done");
  printInfo(Serial);
}

void stopServers(){
  debugMessage("stopServers");
  if(connection.getCurrentNetwork() == -1)
    return;
  //  tcpsocketserver.stop();
  //  websocketserver.stop();
  debugMessage("webserver.stop");
  webserver.stop();
  debugMessage("stopServers done");
}

void setRemoteIpAddress(const char* ip){
  debug << "remote ip [" << ip << "]\r\n";
}
void reload(){
  debugMessage("reload");
}

void setup(){
  WiFi.on();

  pinMode(PIR_SIG, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

#if 0
  pinMode(ANALOG_PIN_A, INPUT);
  pinMode(ANALOG_PIN_B, INPUT);
  pinMode(DIGITAL_INPUT_PIN_A, INPUT);
  pinMode(DIGITAL_INPUT_PIN_B, INPUT);
  pinMode(DIGITAL_OUTPUT_PIN_A, OUTPUT);
  pinMode(DIGITAL_OUTPUT_PIN_B, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
#endif

#ifdef SERIAL_DEBUG
  Serial.begin(SERIAL_BAUD_RATE);
  //  Serial1.begin(SERIAL_BAUD_RATE);
  debugMessage("Serial.go");
  //  Serial1.print("Serial1.go");
#endif

  afe.init();

  // WiFi.selectAntenna(DEFAULT_ANTENNA);
  wwd_wifi_select_antenna(WICED_ANTENNA_AUTO);  

  // Called once at startup to initialize the wlan hardware.
  //wlan_setup();
  //  wlan_activate();
  debugMessage("wifi.on");

  if(WiFi.hasCredentials())
    connection.connect(NETWORK_LOCAL_WIFI);
  else
    connection.connect(NETWORK_ACCESS_POINT);

}

void process();
#ifdef SERIAL_CONSOLE
void processSerial();
#endif

void loop(){
  if(connection.connected()){
    process();
  }
#ifdef SERIAL_CONSOLE
  processSerial();
#endif
}

int pir;
void process(){
  int cv = analogRead(PIR_SIG);
  if(abs(cv - pir) > ANALOG_THRESHOLD){
    pir = cv;
  }
}

#include "Scanner.hpp"
Scanner scanner;

#include "stm32f2xx.h"
#ifdef SERIAL_CONSOLE
void processSerial(){
  static bool unlocked = false;
  if(Serial.available() > 0){
    int c = Serial.read();
    if(!unlocked && c != '$')
      return;
    unlocked = true;
    switch(c){
    case 'f':
      debugMessage("f: factory reset");
      factoryReset();
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
      connection.clearCredentials();
      printInfo(Serial);
      break;
    case 'd':
      debugMessage("d: default credentials");
      WiFi.setCredentials(BISCUIT_WIFI_SSID, BISCUIT_WIFI_PASSWORD, WPA2);
      // connection.setCredentials(BISCUIT_WIFI_SSID, BISCUIT_WIFI_PASSWORD, BISCUIT_WIFI_SECURITY);
      printInfo(Serial);
      break;
    case '+':
      debugMessage("+: add credentials");
      readCredentials(Serial);
      break;
    case '=':
      debugMessage("=: set access point credentials");
      readAccessPointCredentials(Serial);
      break;
    case 'a':
      debugMessage("a: access point connect");
      connection.connect(NETWORK_ACCESS_POINT);
      break;
    case 'w':
      debugMessage("w: wifi connect");
      connection.connect(NETWORK_LOCAL_WIFI);
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
    case '*':
      debugMessage("*: print local IP address");
      Serial.println(connection.getLocalIPAddress());
      break;
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
	break;
      case '1':
	debugMessage("1: select AP");
	wlan_select_interface(NETWORK_ACCESS_POINT);
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
	debugMessage(">: start DNS");
	WiFi.startDNS();
	break;
      case '<':
	debugMessage("<: stop DNS");
	WiFi.stopDNS();
	break;
      case 'o':
	debugMessage("o: WiFi.on");
	WiFi.on();
	break;
      case 'w':
	debugMessage("w: WiFi.connect");
	WiFi.connect();
	break;
      case 'x':
	debugMessage("x: WiFi.disconnect");
	WiFi.disconnect();
	break;
      }
      break;
    }
    case '[':
      debugMessage("[: reset true");
      afe.reset(true);
      break;
    case ']':
      debugMessage("[: reset false");
      afe.reset(false);
      break;
    case '{':
      debugMessage("{: ls");
      afe.setSerialSpeed(600);
      break;
    case '}':
      debugMessage("}: hs");
      afe.setSerialSpeed(9600);
      break;
    case 'h':
      debugMessage("h: high rx");
      pinMode(CS_TX, INPUT);
      digitalWrite(CS_TX, HIGH);
      break;
    case 'l':
      debugMessage("l: low rx");
      pinMode(CS_TX, INPUT);
      digitalWrite(CS_TX, LOW);
      break;
    case 'o':
      debugMessage("o: led on/off");
      static bool ledon = false;
      ledon = !ledon;
      afe.setLed(ledon);
      break;
    case 'r':
      debugMessage("r: soft reset");
      afe.sendInstruction(AnalogFrontEnd::SOFTWARE_RESET);
      break;
    case 'g':
      debugMessage("g: wakeup");
      afe.sendInstruction(AnalogFrontEnd::WAKEUP);
      break;
    case 'S': {
      uint32_t tmpreg = 0x00, apbclock = 0x00;
      uint32_t integerdivider = 0x00;
      uint32_t fractionaldivider = 0x00;
      RCC_ClocksTypeDef RCC_ClocksStatus;
      RCC_GetClocksFreq(&RCC_ClocksStatus);
      debug << "RCC_ClocksStatus.PCLK2_Frequency [" << RCC_ClocksStatus.PCLK2_Frequency
	    << "] RCC_ClocksStatus.PCLK1_Frequency [" << RCC_ClocksStatus.PCLK1_Frequency << "]\r\n";
      integerdivider = ((25 * apbclock) / (2 * (600)));
      debug << "mul8[" << ((USART1->CR1 & USART_CR1_OVER8) != 0) << "]\r\n";
      integerdivider = ((25 * apbclock) / (2 * (600)));
      tmpreg = (integerdivider / 100) << 4;
      fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
      debug << "aye[" << (int)integerdivider << "][" << (int)tmpreg << "][" << (int)fractionaldivider << "]\r\n";
      integerdivider = ((25 * apbclock) / (4 * (600)));
      tmpreg = (integerdivider / 100) << 4;
      fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
      debug << "aye[" << (int)integerdivider << "][" << (int)tmpreg << "][" << (int)fractionaldivider << "]\r\n";
    }
    }
  }
}
#endif /* SERIAL_CONSOLE */

void factoryReset(){
  networkSettings.reset();
  networkSettings.clearFlash();
  connection.clearCredentials();
  //  connection.setHostname(OSM_AP_HOSTNAME);
  connection.setAccessPointPrefix(OSM_AP_HOSTNAME);
  connection.setAccessPointCredentials(OSM_AP_SSID, OSM_AP_PASSWD, OSM_AP_AUTH);
  connection.connect(NETWORK_ACCESS_POINT);
}

const char* getDeviceName(){
  return connection.getAccessPointSSID();
}

void setDeviceName(const char* name){
  connection.setAccessPointPrefix(name);
}
