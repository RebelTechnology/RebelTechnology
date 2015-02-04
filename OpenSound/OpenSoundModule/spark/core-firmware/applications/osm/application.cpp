#include "application.h"
#include "OSC/OSCMessage.h"
#include "OSC/OSCBundle.h"
#include "http-server/HttpRequest.h"
#include "http-server/HttpResponse.h"

#define DEBUG_USART

#ifdef DEBUG_USART
#include <stdarg.h>
void pnprintf(Print& p, uint16_t bufsize, const char* fmt, ...) {
   char buff[bufsize];
   va_list args;
   va_start(args, fmt);
   vsnprintf(buff, bufsize, fmt, args);
   va_end(args);
   p.println(buff);
}
#define Serial_printf(fmt, ...) pnprintf(Serial, 128, fmt, __VA_ARGS__)
#define Serial_print(x) Serial.print(x)
#define Serial_println(x) Serial.println(x)
#else // DEBUG_USART
#define Serial_printf(...) 
#define Serial_print(x) 
#define Serial_println(x) 
#endif // DEBUG_USART

/* SPI uses pins A2 to A5 */
int triggerOutputPinA = D0;
int triggerOutputPinB = D1;
int triggerInputPinA  = D2;
int triggerInputPinB  = D3;
int cvOutputPinA      = A6;
int cvOutputPinB      = A7;
int cvInputPinA       = A0;
int cvInputPinB       = A1;
int ledPin            = D7;
int DAC_CS_PIN        = A2;
int DAC_SCK_PIN       = A3;
int DAC_SDI_PIN       = A5;

#define BUTTON_PIN      D6
#define GREEN_LED_PIN   A6
#define RED_LED_PIN     A7

char* OscCmd_a_trigger   = (char*)"/trigger_a";
char* OscCmd_b_trigger   = (char*)"/trigger_b";
char* OscCmd_status      = (char*)"/status";
char* OscCmd_ab_cv       = (char*)"/cv";
char* OscCmd_a_cv        = (char*)"/cv_a";
char* OscCmd_b_cv        = (char*)"/cv_b";
char* OscCmd_led         = (char*)"/led";
char* OscCmd_ip          = (char*)"/localip";
char* OscCmd_port        = (char*)"/localport";
char* OscCmd_gain        = (char*)"/gain";
char* OscCmd_ping        = (char*)"/ping"; // todo

IPAddress remoteIPAddress(192,168,2,179);
bool autoRemoteIPAddress = true;
int localPort = 8000;
int remotePort = 9000;

enum LedPin {
  LED_NONE,
  LED_GREEN,
  LED_RED,
  };

LedPin getLed();

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

#define UDP_TX_BUFFER_SIZE 128
#define DAC_A_B_BIT   (1<<7) // 0=DAC A, 1=DAC b
#define DAC_BUF_BIT   (1<<6)
#define DAC_GA_BIT    (1<<5) // 0=2x, 1=1x gain
#define DAC_SHDN_BIT  (1<<4) // 0=shutdown, 1=normal
uint8_t TRANSFER_BITS = (DAC_SHDN_BIT | DAC_GA_BIT | DAC_BUF_BIT);

static void spi_transfer(uint8_t working) {
  // function to actually bit shift the data byte out
  for(int i = 1; i <= 8; i++) {
    if(working > 127)
      digitalWrite (DAC_SDI_PIN, HIGH); // if it is a 1 (ie. B1XXXXXXX), set the master out pin high
    else
      digitalWrite (DAC_SDI_PIN, LOW); // if it is not 1 (ie. B0XXXXXXX), set the master out pin low
    digitalWrite (DAC_SCK_PIN, HIGH); // set clock high, the pot IC will read the bit into its register
    working = working << 1;
    digitalWrite(DAC_SCK_PIN, LOW); // set clock low, the pot IC will stop reading and prepare for the next iteration (next significant bit
  }
}

