#include "web.h"

static const char OSM_HELLO[] = OSM_HTML_BEGIN "<h1>Hello!</h1>" OSM_HTML_END;

static const char OSM_INDEX[] = OSM_HTML_BEGIN \
  "<h1>Open Sound Module</h1>" \
  "<p><a href='/settings'>Network Settings</a></p>" \
  "<p><a href='/address'>OSC Addresses</a></p>" \
  "<p><a href='/auth'>Add WiFi Credentials</a></p>" \
  "<p><a href='/reconnect_sta'>Reconnect as WiFi Client</a></p>" \
  "<p><a href='/reconnect_ap'>Reconnect as Access Point</a></p>" \
  "<p><a href='/status'>Device Status</a></p></ul>" \
  "<p><a href='/about'>About Open Sound Modular</a></p>" \
  OSM_HTML_END;

static const char OSM_ABOUT[] = OSM_HTML_BEGIN \
  "<h1>About</h1>" \
  "<p>WiFi OSC to CV/Gate interface</p>" \
  "<p>See <a href='http://www.rebeltech.org/products/open-sound-module/'>Rebel Technology</a> for instructions and information.</p>" \
  << "<br><a href='/'>back</a>"  
  OSM_HTML_END;

static const char OSM_STYLE[] = "html{height:100%;margin:auto;background-color:white}body{box-sizing:border-box;min-height:100%;padding:20px;background-color:#3399ff;font-family:'Lucida Sans Unicode','Lucida Grande',sans-serif;font-weight:normal;color:white;margin-top:0;margin-left:auto;margin-right:auto;margin-bottom:0;max-width:400px;text-align:center;border:1px solid #6e6e70;border-radius:4px}div{margin-top:25px;margin-bottom:25px}h1{margin-top:25px;margin-bottom:25px}button{border-color:#1c75be;background-color:#1c75be;color:white;border-radius:5px;height:30px;font-size:15px;font-weight:bold}button.input-helper{background-color:#bebebe;border-color:#bebebe;color:#6e6e70;margin-left:3px}button:disabled{background-color:#bebebe;border-color:#bebebe;color:white}input[type='text'],input[type='password']{background-color:white;color:#6e6e70;border-color:white;border-radius:5px;height:25px;text-align:center;font-size:15px}input:disabled{background-color:#bebebe;border-color:#bebebe}input[type='radio']{position:relative;bottom:-0.33em;margin:0;border:0;height:1.5em;width:15%}label{padding-top:7px;padding-bottom:7px;padding-left:5%;display:inline-block;width:80%;text-align:left}input[type='radio']:checked+label{font-weight:bold;color:#1c75be}.scanning-error{font-weight:bold;text-align:center}.radio-div{box-sizing:border-box;margin:2px;margin-left:auto;margin-right:auto;background-color:white;color:#6e6e70;border:1px solid #6e6e70;border-radius:3px;width:100%;padding:5px}#networks-div{margin-left:auto;margin-right:auto;text-align:left}#device-id{text-align:center}#scan-button{min-width:100px}#connect-button{display:block;min-width:100px;margin-top:10px;margin-left:auto;margin-right:auto;margin-bottom:20px}#password{margin-top:20px;margin-bottom:10px}";

START_OF_HTTP_PAGE_DATABASE(osm_http_pages)
    ROOT_HTTP_PAGE_REDIRECT("/index.html"),
    { "/index.html", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_INDEX, sizeof(OSM_INDEX)-1 }},
    { "/style.css", "text/css", WICED_STATIC_URL_CONTENT, 
    .url_content.static_data = {OSM_STYLE, sizeof(OSM_STYLE)-1 }},
    { "/hello", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_HELLO, sizeof(OSM_HELLO)-1 }},
    { "/about", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_ABOUT, sizeof(OSM_ABOUT)-1 }},
    { "/status", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_status, 0 }, },
    { "/settings", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_settings, 0 }, },
    { "/address", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_address, 0 }, },
    { "/auth", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_auth, 0 }, },
    { "/reconnect_sta", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reconnect, 0 }, },
    { "/reconnect_ap", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_reconnect, 1 }, },
END_OF_HTTP_PAGE_DATABASE();

