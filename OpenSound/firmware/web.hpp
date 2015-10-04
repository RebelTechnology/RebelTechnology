#include "http_server.h"
#include "application.h"
#include "opensound.h"

// extern "C" wiced_http_page_t osm_http_pages[];

extern "C" {
#include "web.h"
};

class WebServer {
private:
  wiced_http_server_t server;
public:
  void begin(){
    // server, port, max sockets, pages, interface, url processor stack size
    //    wiced_http_server_start(&server, 80, 4, osm_http_pages, WICED_AP_INTERFACE, 1024);
    extern wiced_interface_t network; // WICED_STA_INTERFACE or WICED_AP_INTERFACE
    wiced_http_server_start(&server, 80, 4, osm_http_pages, network, 1024);
  }
  void stop(){
    wiced_http_server_stop(&server);
  }
  //void processConnection();
};

extern WebServer webserver;
void configureWeb();

class UrlScanner {
private:
  const char* url;
  int len;
public:
  UrlScanner(const char* u) : url(u) {
    len = strlen(url);
    debug << "url: " << url << "[" << len << "]\r\n";
  }
  UrlScanner(const void* u, size_t l) : url((const char*)u), len(l)  {
    debug << "body: " << url << "[" << len << "]\r\n";
  }
  char* getParameter(const char* name){
    return getParameter(name, strlen(name));
  }
  char* getParameter(const char* name, size_t nlen){
    char* found = NULL;
    int i = 0;
    while(i<len && found == NULL){
      debug << "looking for [" << name << "][" << nlen << "] in [" << &url[i] << "][" << len << "]\r\n";
      if(strncmp(&url[i], name, nlen) == 0){
	i += nlen+1;
	found = (char*)&url[i];
      }
      do{
	i++; // fast forward to next parameter or end of list
      }while(i < len && url[i] != '&' && url[i] != '\x00' && url[i] != '\n');
      if(i < len){
	if(url[i] == '&'){
	  // replace & with \0 at the end of the parameter value
	  char* tmp = (char*)url;
	  tmp[i] = '\x00';
	}
	i++;
      }
    }
    return found;
  }
};

class Streamer : public Print {
private:
  wiced_http_response_stream_t* stream;
public:
  Streamer(wiced_http_response_stream_t* s) : stream(s){}
  // void write(const char* data){
  //   wiced_http_response_stream_write(stream, data, strlen(data));
  // }
  size_t write(const char* data){
    return write(data, strlen(data));
  }
  size_t write(uint8_t data){
    return write(&data, 1);
  }
  size_t write(const void* data, size_t size){
    wiced_http_response_stream_write(stream, data, size);
    return size;
  }
  void flush(){
    wiced_http_response_stream_flush(stream);
  }
};

#if 0 // superceded by Print template in opensound.h
inline Streamer &operator <<(Streamer &obj, const char* arg) { 
  obj.write(arg); 
  return obj; 
}
#endif

#if 0
#include "WebServer.h"

void connect(int iface);
void stopServers();
void startServers();

#define PREFIX ""
WebServer webserver(PREFIX, HTTP_SERVER_PORT);

template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

const char web_title[] = "<html><head><title>OpenSoundModule</title></head><body>";

void webIndex(WebServer &server, WebServer::ConnectionType type, char *, bool){
  server.httpSuccess();
  if(type != WebServer::HEAD){
    server << web_title
	   << "<h1>OpenSoundModule v0.1</h1><ul>"
    	   << "<li><a href='/settings'>Network Settings</a></li>"
    	   << "<li><a href='/address'>OSC Addresses</a></li>"
    	   << "<li><a href='/auth'>Add WIFI Credentials</a></li>"
    	   << "<li><a href='/reconnect?net=0'>Reconnect as Wifi Client</a></li>"
    	   << "<li><a href='/reconnect?net=1'>Reconnect as Access Point</a></li>"
	   << "</ul></body></html>";
  }
}

void webSettings(WebServer &server, WebServer::ConnectionType type, char* url_tail, bool tail_complete){
  server.httpSuccess();
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
  if(type != WebServer::HEAD){
    server << web_title
	   << "<form action='/settings' method='POST'>"
	   << "Local IP: "
	   << WiFi.localIP()
	   << "<br>Local Port:<br><input type='text' name='localport' value='"
	   << localPort
	   << "'><br>"
	   << "Remote IP:<br><input type='text' name='remoteip' value='"
	   << remoteIPAddress
	   << "'><br>"
	   << "Remote Port:<br><input type='text' name='remoteport' value='"
	   << remotePort
	   << "'><br>"
	   << "<br><input type='submit'></form>"
	   << "<br><a href='/'>return</a></body></html>";
  }
}

