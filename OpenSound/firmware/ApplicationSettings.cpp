#include "ApplicationSettings.h"
#include "application.h"

#define APPLICATION_SETTINGS_ADDRESS 1024

void ApplicationSettings::init(){
  checksum = sizeof(*this) ^ 0xffffffff;
  if(settingsInFlash())
    loadFromFlash();
  else
    reset();
}

const char DEFAULT_ADDRESS[5][16] = { "/status", "/a/cv", "/b/cv", "/a/tr", "/b/tr" };
 
void ApplicationSettings::reset(){
  memcpy(inputAddress, DEFAULT_ADDRESS, sizeof(DEFAULT_ADDRESS));
  memcpy(outputAddress, DEFAULT_ADDRESS, sizeof(DEFAULT_ADDRESS));
}

bool ApplicationSettings::settingsInFlash(){
  uint32_t verify = EEPROM.read(APPLICATION_SETTINGS_ADDRESS) << 24;
  verify |= EEPROM.read(APPLICATION_SETTINGS_ADDRESS+1) << 16;
  verify |= EEPROM.read(APPLICATION_SETTINGS_ADDRESS+2) << 8;
  verify |= EEPROM.read(APPLICATION_SETTINGS_ADDRESS+3);
  return EEPROM.read(APPLICATION_SETTINGS_ADDRESS) == checksum;
}

void ApplicationSettings::loadFromFlash(){
  EEPROM.get(APPLICATION_SETTINGS_ADDRESS, *this);
  /*
  uint8_t* ptr = (uint8_t*)this;
  for(int i=0; i<sizeof(*this); ++i)
    *ptr = EEPROM.read(APPLICATION_SETTINGS_ADDRESS+i);
    */
}

void ApplicationSettings::saveToFlash(){
  EEPROM.put(APPLICATION_SETTINGS_ADDRESS, *this);
}

void ApplicationSettings::clearFlash(){
  EEPROM.write(APPLICATION_SETTINGS_ADDRESS, 0);
}
