#include "StompBox.h"
#include "errorhandlers.h"
#include "stm32f7xx_hal.h"

class ProgressPatch : public Patch {
private:
public:
  ProgressPatch(){
  }
  void processAudio(AudioBuffer& samples){
  }

  void processScreen(ScreenBuffer& screen){
    screen.clear();
    screen.setTextSize(1);
    screen.print(20, 0, "Rebel Technology");
    if(getErrorStatus() != NO_ERROR && getErrorMessage() != NULL){
      screen.print(2, 12, getErrorMessage());
    }
    screen.setTextSize(3);
    screen.setCursor(30, 20);
    screen.print((int)(getParameterValue(PARAMETER_A)*100));
    screen.print("%");

    screen.setTextSize(1);
    screen.setCursor(0, 56);
    screen.print((int)(getParameterValue(PARAMETER_B)*4096));
    screen.setCursor(32, 56);
    screen.print((int)(getParameterValue(PARAMETER_C)*4096));
    screen.print(" / ");
    screen.print((int)(getParameterValue(PARAMETER_D)*4096));
  }
};
