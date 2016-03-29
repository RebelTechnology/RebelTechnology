#include "StompBox.h"

class LissajouPatch : public Patch {
private:
  uint16_t colour;
  uint16_t fadesteps;
  uint16_t fg = WHITE;
public:
  LissajouPatch(){
    colour = WHITE;
    fadesteps = 1;
  }
  void processAudio(AudioBuffer& samples){
    float scale = max(0.1, min(encoder2*0.1+0.1, 10.0));
    screen.setTextColor(fg);
    screen.setTextSize(1);
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    int width = screen.getWidth()/2;
    int height = screen.getHeight()/2;
    int x = width * (getParameterValue(PARAMETER_A) + 0.5);
    int y = height * (getParameterValue(PARAMETER_B) + 0.5);
    screen.fade(fadesteps);
    screen.setCursor(26, 0);
    screen.print("Lissajou");
    screen.setCursor(6, 56);
    screen.print(scale);
    for(int i=0; i<samples.getSize(); ++i)
      screen.drawPixel(x+width*scale*left[i], y-height*scale*right[i], colour);
  }
};
