#include "HttpClient/HttpClient.h"
//#include "MemoryOutStream.h"
#include "StringStream.h"

// https://community.particle.io/t/how-to-post-with-httpclient/13503/4

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
  http_header_t headers[4] = {
    { "Content-Type", "application/json" },
    { "Authorization", "SharedAccessSignature sr=FUIFlSf8vjWgZ/K33JgXh1LVbK6NmFnUcYa7M5eHjFA=" },
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
    // Request path and body can be set at runtime or at setup.
    request.hostname = host;
    request.path = path;
    request.port = port;

    // The library also supports sending a body with your request:
    StringStream stream(request.body);
    printJson(stream);
    //request.body = stream.GetText();

    int index = request.body.indexOf("Channel1");
    if(index > 0){
      int pos = atol(&request.body.c_str()[index+10]);
      debug << "Channel1: " << pos;
      if(pos == 0)
	setRelay(1, false);
      else if(pos == 1)
	setRelay(1, true);
    }
    index = request.body.indexOf("Channel2");
    if(index > 0){
      int pos = atol(&request.body.c_str()[index+10]);
      debug << "Channel2: " << pos;
      if(pos == 0)
	setRelay(2, false);
      else if(pos == 1)
	setRelay(2, true);
    }

    // Send HTTP Post request
    http.post(request, response, headers);
    out.print("{Status: ");
    out.print(response.status);
    out.print(",Body: {");
    out.print(response.body);
    out.print("}}");
  }
};
