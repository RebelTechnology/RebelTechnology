#include "ConnectionManager.h"
#include "opensound.h"
#include "application.h"
#include "wiced.h"
#include "dct.h"

// const int MAX_SSID_PREFIX_LEN = 25;
#define MAX_SSID_PREFIX_LEN 25

static WLanConfig wlan_config;
IPAddress ConnectionManager::getDefaultGateway(){
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucDefaultGateway);
  return ip;
}

int ConnectionManager::getRSSI(){
  return wlan_connected_rssi();
}

IPAddress ConnectionManager::getSubnetMask(){
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucSubnetMask);
  return ip;
}

const char* ConnectionManager::getSSID(){
  if(connection.getCurrentNetwork() == NETWORK_ACCESS_POINT){
    return getAccessPointSSID();
  }else{
    wlan_fetch_ipconfig(&wlan_config);
    return (const char*)wlan_config.uaSSID;
  }
}

void ConnectionManager::printMacAddress(Print& out){
  wlan_fetch_ipconfig(&wlan_config);
  for(int i=0; i<6; i++){
    if(i)out.write(':');      
    out.print(wlan_config.nw.uaMacAddr[i], HEX);
  }
}

IPAddress ConnectionManager::getLocalIPAddress(){
      /*
struct {
    uint16_t size;
    NetworkConfig nw;
    uint8_t uaSSID[33];
} WLanConfig;
struct {
    HAL_IPAddress aucIP;             // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucSubnetMask;     // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDefaultGateway; // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDHCPServer;     // byte 0 is MSB, byte 3 is LSB
    HAL_IPAddress aucDNSServer;      // byte 0 is MSB, byte 3 is LSB
    uint8_t uaMacAddr[6];
} NetworkConfig;
      */
  wlan_fetch_ipconfig(&wlan_config);
  IPAddress ip(wlan_config.nw.aucIP);
  return ip;
}

bool ConnectionManager::isWiFiConnected(){
  extern wiced_interface_t network;
  return wiced_network_is_up(network);
}

bool ConnectionManager::isIpConnected(){
  extern wiced_interface_t network;
  return wiced_network_is_ip_up(network);
}


bool ConnectionManager::connected(){
  unsigned long elapsed = millis() - lastEvent;
  bool connected = false;
  switch(mode){
  case DISCONNECTED:
    if(elapsed % 200 == 0)
      setLed(LED_YELLOW);
    else if(elapsed % 200 == 100)
      setLed(LED_GREEN);
    if(elapsed > 2000){
      if(current_network != next_network)
	current_network = next_network;
      if(current_network == -1)
	current_network = NETWORK_ACCESS_POINT;
      wlan_select_interface(current_network);
      if(current_network == NETWORK_ACCESS_POINT)
	wlan_start_ap();
      //	WiFi.startAccessPoint();
      wlan_connect_init();
      wlan_connect_finalize();
      setMode(CONNECTING);
      setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
    }
    break;
  case CONNECTING:
    if(elapsed % 2000 == 0)
      setLed(LED_NONE);
    else if(elapsed % 2000 == 1000)
      setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
    if(isIpConnected()){
      startServers();
      setMode(CONNECTED);
      setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
    }else if(elapsed > CONNECTION_TIMEOUT){
      cancel();
    }
    break;
  case CONNECTED:
    connected = true;
    break;
  case DISCONNECTING:
    if(elapsed % 1000 == 0)
      setLed(LED_NONE);
    else if(elapsed % 1000 == 800)
      setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
    if(!isWiFiConnected()){
      setMode(DISCONNECTED);
      setLed(LED_NONE);
    }
    break;
  }
  return connected;
}

