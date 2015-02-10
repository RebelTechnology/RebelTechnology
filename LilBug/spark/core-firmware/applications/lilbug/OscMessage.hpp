#ifndef _OSC_MESSAGE_H_
#define _OSC_MESSAGE_H_

#include <inttypes.h>

#define MAX_OSC_PREFIX_SIZE 32
#define MAX_OSC_DATA_SIZE 32
class OscMessage {
  uint8_t prefix[MAX_OSC_PREFIX_SIZE];
  uint8_t prefixLength;
  uint8_t data[MAX_OSC_DATA_SIZE];
  uint8_t dataLength;
public:
  void setAddress(char* a){
    prefixLength = strnlen(a, MAX_OSC_PREFIX_SIZE-5);
    memcpy(prefix, a, prefixLength+1);
    while(++prefixLength & 3) // pad to 4 bytes
      prefix[prefixLength-1] = '\0';
    prefix[prefixLength++] = ',';
  }
  uint8_t add(float value){
    return add('f', (uint8_t*)&value);
    // prefix[prefixLength++] = 'f';
    // set(dataLength, (uint8_t*)&value);
    // dataLength += 4;
    // return dataLength;
  }
  uint8_t add(int32_t value){
    return add('i', (uint8_t*)&value);
  }
  uint8_t add(char type, uint8_t* value, size_t sz){
    for(size_t i=1; i<=sz; ++i)
      data[dataLength++] = value[sz-i];
    return dataLength-sz;
  }
protected:
  uint8_t add(char type, uint8_t* value){
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
    data[index++] = value[0];
  }
  void set(uint8_t index, uint8_t* value, size_t sz){
    for(size_t i=1; i<=sz; ++i)
      data[index++] = value[sz-i];
  }
  void send(Print& out){
    // add zero padding to 
  }
};

#endif /* _OSC_MESSAGE_H_ */
