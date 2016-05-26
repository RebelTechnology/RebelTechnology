#include "StompBox.h"

#include "midi.h"
#include "gpio.h"
extern "C" uint32_t HAL_GetTick();

class PresetDisplayPatch : public Patch {
private:
  int preset;
  const int maxPreset = 11;
  int debounceDelay = 60;
  int size = 5;
  uint16_t x = 4;
  uint16_t y = 28;
  uint16_t bg = BLACK;
  uint16_t fg = WHITE;
public:
  PresetDisplayPatch(){
  }
  void reset(){
    preset = 1;
    // send PC to change to last program, E8: PC40
    midiSendPC(0, 40);
    // send CC 26 value 127 to turn remote control on: CC26/127
    midiSendCC(0, 26, 127);
    // send parameter A value 0 to select first preset: CC20/0
    midiSendCC(0, 20, preset);
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
      preset = min(maxPreset, preset+1);
    else if(dir < 0)
      preset = max(1, preset-1);
    midiSendCC(0, 20, preset*127/maxPreset);
  }
  void processAudio(AudioBuffer& samples){
    if(sw1()){
      screen.fill(fg);
      reset();
    }else{
      screen.fill(bg);
    }
    if(sw2())
      screen.fill(BLUE);
    char low = (preset % 10) +'0';
    char high = (preset/10)+'0';
    screen.drawRotatedChar(x, y, high, fg, bg, size);
    screen.drawRotatedChar(x+size*6+2, y, low, fg, bg, size);
  }
};
