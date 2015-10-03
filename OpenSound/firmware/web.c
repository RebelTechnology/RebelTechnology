#include "web.h"

static const char OSM_HELLO[] = OSM_HTML_BEGIN "<h2>Hello!</h2>" OSM_HTML_END;

static const char OSM_INDEX[] = OSM_HTML_BEGIN \
  "<h1>Open Sound Module v0.1</h1><ul>" \
  "<li><a href='/settings'>Network Settings</a></li>" \
  "<li><a href='/address'>OSC Addresses</a></li>" \
  "<li><a href='/auth'>Add WiFi Credentials</a></li>" \
  "<li><a href='/reconnect_sta'>Reconnect as WiFi Client</a></li>" \
  "<li><a href='/reconnect_ap'>Reconnect as Access Point</a></li>" \
  OSM_HTML_END;

START_OF_HTTP_PAGE_DATABASE(osm_http_pages)
    ROOT_HTTP_PAGE_REDIRECT("/index.html"),
    { "/index.html", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_INDEX, sizeof(OSM_INDEX) }},
    { "/hello", "text/html", WICED_STATIC_URL_CONTENT, 
	.url_content.static_data = {OSM_HELLO, sizeof(OSM_HELLO) }},
    { "/version", "text/html", WICED_DYNAMIC_URL_CONTENT, 
	.url_content.dynamic_data = {process_version, 0 }, },
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

