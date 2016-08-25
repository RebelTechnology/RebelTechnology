#include "StompBox.h"

#include "midi.h"
#include "gpio.h"
#include "OpenWareMidiControl.h"
extern "C" uint32_t HAL_GetTick();

class PresetDisplayPatch : public Patch {
private:
  int counter;
  const int SEND_RATE = 1024;
  int preset0, preset1;
  const int maxPreset = 11;
  int debounceDelay = 0;
  int size = 4; // 5;
  uint16_t x = 14;
  uint16_t y = 8; //28;
  int16_t hspace = -10;
  int16_t vspace = 46;
  uint16_t bg = GREEN; // BLACK;
  uint16_t fg = WHITE;
public:
  PresetDisplayPatch(){
  }
  void reset(){
    preset0 = preset1 = 1;
    // send PC to change to last program, E8: PC40
    midiSendPC(0, 40);
    // send CC 26 value 127 to turn remote control on: CC26/127
    midiSendCC(0, PATCH_CONTROL, 127);
    // send parameter E value 0 to select first preset: CC24/0
    midiSendCC(0, PATCH_PARAMETER_E, preset0);

    midiSendPC(1, 40);
    midiSendCC(1, PATCH_CONTROL, 127);
    midiSendCC(1, PATCH_PARAMETER_E, preset1);
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    if(abs(dir) < 3)
      return;
    static int last = 0;
    int now = HAL_GetTick();
    if(now - last < debounceDelay)
      return;
    last = now;
    if(encoder == 0){
      if(dir > 0)
	preset0 = min(maxPreset, preset0+1);
      else if(dir < 0)
	preset0 = max(1, preset0-1);
      // midiSendCC(0, PATCH_CONTROL, 127);
      midiSendCC(0, PATCH_PARAMETER_E, preset0*127/maxPreset);
    }else if(encoder == 1){
      if(dir > 0)
	preset1 = min(maxPreset, preset1+1);
      else if(dir < 0)
	preset1 = max(1, preset1-1);
      // midiSendCC(1, PATCH_CONTROL, 127);
      midiSendCC(1, PATCH_PARAMETER_E, preset1*127/maxPreset);
    }
  }
  void draw(uint8_t x, uint8_t y, uint8_t preset){
    char low = (preset % 10) +'0';
    char high = (preset/10)+'0';
    screen.drawRotatedChar(x, y, high, fg, bg, size);
    screen.drawRotatedChar(x+size*6+2, y, low, fg, bg, size);
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
    draw(x, y, preset1);
    draw(x+hspace, y+vspace, preset0);
    if(counter++ == 1000){
      midiSendCC(0, PATCH_PARAMETER_E, preset0*127/maxPreset);
    }else if(counter >= 2000){
      midiSendCC(1, PATCH_PARAMETER_E, preset1*127/maxPreset);
      counter = 0;
    }
  }
};
