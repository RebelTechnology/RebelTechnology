class ScopePatch : public Patch {
private:
  uint16_t bg = BLACK;
  uint16_t fg = WHITE;
  uint16_t buffer[2][96];
  int writepos = 0;
  int div = 1;
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
  ScopePatch(){
  }
  void reset(){
    for(int i=0; i<96; ++i){
      buffer[0][i] = 31;
      buffer[1][i] = 33;
    }
  }
  void processAudio(AudioBuffer& samples){
    screen.setTextColor(fg);
    screen.setTextSize(1);
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    float trig = 0.0f;
    int newdiv = encoder2/4;
    if(div != newdiv){
      div = newdiv;
      writepos = 0;
      reset();
    }
    int height = screen.getHeight()/2;
    int offset = 0;
    // fast forward to trigger
    // look for rising edge
    while(left[offset] > trig-0.0001 && offset < samples.getSize())
      offset++;
    while(left[offset] < trig && offset < samples.getSize())
      offset++;
    if(offset+screen.getWidth()*div < samples.getSize())
      writepos = 0;
    for(int i=offset; i<samples.getSize() && writepos < 96; i+=div){
      buffer[0][writepos] = height+height*left[i];
      buffer[1][writepos] = height+height*right[i]+2;
      writepos++;
    }
    screen.fillScreen(bg);
    screen.setCursor(35, 0);
    screen.print("Scope");
    screen.setCursor(0, 56);
    screen.print(div);
    int ly = buffer[0][0];
    int ry = buffer[1][0];
    for(int i=1; i<96; ++i){
      ly = drawVerticalLine(i, ly, buffer[0][i], RED);
      ry = drawVerticalLine(i, ry, buffer[1][i], GREEN);
    }
  }
};
