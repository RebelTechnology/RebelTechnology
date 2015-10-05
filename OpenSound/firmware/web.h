#include "http_server.h"

//#define OSM_HTML_BEGIN "<html><head><title>Open Sound Module</title></head><body>"
#define OSM_HTML_END "</body></html>"

#define OSM_HTML_BEGIN "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'><title>Open Sound Module</title><link rel='stylesheet' type='text/css' href='style.css'></head><body>"

static const char OSM_BEGIN[] = OSM_HTML_BEGIN;
static const char OSM_END[] = OSM_HTML_END;
extern const wiced_http_page_t osm_http_pages[];

int32_t process_status(const char* url, wiced_http_response_stream_t* stream, void* arg, wiced_http_message_body_t* body);			
int32_t process_settings(const char* url, wiced_http_response_stream_t* stream, void* arg, wiced_http_message_body_t* body);
int32_t process_address(const char* url, wiced_http_response_stream_t* stream, void* arg, wiced_http_message_body_t* body);
int32_t process_auth(const char* url, wiced_http_response_stream_t* stream, void* arg, wiced_http_message_body_t* body);
int32_t process_reconnect(const char* url, wiced_http_response_stream_t* stream, void* arg, wiced_http_message_body_t* body);
			  
