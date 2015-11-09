#include "ApplicationSettings.h"
#include "application.h"

void NetworkSettings::reset(){
  localPort = 80;
  remotePort = 80;
  // http://requestb.in/vbkhorvb?inspect
  //remoteHost = "requestb.in";
  //remotePath = "/vbkhorvb";
  remoteHost = "biscuitwebservice.azurewebsites.net";
  remotePath = "/api/outlets/D5BFAADC-31B2-43AD-91E7-20F439C54D01";

  resendPeriod = 10*60*1000;
}
