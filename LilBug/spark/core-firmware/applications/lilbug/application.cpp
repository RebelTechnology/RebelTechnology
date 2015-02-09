#include "application.h"
#include "OSC/OSCMessage.h"
// #include "OSC/OSCBundle.h"
#include "http-server/HttpRequest.h"
#include "http-server/HttpResponse.h"

// The maximum WiFi packet size that the Spark Core can handle is just over 1400 bytes

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

#include "OscMessage.hpp"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#include "SocketManager.hpp"

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
private:
  const char* htmlHeader =
    "<html><head><title>Lil'Bug</title></head><body>"
    "<h1>Lil'Bug</h1>";
  const size_t htmlHeaderLen = strlen(htmlHeader);
  const char* htmlFooter =
    "</body></html>\r\n";
  const size_t htmlFooterLen = strlen(htmlFooter);
protected:
  Stream& printBody(Stream& out) const {
    // out.print("<html><head><title>OpenSoundModule</title></head><body>");
    // out.print("<h1>OpenSoundModule</h1>");
    // out.print("<html><body>");
    out.write((uint8_t*)htmlHeader, htmlHeaderLen);
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
    // out.print("</body></html>\r\n");
    out.write((uint8_t*)htmlFooter, htmlFooterLen);
    return out;
  }
};

