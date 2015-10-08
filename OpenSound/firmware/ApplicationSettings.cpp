#include "ApplicationSettings.h"
#include "application.h"

const char DEFAULT_ADDRESS[5][16] = { "/status", "/a/cv", "/b/cv", "/a/tr", "/b/tr" };
#define UDP_REMOTE_PORT       9000
#define UDP_LOCAL_PORT        8000

void NetworkSettings::reset(){
  remotePort = UDP_REMOTE_PORT;
  localPort = UDP_LOCAL_PORT;
  autoremote = true;
  broadcast = true;
}

void AddressSettings::reset(){
  memcpy(inputAddress, DEFAULT_ADDRESS, sizeof(DEFAULT_ADDRESS));
  memcpy(outputAddress, DEFAULT_ADDRESS, sizeof(DEFAULT_ADDRESS));
}

