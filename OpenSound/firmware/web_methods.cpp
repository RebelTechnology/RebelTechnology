#include "web.hpp"
#include "opensound.h"
#include "application.h"
#include "ApplicationSettings.h"
#include "OscSender.h"
#include "OscServer.h"

WebServer webserver;
extern OscSender oscsender;
extern OscServer oscserver;

void configureWeb(){
}

int32_t process_status(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){		       
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Status</h1><h2>Open Sound Module</h2><p>firmware v0.1</p>";	 
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
  stream << "<p>Device ID: " << Spark.deviceID() << "</p>"
	 << "<p>SSID: " << WiFi.SSID() << "</p>"
	 << "<p>Gateway: " << WiFi.gatewayIP() << "</p>"
	 << "<p>RSSI: " << WiFi.RSSI() << "</p>"
	 << "<p>Local IP: " << WiFi.localIP() << "</p>"
	 << "<p>Local Port: " << settings.localPort << "</p>"
	 << "<p>Remote IP: " << settings.remoteIPAddress << "</p>"
	 << "<p>Remote Port: " << settings.remotePort << "</p>";

  byte mac[6];
  WiFi.macAddress(mac);
  stream.print("<p>MAC Address: ");
  for(int i=0; i<6; i++){
    if(i)
      stream.write(':');
    stream.print(mac[i], HEX);
  }
  stream << "</p><button onclick='location.href=\"/reconnect_sta\"'>Reconnect as WiFi Client</button>"
	 << "<br><button onclick='location.href=\"/reconnect_ap\"'>Reconnect as Access Point</button>"
    /*
  stream << "</p<p><a href='/'>Reconnect as WiFi Client</a></p>"
	 << "<p><a href='/reconnect_ap'>Reconnect as Access Point</a></p>"
    */
	 << OSM_BACK << OSM_END;
	 
  return 0;
}

int32_t process_settings(const char* u, wiced_http_response_stream_t* s, void* arg, 
			 wiced_http_message_body_t* body){
  UrlScanner url(u);
  bool updated = false;
  const char* param = url.getParameter("localport");
  if(param != NULL){
    settings.localPort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteport");
  if(param != NULL){
    settings.remotePort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteip");
  if(param != NULL){
    setRemoteIpAddress(param);
    updated = true;
  }
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  if(updated){
    stream << "<h3>Settings updated</h3>";
    reload();
  }
  stream << "<h1>Network Settings</h1>"
	 << "<form action='/settings' method='GET'>"
	 << "<p>Local IP</p><p>" << WiFi.localIP() << "</p>"
	 << "<p>Local Port</p><input type='text' name='localport' value='"
	 << settings.localPort << "'><br>"	 
    	 << "<p>Remote IP</p><input type='text' name='remoteip' value='";
  if(oscserver.isAutoMode())
    stream << "auto'><br>";
  else if(oscserver.isBroadcastMode())
    stream << "broadcast'><br>";
  else 
    stream << settings.remoteIPAddress << "'><br>";
  stream << "<p>Remote Port</p><input type='text' name='remoteport' value='"
	 << settings.remotePort << "'><br>"
	 << "<button type='submit'>Update</button></form>"
	 << OSM_BACK << OSM_END;
  return 0;
}

int32_t process_address(const char* u, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  UrlScanner url(u);
  const char inputs[] = "01234";
  const char outputs[] = "56789";
  bool updated = false;
  for(int i=0; i<5; ++i){
    char* param = url.getParameter(&inputs[i], 1);
    if(param != NULL){
      debug << "setting input address [" << i << "] to value [" << param << "]\r\n";
      oscserver.setAddress(i, param);
      updated = true;
    }
    param = url.getParameter(&outputs[i], 1);
    if(param != NULL){
      debug << "setting output address [" << i << "] to value [" << param << "]\r\n";
      oscsender.setAddress((OscSender::OscMessageId)i, param);
      updated = true;
    }
  }
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>OSC Address Mapping</h1><form action='/address' method='GET'>";
  if(updated){
    stream << "<h3>Settings updated</h3>";
    reload();
  }
  stream << "<h2>Inputs</h2>"
	 << "<p>Status</p><input type='text' name='0' value='" << oscserver.getAddress(0) << "'><br>"
	 << "<p>CV A</p><input type='text' name='1' value='" << oscserver.getAddress(1) << "'><br>"
	 << "<p>CV B</p><input type='text' name='2' value='" << oscserver.getAddress(2) << "'><br>"
	 << "<p>Trigger A</p><input type='text' name='3' value='" << oscserver.getAddress(3) << "'><br>"
	 << "<p>Trigger B</p><input type='text' name='4' value='" << oscserver.getAddress(4) << "'><br>";
  stream << "<h2>Outputs</h2>"
	 << "<p>Status</p><input type='text' name='5' value='" << oscsender.getAddress(OscSender::STATUS) << "'><br>"
	 << "<p>CV A</p><input type='text' name='6' value='" << oscsender.getAddress(OscSender::CV_A) << "'><br>"
	 << "<p>CV B</p><input type='text' name='7' value='" << oscsender.getAddress(OscSender::CV_B) << "'><br>"
	 << "<p>Trigger A</p><input type='text' name='8' value='" << oscsender.getAddress(OscSender::TRIGGER_A) << "'><br>"
	 << "<p>Trigger B</p><input type='text' name='9' value='" << oscsender.getAddress(OscSender::TRIGGER_B) << "'><br>"
	 << "<button type='submit'>Update</button></form>";
  stream << OSM_BACK << OSM_END;
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
	 << "<p>SSID</p><input name='ssid' type='text'><br>"
	 << "<p>Password</p><input name='password' type='password'><br>"
	 << "<p>Authentication</p><select name='auth'>"
	 << "<option value='0'>Open</option>"
	 << "<option value='1'>WEP</option>"
	 << "<option value='2'>WPA</option>"
	 << "<option value='3'>WPA2</option>"
	 << "</select><br>"
	 << "<button type='submit'>Update</button></form>"
	 << OSM_BACK << OSM_END;
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

int32_t process_save(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  settings.saveToFlash();
  Streamer stream(s);
  stream << OSM_BEGIN
	 << "<h1>Saved Settings</h1><p>Device settings saved to flash</p>"
	 << OSM_BACK << OSM_END;
  return 0;
}

int32_t process_reset(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  settings.reset();
  settings.clearFlash();
  reload();
  Streamer stream(s);
  stream << OSM_BEGIN
	 << "<h1>Reset Settings</h1><p>Device settings reset to factory defaults</p>"
	 << OSM_BACK << OSM_END;
  return 0;
}
