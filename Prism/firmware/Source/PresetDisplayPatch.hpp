#include "StompBox.h"

#include "midi.h"

static int currentPrograms[2] = {0};
void midiReceivePC(uint8_t ch, uint8_t pc){
  if(ch < 2)
    currentPrograms[ch] = pc;
}
// void midiReceiveCC(uint8_t ch, uint8_t cc, uint8_t value)

class PresetDisplayPatch : public Patch {
private:
public:
  PresetDisplayPatch(){
  }
  void encoderChanged(uint8_t encoder, int32_t dir){
    if(dir > 0)
      currentPrograms[1] = min(12, currentPrograms[1]+1);
    else
      currentPrograms[1] = max(0, currentPrograms[1]-1);
    midiSendPC(0, currentPrograms[1]);
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
  }
};
