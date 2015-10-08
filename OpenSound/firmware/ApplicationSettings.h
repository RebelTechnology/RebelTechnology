#ifndef __ApplicationSettings_H__
#define __ApplicationSettings_H__

#include <inttypes.h>
#include "application.h"

#define NETWORK_SETTINGS_ADDRESS 0
#define ADDRESS_SETTINGS_ADDRESS 64
#define MAX_OSC_ADDRESS_LEN 16

template<int address>
class ApplicationSettings {
private:
  uint32_t checksum;
public:
  virtual void reset() = 0;
  void init(){
    checksum = sizeof(*this) ^ 0xffffffff;
    if(settingsInFlash())
      loadFromFlash();
    else
      reset();
  }
  bool settingsInFlash(){
    uint32_t verify = EEPROM.read(address) << 24;
    verify |= EEPROM.read(address+1) << 16;
    verify |= EEPROM.read(address+2) << 8;
    verify |= EEPROM.read(address+3);
    return EEPROM.read(address) == checksum;
  }
  void loadFromFlash(){
    EEPROM.get(address, *this);
  }
  void saveToFlash(){
    EEPROM.put(address, *this);
  }
  void clearFlash(){
    EEPROM.write(address, 0);
  }
};

class NetworkSettings : public ApplicationSettings<NETWORK_SETTINGS_ADDRESS> {
public:
  int localPort;
  int remotePort;
  bool broadcast;
  bool autoremote;
  IPAddress remoteIPAddress;
public:
  void reset();
  bool equals(const NetworkSettings& other){
    return memcmp(this, &other, sizeof(*this)) == 0;
  }
  bool hasChanged(){
    if(settingsInFlash()){
      NetworkSettings other;
      other.init();
      if(equals(other))
	return false;
    }
    return true;
  }
};

class AddressSettings : public ApplicationSettings<ADDRESS_SETTINGS_ADDRESS> {
public:
  char inputAddress[5][MAX_OSC_ADDRESS_LEN];
  char outputAddress[5][MAX_OSC_ADDRESS_LEN];
public:
  void reset();
  bool equals(const AddressSettings& other){
    return memcmp(this, &other, sizeof(*this)) == 0;
  }
  bool hasChanged(){
    if(settingsInFlash()){
      AddressSettings other;
      other.loadFromFlash();
      if(equals(other))
	return false;
    }
    return true;
  }
  const char* getInputAddress(int i){
    return inputAddress[i];
  }
  const char* getOutputAddress(int i){
    return outputAddress[i];
  }
  void setInputAddress(int i, const char* address){
    strncpy(inputAddress[i], address, MAX_OSC_ADDRESS_LEN);
    inputAddress[i][MAX_OSC_ADDRESS_LEN-1] = '\0';
  }
  void setOutputAddress(int i, const char* address){
    strncpy(outputAddress[i], address, MAX_OSC_ADDRESS_LEN);
    outputAddress[i][MAX_OSC_ADDRESS_LEN-1] = '\0';
  }
};

extern NetworkSettings networkSettings;
extern AddressSettings addressSettings;

#endif // __ApplicationSettings_H__
