#include "StompBox.h"

#include "midi.h"

static int currentPrograms[2] = {0};
static int parameterA = 0;
void midiReceivePC(uint8_t ch, uint8_t pc){
  if(ch < 2)
    currentPrograms[ch] = pc;
}

class PresetDisplayPatch : public Patch {
private:
public:
  PresetDisplayPatch(){
  }
  void reset(){
    // send PC to change to last program, E8: PC40
    midiSendPC(0, 40);
    // send CC 26 value 127 to turn remote control on: CC26/127
    midiSendCC(0, 26, 127);
    // send parameter A value 0 to select first preset: CC20/0
    midiSendCC(0, 20, 0);
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    // if(dir > 0)
    //   currentPrograms[1] = min(12, currentPrograms[1]+1);
    // else
    //   currentPrograms[1] = max(0, currentPrograms[1]-1);
    // midiSendPC(0, currentPrograms[1]);
    if(dir > 0)
      parameterA = min(12, parameterA+1);
    else if(dir < 0)
      parameterA = max(0, parameterA-1);
  }
  void processAudio(AudioBuffer& samples){
    screen.fill(WHITE);
    screen.setTextColour(BLACK);
    screen.setTextSize(1);
    screen.print(2, 2, "Theremin");
    screen.print(2, 12, "Bollards");
    screen.setCursor(2, 24);
    screen.print("PC ");
    screen.print(currentPrograms[0]);
    screen.print("/");
    screen.print(currentPrograms[1]);    
    screen.setCursor(2, 36);
    screen.print("CC ");
    screen.print(parameterA);
  }
};
