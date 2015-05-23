#ifndef _OSC_MESSAGE_H_
#define _OSC_MESSAGE_H_

#include <inttypes.h>
#include <string.h>
#include "lwip/def.h" // for htonl() and ntohl()
/* todo: optimise htonl() using __REV() cortex M4 intrinsic */

/*
  todo: define get/set methods with two different indexes: field and offset
  void* getDataAt(offset) / getField(index)
*/

#define OSC_MESSAGE_MAX_PREFIX_SIZE 32
#define OSC_MESSAGE_MAX_DATA_SIZE 32
class OscMessage {
public:
  uint8_t prefix[OSC_MESSAGE_MAX_PREFIX_SIZE];
  uint8_t prefixLength;
  uint8_t* types;
  uint8_t data[OSC_MESSAGE_MAX_DATA_SIZE];
  uint8_t dataLength;
public:
  OscMessage() : prefixLength(0), types(NULL), dataLength(0){}

  OscMessage(char* a) : prefixLength(0), dataLength(0){
    setAddress(a);
  }

  void parse(uint8_t* buffer, int length){
    setAddress((char*)buffer);
    int i = prefixLength;
    while(buffer[i] != '\0'){
      char type = (char)buffer[i++];
      addType(type, getDataSize(type));
    }
    i++; // add space for at least one \0
    while(i & 3) // pad to 4 bytes
      i++;
    memcpy(data, &buffer[i], length-i);    
  }

  int size(){
    int size = 0;
    while(types[size] != '\0')
      size++;
    return size;
  }

  char* getAddress(){
    return (char*)prefix;
  }

  int8_t getDataSize(char type){
    switch(type){
    case 'i':
    case 'f':
      return 4;
    }
    return 0;
  }

  int getOffset(int8_t index){
    int offset = 0;
    for(int i=0; i<index; ++i)
      offset += getDataSize(types[i]);
    return offset;
  }

  int32_t getInt(int8_t index){
    // if(types[index] != 'i')
    // return 0;
    int offset = getOffset(index);
    union { int32_t i; uint8_t b[4]; } u;
    memcpy(u.b, &data[offset], 4);
    return htonl(u.i);
  }

  float getFloat(int8_t index){
    int offset = getOffset(index);
    union { float f; uint8_t b[4]; } u;
    memcpy(u.b, &data[offset], 4);
    return htonl(u.f);
  }

  void setAddress(char* a){
    prefixLength = strnlen(a, OSC_MESSAGE_MAX_PREFIX_SIZE-5)+1;
    memcpy(prefix, a, prefixLength);
    while(prefixLength & 3) // pad to 4 bytes
      prefix[prefixLength++] = '\0';
    prefix[prefixLength++] = ',';
    types = prefix+prefixLength;
  }

  int copy(uint8_t* buf, int buflen){
    if(buflen < prefixLength)
      return -1;
    memcpy(buf, prefix, prefixLength);
    int len = prefixLength;
    buf[len++] = '\0';
    while(len & 3) // pad to 4 bytes
      buf[len++] = '\0';
    if(buflen < len+dataLength)
      return -1;
    memcpy(buf+len, data, dataLength);
    len += dataLength;
    while(len & 3) // pad to 4 bytes
      buf[len++] = '\0';
    return len;
  }

  // void send(Print& out){
  //   out.write(prefix, prefixLength);
  //   // add zero padding
  //   switch((prefixLength) & 3){
  //   case 0:
  //     out.write((uint8_t)'\0');
  //   case 1:
  //     out.write((uint8_t)'\0');
  //   case 2:
  //     out.write((uint8_t)'\0');
  //   case 3:
  //     out.write((uint8_t)'\0');
  //   }
  //   out.write(data, dataLength);
  // }

  uint8_t add(float value){
    return add('f', (uint8_t*)&value);
  }
  uint8_t add(int32_t value){
    return add('i', (uint8_t*)&value);
  }
  uint8_t addString(char type, uint8_t* value, size_t sz){
    uint8_t index = dataLength;
    for(size_t i=1; i<=sz; ++i)
      data[dataLength++] = value[i]; // why backwards?
      // data[dataLength++] = value[sz-i]; // why backwards?
    while(dataLength & 3) // pad to 4 bytes
      data[dataLength++] = '\0';
    return index;
  }
protected:
  void addType(char type, size_t size){
    prefix[prefixLength++] = type;
    dataLength += size;
  }
  uint8_t add(char type, uint8_t* value){
    prefix[prefixLength++] = type;
    data[dataLength++] = value[3];
    data[dataLength++] = value[2];
    data[dataLength++] = value[1];
    data[dataLength++] = value[0];
    return dataLength-4;
  }
public:
  void set(uint8_t index, float value){
    set(index, (uint8_t*)&value);
  }
  void set(uint8_t index, int32_t value){
    set(index, (uint8_t*)&value);
  }
  void set(uint8_t index, uint8_t* value){
    data[index++] = value[3];
    data[index++] = value[2];
    data[index++] = value[1];
    data[index] = value[0];
  }
  void set(uint8_t index, uint8_t* value, size_t sz){
    for(size_t i=1; i<=sz; ++i)
      data[index++] = value[sz-i];
  }
};

#endif /* _OSC_MESSAGE_H_ */
