#include "StompBox.h"

class SplashPatch : public Patch {
private:
  float x = 14;
  float y = 10;
  float ratex = 0.01;
  float ratey = 0.001;
public:
  SplashPatch(){
  }
  void processAudio(AudioBuffer& samples){
    screen.fillScreen(WHITE);
    screen.setTextColor(BLACK);
    screen.setTextSize(2);
    screen.setCursor(x, y);
    screen.print("PRISM");
    screen.setTextSize(1);
    screen.setCursor(0, 56);
    screen.print("Rebel Technology");
    // animate
    if(x < 24 && ratex > 0)
      x += ratex;
    else if(x > 10 && ratex < 0)
      x += ratex;
    else
      ratex *= -1;
    if(y < 40 && ratey > 0)
      y += ratey;
    else if(y > 10 && ratey < 0)
      y += ratey;
    else
      ratey *= -1;
  }
};
