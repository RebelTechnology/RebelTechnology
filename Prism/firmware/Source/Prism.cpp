#include "mxconstants.h"
#include "SampleBuffer.hpp"
#include "ScreenBuffer.h"
#include "Prism.h"
#include "StompBox.h"

ScreenBuffer screen(OLED_WIDTH, OLED_HEIGHT);

// #include "ScopePatch.hpp"
// #include "LissajouPatch.hpp"
// #include "DemoPatch.hpp"
// #include "SplashPatch.hpp"
#include "PresetDisplayPatch.hpp"

SampleBuffer samples;
// ScopePatch scope;
// LissajouPatch lissajou;
// DemoPatch demo;
// SplashPatch splash;
PresetDisplayPatch preset;
// why is last patch not enabling?
// add polar coordinates plotting
Patch* patches[1] = {&preset};
// Patch* patches[1] = {&scope, &lissajou, &preset, &splash};

extern uint16_t adc_values[4];

uint8_t currentPatch = 0;
void changePatch(uint8_t pid){
  if(pid < 3 && pid != currentPatch){
    currentPatch = pid;
    screen.fill(WHITE);
    patches[currentPatch]->reset();
  }
}

void encoderChanged(uint8_t encoder, int32_t value){
  static int16_t encoders[2] = {INT16_MAX/2, INT16_MAX/2};
  // todo: debounce
  // if(encoder == 1){
    // pass encoder change event to patch
    int32_t delta = value - encoders[encoder];
    patches[currentPatch]->encoderChanged(encoder, delta);
    encoders[encoder] = value;
  // }
  // if(encoder == 0){
  //   if(value > encoders[encoder]){
  //     if(currentPatch == 3)
  // 	changePatch(0);
  //     else
  // 	changePatch(currentPatch+1);
  //   }else if(value < encoders[encoder]){
  //     if(currentPatch == 0)
  // 	changePatch(3);
  //     else
  // 	changePatch(currentPatch-1);
  //   }
  //   encoders[encoder] = value;
  // }
}

void setup(ProgramVector* pv){
  patches[currentPatch]->reset();
// #ifdef DEBUG_MEM
// #ifdef ARM_CORTEX
//   size_t before = xPortGetFreeHeapSize();
// #endif
// #endif
// #include "patch.cpp"
// #ifdef DEBUG_MEM
// #ifdef ARM_CORTEX
//   pv->heap_bytes_used = before - xPortGetFreeHeapSize();
// #endif
// #endif
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  screen.setBuffer(pv->pixels);
  patches[currentPatch]->processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
