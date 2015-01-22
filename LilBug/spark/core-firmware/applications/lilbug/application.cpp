#include "application.h"
#include "OSC/OSCMessage.h"
#include "OSC/OSCBundle.h"
#include "http-server/HttpRequest.h"
#include "http-server/HttpResponse.h"

#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#define DEBUG_USART

int ledPin               = D7; // Spark core blue led

char* OscCmd_status      = "/status";
char* OscCmd_led         = "/led";
char* OscCmd_ip          = "/localip";
char* OscCmd_port        = "/localport";
char* OscCmd_ping        = "/ping"; // todo
char* OscCmd_note_on     = "note_on";
char* OscCmd_note_off    = "note_off";
char* OscCmd_control_change          = "cc";
char* OscCmd_pitch_bend          = "pb";

IPAddress remoteIPAddress(192,168,2,179);
bool autoRemoteIPAddress = true;
int localPort = 8000;
int remotePort = 9000;

#define UDP_TX_BUFFER_SIZE 128

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
    out.print("<html><body>");
    out.print("<form action='/settings'>");
    out.print("<p>OpenSound IP: ");
    out.print(WiFi.localIP());
    out.print("</p><p>Port: <input type='text' name='localport' value='");
    out.print(localPort);
    out.print("'/></p>");
    out.print("<p>Remote IP: <input type='text' name='remoteip' value='");
    out.print(remoteIPAddress);
    out.print("'/></p>");
    out.print("<p>Port: <input type='text' name='remoteport' value='");
    out.print(remotePort);
    out.print("'/></p>");
    out.print("<input type='submit'/>");
    out.print("</form>");
    out.print("</body></html>\r\n");
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
  Serial.print("Remote IP (broadcast): ");
  Serial.println(remoteIPAddress);
}

void setIpAddress(String ip){
  Serial.print("Set remote IP: ");
  Serial.println(ip);
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
  Serial.print("Remote IP: ");
  Serial.println(remoteIPAddress);
}

class WebServer : public TCPServer {
public:
  const Configuration config;
  WebServer() : TCPServer(80) {}
  WebServer(const unsigned aPort) : TCPServer(aPort) {}
  
  void loop() {
    if(TCPClient client = available()){
      Serial.println("http request");
      HttpRequest hr;
      while(int numBytes = client.available()) {
        Serial.print("Reading http request ");
	Serial.println(numBytes);
        for(int i = 0; i < numBytes; ++i)
          hr.parse(client.read());
      }
      String url(hr.URL());
      if(url.indexOf("/settings?") >= 0){
	localPort = getParameter(url, "localport", String(localPort)).toInt();
	setIpAddress(getParameter(url, "remoteip", String("auto")));
	remotePort = getParameter(url, "remoteport", String(remotePort)).toInt();
	Serial.println(localPort);
	Serial.println(remotePort);
      }else if(url.indexOf("/D0/on") >= 0) {
	Serial.println("Turning D0 on");
	digitalWrite(D0, HIGH);
      }else if(url.indexOf("/D0/off") >= 0) {
	Serial.println("Turning D0 off");
	digitalWrite(D0, LOW);
      }else if(url.indexOf("/D7/on") >= 0) {
	digitalWrite(D7, HIGH);
      }else if(url.indexOf("/D7/off") >= 0) {
	digitalWrite(D7, LOW);
      }
      client << config;
      if(client.connected()){
	delay(20);
	if(client.connected())
	  delay(40);
	if(client.connected())
	  delay(40);
	if(client.connected()){
	  client.stop();
	  Serial.println("Client stopped");
	}
      }
      Serial.println("Client disconnected");
    }
  }
};

WebServer ws;

void toggleLed(){
  digitalWrite(ledPin, digitalRead(ledPin) == HIGH ? LOW : HIGH);
  Serial.println("toggle LED " +  String(digitalRead(ledPin)));
}

class MyUDP : public UDP {
private :
  uint8_t txbuffer[UDP_TX_BUFFER_SIZE];
  int txoffset = 0;
public :
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
  Serial.print("Local IP: ");
  Serial.println(ip);
}

void sendPort(){
  OSCMessage msg(OscCmd_port);
  msg.add(localPort);
  sendMessage(msg);
  Serial.print("Local port: ");
  Serial.println(localPort);
}

SYSTEM_MODE(MANUAL);

void setup() {
  pinMode(ledPin, OUTPUT);

  toggleLed();
  Serial1.begin(115200);
  Serial.begin(9600);
  Serial.println("Connecting");
  WiFi.connect();
  while(WiFi.connecting()){
    // wait for connection
    Serial.print('.');
    delay(100);
  }
  Serial.println("> Wifi ready");
  IPAddress zero(0UL);
  while(WiFi.localIP() == zero){
    // wait for IP (workaround)
    Serial.print('-');
    delay(100);
  }
  Serial.println("> DHCP ready");
  setBroadcastMode();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  ws.begin();
  udp.begin(localPort);
  sendIp();
  sendPort();
  toggleLed();
  Serial.println("Showtime");
}