void webReconnect(WebServer &server, WebServer::ConnectionType type, 
		  char* url_tail, bool tail_complete){
  URLPARAM_RESULT rc;
  char name[8];
  char value[8];
  int net = -1;
  debugMessage("/reconnect");
  while(strlen(url_tail)){
    rc = server.nextURLparam(&url_tail, name, sizeof(name), value, sizeof(value));
#ifdef SERIAL_DEBUG
    Serial.print("reconnect ");
    Serial.print(name);
    Serial.print(": ");
    Serial.println(value);
#endif
    if(strcmp(name, "net"))
      net = strtol(value, NULL, 10);
  }
  server.httpSeeOther(PREFIX "/index.html");
  if(net >= 0){
    debugMessage("reconnect request");
    stopServers();
    connect(net);
    startServers();
  }
}

void webAuth(WebServer &server, WebServer::ConnectionType type, 
		    char* url_tail, bool tail_complete){
  server.httpSuccess();
  if(type == WebServer::POST){
    bool repeat;
    char ssid[16], password[16];
    unsigned int auth = -1;
    char name[16], value[16];
    do{
      repeat = server.readPOSTparam(name, sizeof(name), value, sizeof(value));
      if(strcmp(name, "ssid") == 0){
	strcpy(ssid, value);
      }else if(strcmp(name, "password") == 0){
	strcpy(password, value);
      }else if(strcmp(name, "auth") == 0){
	// Options are UNSEC 0, WEP 1, WPA 2, or WPA2 3.
	auth = strtoul(value, NULL, 10);
      }
    }while(repeat);
    if(auth >= 0){
      debugMessage("set credentials");
      WiFi.setCredentials(ssid, password, auth);
      // Photon remembers the 5 most recently set credentials
    }
  }
  if(type != WebServer::HEAD){
    server << web_title
	   << "<form action='auth' method='POST'>"
	   << "SSID:<br><input name='ssid' type='text'><br>"
	   << "Password:<br><input name='password' type='password'><br>"
	   << "Authentication: <br> <select name='auth'><br>"
	   << "<option value='0'>Open</option>"
	   << "<option value='1'>WEP</option>"
	   << "<option value='2'>WPA</option>"
	   << "<option value='3'>WPA2</option>"
	   << "</select><br>"
	   << "<br><input type='submit'></form>"
	   << "<br><a href='/'>return</a></body></html>";
  }
}

void webAddress(WebServer &server, WebServer::ConnectionType type, char* url_tail, bool tail_complete){
  server.httpSuccess();
  if(type == WebServer::POST){
    bool repeat;
    char name[4], value[16];
    do{
      repeat = server.readPOSTparam(name, sizeof(name), value, sizeof(value));
      unsigned int mid = strtoul(name, NULL, 10);
      if(mid < Osc::MESSAGE_COUNT && strnlen(name, sizeof(name)) > 0){
#ifdef SERIAL_DEBUG
	Serial.print("set address ");
	Serial.print(mid);
	Serial.print(": ");
	Serial.println(value);
#endif
	osc.setAddress((Osc::OscMessageId)mid, value);
      }
    }while(repeat);
  }
  //    for(int i=0; i<Osc::MESSAGE_COUNT; ++i)
  if(type != WebServer::HEAD){
    server << web_title
	   << "<h2>Outputs</h2>"
	   << "<form action='/address' method='POST'>"
	   << "Status:<br><input type='text' name='0' value='" << osc.getAddress(Osc::STATUS) << "'><br>"
	   << "CV A:<br><input type='text' name='1' value='" << osc.getAddress(Osc::CV_A) << "'><br>"
	   << "CV B:<br><input type='text' name='2' value='" << osc.getAddress(Osc::CV_B) << "'><br>"
	   << "Trigger A:<br><input type='text' name='3' value='" << osc.getAddress(Osc::TRIGGER_A) << "'><br>"
	   << "Trigger B:<br><input type='text' name='4' value='" << osc.getAddress(Osc::TRIGGER_B) << "'><br>"
	   << "<br><input type='submit'></form>"
	   << "<br><a href='/'>return</a></body></html>";
  }
}

void configureWeb(){
  // webserver = WebServer(HTTP_SERVER_PORT);
  // websocketserver = WebSocketServer(WEBSOCKET_SERVER_PORT);
  // websocketserver.begin();
  // tcpsocketserver.begin();

  webserver.setDefaultCommand(&webIndex);
  webserver.addCommand("index.html", &webIndex);
  webserver.addCommand("settings", &webSettings);
  webserver.addCommand("address", &webAddress);
  webserver.addCommand("auth", &webAuth);
  webserver.addCommand("reconnect", &webReconnect);
}

#endif
