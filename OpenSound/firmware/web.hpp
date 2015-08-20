#include "WebServer.h"

void connect(int iface);
void stopServers();
void startServers();

#if 1
#define PREFIX ""
WebServer webserver(PREFIX, HTTP_SERVER_PORT);
#else
WebServer webserver(HTTP_SERVER_PORT);
#endif

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
    Serial.print("reconnect ");
    Serial.print(name);
    Serial.print(": ");
    Serial.println(value);
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
	Serial.print("set address ");
	Serial.print(mid);
	Serial.print(": ");
	Serial.println(value);
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
