
#include "bug.h"
#include "websocket.h"
#include "websocket_server.h"
#define BUF_LEN 512
  
class WebSocketServer {
private:
  enum WebSocketService {
    NO_SERVICE,
    ECHO_SERVICE,
    STATUS_SERVICE,
    MIDI_SERVICE,
    OSC_SERVICE
  };
  uint8_t buffer[BUF_LEN];
  int readLength;
  size_t frameSize;
  enum wsState state;
  enum wsFrameType frameType;
  struct handshake hs;
  void* socket;
  WebSocketService service;
public:
  WebSocketServer(){
  }

  void reset(){
    memset(buffer, 0, BUF_LEN);
    nullHandshake(&hs);
    service = NO_SERVICE;
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

  int processHandshake(struct handshake hs){
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
    service = NO_SERVICE;
    frameSize = sprintf((char *)buffer, PSTR("HTTP/1.1 404 Not Found\r\n\r\n"));
    send_websocket_data( socket, buffer, frameSize );
    return -1;
  }

  void controlChange(uint8_t channel, uint8_t cc, uint8_t value){
    uint8_t buf[] = { (uint8_t)(0xb0 | channel), 
		      (uint8_t)(cc & 0x7f), 
		      (uint8_t)(value & 0x7f) };
    sendMidiData(buf, sizeof(buf));
  }

  void noteOff(uint8_t channel, uint8_t note, uint8_t velocity){
    uint8_t buf[] = { (uint8_t)(0x80 | channel), 
		      (uint8_t)(note & 0x7f), 
		      (uint8_t)(velocity & 0x7f) };
    sendMidiData(buf, sizeof(buf));
  }

  void noteOn(uint8_t channel, uint8_t note, uint8_t velocity){
    uint8_t buf[] = { (uint8_t)(0x90 | channel), 
		      (uint8_t)(note & 0x7f), 
		      (uint8_t)(velocity & 0x7f) };
    sendMidiData(buf, sizeof(buf));
  }

  void sendMidiData(uint8_t* data, size_t dataSize){
    if(service == MIDI_SERVICE){
      // uint8_t output[16];
      // base64_encode(data, dataSize, output, sizeof(output), BASE64_STANDARD);
      sendBinaryFrame(data, dataSize);
// todo: synchronise with semaphores or queue
    }
  }

  void processMidi(uint8_t* data, size_t dataSize){
    process_midi(data, dataSize);
  }

  void processTextFrame(uint8_t* data, size_t dataSize){
    switch(service){
    case ECHO_SERVICE:
      processEcho(data, dataSize);
      break;
    default:
      break;
    }
  }    

  void processBinaryFrame(uint8_t* data, size_t dataSize){
    switch(service){
    case MIDI_SERVICE:
      processMidi(data, dataSize);
      break;
    default:
      break;
    }
  }    

  void processEcho(uint8_t* data, size_t dataSize){
    uint8_t *receivedString = NULL;
    receivedString = (uint8_t *)malloc(dataSize+1);
    assert(receivedString);
    memcpy(receivedString, data, dataSize);
    receivedString[ dataSize ] = 0;
    sendTextFrame(receivedString, dataSize);
    free(receivedString);
  }

  void sendBinaryFrame(uint8_t* data, size_t dataSize){
    prepareBuffer();
    wsMakeFrame(data, dataSize, buffer, &frameSize, WS_BINARY_FRAME);
    send_websocket_data( socket, buffer, frameSize );
  }

  void sendTextFrame(uint8_t* data, size_t dataSize){
    prepareBuffer();
    wsMakeFrame(data, dataSize, buffer, &frameSize, WS_TEXT_FRAME);
    send_websocket_data( socket, buffer, frameSize );
  }

  int process(void* sock){
    socket = sock;
    uint8_t* data = NULL;
    size_t dataSize = 0;
    while(frameType == WS_INCOMPLETE_FRAME) {
      // wait for data
      do{
	readLength = recv_websocket_data(socket, buffer, BUF_LEN);
      }while(readLength <= 0);
      // WPRINT_APP_INFO(("websocket recv packet %d", readLength));

      assert(readLength <= BUF_LEN);

      if (state == WS_STATE_OPENING) {
	frameType = wsParseHandshake(buffer, readLength, &hs);
	service = NO_SERVICE;
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
	  service = NO_SERVICE;
	  initNewFrame();
	}
      }    

      if(state == WS_STATE_OPENING) {
	assert(frameType == WS_OPENING_FRAME);
	if (frameType == WS_OPENING_FRAME) {
	  // if resource is right, generate answer handshake and send it
	  if(processHandshake(hs))
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
	  processTextFrame(data, dataSize);
	  initNewFrame();
        } else if(frameType == WS_BINARY_FRAME) {
	  processBinaryFrame(data, dataSize);
	  initNewFrame();
        }
      }
    } // read/write cycle
    return 0;
  }
};
