#include "ConnectionManager.h"
#include "opensound.h"
#include "application.h"
#include "wiced.h"
#include "dct.h"

// const int MAX_SSID_PREFIX_LEN = 25;
#define MAX_SSID_PREFIX_LEN 25
#define MAX_FAILURES 3

ConnectionManager::ConnectionManager() 
  : mode(DISCONNECTED),
    current_network(-1), next_network(-1), 
    failures(2), status(0) {
  lastEvent = millis();
}

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

void ConnectionManager::updateLed(){
  setLed(current_network == NETWORK_LOCAL_WIFI ? LED_GREEN : LED_YELLOW);
}

#if 0
bool net_connect_sta(){
  wiced_result_t result;
  debugMessage("net_connect_sta");
  result = wiced_wlan_connectivity_init();
  if(result == WICED_SUCCESS){
    result = wiced_interface_up(WICED_STA_INTERFACE);
    if(!result)
      result = wiced_network_up(WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL);
    //    result = wiced_network_up(WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER, NULL);
  }else{
    debugMessage("wiced_wlan_connectivity_init FAILED");
  }
  return result == WICED_SUCCESS;
  /*
  result = wiced_interface_up(network);
  if(result == WICED_SUCCESS){
    result = wiced_network_up(network, WICED_USE_EXTERNAL_DHCP_SERVER, NULL);
  }
  */
}

extern "C" const wiced_ip_setting_t device_init_ip_settings;
bool net_connect_ap(){
  wiced_result_t result;
  debugMessage("net_connect_ap");
  result = wiced_wlan_connectivity_init();
  if(result == WICED_SUCCESS)
    result = wiced_network_up(WICED_AP_INTERFACE, WICED_USE_INTERNAL_DHCP_SERVER, 
			      &device_init_ip_settings );
  else
    debugMessage("wiced_wlan_connectivity_init FAILED");
  return result == WICED_SUCCESS;
}

bool net_disconnect(){
  wiced_result_t result;
  debugMessage("net_disconnect");
  result = (wiced_result_t)wlan_disconnect_now();
  HAL_WLAN_notify_disconnected();
  return result == WICED_SUCCESS;  
}
#else
bool net_disconnect(){
  WiFi.disconnect();
  return true;
}
#endif

static dns_redirector_t dns_redirector;
bool start_dns_redirector(){
  wiced_result_t result;
  debugMessage("wiced_dns_redirector_start");
  result = wiced_dns_redirector_start(&dns_redirector, WICED_AP_INTERFACE);
  return result == WICED_SUCCESS;
}

bool stop_dns_redirector(){
  wiced_result_t result;
  debugMessage("wiced_dns_redirector_stop");
  result = wiced_dns_redirector_stop(&dns_redirector);
  return result == WICED_SUCCESS;
}

bool ConnectionManager::start(ServiceType type){
  debug << "START[" << type << "]\r\n";
  if(getStatus(type))
    return false;
  bool result = false;
  switch(type){
  case WIFI:
#if 0
    if(current_network == NETWORK_LOCAL_WIFI)
      result = net_connect_sta();
    else if(current_network == NETWORK_ACCESS_POINT)
      result = net_connect_ap();
    wlan_select_interface(current_network);
    if(result)
      HAL_WLAN_notify_connected();
    HAL_WLAN_notify_dhcp(result);
#else
    if(!WiFi.hasCredentials())
      current_network = NETWORK_ACCESS_POINT;
    wlan_select_interface(current_network);
    WiFi.connect();
    result = true;
#endif
    break;
  case DNS_REDIRECT:
    result = start_dns_redirector();
    break;
  case SERVERS:
    startServers();
    result = true;
    break;
  }
  if(result)
    status |= type;
  else
    debugMessage("START FAILED");
  return result;
}

bool ConnectionManager::stop(ServiceType type){
  if(!getStatus(type))
    return false;
  bool result = false;
  switch(type){
  case WIFI:
    result = net_disconnect();
    break;
  case DNS_REDIRECT:
    result = stop_dns_redirector();
    break;
  case SERVERS:
    stopServers();
    result = true;
    break;
  }
  if(result)
    status &= ~type;
  else
    debugMessage("STOP FAILED");
  return result;
}