String getParameter(String url, const String& name, const String& def){
  int start = url.indexOf('?');
  if(start < 0)
    return def;
  int pos = url.indexOf(name, start);
  if(pos < 0)
    return def;
  int end = url.indexOf('&', pos);
  if(end > 0)
    return url.substring(pos+name.length()+1, end);
  else
    return url.substring(pos+name.length()+1);
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

// class HttpStatus : public SocketService {
// private:
//   char buffer[128];
//   int length;
// public:
//   HttpStatus(int status, char* message){
//     memcpy(buffer, "http/1.1 "
//   }
//   SocketService* process(Socket& sock){
//     aStream.print("http/1.1 ");
//     aStream.print(aResponse.fStatus);
//   }
// };

class HttpStatus404 : public SocketService {
  SocketService* process(Socket& sock){
    Serial_println("http 404");
    const char* message = 
      "HTTP/1.1 404 Not Found\r\n"
      "Connection: close\r\n"
      "\r\n";
    sock.write((uint8_t*)message, strlen(message));
    return NULL;
  }  
};

class HttpStatus204 : public SocketService {
  SocketService* process(Socket& sock){
    Serial_println("http 204");
    const char* message = 
      "HTTP/1.1 204 No Content\r\n"
      "Connection: close\r\n"
      "\r\n";
    sock.write((uint8_t*)message, strlen(message));
    return NULL;
  }  
};

class HttpIndex : public SocketService {
private:
  SocketService* process(Socket& sock){
    Serial_println("http index");
    const char* body = 
      "<html><head><title>Lil'Bug</title></head><body>"
      "<h1>Lil'Bug</h1>"
      "</body></html>\r\n";
    const char* headers = 
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html; charset=utf-8\r\n"
      "Connection: close\r\n"
      "\r\n";
    sock.write((uint8_t*)headers, strlen(headers));
    sock.write((uint8_t*)body, strlen(body));
    return NULL;
  }  
};

HttpStatus404 response404;
HttpStatus204 response204;
HttpIndex responseIndex;

class HttpService : public SocketService {
// class WebServer : public TCPServer {
public:
  ConfigurationResponse config;
  HttpResponseStatic ok;
  HttpResponseStatic err404;

  HttpService() : 
    ok("ok\r\n", 4), err404(NULL, 0) {
    err404.status(404);
  }

  SocketService* handleRequest(String& url){
    if(url.indexOf("/settings?") >= 0){
      localPort = getParameter(url, "localport", String(localPort)).toInt();
      setIpAddress(getParameter(url, "remoteip", String("auto")));
      remotePort = getParameter(url, "remoteport", String(remotePort)).toInt();
      Serial_println(localPort);
      Serial_println(remotePort);
      return &responseIndex;
    }else if(url.indexOf(OscCmd_note_on) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int note = getParameter(url, "note", "0").toInt();
      int velocity = getParameter(url, "velocity", "0").toInt();
      writer.noteOn(channel, note, velocity);
      return &response204;
    }else if(url.indexOf(OscCmd_note_off) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int note = getParameter(url, "note", "0").toInt();
      writer.noteOff(channel, note, 0);
      return &response204;
    }else if(url.indexOf(OscCmd_control_change) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int cc = getParameter(url, "cc", "0").toInt();
      int value = getParameter(url, "value", "0").toInt();
      writer.controlChange(channel, cc, value);
      return &response204;
    }else if(url.indexOf(OscCmd_pitch_bend) >= 0) {
      int channel = getParameter(url, "channel", "0").toInt();
      int value = getParameter(url, "value", "0").toInt();
      writer.pitchBend(channel, value);
      return &response204;
    }else if(url.indexOf("/led") >= 0) {
      toggleLed();
      return &response204;
    }else if(url.indexOf("/D7/on") >= 0) {
      digitalWrite(D7, HIGH);
      return &response204;
    }else if(url.indexOf("/D7/off") >= 0) {
      digitalWrite(D7, LOW);
      return &response204;
    }else if(url.indexOf("index.htm") >= 0) {
      return &responseIndex;
    }
    return &response404;
  }

  SocketService* process(Socket& sock){
      uint8_t buf[128];
      int sz = sock.read(buf, sizeof(buf));
      HttpRequest hr;
      for(int i = 0; i < sz; ++i)
	hr.parse(buf[i]);
      // while(int numBytes = client.available()) {
      //   Serial_print("Reading http request ");
      // 	Serial_println(numBytes);
      //   for(int i = 0; i < numBytes; ++i)
      //     hr.parse(client.read());
      // }
      String url(hr.URL());
      Serial_print("HTTP request: ");
      Serial_println(url);
      return handleRequest(url);
      // client << res;
      // // todo: implement non-blocking wait / disconnect queue
      // blockWaiting(client, 200);
      // client.flush();
      // client.stop();
    }

};

// WebServer ws(80);
SocketManager sockets;

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
  OscMessage msg(OscCmd_port);
  msg.add((int32_t)localPort);
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
    while(bytesToRead--)
      msg.fill(udp.read());
    udp.flush();
    if(!msg.hasError()) {
      Serial_println("Received osc message");
      msg.dispatch(OscCmd_led, setLED);
      msg.dispatch(OscCmd_note_on, oscNoteOn);
      msg.dispatch(OscCmd_note_off, oscNoteOff);
      msg.dispatch(OscCmd_control_change, oscControlChange);
      msg.dispatch(OscCmd_pitch_bend, oscPitchBend);
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

// class WritingService : public SocketService {
// public:
//   SocketService* process(Socket& sock){
//     const char* buf = 
//       "HTTP/1.1 404 Not Found"
//       "\r\n\r\n";
//     sock.write((uint8_t*)buf, strlen(buf));
//     Serial.println("closing");
//     return NULL;
//   }
// };
// WritingService closer;

// class DebugService : public SocketService {
// public:
//   SocketService* process(Socket& sock){
//     uint8_t buf[32];
//     int sz = sock.read(buf, 32);
//     for(int i=0; i<sz; ++i)
//       Serial_printf("rx %02d 0x%02x (%c)", i, buf[i], buf[i]);
//     if(sz >= 4 &&
//        buf[sz-1] == 0x0a &&
//        buf[sz-2] == 0x0d &&
//        buf[sz-3] == 0x0a &&
//        buf[sz-4] == 0x0d)
//       return &closer;
//     return &closer;
//     // if(sz == 32)
//     //   return this;
//     // return &closer;
//   }
// };

// DebugService service;
HttpService service;

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

  sockets.connect(80, &service); // bind to port 80

  // ws.begin();

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
  sockets.doAccept();
  sockets.loop();
  // ws.loop();
}
