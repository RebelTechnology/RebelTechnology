#include "web.hpp"
#include "opensound.h"
#include "application.h"

WebServer webserver;

void configureWeb(){
}

int32_t process_version(const char* url, wiced_http_response_stream_t* stream, void* arg, 
			wiced_http_message_body_t* body){
  wiced_http_response_stream_write(stream, OSM_BEGIN, sizeof(OSM_BEGIN));
  const char str[] = "<h2>v0.1</h2>";
  wiced_http_response_stream_write(stream, str, sizeof(str));
  wiced_http_response_stream_write(stream, OSM_END, sizeof(OSM_END));
  return 0;
}

int32_t process_settings(const char* url, wiced_http_response_stream_t* s, void* arg, 
			 wiced_http_message_body_t* body){
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  stream << "<form action='/settings' method='POST'>"
	 << "Local IP: "
	 << WiFi.localIP()
	 << "<br>Local Port:<br><input type='text' name='localport' value='"
	 << localPort
	 << "'><br>"
    //	 << "Remote IP:<br><input type='text' name='remoteip' value='"
    //	 << remoteIPAddress
    //	 << "'><br>"
	 << "Remote Port:<br><input type='text' name='remoteport' value='"
	 << remotePort
	 << "'><br>"
	 << "<br><input type='submit'></form>"
	 << "<br><a href='/'>return</a>";
  stream.write(OSM_END, sizeof(OSM_END));
  return 0;
}

int32_t process_address(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  stream << "<h2>Outputs</h2>"
	 << "<form action='/address' method='POST'>"
	 << "Status:<br><input type='text' name='0' value='" << osc.getAddress(Osc::STATUS) << "'><br>"
	 << "CV A:<br><input type='text' name='1' value='" << osc.getAddress(Osc::CV_A) << "'><br>"
	 << "CV B:<br><input type='text' name='2' value='" << osc.getAddress(Osc::CV_B) << "'><br>"
	 << "Trigger A:<br><input type='text' name='3' value='" << osc.getAddress(Osc::TRIGGER_A) << "'><br>"
	 << "Trigger B:<br><input type='text' name='4' value='" << osc.getAddress(Osc::TRIGGER_B) << "'><br>"
	 << "<br><input type='submit'></form>"
	 << "<br><a href='/'>return</a>";
  stream.write(OSM_END, sizeof(OSM_END));
  return 0;
}

int32_t process_auth(const char* url, wiced_http_response_stream_t* s, void* arg, wiced_http_message_body_t* body){
  Streamer stream(s);
  stream.write(OSM_BEGIN, sizeof(OSM_BEGIN));
  /*
  stream.write("<form action='auth' method='POST'>");
  */
  stream << "<form action='auth' method='POST'>"	
	 << "SSID:<br><input name='ssid' type='text'><br>"
	 << "Password:<br><input name='password' type='password'><br>"
	 << "Authentication: <br> <select name='auth'><br>"
	 << "<option value='0'>Open</option>"
	 << "<option value='1'>WEP</option>"
	 << "<option value='2'>WPA</option>"
	 << "<option value='3'>WPA2</option>"
	 << "</select><br>"
	 << "<br><input type='submit'></form>"
	 << "<br><a href='/'>return</a>";
  stream.write(OSM_END, sizeof(OSM_END));
  return 0;
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
			  