static void spi_out(uint8_t high, uint8_t low) {
  digitalWrite(DAC_CS_PIN, LOW);
  spi_transfer(high);
  spi_transfer(low);
  digitalWrite(DAC_CS_PIN, HIGH);
}

static void spi_init() {
  pinMode(DAC_CS_PIN, OUTPUT); // set CS pin to output
  pinMode(DAC_SCK_PIN, OUTPUT); // set SCK pin to output
  pinMode(DAC_SDI_PIN, OUTPUT); // set MOSI pin to output
  digitalWrite(DAC_CS_PIN, HIGH); // hold slave select 1 pin high, so that chip is not selected to begin with
}

/**
<html><head><title>OpenSoundModule</title></head><body>
<h1>OpenSoundModule</h1>
<form action='/settings'>
<p>Local IP: xyz
</p><p>Port: <input type='text' name='localport' value='8888'/></p>
<p>Remote IP: <input type='text' name='remoteip' value='123.1.2.3'/></p>
<p>Port: <input type='text' name='remoteport' value='9999'/></p>
<input type='submit'/>
</form>
</body></html>
*/
class Configuration : public HttpResponse {
protected:
  Stream& printBody(Stream& out) const {
    // out.print("<html><head><title>OpenSoundModule</title></head><body>");
    // out.print("<h1>OpenSoundModule</h1>");
    out.write("<html><body>");
    out.write("<form action='/settings'>");
    out.write("<p>OpenSound IP: ");
    out.print(WiFi.localIP());
    out.write("</p><p>Port: <input type='text' name='localport' value='");
    out.print(localPort);
    out.write("'/></p>");
    out.write("<p>Remote IP: <input type='text' name='remoteip' value='");
    out.print(remoteIPAddress);
    out.write("'/></p>");
    out.write("<p>Port: <input type='text' name='remoteport' value='");
    out.print(remotePort);
    out.write("'/></p>");
    out.write("<input type='submit'/>");
    out.write("</form>");
    out.write("</body></html>\r\n");
    return out;
  }
};

String getParameter(String url, const String& name, const String& def){
  int pos = url.indexOf(name);
  if(pos < 0)
    return def;
  url = url.substring(pos+name.length()+1);
  pos = url.indexOf('&');
  if(pos > 0)
    return url.substring(0, pos);
  return url;
}

void setBroadcastMode(){
  remoteIPAddress = WiFi.localIP();
  remoteIPAddress[3] = 255;
  Serial_print("Remote IP (broadcast): ");
  Serial_println(remoteIPAddress);
}

void setIpAddress(String ip){
  Serial_print("Set remote IP: ");
  Serial_println(ip);
  ip.toLowerCase();
  if(ip.startsWith("auto")){
    autoRemoteIPAddress = true;
    return;
  }
  if(ip.equalsIgnoreCase("broadcast")){
    autoRemoteIPAddress = false;
    setBroadcastMode();
    return;
  }
  autoRemoteIPAddress = false;
  int pos = 0;
  int idx = ip.indexOf('.');
  for(int i=0; i<3; ++i){
    remoteIPAddress[i] = ip.substring(pos, idx).toInt();
    pos = idx+1;
    idx = ip.indexOf('.', pos);
  }
  remoteIPAddress[3] = ip.substring(pos).toInt();
  Serial_print("Remote IP: ");
  Serial_println(remoteIPAddress);
}

class WebServer : public TCPServer {
public:
  const Configuration config;
  WebServer() : TCPServer(80) {}
  WebServer(const unsigned aPort) : TCPServer(aPort) {}
  
