
#include "websocket.h"
#include "websocket_server.h"
#define BUF_LEN 512

  
class WebSocketServer {
private:
  uint8_t buffer[BUF_LEN];
  int readLength;
  size_t frameSize;
  enum wsState state;
  enum wsFrameType frameType;
  struct handshake hs;
public:

  WebSocketServer(){
    memset(buffer, 0, BUF_LEN);
    nullHandshake(&hs);

    readLength = 0;
    frameSize = BUF_LEN;
    state = WS_STATE_OPENING;
    frameType = WS_INCOMPLETE_FRAME;
  }

  void prepareBuffer(){
    frameSize = BUF_LEN; 
    memset(buffer, 0, BUF_LEN);
  }

  void initNewFrame(){
    frameType = WS_INCOMPLETE_FRAME; 
    readLength = 0; 
    memset(buffer, 0, BUF_LEN);
  }

  enum WebSocketService {
    ECHO_SERVICE,
    STATUS_SERVICE,
    MIDI_SERVICE,
    OSC_SERVICE
  };

  WebSocketService service;

  int processHandshake(void* socket, struct handshake hs){
    if(strcmp(hs.resource, "/echo") == 0){
      service = ECHO_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/status") == 0){
      service = STATUS_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/midi") == 0){
      service = MIDI_SERVICE;
      return 0;
    }
    if(strcmp(hs.resource, "/osc") == 0){
      service = OSC_SERVICE;
      return 0;
    }
    frameSize = sprintf((char *)buffer, PSTR("HTTP/1.1 404 Not Found\r\n\r\n"));
    send_websocket_data( socket, buffer, frameSize );
    return -1;
  }

  void processTextFrame(void* socket, uint8_t* data, size_t dataSize){
    switch(service){
    case ECHO_SERVICE:
      processEcho(socket, data, dataSize);
      break;
    default:
      break;
    }
  }    

  void processEcho(void* socket, uint8_t* data, size_t dataSize){
    uint8_t *receivedString = NULL;
    receivedString = (uint8_t *)malloc(dataSize+1);
    assert(receivedString);
    memcpy(receivedString, data, dataSize);
    receivedString[ dataSize ] = 0;
    sendTextFrame(socket, receivedString, dataSize);
    free(receivedString);
  }

  void sendTextFrame(void* socket, uint8_t* data, size_t dataSize){
    prepareBuffer();
    wsMakeFrame(data, dataSize, buffer, &frameSize, WS_TEXT_FRAME);
    send_websocket_data( socket, buffer, frameSize );
  }

  int process(void* socket){  
    uint8_t* data = NULL;
    size_t dataSize = 0;
    while(frameType == WS_INCOMPLETE_FRAME) {
      // wait for data
      do{
	readLength = recv_websocket_data(socket, buffer, BUF_LEN);
      }while(readLength <= 0);
      WPRINT_APP_INFO(("websocket recv packet %d", readLength));

      assert(readLength <= BUF_LEN);

      if (state == WS_STATE_OPENING) {
	frameType = wsParseHandshake(buffer, readLength, &hs);
      } else {
	frameType = wsParseInputFrame(buffer, readLength, &data, &dataSize);
      }
    
      if ((frameType == WS_INCOMPLETE_FRAME && readLength == BUF_LEN) || frameType == WS_ERROR_FRAME) {
#ifdef DEBUG
	if (frameType == WS_INCOMPLETE_FRAME)
	  WPRINT_APP_INFO(PSTR("buffer too small"));
	else
	  WPRINT_APP_INFO(PSTR("error in incoming frame\n"));
#endif
      	if (state == WS_STATE_OPENING) {
	  prepareBuffer();
	  frameSize = sprintf((char *)buffer,
			      PSTR("HTTP/1.1 400 Bad Request\r\n"
				   "%s%s\r\n\r\n"),
			      versionField,
			      version);
	  send_websocket_data( socket, buffer, frameSize );
	  break;
	} else {
	  prepareBuffer();
	  wsMakeFrame(NULL, 0, buffer, &frameSize, WS_CLOSING_FRAME);
	  send_websocket_data( socket, buffer, frameSize );
	  state = WS_STATE_CLOSING;
	  initNewFrame();
	}
      }    

      if(state == WS_STATE_OPENING) {
	assert(frameType == WS_OPENING_FRAME);
	if (frameType == WS_OPENING_FRAME) {
	  // if resource is right, generate answer handshake and send it
	  if(processHandshake(socket, hs))
	    return 0;
	  prepareBuffer();
	  wsGetHandshakeAnswer(&hs, buffer, &frameSize);
	  freeHandshake(&hs);
	  send_websocket_data( socket, buffer, frameSize );
	  state = WS_STATE_NORMAL;
	  initNewFrame();
	}
      } else {
        if (frameType == WS_CLOSING_FRAME) {
          if (state == WS_STATE_CLOSING) {
            break;
          } else {
            prepareBuffer();
            wsMakeFrame(NULL, 0, buffer, &frameSize, WS_CLOSING_FRAME);
	    send_websocket_data( socket, buffer, frameSize );
            break;
          }
        } else if(frameType == WS_TEXT_FRAME) {
	  processTextFrame(socket, data, dataSize);
	  initNewFrame();
        }
      }
    } // read/write cycle
    return 0;
  }
};