#include "HttpRequest.h"
#include "HttpResponse.h"

String ssid = "FortRebel";
String passwd = "notwhattheyseem";
extern IPAddress remoteIPAddress;
extern int remotePort;
extern int localPort;
void setCredentials(String ssid, String passwd);

class ConfigurationResponse : public HttpResponse {
protected:
  Stream& printBody(Stream& out) const {
    out.write("<html><body>");
    out.write("<form action='/settings'>");
    out.write("<p>Device IP: ");
    out.print(WiFi.localIP());
    out.write("</p><p>Port: <input type='text' name='localport' value='");
    out.print(ssid);
    out.write("'/></p>");
    out.write("<p>Remote IP: <input type='text' name='remoteip' value='");
    out.print(passwd);
    out.write("'/></p>");
    out.write("<p>Port: <input type='text' name='remoteport' value='");
    out.print(remotePort);
    out.write("'/></p>");
    out.write("<input type='submit'/>");
    out.write("</form>");
    out.write("</body></html>\r\n");
    return out;
  }
};

String getParameter(String url, const String& name, const String& def){
  int pos = url.indexOf(name);
  if(pos < 0)
    return def;
  url = url.substring(pos+name.length()+1);
  pos = url.indexOf('&');
  if(pos > 0)
    return url.substring(0, pos);
  return url;
}

class WebServer : public TCPServer {
private:
    HttpRequest hr;
public:
  const ConfigurationResponse config;
  WebServer() : TCPServer(80) {}
  WebServer(const unsigned aPort) : TCPServer(aPort) {}
  
  TCPClient client;

  void loop() {
    if(client.connected()){
      process();
    }else if(!client.status()){
      client = available();
      if(client.status()){
	debugMessage("http request");
	hr.reset();
	process();
      }
    }
  }

  void process(){
    int numBytes = client.available();
    while(!hr.done && numBytes > 0) {
      debugMessage("http parse");
      for(int i=0; i<numBytes && !hr.done; ++i)
	hr.parse(client.read());
      numBytes = client.available();
    }
    if(!hr.done)
      return;
    String url(hr.URL());
    debugMessage("http: "+url);

    // while(int numBytes = client.available()){
    //   Serial.print("Reading http request ");
    //   Serial.println(numBytes);
    //   for(int i = 0; i < numBytes; ++i)
    // 	hr.parse(client.read());
    // }
    // String url(hr.URL());
    if(url.indexOf("/settings?") >= 0){
      ssid = getParameter(url, "ssid", ssid);
      passwd = getParameter(url, "password", passwd);
    }else if(url.indexOf("/D0/on") >= 0) {
      debugMessage("Turning D0 on");
      digitalWrite(D0, HIGH);
    }else if(url.indexOf("/D0/off") >= 0) {
      debugMessage("Turning D0 off");
      digitalWrite(D0, LOW);
    }else if(url.indexOf("/D7/on") >= 0) {
      digitalWrite(D7, HIGH);
    }else if(url.indexOf("/D7/off") >= 0) {
      digitalWrite(D7, LOW);
    }
    client << config;
    blockWaiting(client, 100);
    // client.flush();
    // client.stop();
    client = available();
    hr.reset();
  }

  void blockWaiting(TCPClient& client, unsigned long timeOut){
    unsigned long startWait = millis();
    while(client.available() == 0) {
      if(millis() - startWait > timeOut) 
        return;
    }
    while(client.available() > 0){
      client.read();  // discard read data
      if(millis() - startWait > timeOut) 
        return;
    }
  }
};
