#include "StompBox.h"
#include "errorhandlers.h"

class SplashPatch : public Patch {
private:
  float x = 0;
  float y = 0;
  float ratex = 0.1;
  float ratey = 0.1;
public:
  SplashPatch(){
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    if(encoder == 1){
      ratex += dir/50.0f;
    }else{
      ratey += dir/50.0f;
    }
  }
  void processAudio(AudioBuffer& samples){
    screen.clear();
    if(getErrorStatus() != NO_ERROR && getErrorMessage() != NULL){
      screen.setTextSize(1);
      screen.print(2, 32, getErrorMessage());
    }else if(!sw2()){
      screen.setTextSize(2);
      screen.print(x, y, "PLAYER");
    }
    // if(sw1()){
    //   screen.fill(WHITE);
    //   screen.setTextColour(BLACK);
    // }

    if(sw2()){
      uint8_t* buffer;
      buffer = (uint8_t*)EXTRAM;
      uint8_t* src = (uint8_t*)(float*)(samples.getSamples(LEFT_CHANNEL));
      memcpy(buffer, src, 256);
      int failures = 0; 
      for(int i=0; i<256; ++i)
	if(buffer[i] != src[i])
	  ++failures;
      screen.print(20, 20, "fail: ");
      screen.print(failures);
      setErrorMessage(NO_ERROR, NULL);
    }

    if(tr1())
      screen.print(20, 20, "TR1");
    if(tr2())
      screen.print(20, 40, "TR2");

    if(sw1())
      screen.print(60, 20, "SW1");
    if(sw2())
      screen.print(60, 40, "SW2");

    screen.setTextSize(1);
    // screen.print(20, screen.getHeight()-8, "Rebel Technology");
    screen.print(20, 0, "Rebel Technology");
    // animate
    x += ratex;
    if(x < 0){
      x = 0;
      ratex = +0.05;
    }else if(x > 58){
      x = 58;
      ratex = -0.04;      
    }
    y += ratey;
    if(y < 0){
      y = 0;
      ratey = +0.02;
    }else if(y > 48){
      y = 48;
      ratey = -0.03;
    }
  }
};