  void loop() {
    if(TCPClient client = available()){
      Serial_println("http request");
      HttpRequest hr;
      while(int numBytes = client.available()) {
        Serial_print("Reading http request ");
	Serial_println(numBytes);
        for(int i = 0; i < numBytes; ++i)
          hr.parse(client.read());
      }
      String url(hr.URL());
      if(url.indexOf("/settings?") >= 0){
	localPort = getParameter(url, "localport", String(localPort)).toInt();
	setIpAddress(getParameter(url, "remoteip", String("auto")));
	remotePort = getParameter(url, "remoteport", String(remotePort)).toInt();
	Serial_println(localPort);
	Serial_println(remotePort);
      }else if(url.indexOf("/D0/on") >= 0) {
	Serial_println("Turning D0 on");
	digitalWrite(D0, HIGH);
      }else if(url.indexOf("/D0/off") >= 0) {
	Serial_println("Turning D0 off");
	digitalWrite(D0, LOW);
      }else if(url.indexOf("/D7/on") >= 0) {
	digitalWrite(D7, HIGH);
      }else if(url.indexOf("/D7/off") >= 0) {
	digitalWrite(D7, LOW);
      }
      client << config;
      blockWaiting(client, 200);
      // client.flush();
      client.stop();
    }
  }

  void blockWaiting(TCPClient& client, unsigned long timeOut){
    unsigned long startWait = millis();
    while(client.available() == 0) {
      if(millis() - startWait > timeOut) 
        return;
    }
    while(client.available() > 0){
      client.read();  // discard read data
      if(millis() - startWait > timeOut) 
        return;
    }
  }
};

WebServer ws;

void setupDAC(){
  // pinMode(DAC_CS_PIN, OUTPUT); // not done by SPI.begin()?
  // digitalWrite(DAC_CS_PIN, HIGH);
  // SPI.begin();
  // SPI.setBitOrder(MSBFIRST);
  // // SPI.setClockDivider(SPI_CLOCK_DIV64);
  // SPI.setClockDivider(SPI_CLOCK_DIV256);
  // // SPI.setDataMode(SPI_MODE1); /* for mode 0,0 */
  // SPI.setDataMode(SPI_MODE1);
  spi_init();
}

void setDAC(int ch, int value){
  if(ch == cvOutputPinA){
    spi_out(TRANSFER_BITS | (value >> 8 & 0xf), value & 0xff);
  }else{
    spi_out(TRANSFER_BITS | DAC_A_B_BIT | (value >> 8 & 0xf), value & 0xff);
  }
  // digitalWrite(DAC_CS_PIN, LOW);
  // if(ch == cvOutputPinA){
  //   SPI.transfer(TRANSFER_BITS | ((value && 0x0f00) >> 8));
  // }else{
  //   SPI.transfer(TRANSFER_BITS | DAC_A_B_BIT | ((value & 0x0f00) >> 8));
  // }
  // SPI.transfer(value & 0x00ff);
  // digitalWrite(DAC_CS_PIN, HIGH);
  Serial_print("DAC transfer ");
  Serial_print(ch);
  Serial_print(": ");
  Serial_println(value);
}

void toggleLed(){
  digitalWrite(ledPin, digitalRead(ledPin) == HIGH ? LOW : HIGH);
  Serial_println("toggle LED " +  String(digitalRead(ledPin)));
}

class MyUDP : public UDP {
private :
  uint8_t txbuffer[UDP_TX_BUFFER_SIZE];
  int txoffset;
public :
  MyUDP() : txoffset(0) {}
  virtual int beginPacket(IPAddress ip, uint16_t port){
    txoffset = 0;
    return UDP::beginPacket(ip, port);
  };
  virtual int endPacket(){
    return UDP::write(txbuffer, txoffset);
  };
  virtual size_t write(uint8_t buffer) {
    write(&buffer, 1);
    return 1;
  }
  virtual size_t write(const uint8_t *buffer, size_t size) {
    memcpy(&txbuffer[txoffset], buffer, size);
    txoffset += size;
    return size;
  }
};

MyUDP udp;

void sendMessage(OSCMessage& msg){
  udp.beginPacket(remoteIPAddress, remotePort);
  msg.send(udp);
  udp.endPacket();
}

