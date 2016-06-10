#include "StompBox.h"

class DemoPatch : public Patch {
private:
  int step = 0;
  int wait = 0;
  float fps = 23.43750; // sampling rate / block size
public:
  DemoPatch(){
    // fps = getSampleRate() / getBlockSize();
  }
 void reset(){
    step = 0;
    wait = 0;
  }
  void processAudio(AudioBuffer& samples){
    if(wait > 0){
      wait--;
      return;
    }
    switch(step++){
    case 0:
      // draw some pixels
      screen.fill(WHITE);
      for(int i=0; i<31; i+=3)
	screen.setPixel(i*3, i*2, BLACK);
      break;
    case 1:
      screen.fill(MAGENTA);
      break;
    case 2:
      screen.fill(YELLOW);
      break;
    case 3:
      screen.fill(WHITE);
      break;
    case 4:
      screen.fill(BLACK);
      for (int16_t i=1; i<screen.getWidth(); i+=4)
	screen.drawLine(0, 0, i, screen.getHeight()-1, GREEN);
      break;
    case 5:
      for (int16_t i=1; i<screen.getHeight(); i+=4)
	screen.drawLine(0, 0, screen.getWidth()-1, i, BLUE);
      break;
    case 6:
      screen.fill(WHITE);
      screen.setTextColour(BLACK);
      screen.setTextSize(2);
      screen.setCursor(40, 30);
      screen.print("Hello, world!");
      break;
    case 7:
      screen.fill(BLACK);
      screen.setTextColour(WHITE);
      screen.setTextSize(1);
      screen.setCursor(0,0);
      screen.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer iaculis pellentesque sem, sit amet pulvinar ex placerat et.");
      break;
    default:
      step = 0;
      break;
    }
    wait = 2*fps;
  }
};
