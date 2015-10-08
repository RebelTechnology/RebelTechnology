#include "web.hpp"
#include "opensound.h"
#include "application.h"
#include "ApplicationSettings.h"

WebServer webserver;

void configureWeb(){
}

int32_t process_status(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){		       
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Status</h1><h2>Open Sound Module</h2>";
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
  stream << "<p>ID: " << Spark.deviceID() << "</p>"
	 << "<p>SSID: " << WiFi.SSID() << "</p>"
	 << "<p>Gateway: " << WiFi.gatewayIP() << "</p>"
	 << "<p>RSSI: " << WiFi.RSSI() << "</p>"
	 << "<p>Local IP: " << WiFi.localIP() << "</p>"
	 << "<p>Local Port: " << networkSettings.localPort << "</p>"
	 << "<p>Remote IP: " << 
  if(networkSettings.autoremote)
    stream << "auto'></p>";
  else if(networkSettings.broadcast)
    stream << "broadcast'></p>";
  else 
    stream << networkSettings.remoteIPAddress << "'></p>";
  stream << "<p>Remote Port: " << networkSettings.remotePort << "</p>";

  byte mac[6];
  WiFi.macAddress(mac);
  stream.print("<p>MAC Address: ");
  for(int i=0; i<6; i++){
    if(i)
      stream.write(':');
    stream.print(mac[i], HEX);
  }
  if(networkSettings.hasChanged())
    stream << "</p><button onclick='location.href=\"/save_net\"'>Save Network Settings</button>";
  stream << "<br><button onclick='location.href=\"/reset_net\"'>Reset Network Settings</button>";
  if(addressSettings.hasChanged())
    stream << "<br><button onclick='location.href=\"/save_osc\"'>Save Address Mappings</button>";
  stream << "<br><button onclick='location.href=\"/reset_osc\"'>Reset Address Mappings</button>";
  stream << "<br><button onclick='location.href=\"/reconnect_sta\"'>Reconnect as WiFi Client</button>"
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
    networkSettings.localPort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteport");
  if(param != NULL){
    networkSettings.remotePort = atol(param);
    updated = true;
  }
  param = url.getParameter("remoteip");
  if(param != NULL){
    setRemoteIpAddress(param);
    updated = true;
  }
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Network Settings</h1>"
	 << "<form action='/settings' method='GET'>"
	 << "<p>Local IP</p><p>" << WiFi.localIP() << "</p>"
	 << "<p>Local Port</p><input type='text' name='localport' value='"
	 << networkSettings.localPort << "'><br>"	 
    	 << "<p>Remote IP</p><input type='text' name='remoteip' value='";
  if(networkSettings.autoremote)
    stream << "auto'><br>";
  else if(networkSettings.broadcast)
    stream << "broadcast'><br>";
  else 
    stream << networkSettings.remoteIPAddress << "'><br>";
  stream << "<p>Remote Port</p><input type='text' name='remoteport' value='"
	 << networkSettings.remotePort << "'><br>"
	 << "<button type='submit'>Update</button></form>";

  if(updated){
    stream << "<h3>Settings updated</h3>";
    stream << "<br><button onclick='location.href=\"/save_net\"'>Store Settings</button>";
    reload();
  }
  stream << OSM_BACK << OSM_END;
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
      addressSettings.setInputAddress(i, param);
      updated = true;
    }
    param = url.getParameter(&outputs[i], 1);
    if(param != NULL){
      debug << "setting output address [" << i << "] to value [" << param << "]\r\n";
      addressSettings.setOutputAddress(i, param);
      updated = true;
    }
  }
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>OSC Address Mapping</h1><form action='/address' method='GET'>";
  stream << "<h2>Inputs</h2>"
	 << "<p>Status</p><input type='text' name='0' value='" << addressSettings.getInputAddress(0) << "'><br>"
	 << "<p>CV A</p><input type='text' name='1' value='" << addressSettings.getInputAddress(1) << "'><br>"
	 << "<p>CV B</p><input type='text' name='2' value='" << addressSettings.getInputAddress(2) << "'><br>"
	 << "<p>Trigger A</p><input type='text' name='3' value='" << addressSettings.getInputAddress(3) << "'><br>"
	 << "<p>Trigger B</p><input type='text' name='4' value='" << addressSettings.getInputAddress(4) << "'><br>";
  stream << "<h2>Outputs</h2>"
	 << "<p>Status</p><input type='text' name='5' value='" << addressSettings.getOutputAddress(0) << "'><br>"
	 << "<p>CV A</p><input type='text' name='6' value='" << addressSettings.getOutputAddress(1) << "'><br>"
	 << "<p>CV B</p><input type='text' name='7' value='" << addressSettings.getOutputAddress(2) << "'><br>"
	 << "<p>Trigger A</p><input type='text' name='8' value='" << addressSettings.getOutputAddress(3) << "'><br>"
	 << "<p>Trigger B</p><input type='text' name='9' value='" << addressSettings.getOutputAddress(4) << "'><br>"
	 << "<button type='submit'>Update</button></form>";
  if(updated){
    stream << "<h3>Settings updated</h3>";
    stream << "<br><button onclick='location.href=\"/save_osc\"'>Store Settings</button>";
    reload();
  }
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
	 << "<button type='submit'>Connect</button></form>"
	 << OSM_BACK << OSM_END;
  debug << "msg body [" << body->message_data_length << "/" << body->total_message_data_remaining << "]\r\n";
  return 0;
}

int32_t process_reconnect(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  // raw
  Streamer stream(s);
  stream << OSM_BEGIN;
  if((int)arg == 1){
    stream.write("<h2>Reconnecting as WiFi Access Point</h2>");
  }else if((int)arg == 2){
    stream.write("<h2>Reconnecting as WiFi Client</h2>");
  }
  stream << OSM_END;
  stream.flush();
  if((int)arg == 1){
    stopServers();
    connect(NETWORK_LOCAL_WIFI);
    startServers();
  }else if((int)arg == 2){
    stopServers();
    connect(NETWORK_ACCESS_POINT);
    startServers();
  }
  return 0;
}

int32_t process_save(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  if((int)arg == 1){
    networkSettings.saveToFlash();
    //    EEPROM.put(NETWORK_SETTINGS_ADDRESS, networkSettings);
  }else if((int)arg == 2){
    //    EEPROM.put(ADDRESS_SETTINGS_ADDRESS, addressSettings);
    addressSettings.saveToFlash();
  }
  Streamer stream(s);
  stream << OSM_BEGIN;
  stream << "<h1>Saved Settings</h1><p>Device settings saved to flash</p>";
  stream << OSM_BACK << OSM_END;
  return 0;
}

int32_t process_reset(const char* u, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  Streamer stream(s);
  stream << OSM_BEGIN << "<h1>Reset Settings</h1>";	 
  UrlScanner url(u);
  const char* param = url.getParameter("confirm");
  if(param != NULL){
    if((int)arg == 1){
      networkSettings.reset();
      networkSettings.clearFlash();
      stream << "<p>Network settings reset to factory defaults</p>";
    }else if((int)arg == 2){
      addressSettings.reset();
      addressSettings.clearFlash();
      stream << "<p>OSC address mappings reset to factory defaults</p>";
    }
    reload();
  }else{
    stream << "<p>Really reset?</p>";
    if((int)arg == 1){
      stream << "<br><button onclick='location.href=\"/reset_net?confirm=yes\"'>Yes</button>";
    }else if((int)arg == 2){
      stream << "<br><button onclick='location.href=\"/reset_osc?confirm=yes\"'>Yes</button>";
    }
  }
  stream << OSM_BACK << OSM_END;
  return 0;
}
