#include "StompBox.h"

class LissajouPatch : public Patch {
private:
  uint16_t colour;
  uint16_t fadesteps;
public:
  LissajouPatch(){
    colour = WHITE;
    fadesteps = 1;
  }
  void processAudio(AudioBuffer& samples){
    if(getParameterValue(PARAMETER_A) > 0.1 && getParameterValue(PARAMETER_A) < 1.0)
      colour = getParameterValue(PARAMETER_A)*WHITE;
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    int height = screen.getHeight()/2;
    int width = screen.getWidth()/2;
    screen.fade(fadesteps);
    screen.setCursor(26, 0);
    screen.print("lissajou");
    // screen.setCursor(6, 56);
    // screen.print(colour);
    for(int i=0; i<samples.getSize(); ++i){
      screen.drawPixel(width+width*left[i], height+height*right[i], colour);
    }
  }
};
