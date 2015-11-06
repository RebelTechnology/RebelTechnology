#ifdef SERIAL_CONSOLE
#include "Scanner.hpp"
Scanner scanner;

void processSerial(){
  static bool unlocked = false;
  if(Serial.available() > 0){
    int c = Serial.read();
    if(!unlocked && c != '$')
      return;
    unlocked = true;
    switch(c){
    case '*':
      debugMessage("*: print local IP address");
      Serial.println(connection.getLocalIPAddress());
      break;
    case ':': {
      debugMessage("System Admin");
      while(Serial.available() < 1); // wait
      c = Serial.read();
      switch(c){
      case '?':
	debugMessage("?: print info");
	printInfo(Serial);
	break;
      case 's':
	debugMessage("s: scan wifi");
	scanner.start();
	break;
      case '+':
	debugMessage("+: add credentials");
	readCredentials(Serial);
	break;
      case '=':
	debugMessage("=: set access point credentials");
	readAccessPointCredentials(Serial);
	break;
      case 'f':
	debugMessage("f: factory reset");
	factoryReset();
	break;
      case '!':
	debugMessage("!: clear credentials");
	connection.clearCredentials();
	printInfo(Serial);
	break;
      case 'd':
	debugMessage("d: default credentials");
	WiFi.setCredentials(BISCUIT_WIFI_SSID, BISCUIT_WIFI_PASSWORD, WPA2);
	// connection.setCredentials(BISCUIT_WIFI_SSID, BISCUIT_WIFI_PASSWORD, BISCUIT_WIFI_SECURITY);
	printInfo(Serial);
	break;
      case 'a':
	debugMessage("a: access point connect");
	connection.connect(NETWORK_ACCESS_POINT);
	break;
      case 'w':
	debugMessage("w: wifi connect");
	connection.connect(NETWORK_LOCAL_WIFI);
	break;
      case '0':
	debugMessage("0: internal antenna");
	WiFi.selectAntenna(ANT_INTERNAL);
	break;
      case '1':
	debugMessage("1: auto antenna");
	WiFi.selectAntenna(ANT_AUTO);
	break;
      case '2':
	debugMessage("2: external antenna");
	WiFi.selectAntenna(ANT_EXTERNAL);
	break;
      case '<':
	debugMessage("<: stop servers");
	stopServers();
	break;
      case '>':
	debugMessage(">: start servers");
	startServers();
	break;
	/*
	  case '+':
	  debugMessage("+: activate wlan");
	  wlan_activate();
	  break;
	  case '-':
	  debugMessage("-: deactivate wlan");
	  wlan_deactivate();
	  break;
	  case '0':
	  debugMessage("0: select STA");
	  wlan_select_interface(NETWORK_LOCAL_WIFI);
	  break;
	  case '1':
	  debugMessage("1: select AP");
	  wlan_select_interface(NETWORK_ACCESS_POINT);
	  break;
	  case 'i':
	  debugMessage("i: connect init");
	  wlan_connect_init();
	  break;
	  case 'f':
	  debugMessage("f: connect finalise");
	  wlan_connect_finalize();
	  break;
	  case 'd':
	  debugMessage("d: disconnect");
	  wlan_disconnect_now();
	  break;
	  case '>':
	  debugMessage(">: start DNS");
	  WiFi.startDNS();
	  break;
	  case '<':
	  debugMessage("<: stop DNS");
	  WiFi.stopDNS();
	  break;
	  case 'o':
	  debugMessage("o: WiFi.on");
	  WiFi.on();
	  break;
	  case 'w':
	  debugMessage("w: WiFi.connect");
	  WiFi.connect();
	  break;
	  case 'x':
	  debugMessage("x: WiFi.disconnect");
	  WiFi.disconnect();
	  break;
	*/
      }
      break;
    }
    case '[':
      debugMessage("[: reset true");
      afe.reset(true);
      break;
    case ']':
      debugMessage("[: reset false");
      afe.reset(false);
      break;
    case '{':
      debugMessage("{: ls");
      afe.setSerialSpeed(9600);
      break;
    case '}':
      debugMessage("}: hs");
      afe.setSerialSpeed(115200);
      break;
    case 'r':
      debugMessage("r: run");
      afe.start();
      break;
    case 'R':
      debugMessage("R: stop");
      afe.stop();
      break;
    case '?':
      debugMessage("?: sensors");
      printSensors(Serial);
      break;
    case 'u':
      debugMessage("u: update");
      afe.update();
      afe.print(Serial);
      break;
    case 'h':
      debugMessage("h: toggle HP filter");
      static bool filter = false;
      filter = !filter;
      afe.setHpFilter(filter);
      break;
    case 'g':
      debugMessage("g: toggle gain");
      static bool gain = false;
      gain = !gain;
      afe.setCurrentGain(gain);
      break;
    case 't':
      debugMessage("t: toggle temperature sensor");
      static bool temperature = false;
      temperature = !temperature;
      afe.setTemperatureSensor(temperature);
      break;
    }
  }
}
#endif /* SERIAL_CONSOLE */