bool ConnectionManager::connected(){
  unsigned long elapsed = millis() - lastEvent;
  bool connected = false;
  switch(mode){
  case DISCONNECTED:
    if(elapsed % 160 == 0)
      setLed(LED_YELLOW);
    else if(elapsed % 160 == 80)
      setLed(LED_GREEN);
    if(elapsed > 2000){
      // transitioning from DISCONNECTED to CONNECTING
      if(next_network == -1)
	next_network = NETWORK_ACCESS_POINT;
      current_network = next_network;
      //      wlan_select_interface(current_network);
      start(WIFI);
      setMode(CONNECTING);
    }
    break;
  case CONNECTING:
    if(elapsed % 1200 == 0)
      setLed(LED_NONE);
    else if(elapsed % 1200 == 600)
      updateLed();
    if(isIpConnected()){
      // transitioning from CONNECTING to CONNECTED
      failures = 0;
      if(current_network == NETWORK_ACCESS_POINT)
	start(DNS_REDIRECT);
      start(SERVERS);
      setMode(CONNECTED);
      updateLed();
    }else if(elapsed > CONNECTION_TIMEOUT){
      cancel();
      if(++failures > MAX_FAILURES)
	next_network = -1;
    }
    break;
  case CONNECTED:
    connected = isIpConnected();
    if(!connected)
      setMode(DISCONNECTING);
    connected = true;
    break;
  case DISCONNECTING:
    if(elapsed % 800 == 0)
      setLed(LED_NONE);
    else if(elapsed % 800 == 600)
      updateLed();
    if(!isWiFiConnected()){
      // transitioning from DISCONNECTING to DISCONNECTED
      setMode(DISCONNECTED);
    }else if(elapsed > 2000){
      stop(SERVERS);
      stop(DNS_REDIRECT);
      stop(WIFI);
    }
    break;
  }
  return connected;
}

void ConnectionManager::setMode(OpenSoundMode m){
  mode = m;
  lastEvent = millis();
  setLed(LED_NONE);
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
  debug << "connect() to [" << iface << "] from [" << current_network << "]\r\n";
  if(current_network != iface){
    if(mode == CONNECTING)
      cancel();
    setMode(DISCONNECTING);
    next_network = iface;
  }
}

void ConnectionManager::disconnect(){
  debugMessage("disconnect()");
  setMode(DISCONNECTING);
}

void ConnectionManager::cancel(){
  debugMessage("wlan_connect_cancel()");
  wlan_connect_cancel(false);
  setMode(DISCONNECTING);
}

bool ConnectionManager::setCredentials(const char* ssid, const char* passwd, const char* auth){
  debug << "setting credentials for ssid[" << ssid << "] auth[" << auth << "]\r\n";
  WLanCredentials creds;
  memset(&creds, 0, sizeof(creds));
  creds.len = sizeof(creds);
  creds.ssid = ssid;
  creds.ssid_len = strlen(ssid);
  creds.password = passwd;
  creds.password_len = strlen(passwd);
  int sec = atol(auth);
  debug << "passwd[" << passwd << "] sec[" << sec << "]\r\n";
  switch(sec){
  case 0: // Open
    creds.security = WLAN_SEC_UNSEC;
    break;
  case 1: // WEP
    creds.security = WLAN_SEC_WEP;
    break;
  case 2: // WPA
    creds.security = WLAN_SEC_WPA;
    break;
  case 3: // WPA2
    creds.security = WLAN_SEC_WPA2;
    if(creds.password_len < 8){
      debugMessage("password too short for WPA2");
      return false;
    }
    break;
  default:
    return false;
  }
  // creds.cipher = 0: not set
  // creds.cipher = WLAN_CIPHER_AES_TKIP; // AES or TKIP
  debugMessage("wlan_set_credentials");
  wlan_set_credentials(&creds);
  system_notify_event(wifi_credentials_add, 0, &creds);
  return true;
  /*
  int sec = atol(auth);
  if(sec >= 0 && sec <= 3){
    //    WiFi.disconnect();
    WiFi.setCredentials(ssid, passwd, sec);
    //    WiFi.connect();
  }
  */
}

void ConnectionManager::clearCredentials(){
  debugMessage("clearing credentials");
  WiFi.clearCredentials();
}

const char* ConnectionManager::getAccessPointSSID(){
  wiced_config_soft_ap_t* ap;
  wiced_dct_read_lock((void**)&ap, WICED_FALSE, DCT_WIFI_CONFIG_SECTION, OFFSETOF(platform_dct_wifi_config_t, soft_ap_settings), sizeof(wiced_config_soft_ap_t));
  int len = min(ap->SSID.length+1, MAX_SSID_PREFIX_LEN);
  memcpy(wlan_config.uaSSID, ap->SSID.value, len);
  wlan_config.uaSSID[len-1] = '\0';
  wiced_dct_read_unlock(ap, WICED_FALSE);
  return (const char*)wlan_config.uaSSID;
}

bool ConnectionManager::setAccessPointCredentials(const char* ssid, const char* passwd, const char* auth){
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
  if(sec == 3 && ap.SSID.length < 8){
    debugMessage("password too short for WPA2");
    return false; // password too short for WPA2
  }
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

// #define HOSTNAME_SIZE 32
static char hostname[HOSTNAME_SIZE];
const char* ConnectionManager::getHostname(){  
  wiced_result_t ret = wiced_network_get_hostname(hostname, HOSTNAME_SIZE);
  hostname[HOSTNAME_SIZE-1] = '\0';
  return hostname;
}

void ConnectionManager::setHostname(const char* name){
  strncpy(hostname, name, HOSTNAME_SIZE);
  hostname[HOSTNAME_SIZE-1] = '\0';
  wiced_result_t ret = wiced_network_set_hostname(hostname);

}