void ConnectionManager::setMode(OpenSoundMode m){
  mode = m;
  lastEvent = millis();
  switch(mode){
  case DISCONNECTED:
    debugMessage("DISCONNECTED");
    break;
  case CONNECTING:
    debugMessage("CONNECTING");
    break;
  case CONNECTED:
    debugMessage("CONNECTED");
    break;
  case DISCONNECTING:
    debugMessage("DISCONNECTING");
    break;
  }
}

void ConnectionManager::connect(int iface){
  debugMessage("connect()");
  if(current_network != iface){
    if(getMode() == CONNECTED){
      disconnect();
    }else if(getMode() == CONNECTING){
      cancel();
    }
    next_network = iface;
  }
  setLed(iface == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);  
}

void ConnectionManager::disconnect(){
  debugMessage("disconnect()");
  if(mode == CONNECTED)
    stopServers();
  if(current_network == NETWORK_ACCESS_POINT)
    wlan_stop_ap();
  //    WiFi.stopAccessPoint();
  setMode(DISCONNECTING);
  setLed(LED_NONE);
}

void ConnectionManager::cancel(){
  debugMessage("cancel()");
  wlan_connect_cancel(false);
  setMode(DISCONNECTING);
  setLed(LED_NONE);
}

void ConnectionManager::setCredentials(const char* ssid, const char* passwd, const char* auth){
  debug << "setting credentials for ssid[" << ssid << "] auth[" << auth << "]\n";
  int sec = atol(auth);
  if(sec >= 0 && sec <= 3){
    //    WiFi.disconnect();
    WiFi.setCredentials(ssid, passwd, sec);
    //    WiFi.connect();
  }
}

void ConnectionManager::clearCredentials(){
  debugMessage("clearing credentials");
  WiFi.clearCredentials();
}


const char* ConnectionManager::getAccessPointSSID(){
  wiced_config_soft_ap_t* ap;
  wiced_result_t result = wiced_dct_read_lock((void**)&ap, WICED_FALSE, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t));
  int len = min(ap->SSID.length+1, min(33, MAX_SSID_PREFIX_LEN));
  memcpy(wlan_config.uaSSID, ap->SSID.value, len);
  wlan_config.uaSSID[len] = '\0';
  wiced_dct_read_unlock(&ap, WICED_FALSE);
  return result == WICED_SUCCESS ? (const char*)wlan_config.uaSSID : NULL;
}

int ConnectionManager::setAccessPointCredentials(const char* ssid, const char* passwd, const char* auth){
  //void setAccessPoint(char* prefix, char* auth){
  wiced_config_soft_ap_t ap;
  ap.SSID.length = strnlen(ssid, MAX_SSID_PREFIX_LEN);
  strncpy((char*)ap.SSID.value, ssid, ap.SSID.length);
  ap.channel = 11;
  ap.details_valid = WICED_TRUE;
  int sec = atol(auth);
  switch(sec){
  case 0: // Open
    ap.security = WICED_SECURITY_OPEN;
    break;
  case 1: // WEP
    ap.security = WICED_SECURITY_WEP_PSK;
    break;
  case 2: // WPA
    ap.security = WICED_SECURITY_WPA_TKIP_PSK;
    break;
  case 3: // WPA2
    ap.security = WICED_SECURITY_WPA2_AES_PSK;
    break;
  default:
    return false;
  }
  if(sec == 3 && ap.SSID.length < 8)
    return false; // password too short for WPA2
  ap.security_key_length = strnlen(passwd, SECURITY_KEY_SIZE);
  strncpy(ap.security_key, passwd, ap.security_key_length);
  wiced_result_t result = wiced_dct_write(&ap, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t));
  return result == WICED_SUCCESS;
}

void ConnectionManager::setAccessPointPrefix(const char* prefix){
  wiced_ssid_t ssid;
  ssid.length = strnlen(prefix, MAX_SSID_PREFIX_LEN);
  strncpy((char*)ssid.value, prefix, ssid.length);
  dct_write_app_data(&ssid, DCT_SSID_PREFIX_OFFSET, ssid.length+1);
}
