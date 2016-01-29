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
int pir;
int maxpir;

const char* BISCUIT_WIFI_SSID = "FortRebel";
const char* BISCUIT_WIFI_PASSWORD = "notwhattheyseem";
const char* BISCUIT_WIFI_SECURITY = "3";
#define OSM_AP_SSID                   "Biscuit-FEHG"
#define OSM_AP_PASSWD                 "password"
#define OSM_AP_AUTH                   "3"
#define OSM_AP_HOSTNAME               "Biscuit"

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

  class Measurements {
  public:
    float voltage;
    float current;
    float power;
    float rmsVoltage;
    float rmsCurrent;
    float rmsPower;
    float peakVoltage;
    float peakCurrent;
    float reactivePower;
    float apparentPower;
    float quadraturePower;
    float powerFactor;
    void print(Print& out){
      out << "V\t[" << voltage << "]\r\n";
      out << "Vrms\t[" << rmsVoltage << "]\r\n";
      out << "Vpeak\t[" << peakVoltage << "]\r\n";
      out << "A\t[" << current << "]\r\n";
      out << "Arms\t[" << rmsCurrent << "]\r\n";
      out << "Apeak\t[" << peakCurrent << "]\r\n";
      out << "P\t[" << power << "]\r\n";
      out << "Prms\t[" << rmsPower << "]\r\n";
      out << "Prea\t[" << reactivePower << "]\r\n";
      out << "Papp\t[" << apparentPower << "]\r\n";
      out << "Pqua\t[" << quadraturePower << "]\r\n";
      out << "PF\t[" << powerFactor << "]\r\n";
    }
    void json(Print& out){
      out << "V:" << voltage << ","
	  << "Vrms:" << rmsVoltage << ","
	  << "Vpeak:" << peakVoltage << ","
	  << "A:" << current << ","
	  << "Arms:" << rmsCurrent << ","
	  << "Apeak:" << peakCurrent << ","
	  << "P:" << power << ","
	  << "Prms:" << rmsPower << ","
	  << "Prea:" << reactivePower << ","
	  << "Papp:" << apparentPower << ","
	  << "Pqua:" << quadraturePower << ","
	  << "PF:" << powerFactor;
    }
  };
  Measurements ch1, ch2;
  float totalActivePower, totalReactivePower, totalApparentPower;

  void update(){
    selectPage(0);
#if 0
    ch1.peakVoltage = readSensor(36);
    ch1.peakCurrent = readSensor(37);
    ch2.peakVoltage = readSensor(38);
    ch2.peakCurrent = readSensor(39);
    selectPage(16);
    ch1.current = readSensor(2);
    ch1.voltage = readSensor(3);
    ch1.power = readSensor(4);
    ch1.rmsPower = readSensor(5);
    ch1.rmsCurrent = readSensor(6);
    ch1.rmsVoltage = readSensor(7);
    ch2.current = readSensor(8);
    ch2.voltage = readSensor(9);
    ch2.power = readSensor(10);
    ch2.rmsPower = readSensor(11);
    ch2.rmsCurrent = readSensor(12);
    ch2.rmsVoltage = readSensor(13);
    ch1.reactivePower = readSensor(14);
    ch1.quadraturePower = readSensor(15);
    ch2.reactivePower = readSensor(16);
    ch2.quadraturePower = readSensor(17);
    ch1.apparentPower = readSensor(20);
    ch1.powerFactor = readSensor(21);
    ch2.apparentPower = readSensor(24);
    ch2.powerFactor = readSensor(25);
#else
    ch1.peakVoltage = readSensor(36);
    ch2.peakCurrent = readSensor(37);
    ch2.peakVoltage = readSensor(38);
    ch1.peakCurrent = readSensor(39);
    selectPage(16);
    ch2.current = readSensor(2);
    ch1.voltage = readSensor(3);
    ch2.power = readSensor(4);
    ch2.rmsPower = readSensor(5);
    ch2.rmsCurrent = readSensor(6);
    ch2.rmsVoltage = readSensor(7);
    ch1.current = readSensor(8);
    ch2.voltage = readSensor(9);
    ch1.power = readSensor(10);
    ch1.rmsPower = readSensor(11);
    ch1.rmsCurrent = readSensor(12);
    ch2.rmsVoltage = readSensor(13);
    ch2.reactivePower = readSensor(14);
    ch2.quadraturePower = readSensor(15);
    ch1.reactivePower = readSensor(16);
    ch1.quadraturePower = readSensor(17);
    ch2.apparentPower = readSensor(20);
    ch2.powerFactor = readSensor(21);
    ch1.apparentPower = readSensor(24);
    ch1.powerFactor = readSensor(25);
#endif
    totalActivePower = readSensor(29);
    totalApparentPower = readSensor(30);
    totalReactivePower = readSensor(31);
  }

