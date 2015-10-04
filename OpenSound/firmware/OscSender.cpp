#include "application.h"
#include "OscSender.h"
#include "OscServer.h"

extern OscServer oscserver;

void OscSender::send(OscMessageId mid, int value){
  if(mid < MESSAGE_COUNT){ 
    messages[mid].setInt(0, value);
    oscserver.beginPacket();
    messages[mid].write(oscserver);
    oscserver.endPacket();
  }
}

void OscSender::send(OscMessageId mid, float value){
  if(mid < MESSAGE_COUNT){
    messages[mid].setFloat(0, value);
    oscserver.beginPacket();
    messages[mid].write(oscserver);
    oscserver.endPacket();
  }
}

void OscSender::send(OscMessageId mid, const char* value){
  if(mid < MESSAGE_COUNT){
    messages[mid].setString(0, value);
    oscserver.beginPacket();
    messages[mid].write(oscserver);
    oscserver.endPacket();
  }
}
