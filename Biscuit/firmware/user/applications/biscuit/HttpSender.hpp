#include "HttpClient/HttpClient.h"
//#include "MemoryOutStream.h"
#include "StringStream.h"

class HttpSender {
private:
  const int SEND_PERIOD = 20000;
public:
  /**
   * Declaring the variables.
   */
  unsigned int nextTime = 0;    // Next time to contact the server
  HttpClient http;

  // Headers currently need to be set at init, useful for API keys etc.
  http_header_t headers[2] = {
    //  { "Content-Type", "application/json" },
    { "Accept" , "application/json" },
    // { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
  };

  http_request_t request;
  http_response_t response;

  void setup() {
    //Serial.begin(9600);
  }

  void loop() {
    if(nextTime > millis())
      return;
    send(networkSettings.remoteHost, 
	 networkSettings.remotePort, 
	 networkSettings.remotePath, Serial);
    nextTime = millis() + SEND_PERIOD;
  }

  void send(String host, int port, String path, Print& out) {
    out.println("HTTP>\tSend.");
    // Request path and body can be set at runtime or at setup.
    request.hostname = host;
    request.path = path;
    request.port = port;

    // The library also supports sending a body with your request:
    StringStream stream(request.body);
    printJson(stream);
    //request.body = stream.GetText();
    //request.body = "{\"key\":\"value\"}";

    // Get request
    http.get(request, response, headers);
    out.print("Application>\tResponse status: ");
    out.println(response.status);

    out.println("Application>\tHTTP Response Body: ");
    out.println(response.body);
  }
};
