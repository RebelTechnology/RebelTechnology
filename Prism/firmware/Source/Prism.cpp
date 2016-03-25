#include "mxconstants.h"
#include "SampleBuffer.hpp"
#include "Prism.h"
#include "SSD1331.h"
#include "StompBox.h"

bool dobypass = true;
bool dowave = true;
bool dooffset = true;

extern SSD1331 screen;

extern volatile int32_t encoder1;
extern volatile int32_t encoder2;
extern uint16_t adc_values[4];
extern int32_t encoder3;

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

class OffsetPatch : public Patch {
private:
public:
  void processAudio(AudioBuffer& samples){
    float* left = samples.getSamples(0);
    float* right = samples.getSamples(1);
    for(int i=0; i<samples.getSize(); ++i){
      left[i] += encoder2 / 256.0f - 0.5;
      right[i] += adc_values[0] / 4096.0f - 0.5;
    }
  }
};

SampleBuffer samples;
ScopePatch patch;
void setup(ProgramVector* pv){
#ifdef DEBUG_MEM
#ifdef ARM_CORTEX
  size_t before = xPortGetFreeHeapSize();
#endif
#endif
// #include "patch.cpp"
#ifdef DEBUG_MEM
  // todo xPortGetFreeHeapSize() before and after
  // extern uint32_t total_heap_used;
  // pv->heap_bytes_used = total_heap_used;
#ifdef ARM_CORTEX
  getProgramVector()->heap_bytes_used = before - xPortGetFreeHeapSize();
#endif
#endif
  // samples = new SampleBuffer(getBlockSize());
  // samples = new SampleBuffer();
  // patch = new ScopePatch();
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  patch.processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
