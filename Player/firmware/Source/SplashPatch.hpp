#include "StompBox.h"

class SplashPatch : public Patch {
private:
  float x = 17;
  float y = 10;
  float ratex = 0.01;
  float ratey = 0.01;
public:
  SplashPatch(){
  }
  void processAudio(AudioBuffer& samples){
    screen.clear();
    // screen.fill(WHITE);
    // screen.setTextColour(BLACK);
    screen.setTextSize(2);
    screen.print(x, y, "PLAYER");
    screen.setTextSize(1);
    screen.print(20, screen.getHeight()-8, "Rebel Technology");
    // animate
    x += ratex;
    if(x < 10){
      x = 10;
      ratex = +0.05;
    }else if(x > 60){
      x = 60;
      ratex = -0.04;      
    }
    y += ratey;
    if(y < 5){
      y = 5;
      ratey = +0.02;
    }else if(y > 48){
      y = 48;
      ratey = -0.03;
    }
  }
};