void setTrigger(int pin, OSCMessage &message){
  if(message.size() > 0){
    bool value;
    switch(message.getType(0)){
    case 'i':
    case 'h':
      value = message.getInt(0) != 0;
      break;
    case 'f':
      value = message.getFloat(0) != 0.0;
      break;
    case 'd':
      value = message.getDouble(0) != 0.0;
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
    digitalWrite(pin, value ? LOW : HIGH);    
    Serial.println("Set trigger " + String(pin) + " " + String(value));
  }
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

void setLED(OSCMessage &mess){
  toggleLed();
}

void sendStatus(OSCMessage &mess){
  sendIp();
  sendPort();
}

#define MIDI_BUFFER_LENGTH 128
uint8_t buffer[MIDI_BUFFER_LENGTH];
MidiReader reader(buffer, MIDI_BUFFER_LENGTH);
MidiWriter writer;

void oscNoteOn(OSCMessage &message){
  if(message.size() > 2){
    int channel = message.getInt(0);
    int note = message.getInt(1);
    int velocity = message.getInt(2);
    writer.noteOn(channel, note, velocity);
  }
}

void oscNoteOff(OSCMessage &message){
  if(message.size() > 1){
    int channel = message.getInt(0);
    int note = message.getInt(1);
    writer.noteOff(channel, note, 0);
  }
}

void oscControlChange(OSCMessage &message){
  if(message.size() > 2){
    int channel = message.getInt(0);
    int cc = message.getInt(1);
    int value = message.getInt(2);
    writer.controlChange(channel, cc, value);
  }
}

void oscPitchBend(OSCMessage &message){
  if(message.size() > 1){
    int channel = message.getInt(0);
    int value = message.getInt(1);
    writer.pitchBend(channel, value);
  }
}

void pollOsc(){
  int bytesToRead = udp.parsePacket();
  if(bytesToRead > 0) {
    if(autoRemoteIPAddress){
      remoteIPAddress = udp.remoteIP();
      Serial.print("Remote IP (auto): ");
      Serial.println(remoteIPAddress);
    }
    OSCMessage msg;
    while(bytesToRead--) {
      msg.fill(udp.read());
    }
    udp.flush();
    if(!msg.hasError()) {
      Serial.println("Received osc message");
      msg.dispatch(OscCmd_led , setLED);
      msg.dispatch(OscCmd_note_on , oscNoteOn);
      msg.dispatch(OscCmd_note_off , oscNoteOff);
      msg.dispatch(OscCmd_control_change , oscControlChange);
      msg.dispatch(OscCmd_pitch_bend , oscPitchBend);
      // msg.dispatch(OscCmd_a_trigger, triggerA);
      // msg.dispatch(OscCmd_b_trigger, triggerB);
      // msg.dispatch(OscCmd_a_cv, cvA);
      // msg.dispatch(OscCmd_b_cv, cvB);
      // msg.dispatch(OscCmd_ab_cv, cvAB);
      msg.dispatch(OscCmd_status , sendStatus);
    }else{
      Serial.println("osc error "+msg.getError());
    }
  }
}

void pollMidi(){
  int bytesToRead = Serial1.available();
  while(bytesToRead-- > 0){
    MidiReaderStatus status = reader.read(Serial1.read());
    if(status == ERROR_STATUS){
      reader.clear();
#ifdef DEBUG_USART
      Serial.println("MIDI read error");
#endif /* DEBUG_USART */
    }else if(status == READY_STATUS){
#ifdef DEBUG_USART
      Serial.println("MIDI read ok");
#endif /* DEBUG_USART */
      switch(reader.getStatus()){
      case NOTE_ON: {
	OSCMessage msg(OscCmd_note_on);
	msg.add(reader.getChannel());
	msg.add(reader.getNoteNumber());
	msg.add(reader.getVelocity());
	sendMessage(msg);
	break;
      }
      case NOTE_OFF: {
	OSCMessage msg(OscCmd_note_off);
	msg.add(reader.getChannel());
	msg.add(reader.getNoteNumber());
	sendMessage(msg);
	break;
      }
      case CONTROL_CHANGE:{
	OSCMessage msg("cc");
	msg.add(reader.getChannel());
	msg.add(reader.getControllerNumber());
	msg.add(reader.getControllerValue());
	sendMessage(msg);
	break;
      }
      case PITCH_BEND_CHANGE:{
	OSCMessage msg("pb");
	int value = reader.getRawData()[1] << 7;
	value |= reader.getRawData()[2];
	msg.add(reader.getChannel());
	msg.add(value);
	sendMessage(msg);
	break;
      }
      }
    }else{
#ifdef DEBUG_USART
      Serial.print(".");
#endif /* DEBUG_USART */
    }
  }
}

void loop(){
  pollOsc();
  pollMidi();
  ws.loop();
}
