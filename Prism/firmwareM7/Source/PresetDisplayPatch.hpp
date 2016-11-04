#include "StompBox.h"

#include "midi.h"
#include "gpio.h"
#include "OpenWareMidiControl.h"
extern "C" uint32_t HAL_GetTick();

#define MAX_PRESET     11
#define MANUAL_PRESET (MAX_PRESET+1)

class PresetDisplayPatch : public Patch {
private:
  const int SEND_RATE = 357;
  const int OWL_A_CH = 1;
  const int OWL_B_CH = 2;
  const int OWL_C_CH = 3;
  const int OWL_D_CH = 4;
  int counter;
  int preset0, preset1;
  int debounceDelay = 0;
  int size = 4; // 5;
#ifdef SSD1331
  uint16_t x = 14;
  uint16_t y = 8;
#else
  uint16_t x = 30;
  uint16_t y = 8;
#endif
  int16_t hspace = -10;
  int16_t vspace = 46;
  uint16_t bg = GREEN; // BLACK;
  uint16_t fg = WHITE;
public:
  PresetDisplayPatch(){
  }
  void reset(){
    preset0 = preset1 = 1;
    setParameterValue(PARAMETER_A, preset0*4096/MANUAL_PRESET+1);
    setParameterValue(PARAMETER_B, preset1*4096/MANUAL_PRESET+1);

    // // send PC to change to last program, E8: PC40
    // midiSendPC(OWL_A_CH, 40);
    // send CC 26 value 127 to turn remote control on: CC26/127
    midiSendCC(OWL_A_CH, PATCH_CONTROL, 127);
    // send parameter E value 0 to select first preset: CC24/0
    midiSendCC(OWL_A_CH, PATCH_PARAMETER_E, preset0);

    midiSendCC(OWL_B_CH, PATCH_CONTROL, 127);
    midiSendCC(OWL_B_CH, PATCH_PARAMETER_E, preset0);

    midiSendCC(OWL_C_CH, PATCH_CONTROL, 127);
    midiSendCC(OWL_C_CH, PATCH_PARAMETER_E, preset1);
    midiSendCC(OWL_D_CH, PATCH_CONTROL, 127);
    midiSendCC(OWL_D_CH, PATCH_PARAMETER_E, preset1);
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    // if(abs(dir) < 3)
    //   return;
    static int last = 0;
    int now = HAL_GetTick();
    if(now - last < debounceDelay)
      return;
    last = now;
    if(encoder == 0){
      if(dir > 2)
	preset0 = min(MAX_PRESET, preset0+1);
      else if(dir < 2)
	preset0 = max(1, preset0-1);
      midiSendCC(OWL_A_CH, PATCH_PARAMETER_E, preset0*127/MANUAL_PRESET);
      midiSendCC(OWL_B_CH, PATCH_PARAMETER_E, preset0*127/MANUAL_PRESET);
      setParameterValue(PARAMETER_A, preset0*4096/MANUAL_PRESET+1);
    }else if(encoder == 1){
      if(dir > 0)
	preset1 = min(MAX_PRESET, preset1+1);
      else if(dir < 0)
	preset1 = max(1, preset1-1);
      midiSendCC(OWL_C_CH, PATCH_PARAMETER_E, preset1*127/MANUAL_PRESET);
      midiSendCC(OWL_D_CH, PATCH_PARAMETER_E, preset1*127/MANUAL_PRESET);
      setParameterValue(PARAMETER_B, preset1*4096/MANUAL_PRESET+1);
    }
  }
  void draw(uint8_t x, uint8_t y, uint8_t preset){
    switch(preset){
    case MAX_PRESET:
      screen.setTextSize(2);
      screen.print(x, y, "Pass");
      break;
    case MANUAL_PRESET:
      screen.setTextSize(2);
      screen.print(x, y, "Man");
      break;
    default:
      char low = (preset % 10) +'0';
      char high = (preset/10)+'0';
      screen.drawRotatedChar(x, y, high, fg, bg, size);
      screen.drawRotatedChar(x+size*6+2, y, low, fg, bg, size);
      break;
    }
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

    preset0 = max(1, min(MANUAL_PRESET, getParameterValue(PARAMETER_A)*MANUAL_PRESET));
    preset1 = max(1, min(MANUAL_PRESET, getParameterValue(PARAMETER_B)*MANUAL_PRESET));

    draw(x, y, preset1);
    draw(x+hspace, y+vspace, preset0);

    if(counter++ == SEND_RATE){
      if(preset0 < MANUAL_PRESET)
	midiSendCC(OWL_A_CH, PATCH_PARAMETER_E, preset0*127/MANUAL_PRESET);
    }else if(counter == SEND_RATE*2){
      if(preset0 < MANUAL_PRESET)
	midiSendCC(OWL_B_CH, PATCH_PARAMETER_E, preset0*127/MANUAL_PRESET);
    }else if(counter == SEND_RATE*3){
      if(preset1 < MANUAL_PRESET)
	midiSendCC(OWL_C_CH, PATCH_PARAMETER_E, preset1*127/MANUAL_PRESET);
    }else if(counter >= SEND_RATE*4){
      if(preset1 < MANUAL_PRESET)
	midiSendCC(OWL_D_CH, PATCH_PARAMETER_E, preset1*127/MANUAL_PRESET);
      counter = 0;
    }
  }
};
