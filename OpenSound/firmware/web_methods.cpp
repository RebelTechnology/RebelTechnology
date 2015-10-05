#include "web.hpp"
#include "opensound.h"
#include "application.h"
#include "OscSender.h"
#include "OscServer.h"

WebServer webserver;
extern OscSender oscsender;
extern OscServer oscserver;

void configureWeb(){
}

int32_t process_status(const char* url, wiced_http_response_stream_t* s, void* arg, 
			wiced_http_message_body_t* body){
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Status</h1><p>firmware v0.1</p>";	 
  if(WiFi.connecting())
    stream << "<p>Device Connecting</p>";
  if(WiFi.listening())
    stream << "<p>Device Listening</p>";
  if(WiFi.ready())
    stream << "<p>Device Ready</p>";
  /*
  if(WiFi.hasCredentials())
    stream << "<p>Device Has WiFi Credentials</p>";
  */
  stream << "<p>Device ID: " << Spark.deviceID() << "</p>";
  stream << "<p>SSID: " << WiFi.SSID() << "</p>";
  stream << "<p>Gateway: " << WiFi.gatewayIP() << "</p>";
  stream << "<p>RSSI: " << WiFi.RSSI() << "</p>";
  stream << "<p>Local IP: " << WiFi.localIP() << "</p>";
  stream << "<p>Local Port: " << localPort << "</p>";
  stream << "<p>Remote IP: " << oscserver.remoteIP() << "</p>";
  stream << "<p>Remote Port: " << oscserver.remotePort() << "</p>";
  byte mac[6];
  WiFi.macAddress(mac);
  stream.print("<p>MAC Address: ");
  for(int i=0; i<6; i++){
    if(i)
      stream.write(':');
    stream.print(mac[i], HEX);
  }
  stream << "</p><br><a href='/'>back</a>" << OSM_END;
	 
  return 0;
}

int32_t process_settings(const char* u, wiced_http_response_stream_t* s, void* arg, 
			 wiced_http_message_body_t* body){
  UrlScanner url(u);
  bool updated = false;
  const char* param = url.getParameter("localport");
  if(param != NULL){
    localPort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteport");
  if(param != NULL){
    remotePort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteip");
  if(param != NULL){
    setRemoteIpAddress(param);
    updated = true;
  }
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  if(updated)
    stream << "<h3>Settings updated</h3>";
  extern IPAddress remoteIPAddress;
  stream << "<h1>Network Settings</h1>"
	 << "<form action='/settings' method='GET'>"
	 << "Local IP: " << WiFi.localIP()	 
	 << "<br>Local Port:<br><input type='text' name='localport' value='"
	 << localPort << "'><br>"	 
    	 << "Remote IP:<br><input type='text' name='remoteip' value='";
  if(oscserver.isBroadcastMode())
    stream << "broadcast'><br>";
  else if(oscserver.isAutoMode())
    stream << "auto'><br>";
  else
    stream << remoteIPAddress << "'><br>";
  stream << "Remote Port:<br><input type='text' name='remoteport' value='"
	 << remotePort << "'><br>"
	 << "<br><input type='submit'></form>"
	 << "<br><a href='/'>back</a>";
  stream.write(OSM_END, sizeof(OSM_END));
  return 0;
}

int32_t process_address(const char* u, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  UrlScanner url(u);
  const char inputs[] = "01234";
  const char outputs[] = "56789";
  for(int i=0; i<5; ++i){
    char* param = url.getParameter(&inputs[i], 1);
    if(param != NULL){
      debug << "setting input address [" << i << "] to value [" << param << "]\r\n";
      oscserver.setAddress(i, param);
    }
    param = url.getParameter(&outputs[i], 1);
    if(param != NULL){
      debug << "setting output address [" << i << "] to value [" << param << "]\r\n";
      oscsender.setAddress((OscSender::OscMessageId)i, param);
    }
  }

  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>OSC Address Mapping</h1><form action='/address' method='GET'>";
  stream << "<h2>Inputs</h2>"
	 << "Status:<br><input type='text' name='0' value='" << oscserver.getAddress(0) << "'><br>"
	 << "CV A:<br><input type='text' name='1' value='" << oscserver.getAddress(1) << "'><br>"
	 << "CV B:<br><input type='text' name='2' value='" << oscserver.getAddress(2) << "'><br>"
	 << "Trigger A:<br><input type='text' name='3' value='" << oscserver.getAddress(3) << "'><br>"
	 << "Trigger B:<br><input type='text' name='4' value='" << oscserver.getAddress(4) << "'><br>";

  stream << "<h2>Outputs</h2>"
	 << "Status:<br><input type='text' name='5' value='" << oscsender.getAddress(OscSender::STATUS) << "'><br>"
	 << "CV A:<br><input type='text' name='6' value='" << oscsender.getAddress(OscSender::CV_A) << "'><br>"
	 << "CV B:<br><input type='text' name='7' value='" << oscsender.getAddress(OscSender::CV_B) << "'><br>"
	 << "Trigger A:<br><input type='text' name='8' value='" << oscsender.getAddress(OscSender::TRIGGER_A) << "'><br>"
	 << "Trigger B:<br><input type='text' name='9' value='" << oscsender.getAddress(OscSender::TRIGGER_B) << "'><br>";

  stream << "<br><input type='submit'></form>"
	 << "<br><a href='/'>back</a>" << OSM_END;
  return 0;
}

int32_t process_auth(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  debug << "msg body [" << body->message_data_length << "/" << body->total_message_data_remaining << "]\r\n";
  debug << "msg url [" << url << "]\r\n";
  UrlScanner params(body->data, body->message_data_length);
  char* ssid = params.getParameter("ssid");
  char* pass = params.getParameter("password");
  char* auth = params.getParameter("auth");
  if(ssid != NULL && pass != NULL && auth != NULL){
    setCredentials(ssid, pass, auth);
  }
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Connect</h1>"
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
	 << "<br><a href='/'>back</a>";
  stream.write(OSM_END, sizeof(OSM_END));
  debug << "msg body [" << body->message_data_length << "/" << body->total_message_data_remaining << "]\r\n";  return 0;
}

int32_t process_reconnect(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  if((int)arg == 1){
    stream.write("Reconnecting as WiFi Access Point");
  }else if((int)arg == 0){
    stream.write("Reconnecting as WiFi Client");
  }
  stream.write(OSM_END, sizeof(OSM_END));
  stream.flush();
  if((int)arg == 1){
    stopServers();
    connect(NETWORK_LOCAL_WIFI);
    startServers();
  }else if((int)arg == 0){
    stopServers();
    connect(NETWORK_ACCESS_POINT);
    startServers();
  }
  return 0;
}
			  
