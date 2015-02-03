#include "application.h"
#include "OSC/OSCMessage.h"
// #include "OSC/OSCBundle.h"
#include "http-server/HttpRequest.h"
#include "http-server/HttpResponse.h"

// #define DEBUG_USART

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

#include "OscMessage.hpp"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"

int ledPin               = D7; // Spark core blue led

char* OscCmd_status              = (char*)"/status";
char* OscCmd_led                 = (char*)"/led";
char* OscCmd_ip                  = (char*)"/localip";
char* OscCmd_port                = (char*)"/localport";
char* OscCmd_ping                = (char*)"/ping";
char* OscCmd_note_on             = (char*)"note_on";
char* OscCmd_note_off            = (char*)"note_off";
char* OscCmd_control_change      = (char*)"cc";
char* OscCmd_pitch_bend          = (char*)"pb";

IPAddress remoteIPAddress(192,168,2,179);
bool autoRemoteIPAddress = true;
int localPort = 8000;
int remotePort = 9000;

#define UDP_TX_BUFFER_SIZE 128

SYSTEM_MODE(MANUAL);

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
class ConfigurationResponse : public HttpResponse {
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

// int lastIndexOf(const char * s, char target){
//    int ret = -1;
//    int curIdx = 0;
//    while(s[curIdx] != '\0'){
//      if(s[curIdx] == target) 
//        ret = curIdx;
//      curIdx++;
//    }
//    return ret;
// }

// int getIntegerSuffix(const String& url){
//   // int idx = str.lastIndexOf('/');
//   String sub = str.substring(str.lastIndexOf('/')+1);
//   return sub.toInt();
// }

// int getIntegerSuffix(const String& url, int pos){
//   String sub = str.substring(str.indexOf('/', pos)+1);
//   return sub.toInt();
// }

void toggleLed(){
  digitalWrite(ledPin, digitalRead(ledPin) == HIGH ? LOW : HIGH);
  Serial_println("toggle LED " +  String(digitalRead(ledPin)));
}

class BufferedUdp : public UDP {
private :
  uint8_t txbuffer[UDP_TX_BUFFER_SIZE];
  int txoffset;
public :
  BufferedUdp() : txoffset(0){}
  virtual int beginPacket(IPAddress ip, uint16_t port){
    txoffset = 0;
    return UDP::beginPacket(ip, port);
  }
  virtual int endPacket(){
    return UDP::write(txbuffer, txoffset);
  }
  virtual size_t write(uint8_t buffer) {
    txbuffer[txoffset++] = buffer;
    // write(&buffer, 1);
    return 1;
  }
  virtual size_t write(const uint8_t *buffer, size_t size) {
    memcpy(&txbuffer[txoffset], buffer, size);
    txoffset += size;
    return size;
  }
};

BufferedUdp udp;
MidiWriter writer;

class WebServer : public TCPServer {
public:
  ConfigurationResponse config;
  HttpResponseStatic ok;

  WebServer() : TCPServer(80), ok("ok", 2) {}
  WebServer(const unsigned aPort) : TCPServer(aPort), ok("ok", 2) {}

  HttpResponse& handleRequest(String& url){
    if(url.indexOf("/settings?") >= 0){
      localPort = getParameter(url, "localport", String(localPort)).toInt();
      setIpAddress(getParameter(url, "remoteip", String("auto")));
      remotePort = getParameter(url, "remoteport", String(remotePort)).toInt();
      Serial_println(localPort);
      Serial_println(remotePort);
      return config;
    }else if(url.indexOf(OscCmd_note_on) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int note = getParameter(url, "note", "0").toInt();
      int velocity = getParameter(url, "velocity", "0").toInt();
      writer.noteOn(channel, note, velocity);
      return ok;
    }else if(url.indexOf(OscCmd_note_off) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int note = getParameter(url, "note", "0").toInt();
      writer.noteOff(channel, note, 0);
      return ok;
    }else if(url.indexOf(OscCmd_control_change) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int cc = getParameter(url, "cc", "0").toInt();
      int value = getParameter(url, "value", "0").toInt();
      writer.controlChange(channel, cc, value);
      return ok;
    }else if(url.indexOf("/led") >= 0) {
      toggleLed();
      return config;
    }else if(url.indexOf("/D7/on") >= 0) {
      digitalWrite(D7, HIGH);
      return config;
    }else if(url.indexOf("/D7/off") >= 0) {
      digitalWrite(D7, LOW);
      return config;
    }
  }
  
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
      HttpResponse& res = handleRequest(url);
      client << res;
      if(client.connected()){
	delay(20);
	if(client.connected())
	  delay(40);
	if(client.connected())
	  delay(40);
	if(client.connected()){
	  client.stop();
	  Serial_println("Client stopped");
	}
      }
      if(client.connected()){
	client.stop();
      Serial_println("Client disconnected");
      }
    }
  }
};

