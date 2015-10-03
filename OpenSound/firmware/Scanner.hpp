#include "wiced.h"

class Scanner {
public:
  bool start(){
    wiced_result_t ret = wiced_wifi_scan_networks(scan_handler, this);
    return ret == WICED_SUCCESS;
  }

  virtual void done(){
    Serial.println("scan complete");    
  }

  virtual void scan(char* ssid, int sec, int channel, int dBm, uint32_t maxRate){
    Serial.print("scan SSID: ");
    Serial.print((char*)ssid);
    Serial.print("\tsecurity: ");
    Serial.print(sec);
    Serial.print("\tchannel: ");
    Serial.print(channel);
    Serial.print("\tmax rate: ");
    Serial.print(maxRate);
    Serial.print("\tRSSI: ");
    Serial.print(dBm);
    Serial.println("dBm");
  }

  static wiced_result_t scan_handler(wiced_scan_handler_result_t* malloced_scan_result){
    Scanner* scanner = (Scanner*)malloced_scan_result->user_data;
    malloc_transfer_to_curr_thread( malloced_scan_result );
  // ScanEntry& entry = cmd.write_;
  // memset(&entry, 0, sizeof(entry));
  //  if(malloced_scan_result->status == WICED_SCAN_INCOMPLETE){
    if(malloced_scan_result->status != WICED_SCAN_ABORTED){
      wiced_scan_result_t& ap_details = malloced_scan_result->ap_details;
      // unsigned ssid_len = ap_details.SSID.length > 32 ? 32 : ap_details.SSID.length;
      scanner->scan((char*)ap_details.SSID.value, ap_details.security, ap_details.channel,
		    ap_details.signal_strength, ap_details.max_data_rate);
      /*
      memcpy(entry.ssid, ap_details.SSID.value, ssid_len);
      entry.ssid[ssid_len] = 0;
      entry.rssi = ap_details.signal_strength;
      entry.security = ap_details.security;
      entry.channel = ap_details.channel;
      entry.max_data_rate = ap_details.max_data_rate;
    }
  else
    {
      entry.done = 1;
      */
	       }
  //wiced_rtos_push_to_queue(&cmd.queue_, &entry, WICED_WAIT_FOREVER);
    free(malloced_scan_result);
    return WICED_SUCCESS;
  }
};