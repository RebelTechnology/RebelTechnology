#include "ApplicationSettings.h"
#include "application.h"

const char DEFAULT_ADDRESS[5][16] = { "/osm/status", "/osm/a/cv", "/osm/b/cv", "/osm/a/tr", "/osm/b/tr" };
#define UDP_REMOTE_PORT       9000
#define UDP_LOCAL_PORT        8000

void NetworkSettings::reset(){
  remotePort = UDP_REMOTE_PORT;
  localPort = UDP_LOCAL_PORT;
  autoremote = true;
  broadcast = true;
}
