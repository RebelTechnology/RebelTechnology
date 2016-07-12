#include "StompBox.h"

class SplashPatch : public Patch {
private:
  float x = 17;
  float y = 10;
  float ratex = 0.01;
  float ratey = 0.001;
public:
  SplashPatch(){
  }
  void processAudio(AudioBuffer& samples){
    screen.fill(WHITE);
    screen.setTextColour(BLACK);
    screen.setTextSize(2);
    screen.print(x, y, "PRISM");
    screen.setTextSize(1);
    screen.print(0, screen.getHeight()-8, "Rebel Technology");
    // animate
    x += ratex;
    if(x < 10){
      x = 10;
    }else if(x > 24){
      x = 24;
      ratex = -0.2;      
    }
    y += ratey;
    if(y < 10){
      y = 10;
      ratey = 0.2;
    }else if(y > 40){
      y = 40;
      ratey = -0.3;
    }
  }
};
