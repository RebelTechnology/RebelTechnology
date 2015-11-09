#include "HttpClient/HttpClient.h"
//#include "MemoryOutStream.h"
#include "StringStream.h"

// https://community.particle.io/t/how-to-post-with-httpclient/13503/4

class HttpSender {
private:
  unsigned int nextTime = 0;    // Next time to contact the server
  HttpClient http;
  http_request_t request;
  http_response_t response;
  http_header_t headers[4] = {
    { "Content-Type", "application/json" },
    { "Authorization", "SharedAccessSignature sr=FUIFlSf8vjWgZ/K33JgXh1LVbK6NmFnUcYa7M5eHjFA=" },
    { "Accept" , "application/json" },
    // { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
  };
public:
  void setup() {
    //Serial.begin(9600);
    nextTime = millis() + networkSettings.resendPeriod;
  }

  void loop() {
    if(networkSettings.resendPeriod != 0 && nextTime > millis())
      return;
    send(networkSettings.remoteHost, 
	 networkSettings.remotePort, 
	 networkSettings.remotePath, Serial);
    nextTime = millis() + networkSettings.resendPeriod;
  }

  void processResponse(const String& re, const String id){
    int index = re.indexOf(id);
    int size = id.length();
    if(index > 0 && re.length() > index+size+2){
      int pos = atol(&(re.c_str()[index+size]));
      debug << "RELAY " << id << ": [" << pos << "]\r\n";
      if(pos == 0)
	setRelay(1, false);
      else if(pos == 1)
	setRelay(1, true);    
    }
  }

  String& getResponseBody(){
    return response.body;
  }

  int getResponseStatus(){
    return response.status;
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

    // Send HTTP Post request
    http.post(request, response, headers);
    out.print("{Status: ");
    out.print(response.status);
    out.print(",Body: {");
    out.print(response.body);
    out.print("}}");

    const static String ch1("Channel1");
    const static String ch2("Channel2");
    processResponse(response.body, ch1);
    processResponse(response.body, ch2);
  }
};
