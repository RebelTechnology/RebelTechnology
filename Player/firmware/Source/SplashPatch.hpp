#include "StompBox.h"

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
      if(dir > 0)
	ratex *= 1.2;
      else
	ratex *= 0.8;
    }else{
      if(dir > 0)
	ratey *= 1.2;
      else
	ratey *= 0.8;
    }
  }
  void processAudio(AudioBuffer& samples){
    screen.clear();
    // if(sw1()){
    //   screen.fill(WHITE);
    //   screen.setTextColour(BLACK);
    // }
    screen.setTextSize(2);
    screen.print(x, y, "PLAYER");

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
