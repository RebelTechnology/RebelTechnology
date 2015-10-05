#ifndef __ApplicationSettings_H__
#define __ApplicationSettings_H__

#include <inttypes.h>

class ApplicationSettings {
public:
  uint32_t checksum;
  char inputAddress[5][16];
  char outputAddress[5][16];

public:
  void init();
  void reset();
  bool settingsInFlash();
  void loadFromFlash();
  void saveToFlash();
  void clearFlash();
};

extern ApplicationSettings settings;

#endif // __ApplicationSettings_H__
