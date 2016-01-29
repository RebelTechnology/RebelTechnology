#ifndef _OSC_MESSAGE_H_
#define _OSC_MESSAGE_H_

#include <inttypes.h>
#include <string.h>

#define OSC_MESSAGE_MAX_PREFIX_SIZE 32
#define OSC_MESSAGE_MAX_DATA_SIZE 32
class OscMessage {
  uint8_t prefix[OSC_MESSAGE_MAX_PREFIX_SIZE];
  uint8_t prefixLength;
  uint8_t data[OSC_MESSAGE_MAX_DATA_SIZE];
  uint8_t dataLength;
public:
  OscMessage(char* a) : prefixLength(0), dataLength(0){
    setAddress(a);
  }
  void setAddress(char* a){
    prefixLength = strnlen(a, OSC_MESSAGE_MAX_PREFIX_SIZE-5)+1;
    memcpy(prefix, a, prefixLength);
    while(prefixLength & 3) // pad to 4 bytes
      prefix[prefixLength++] = '\0';
    prefix[prefixLength++] = ',';
  }

  void send(Print& out){
    out.write(prefix, prefixLength);
    // add zero padding
    switch((prefixLength) & 3){
    case 0:
      out.write((uint8_t)'\0');
    case 1:
      out.write((uint8_t)'\0');
    case 2:
      out.write((uint8_t)'\0');
    case 3:
      out.write((uint8_t)'\0');
    }
    out.write(data, dataLength);
  }

  // void send();

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
