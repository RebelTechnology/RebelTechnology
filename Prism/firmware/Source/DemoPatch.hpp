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
  void processAudio(AudioBuffer& samples){
    if(wait > 0){
      wait--;
      return;
    }
    switch(step++){
    case 0:
      // draw some pixels
      screen.fillScreen(WHITE);
      for(int i=0; i<31; i+=3)
	screen.drawPixel(i*3, i*2, BLACK);
      break;
    case 1:
      screen.fillScreen(MAGENTA);
      break;
    case 2:
      screen.fillScreen(YELLOW);
      break;
    case 3:
      screen.fillScreen(WHITE);
      break;
    case 4:
      screen.fillScreen(BLACK);
      for (int16_t i=1; i<screen.width(); i+=4)
	screen.drawLine(0, 0, i, screen.height()-1, GREEN);
      break;
    case 5:
      for (int16_t i=1; i<screen.height(); i+=4)
	screen.drawLine(0, 0, screen.width()-1, i, BLUE);
      break;
    case 6:
      screen.fillScreen(WHITE);
      screen.setTextColor(BLACK);
      screen.setTextSize(2);
      screen.setCursor(40, 30);
      screen.print("Hello, world!");
      break;
    case 7:
      screen.fillScreen(BLACK);
      screen.setTextColor(WHITE);
      screen.setTextSize(1);
      screen.setCursor(0,0);
      screen.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer iaculis pellentesque sem, sit amet pulvinar ex placerat et.");
      break;
    default:
      step = 0;
      break;
    }
    wait = 10*fps;
  }
};
