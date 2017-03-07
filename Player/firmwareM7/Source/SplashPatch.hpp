#include "StompBox.h"
#include "errorhandlers.h"
#include "stm32f7xx_hal.h"

bool tr1(){
  return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_SET;
}
bool tr2(){
  return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_SET;
}
bool sw1(){
  return HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) != GPIO_PIN_SET;
}
bool sw2(){
  return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) != GPIO_PIN_SET;
}

class SplashPatch : public Patch {
private:
  float x = 0;
  float y = 0;
  float ratex = 0.8;
  float ratey = 0.8;
public:
  SplashPatch(){
  }
  void encoderChanged(PatchParameterId pid, int32_t dir, uint16_t samples){
    if(pid == PARAMETER_A){
      ratex += dir/20.0f;
    }else{
      ratey -= dir/20.0f;
    }
  }
  void processAudio(AudioBuffer& samples){
    // animate
    x += ratex;
    if(x < 0){
      x = 0.1;
      ratex *= -0.9;
    }else if(x > 58){
      x = 58;
      ratex *= -0.9;
    }
    y += ratey;
    if(y < 0){
      y = 0.1;
      ratey *= -0.9;
    }else if(y > 48){
      y = 48;
      ratey *= -0.9;
    }
  }

  void processScreen(ScreenBuffer& screen){
    screen.clear();
    if(getErrorStatus() != NO_ERROR && getErrorMessage() != NULL){
      screen.setTextSize(1);
      screen.print(2, 32, getErrorMessage());
    }else if(!sw2()){
      screen.setTextSize(2);
      screen.print(x, y, "PLAYER");
    }
    // if(sw1()){
    //   screen.fill(WHITE);
    //   screen.setTextColour(BLACK);
    // }

    // FloatArray left = samples.getSamples(LEFT_CHANNEL);
    // FloatArray right = samples.getSamples(RIGHT_CHANNEL);

    if(sw2()){
      int size = 32;
      uint32_t* buffer = (uint32_t*)EXTRAM;
      uint32_t* src = (uint32_t*)screen.getBuffer();
      uint32_t dst[size];
      memcpy(dst, src, size*sizeof(uint32_t));
      memcpy(buffer, dst, size*sizeof(uint32_t));
      int failures = 0; 
      for(int i=0; i<size; ++i)
      	if(buffer[i] != dst[i])
      	  ++failures;
      screen.print(20, 56, "fail: ");
      screen.print(failures);
      setErrorMessage(NO_ERROR, NULL);
      // int fail = testram32(&hsdram1);
      // if(fail > 0){
      // 	screen.print(20, 20, "fail: ");
      // 	screen.print(fail);
      // }
    }else{
      screen.setTextSize(1);
      screen.print(20, 56, "cps: ");
      screen.print((int)(getProgramVector()->cycles_per_block)/getBlockSize());
    }

    if(tr1())
      screen.print(20, 20, "TR1");
    if(tr2())
      screen.print(20, 40, "TR2");

    if(sw1())
      screen.print(60, 20, "SW1");
    if(sw2())
      screen.print(60, 40, "SW2");

    screen.setTextSize(1);
    // screen.print(20, screen.getHeight()-8, "Rebel Technology");
    screen.print(20, 0, "Rebel Technology");
  }
};
