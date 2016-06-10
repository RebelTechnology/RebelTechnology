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
    screen.print(0, 56, "Rebel Technology");
    // animate
    // if(x < 24 && ratex > 0)
    //   x += ratex;
    // else if(x > 10 && ratex < 0)
    //   x += ratex;
    // else
    //   ratex *= -1;
    // if(y < 40 && ratey > 0)
    //   y += ratey;
    // else if(y > 10 && ratey < 0)
    //   y += ratey;
    // else
    //   ratey *= -1;
  }
};
