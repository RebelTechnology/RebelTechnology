#include "StompBox.h"

class ScopePatch : public Patch {
private:
  uint16_t drawVerticalLine(uint16_t x, uint16_t y, uint16_t to, uint16_t c){
    if(y > to)
      drawVerticalLine(x, to, y, c);
    else
      do{
	screen.drawPixel(x, y++, c);
      }while(y < to);
    return to;
  }
public:
  void processAudio(AudioBuffer& samples){
    uint16_t bg = BLACK;
    // uint16_t bg = encoder1;
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    float trig = 0.0f;
    // int divs = samples.getSize()/screen.getWidth();
    int div = min(samples.getSize()/screen.getWidth(), max(1, encoder1));
    int height = screen.getHeight()/2;
    int offset = 0;
    // fast forward to trigger
    // look for rising edge
    while(left[offset] > trig-0.0001 && offset < samples.getSize())
      offset++;
    while(left[offset] < trig && offset < samples.getSize())
      offset++;
    if(offset+screen.getWidth() >= samples.getSize())
      return; // no trigger, don't update screen
    // todo: redraw only parameters ie divs
    screen.fillScreen(bg);
    screen.setCursor(40, 0);
    screen.print("scope");
    screen.setCursor(6, 56);
    screen.print(div);
    int ly = height+height*left[offset];
    int ry = height+height*right[offset];
    int x=0;
    for(int i=offset; i<samples.getSize() && x < screen.getWidth(); i+=div){
      ly = drawVerticalLine(x, ly, height+height*left[i], RED);
      ry = drawVerticalLine(x, ry, height+height*right[i], GREEN);
      x++;
    }
  }
};