WebServer ws;

OscMessage note_on_msg(OscCmd_note_on);
OscMessage note_off_msg(OscCmd_note_off);
OscMessage control_change_msg(OscCmd_control_change);
OscMessage pitch_bend_msg(OscCmd_pitch_bend);

void sendMessage(OscMessage& msg){
  udp.beginPacket(remoteIPAddress, remotePort);
  msg.send(udp);
  udp.endPacket();
}

// void OscMessage::send(){
//   udp.beginPacket(remoteIPAddress, remotePort);
//   send(udp);
//   udp.endPacket();
// }

void sendMessage(OSCMessage& msg){
  udp.beginPacket(remoteIPAddress, remotePort);
  msg.send(udp);
  udp.endPacket();
}

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

void setLED(OSCMessage &mess){
  toggleLed();
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

void sendStatus(OSCMessage &mess){
  sendIp();
  sendPort();
}

void pollOsc(){
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
      Serial_println("osc error "+msg.getError());
    }
  }
}


class LilBug : public MidiReader {
public:

  void setup(){
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
      Serial_println("Set trigger " + String(pin) + " " + String(value));
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

#define MIDI_BUFFER_LENGTH 128
  uint8_t buffer[MIDI_BUFFER_LENGTH];
  // MidiReader reader(buffer, MIDI_BUFFER_LENGTH);
  LilBug() : MidiReader(buffer, MIDI_BUFFER_LENGTH) {}

  void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity){
    if(velocity == 0)
      return handleNoteOff(channel, note, velocity);
    MidiReader::handleNoteOn(channel, note, velocity);
    note_on_msg.set(0, (int32_t)channel);
    note_on_msg.set(4, (int32_t)note);
    note_on_msg.set(8, (int32_t)velocity);
    sendMessage(note_on_msg);
    // simple_note_on.set(0, reader.getChannel());
    // simple_note_on.set(1, reader.getNoteNumber());
    // simple_note_on.set(2, reader.getVelocity());
    // simple_note_on.send();
  }

  void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity){
    MidiReader::handleNoteOff(channel, note, velocity);
    note_off_msg.set(0, (int32_t)channel);
    note_off_msg.set(4, (int32_t)note);
    sendMessage(note_off_msg);
  }

  void handleControlChange(uint8_t channel, uint8_t cc, uint8_t value){
    MidiReader::handleControlChange(channel, cc, value);
    control_change_msg.set(0, (int32_t)channel);
    control_change_msg.set(4, (int32_t)cc);
    control_change_msg.set(8, (int32_t)value);
    sendMessage(control_change_msg);
  }

  void handlePitchBend(uint8_t channel, int16_t value){
    MidiReader::handlePitchBend(channel, value);
    pitch_bend_msg.set(0, (int32_t)channel);
    pitch_bend_msg.set(4, (int32_t)value);
    sendMessage(pitch_bend_msg);
  }

  void pollMidi(){
    int bytesToRead = Serial1.available();
    while(bytesToRead-- > 0){
    // if(Serial1.available()){
      MidiReaderStatus status = read(Serial1.read());
      if(status == ERROR_STATUS){
	MidiReader::clear();
	Serial_println("MIDI read error");
      }else{
	Serial_print(".");
      }
    }
  }
};

LilBug bug;

void setup() {
  pinMode(ledPin, OUTPUT);

  note_on_msg.add((int32_t)0);
  note_on_msg.add((int32_t)0);
  note_on_msg.add((int32_t)0);
  note_off_msg.add((int32_t)0);
  note_off_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  control_change_msg.add((int32_t)0);
  pitch_bend_msg.add((int32_t)0);
  pitch_bend_msg.add((int32_t)0);

  toggleLed();
  Serial1.begin(115200);
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

  bug.setup();
  Serial_println("Showtime");
}

void loop(){
  pollOsc();
  bug.pollMidi();
  ws.loop();
}
