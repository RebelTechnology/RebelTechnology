
#ifndef EOT
#define EOT 0x04
#endif

void printInfo(Print& out);

class TcpSocketServer : public TCPServer {
private:
  TCPClient client;
public:
  TcpSocketServer(const unsigned port) : TCPServer(port) {}
  
  void loop() {
    if(client.connected()){
      while(client.available()){
	char c = client.read();
#ifdef SERIAL_DEBUG
	Serial.print("rx 0x");
	Serial.print(c, HEX);
	Serial.println();
#endif // SERIAL_DEBUG
	if(c == '?'){
	  printInfo(client);
	}else if(c == EOF || c == EOT){
	  debugMessage("tcp EOF/EOT");
	  client.flush_buffer();
	  client.write(c);
	  // client.stop();
	  client = available();
	}else if(c >= '0' && c <= 'z'){
	  Serial1.write(c);
	}
      }
    }else if(!client.status()){
      client = available();
      if(client.status()){
	// RGB.color(RGB_COLOR_MAGENTA);
	debugMessage("tcp request");
	client.write("opensound connected\n");
      }
    }
  }
  
};