void sendIp(){
  // Get the IP address of the Spark Core and send it as an OSC Message
  IPAddress ip = WiFi.localIP();
  OSCMessage msg(OscCmd_ip);
  // msg.add(ip[0]).add(ip[1]).add(ip[2]).add(ip[3]);
  char buf[16];
  sprintf(buf, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  msg.add(buf);
  sendMessage(msg);
  Serial_print("Local IP: ");
  Serial_println(ip);
}

void sendPort(){
  OSCMessage msg(OscCmd_port);
  msg.add(localPort);
  sendMessage(msg);
  Serial_print("Local port: ");
  Serial_println(localPort);
}

SYSTEM_MODE(MANUAL);

void setup() {
  pinMode(triggerOutputPinA, OUTPUT);
  pinMode(triggerOutputPinB, OUTPUT);
  pinMode(triggerInputPinA, INPUT);
  pinMode(triggerInputPinB, INPUT);
  // pinMode(cvOutputPinA, OUTPUT);
  // pinMode(cvOutputPinB, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(cvInputPinA, INPUT);
  pinMode(cvInputPinB, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  setLed(LED_RED);

  toggleLed();
  setupDAC();
  Serial.begin(9600);
  Serial_println("Connecting");
  WiFi.connect();
  while(WiFi.connecting()){
    // wait for connection
    Serial_print('.');
    delay(100);
  }
  Serial_println("> Wifi ready");
  IPAddress zero(0UL);
  while(WiFi.localIP() == zero){
    // wait for IP (workaround)
    Serial_print('-');
    delay(100);
  }
  Serial_println("> DHCP ready");
  setBroadcastMode();
  Serial_print("Connected: ");
  Serial_println(WiFi.localIP());
  ws.begin();
  udp.begin(localPort);
  sendIp();
  sendPort();
  toggleLed();
  Serial_println("Showtime");
  setLed(LED_GREEN);
}

bool getBoolValue(OSCMessage &message, int index){
  bool value = false;
  if(message.size() > index){
    switch(message.getType(index)){
    case 'i':
    case 'h':
      value = message.getInt(index) != 0;
      break;
    case 'f':
      value = message.getFloat(index) != 0.0;
      break;
    case 'd':
      value = message.getDouble(index) != 0.0;
      break;
    case 'T':
    case 'I':
      value = true;
      break;
    case 'F':
    case 'N':
    default:
      value = false;
      break;
    }
  }
  return value;
}

float getFloatValue(OSCMessage &message, int index){
  float value = 0.0f;
  if(message.size() > index){
    switch(message.getType(index)){
    case 'i':
    case 'h':
      value = message.getInt(index)/4095.0f;
      break;
    case 'f':
      value = message.getFloat(index);
      break;
    case 'd':
      value = message.getDouble(index);
      break;
    case 'T':
    case 'I':
      value = 1.0f;
      break;
    case 'F':
    case 'N':
    default:
      value = 0.0f;
      break;
    }
  }
  return min(max(value, 0.0f), 1.0f);
}

void setTrigger(int pin, OSCMessage &message){
  bool value = getBoolValue(message, 0);
  digitalWrite(pin, value ? LOW : HIGH);    
  Serial_println("Set trigger " + String(pin) + " " + String(value));
}

void triggerA(OSCMessage &message){
  setTrigger(triggerOutputPinA, message);
}

void triggerB(OSCMessage &message){
  setTrigger(triggerOutputPinB, message);
}

void setCV(int pin, OSCMessage &message, int index){
  float value = getFloatValue(message, index);
  // analogWrite(pin, (int)(value*256));
  setDAC(pin, (int)(value*4095));
  Serial_println("Set cv " + String(pin) + " " + String(value));
}

void toggleGain(){
  // toggles 2x gain setting
  if(TRANSFER_BITS & DAC_GA_BIT)
    TRANSFER_BITS &= ~DAC_GA_BIT;
  else
    TRANSFER_BITS |= DAC_GA_BIT;
  Serial_println("toggle gain " + String(TRANSFER_BITS & DAC_GA_BIT));
}

void set2xGain(bool gain){
  if(gain)
    TRANSFER_BITS &= ~DAC_GA_BIT;
  else
    TRANSFER_BITS |= DAC_GA_BIT;
  Serial_println("set gain " + String((TRANSFER_BITS & DAC_GA_BIT) ? "1x" : "2x"));
}

void cvA(OSCMessage &message){
  setCV(cvOutputPinA, message, 0);
}

void cvB(OSCMessage &message){
  setCV(cvOutputPinB, message, 0);
}

void cvAB(OSCMessage &message){
  setCV(cvOutputPinA, message, 0);
  setCV(cvOutputPinB, message, 1);
}

void setLED(OSCMessage &message){
  toggleLed();
  if(getBoolValue(message, 0))
    setLed(LED_RED);
  else
    setLed(LED_GREEN);
}

void sendTrigger(int pin){
  char* address;
  if(pin == triggerInputPinA)
    address = OscCmd_a_trigger;
  else
    address = OscCmd_b_trigger;
  OSCMessage msg(address);
  int value = digitalRead(pin);
  msg.add(value);
  sendMessage(msg);
}

void sendCV(int pin){
  char* address;
  if(pin == cvInputPinA)
    address = OscCmd_a_cv;
  else
    address = OscCmd_b_cv;
  OSCMessage msg(address);
  float value = (4095-analogRead(pin))/4095.9f;
  msg.add(value);
  sendMessage(msg);
}

void sendStatus(OSCMessage &mess){
  sendIp();
  sendPort();
  sendCV(cvInputPinA);
  sendCV(cvInputPinB);
  sendTrigger(triggerInputPinA);
  sendTrigger(triggerInputPinB);
}

void setGain(OSCMessage &mess){
  if(getBoolValue(mess, 0))
    set2xGain(true);
  else
    set2xGain(false);
}

int controlValueA, controlValueB;
bool pollCV(int pin){
  int& previous = pin == cvInputPinA ? controlValueA : controlValueB;
  int value = 4095-analogRead(pin);
  if(abs(value - previous) > 32){
    sendCV(pin);
    previous = value;
    return true;
  }
  return false;
}

bool triggerValueA, triggerValueB;
bool pollTrigger(int pin){
  bool& previous = pin == triggerInputPinA ? triggerValueA : triggerValueB;
  bool value = digitalRead(pin) == HIGH;
  if(previous != value){
    sendTrigger(pin);
    previous = value;
    return true;
  }
  return false;
}

bool buttonIsPressed = false;
void loop(){
  if((digitalRead(BUTTON_PIN) == LOW) != buttonIsPressed){
    buttonIsPressed = !buttonIsPressed;
    Serial_println("button press: "+String(buttonIsPressed));
    if(buttonIsPressed){
      setLed(LED_RED);
      sendIp();
      sendPort();
    }else{
      setLed(LED_GREEN);
    }
  }
  int bytesToRead = udp.parsePacket();
  if(bytesToRead > 0) {
    if(autoRemoteIPAddress){
      remoteIPAddress = udp.remoteIP();
      Serial_print("Remote IP (auto): ");
      Serial_println(remoteIPAddress);
    }
    OSCMessage msg;
    while(bytesToRead--) {
      msg.fill(udp.read());
    }
    udp.flush();
    if(!msg.hasError()) {
      Serial_println("Received osc message");
      msg.dispatch(OscCmd_led , setLED);
      msg.dispatch(OscCmd_a_trigger, triggerA);
      msg.dispatch(OscCmd_b_trigger, triggerB);
      msg.dispatch(OscCmd_a_cv, cvA);
      msg.dispatch(OscCmd_b_cv, cvB);
      msg.dispatch(OscCmd_ab_cv, cvAB);
      msg.dispatch(OscCmd_status, sendStatus);
      msg.dispatch(OscCmd_gain, setGain);
    }else{
      Serial_println("osc error "+msg.getError());
    }
  }else{
    pollTrigger(triggerInputPinA);
    pollTrigger(triggerInputPinB);
    pollCV(cvInputPinA);
    pollCV(cvInputPinB);
  }
  ws.loop();
}
