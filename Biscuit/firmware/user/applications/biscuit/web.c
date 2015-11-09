#include "web.h"

static const char OSM_INDEX[] = OSM_HTML_BEGIN			\
  "<h1>Biscuit</h1>"						\
  /*  "<p><a href='/scan'>Scan Networks</a></p>"	 \ */
  "<p><a href='/auth'>Add WiFi Credentials</a></p>"		\
  "<p><a href='/settings'>Network Settings</a></p>"		\
  "<p><a href='/control'>Control</a></p>"			\
  "<p><a href='/sensors'>Sensors</a></p>"			\
  "<p><a href='/status'>Status</a></p></ul>"			\
  "<p><a href='/about'>About</a></p>"				\
  OSM_HTML_END;

static const char OSM_HELLO[] = OSM_HTML_BEGIN "<h1>Hello!</h1>" OSM_HTML_END;

static const char OSM_CONTROL[] = OSM_HTML_BEGIN			\
  "<h1>Control</h1>"							\
  "<br><button id='tra'>Relay 1</button>"				\
  "<br><button id='trb'>Relay 2</button>"				\
  "<script>"								\
  "function tr(i){var rq=new XMLHttpRequest();"				\
  "rq.open('GET', '/relay'+i);rq.send(null);};"				\
  "document.getElementById('tra').onclick=function(){tr(0)};"		\
  "document.getElementById('trb').onclick=function(){tr(1)};"		\
  "</script>"								\
  OSM_HTML_BACK OSM_HTML_END;

static const char OSM_ABOUT[] = OSM_HTML_BEGIN				\
  "<h1>About</h1>"							\
  "<h2>Rinkya Biscuit</h2>"						\
  "<p>WiFi Smart Socket</p>"						\
  "<p>Firmware v0.1</p>"						\
  OSM_HTML_BACK								\
  OSM_HTML_END;

static const char OSM_STYLE[] = 
  "html{height:100%;margin:auto;background-color:white}"		\
  "body{box-sizing:border-box;min-height:80%;padding:20px;background-color:#84AFF4;font-family:'Lucida Sans Unicode','Lucida Grande',sans-serif;font-weight:normal;color:white;margin:4px auto;max-width:380px;text-align:center;border:3px solid #6f8bb8;border-radius:5px}" \
  "div,h1{margin:25px}"							\
  "input,button{margin:10px;height:30px}"				\
  "button,select{border-color:#6f8bb8;background-color:#5f7eb0;color:white;border-radius:5px;font-size:15px;font-weight:bold}" \
  "input[type='text'],input[type='password']{background-color:white;color:#6e6e70;border-color:white;border-radius:5px;height:25px;text-align:center;font-size:15px}" \
  "input[type='radio']{position:relative;bottom:-0.33em;border:0;height:1.5em;width:15%}";

START_OF_HTTP_PAGE_DATABASE(osm_http_pages)
    ROOT_HTTP_PAGE_REDIRECT("/index.html"),
    { "/index.html", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_INDEX, sizeof(OSM_INDEX)-1 }},
    { "/control", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_CONTROL, sizeof(OSM_CONTROL)-1 }},
    { "/style.css", "text/css", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_STYLE, sizeof(OSM_STYLE)-1 }},
    { "/hello", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_HELLO, sizeof(OSM_HELLO)-1 }},
    { "/about", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_ABOUT, sizeof(OSM_ABOUT)-1 }},
    { "/status", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_status, 0 }, },
    { "/sensors", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_sensors, 0 }, },
    { "/settings", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_settings, 0 }, },
    { "/auth", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_auth, 0 }, },
    { "/scan", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_scan, 0 }, },
    { "/reconnect_ap", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reconnect, 1 }, },
    { "/reconnect_sta", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reconnect, 2 }, },
    { "/save_net", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_save, 1 }, },
    { "/reset0", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reset, 0 }, },
    { "/reset1", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reset, 1 }, },
    { "/reset2", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reset, 2 }, },
    { "/reset99", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reset, 99 }, },
    { "/relay0", "application/json", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_relay, 1 }, },
    { "/relay1", "application/json", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_relay, 2 }, },
    { "/json", "application/json", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_json, 0 }, },
    { "/send", "application/json", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_send, 0 }, },
END_OF_HTTP_PAGE_DATABASE();

