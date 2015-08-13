#include "opensound.h"
#include "websocket.h"
  
class WebSocketServer : public TCPServer {
private:
  enum WebSocketService {
    NO_SERVICE,
    ECHO_SERVICE,
    STATUS_SERVICE,
    MIDI_SERVICE,
    OPENSOUND_SERVICE,
    OSC_SERVICE
  };
  uint8_t buffer[WEBSOCKET_BUFFER_SIZE];
  int readLength;
  size_t frameSize;
  enum wsState state;
  enum wsFrameType frameType;
  struct handshake hs;
  WebSocketService service;
  TCPClient client;
public:
  WebSocketServer(const unsigned port) : TCPServer(port) {}

  void loop(){
    if(client.connected()){
      if(process() != 0){
	blockWaiting(client, 200);
	// client.stop();
	client = available();
      }
    }else if(!client.status()){
      client = available();
      if(client.status()){
	debugMessage("websocket connected");
	process();
      }
    }
  }

  void reset(){
    memset(buffer, 0, WEBSOCKET_BUFFER_SIZE);
    nullHandshake(&hs);
    service = NO_SERVICE;
    readLength = 0;
    frameSize = WEBSOCKET_BUFFER_SIZE;
    state = WS_STATE_OPENING;
    frameType = WS_INCOMPLETE_FRAME;
  }

  void prepareBuffer(){
    frameSize = WEBSOCKET_BUFFER_SIZE; 
    memset(buffer, 0, WEBSOCKET_BUFFER_SIZE);
  }

  void initNewFrame(){
    frameType = WS_INCOMPLETE_FRAME; 
    readLength = 0; 
    memset(buffer, 0, WEBSOCKET_BUFFER_SIZE);
  }

  int processHandshake(struct handshake hs){
    if(strcmp(hs.resource, "/echo") == 0){
      service = ECHO_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/status") == 0){
      service = STATUS_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/opensound") == 0){
      service = OPENSOUND_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/osc") == 0){
      service = OSC_SERVICE;
      return 0;
    }
    service = NO_SERVICE;
    frameSize = sprintf((char *)buffer, PSTR("HTTP/1.1 404 Not Found\r\n\r\n"));
    send_websocket_data( buffer, frameSize );
    return -1;
  }

  void sendOpenSoundData(uint8_t* data, size_t dataSize){
    if(service == OPENSOUND_SERVICE){
      // uint8_t output[16];
      // base64_encode(data, dataSize, output, sizeof(output), BASE64_STANDARD);
      sendBinaryFrame(data, dataSize);
// todo: synchronise with semaphores or queue
    }
  }

  void processOpenSound(uint8_t* data, size_t dataSize){
    process_opensound(data, dataSize);
  }

  void processTextFrame(uint8_t* data, size_t dataSize){
    switch(service){
    case ECHO_SERVICE:
      processEcho(data, dataSize);
      break;
    case STATUS_SERVICE:
      processStatus(data, dataSize);
      break;
    default:
      break;
    }
  }    

  void processBinaryFrame(uint8_t* data, size_t dataSize){
    switch(service){
    case OPENSOUND_SERVICE:
      processOpenSound(data, dataSize);
      break;
    default:
      break;
    }
  }    

  void processStatus(uint8_t* data, size_t dataSize){
    debugMessage("websocket status");
    const char msg[] = "I'm fine, thanks, how are you?";
    sendTextFrame((uint8_t*)msg, sizeof(msg)-1);
  }

  void processEcho(uint8_t* data, size_t dataSize){
    uint8_t *receivedString = NULL;
    receivedString = (uint8_t *)malloc(dataSize+1);
    assert(receivedString, "malloc failed");
    memcpy(receivedString, data, dataSize);
    receivedString[ dataSize ] = 0;
    sendTextFrame(receivedString, dataSize);
    free(receivedString);
  }

  void sendBinaryFrame(uint8_t* data, size_t dataSize){
    prepareBuffer();
    wsMakeFrame(data, dataSize, buffer, &frameSize, WS_BINARY_FRAME);
    send_websocket_data( buffer, frameSize );
  }

  void sendTextFrame(uint8_t* data, size_t dataSize){
    prepareBuffer();
    wsMakeFrame(data, dataSize, buffer, &frameSize, WS_TEXT_FRAME);
    send_websocket_data( buffer, frameSize );
  }

  int send_websocket_data(unsigned char * data, int length){
    return client.write(data, length);
  }

  int recv_websocket_data(unsigned char * data, int length){
    return client.read(data, length);
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

  int process(){
    uint8_t* data = NULL;
    size_t dataSize = 0;
    // assert(frameType == WS_INCOMPLETE_FRAME, "weird frame")
    // if(frameType == WS_INCOMPLETE_FRAME) {
      readLength = recv_websocket_data(buffer, WEBSOCKET_BUFFER_SIZE);
      assert(readLength <= WEBSOCKET_BUFFER_SIZE, "recv overflow");
      if(readLength <= 0)
	return 0;

      if (state == WS_STATE_OPENING) {
	frameType = wsParseHandshake(buffer, readLength, &hs);
	service = NO_SERVICE;
      } else {
	frameType = wsParseInputFrame(buffer, readLength, &data, &dataSize);
      }
    
      if(frameType == WS_ERROR_FRAME || (frameType == WS_INCOMPLETE_FRAME && readLength == WEBSOCKET_BUFFER_SIZE)) {
	if(frameType == WS_INCOMPLETE_FRAME)
	  debugMessage("websocket buffer overflow");
	else
	  debugMessage("websocket error frame");
      	if(state == WS_STATE_OPENING) {
	  prepareBuffer();
	  frameSize = sprintf((char *)buffer,
			      PSTR("HTTP/1.1 400 Bad Request\r\n"
				   "%s%s\r\n\r\n"),
			      versionField,
			      version);
	  send_websocket_data( buffer, frameSize );
	  return -1;
	} else {
	  prepareBuffer();
	  wsMakeFrame(NULL, 0, buffer, &frameSize, WS_CLOSING_FRAME);
	  send_websocket_data( buffer, frameSize );
	  state = WS_STATE_CLOSING;
	  service = NO_SERVICE;
	  initNewFrame();
	  return -1;
	}
      }

      if(state == WS_STATE_OPENING) {
	assert(frameType == WS_OPENING_FRAME, "invalid frame type");
	if (frameType == WS_OPENING_FRAME) {
	  // if resource is right, generate answer handshake and send it
	  if(processHandshake(hs) != 0){
	    debugMessage("websocket invalid handshake");
	    return -1;
	  }
	  prepareBuffer();
	  wsGetHandshakeAnswer(&hs, buffer, &frameSize);
	  freeHandshake(&hs);
	  send_websocket_data( buffer, frameSize );
	  state = WS_STATE_NORMAL;
	  initNewFrame();
	}
      } else {
        if (frameType == WS_CLOSING_FRAME) {
          if(state == WS_STATE_CLOSING) {
	    debugMessage("websocket closing");
	    return -1;
          } else {
            prepareBuffer();
            wsMakeFrame(NULL, 0, buffer, &frameSize, WS_CLOSING_FRAME);
	    send_websocket_data( buffer, frameSize );
	    return 0;
          }
        } else if(frameType == WS_TEXT_FRAME) {
	  processTextFrame(data, dataSize);
	  initNewFrame();
        } else if(frameType == WS_BINARY_FRAME) {
	  processBinaryFrame(data, dataSize);
	  initNewFrame();
        }
      }
    return 0;
  }
};
