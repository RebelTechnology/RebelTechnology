#include "wiced.h"

class Scanner {
public:
  void scan(){
    wiced_result_t result = wiced_wifi_scan_networks(scan_handler, this);
  }

static wiced_result_t scan_handler(wiced_scan_handler_result_t* malloced_scan_result){
  Scanner* scanner = (Scanner*)malloced_scan_result->user_data;
  malloc_transfer_to_curr_thread( malloced_scan_result );
  // ScanEntry& entry = cmd.write_;
  // memset(&entry, 0, sizeof(entry));
  if(malloced_scan_result->status == WICED_SCAN_INCOMPLETE){
      wiced_scan_result_t& ap_details = malloced_scan_result->ap_details;
      unsigned ssid_len = ap_details.SSID.length > 32 ? 32 : ap_details.SSID.length;
      Serial.print("scan SSID: ");
      Serial.print((char*)ap_details.SSID.value);
      Serial.print("\tsecurity: ");
      Serial.print(ap_details.security);
      Serial.print("\tchannel: ");
      Serial.print(ap_details.channel);
      Serial.print("\trate: ");
      Serial.print(ap_details.max_data_rate);
      Serial.print("\tRSSI: ");
      Serial.print(ap_details.signal_strength);
      Serial.println();
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
