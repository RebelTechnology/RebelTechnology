#ifndef __ConnectionManager_h__
#define __ConnectionManager_h__

//#include "ApplicationSettings.h"

#define CONNECTION_TIMEOUT 30000

class IPAddress;
class Print;

class ConnectionManager {
  enum OpenSoundMode {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    DISCONNECTING
  };

public:
  //  void init();
  ConnectionManager() : next_network(-1) {}

  bool connected();

  OpenSoundMode getMode(){
    return mode;
  }

  void setMode(OpenSoundMode m);

  void connect(int iface);
  void disconnect();
  void cancel();

  int getCurrentNetwork(){
    return current_network;
  }

  IPAddress getLocalIPAddress();
  IPAddress getSubnetMask();
  IPAddress getDefaultGateway();
  void printMacAddress(Print& out);
  bool isWiFiConnected();
  bool isIpConnected();
  const char* getSSID();
  int getRSSI();
  void setCredentials(const char* ssid, const char* password, const char* auth);
  void clearCredentials();
  int setAccessPointCredentials(const char* ssid, const char* passwd, const char* auth);
  void setAccessPointPrefix(const char* prefix);
private:
  const char* getAccessPointSSID();
  unsigned long lastEvent;
  OpenSoundMode mode = DISCONNECTED;
  int current_network, next_network;
};

extern ConnectionManager connection;

#endif /* __ConnectionManager_h__ */