private:
  uint32_t readRegister(uint8_t reg){
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
  float readSensor(uint8_t reg){    
    int32_t value = readRegister(reg) << 8;
    return value/2147483647.0f;
  }
  uint32_t readRegister(int pg, uint8_t reg){
    selectPage(pg);
    return readRegister(reg);
  }
  void writeRegister(uint8_t pg, uint8_t reg, int value){
    selectPage(pg);
    write(REGISTER_WRITE|reg);
    write((uint8_t)(value & 0xFF));
    value >>= 8;
    write((uint8_t)(value & 0xFF));
    value >>= 8;
    write((uint8_t)(value & 0xFF));
  }
  void setSerialSpeed(long speed){
    // static const int RX_PU_OFF = (1<<18);
    static const int RX_CSUM_OFF = (1<<17);
    static float multiplier = (524288 / (4.096 * 1000000));
    // SerialCtrl: Page 0, Address 7
    int value = RX_CSUM_OFF | (int)(speed * multiplier);
    writeRegister(0, 7, value);
    // speed = reg / multiplier;
    debug << "set serial speed [" << speed << "]\r\n";
    Serial1.end();
    Serial1.begin(speed);
  }
  // a register write command must be followed by 3 bytes of data
  void softreset(){
    sendInstruction(SOFTWARE_RESET);
  }
  void start(){
    sendInstruction(CONTINUOUS_CONV);
  }
  void stop(){
    sendInstruction(HALT_CONV);
  }
  void setLed(bool on){
    debug << "afe set led [" << on << "]\r\n";
    // CONFIG1 page 0, address 1
    int value = readRegister(0, 1);
    // DO2MODE are bits 5 to 7
    // static const uint8_t DO2MODE_MASK = 0x70;
    writeRegister(0, 1, value);
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
    int temp = readRegister(16, 27);
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
    int data = readRegister(16, 29);
    return (data<<8)/2147483647.0f;
    //    return data/8388608.0f;    
  }

  float getTotalApparentPower(){
    int data = readRegister(16, 30);
    return (data<<8)/2147483647.0f;
    //    return data/8388608.0f;
  }

  float getTotalReactivePower(){
    int data = readRegister(16, 31);
    return (data<<8)/2147483647.0f;
    //    return data/8388608.0f;
  }

  void updateRegister(uint8_t page, uint8_t reg, uint32_t bits, bool on){
    uint32_t value = readRegister(page, reg);
    if(on)
      value |= bits;
    else
      value &= ~bits;
    writeRegister(page, reg, value);
  }

  void setTemperatureSensor(bool on){
    // Config0: Page 0, Address 0
    static const int TSEL = (1<<23);
    updateRegister(0, 0, TSEL, on);
  }

  void setCurrentGain(bool high){
    // Config0: Page 0, Address 0
    updateRegister(0, 0, 0b0000000010100000, high);
  }

  void setHpFilter(bool on){
    // Config2: Page 16, Address 0
    updateRegister(16, 0, 0b0000000010101010, on);
    // When using high-pass filters, it is recommended that the DC offset register for the corresponding channel be set to zero.
    updateRegister(16, 0, 0b0000000010101010, on);
    writeRegister(16, 32, 0); // I1 DCOFF
    writeRegister(16, 34, 0); // V1 DCOFF
    writeRegister(16, 39, 0); // I2 DCOFF
    writeRegister(16, 41, 0); // V2 DCOFF
  }

  void calibrate(int ch){
    // stop();
  /*
If there is an AC offset in the Ix RMS calculation, the
AC offset calibration should be performed on the
current channel. Before performing AC offset
calibration, the AC offset register should be set to 0.
It is recommended that T SETTLE be set to 2000ms
before performing an AC offset calibration.
  */
    writeRegister(16, 37, 0); // I1 ACOFF
    writeRegister(16, 44, 0); // I2 ACOFF
    writeRegister(16, 57, 2000); // T SETTLE
    // AC offset calibration
    if(ch == 1){
      sendInstruction(0b110001); // I1
      delay(500);
      sendInstruction(0b110010); // V1
    }else{
      sendInstruction(0b110011); // I2
      delay(500);
      sendInstruction(0b110100); // V2
    }
    delay(500);
/*
Prior to executing the gain calibration command, gain
registers for any path to be calibrated (Vx GAIN , Ix GAIN )
should be set to 1.0
  */
    writeRegister(16, 33, 0x400000); // I1 GAIN
    writeRegister(16, 40, 0x400000); // I2 GAIN
    writeRegister(16, 35, 0x400000); // V1 GAIN
    writeRegister(16, 42, 0x400000); // V2 GAIN
    /*
      afe.writeRegister(16, 7, ??); // V1 RMS
      afe.writeRegister(16, 13, ??); // V1 RMS
    */
    // gain calibration
    if(ch == 1){
      sendInstruction(0b111001); // I1
      delay(500);
      sendInstruction(0b111010); // V1
    }else{
      sendInstruction(0b111011); // I2
      delay(500);
      sendInstruction(0b111100); // V2
    }
      //    sendInstruction(0b111110); // gain calibration, all channels
    delay(500);
    // start();
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
    /*
    out << "serial [" << Serial1.available() << "]";
    out << "reset [" << digitalRead(CS_RST) << "]\r\n";
    out << "DO3 [" << digitalRead(CS_D3) << "]\r\n";
    */
    out << "Total Active Power\t[" << totalActivePower << "]\r\n";
    out << "Total Apparent Power\t[" << totalApparentPower << "]\r\n";
    out << "Total Reactive Power\t[" << totalReactivePower << "]\r\n";
    out << "Channel One\r\n";
    ch1.print(out);
    out << "Relay\t[" << (getRelay(1) ? "on" : "off") << "]\r\n";
    out << "Channel Two\r\n";
    ch2.print(out);
    out << "Relay\t[" << (getRelay(2) ? "on" : "off") << "]\r\n";
  }

  void json(Print& out){
    out << "Temperature:" << getTemperature() << ","
	<< "ActivePower:" << totalActivePower << ","
	<< "ApparentPower:" << totalApparentPower << ","
	<< "ReactivePower:" << totalReactivePower << ","
	<< "Channel1{";
    ch1.json(out);
    out << ",Relay:" << getRelay(1)
	<< "},Channel2{";
    ch2.json(out);
    out << ",Relay:" << getRelay(2)
	<< "}";
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
}

void printSensors(Print& out){
  out << "PIR [" << pir << "][" << maxpir << "]\r\n";
  maxpir = 0;
  afe.update();
  afe.print(out);
}

void printJson(Print& out){
  out << "{DeviceId:'" << Particle.deviceID() << "',MAC:'";
  connection.printMacAddress(out);
  out << "',PIR:" << getPirValue() << ",";
  out << "',MAX:" << maxpir << ",";
  maxpir = 0;
  afe.json(out);
  out.println('}');
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

void reload(){
  debugMessage("reload");
}

void setup(){
  pinMode(PIR_SIG, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
#ifdef SERIAL_DEBUG
  Serial.begin(SERIAL_BAUD_RATE);
  //  Serial1.begin(SERIAL_BAUD_RATE);
  debugMessage("Serial.go");
  //  Serial1.print("Serial1.go");
#endif
  WiFi.on();
  networkSettings.init();
  afe.init();

  // WiFi.selectAntenna(DEFAULT_ANTENNA);
  wwd_wifi_select_antenna(WICED_ANTENNA_AUTO);  

  if(WiFi.hasCredentials())
    connection.connect(NETWORK_LOCAL_WIFI);
  else
    connection.connect(NETWORK_ACCESS_POINT);

  afe.setHpFilter(true);
  afe.setTemperatureSensor(true);
  afe.start();
  setRelay(1, true);
  setRelay(2, true);
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

int getPirValue(){
  return pir;
}

#include "console.hpp"
#include "HttpSender.hpp"
HttpSender sender;
void process(){
  int cv = analogRead(PIR_SIG);
  if(abs(cv - pir) > ANALOG_THRESHOLD){
    pir = cv;
    if(pir > maxpir)
      maxpir = pir;
  }
  sender.loop();
}

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

bool getRelay(int ch){
  if(ch == 1)
    return digitalRead(RELAY1) == HIGH;
  else if(ch == 2)
    return digitalRead(RELAY2) == HIGH;
  return false;
}

void setRelay(int ch, bool on){
  if(ch == 1)
    digitalWrite(RELAY1, on);
  else if(ch == 2)
    digitalWrite(RELAY2, on);
}

void toggleRelay(int ch){
  if(ch == 1)
    digitalWrite(RELAY1, !digitalRead(RELAY1));
  else if(ch == 2)
    digitalWrite(RELAY2, !digitalRead(RELAY2));
}

void sendRequest(Print& out){
  sender.send(networkSettings.remoteHost, 
	      networkSettings.remotePort, 
	      networkSettings.remotePath, out);
}

int getLastResponseStatus(){
  return sender.getResponseStatus();
}

void calibrate(int ch){
  afe.calibrate(ch);
}
