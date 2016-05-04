class LissajouPatch : public Patch {
private:
  uint16_t colour = CYAN;
  uint16_t fadesteps = 1;
  uint16_t fg = WHITE;
  float scale = 1.0;
public:
  LissajouPatch(){}
  void encoderChanged(uint8_t encoder, int32_t dir){
    scale = min(4.0, max(0.1, scale+0.05*dir));
  }
  void processAudio(AudioBuffer& samples){
    screen.setTextColor(fg);
    screen.setTextSize(1);
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    int width = screen.getWidth()/2;
    int height = screen.getHeight()/2;
    int x = width;// * (getParameterValue(PARAMETER_A) + 0.5);
    int y = height;// * (getParameterValue(PARAMETER_B) + 0.5);
    screen.fade(fadesteps);
    screen.setCursor(26, 0);
    screen.print("Lissajou");
    screen.setCursor(0, 56);
    screen.print(scale);
    for(int i=0; i<samples.getSize(); ++i)
      screen.drawPixel(x+width*scale*left[i], y-height*scale*right[i], colour);
  }
};
