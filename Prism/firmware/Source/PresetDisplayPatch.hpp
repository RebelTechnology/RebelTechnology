#include "StompBox.h"

#include "midi.h"
extern "C" uint32_t HAL_GetTick();

class PresetDisplayPatch : public Patch {
private:
  int parameterA = 0;
  const int maxPreset = 24;
  int debounceDelay = 60;
  int size = 5;
  uint16_t x = 1;
  uint16_t y = 28;
  uint16_t bg = BLACK;
  uint16_t fg = WHITE;
public:
  PresetDisplayPatch(){
  }
  void reset(){
    parameterA = 0;
    // send PC to change to last program, E8: PC40
    midiSendPC(0, 40);
    // send CC 26 value 127 to turn remote control on: CC26/127
    midiSendCC(0, 26, 127);
    // send parameter A value 0 to select first preset: CC20/0
    midiSendCC(0, 20, parameterA);
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    // if(dir > 0)
    //   currentPrograms[1] = min(12, currentPrograms[1]+1);
    // else
    //   currentPrograms[1] = max(0, currentPrograms[1]-1);
    // midiSendPC(0, currentPrograms[1]);
    static int last = 0;
    int now = HAL_GetTick();
    if(now - last < debounceDelay)
      return;
    last = now;
    if(dir > 0)
      parameterA = min(maxPreset, parameterA+1);
    else if(dir < 0)
      parameterA = max(0, parameterA-1);
    midiSendCC(0, 20, parameterA);
  }
  void processAudio(AudioBuffer& samples){
    screen.fill(bg);
    char low = (parameterA % 10) +'0';
    char high = (parameterA/10)+'0';
    screen.drawRotatedChar(x, y, high, fg, bg, size);
    screen.drawRotatedChar(x+size*6+4, y, low, fg, bg, size);
  }
};
