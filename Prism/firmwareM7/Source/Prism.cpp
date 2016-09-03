#include "mxconstants.h"
#include "SampleBuffer.hpp"
#include "ScreenBuffer.h"
#include "Prism.h"
#include "StompBox.h"
#include "stm32f7xx_hal.h"
#include "gpio.h"

bool sw1(){
  // return !getPin(SW1_GPIO_Port, SW1_Pin);
  return HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) != GPIO_PIN_SET;
  // HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) 
}

bool sw2(){
  return HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) != GPIO_PIN_SET;
  // return !getPin(SW2_GPIO_Port, SW2_Pin);
}

ScreenBuffer screen(OLED_WIDTH, OLED_HEIGHT);

// #include "ScopePatch.hpp"
// #include "LissajouPatch.hpp"
// #include "DemoPatch.hpp"
#include "SplashPatch.hpp"
#include "PresetDisplayPatch.hpp"

SampleBuffer samples;
// ScopePatch scope;
// LissajouPatch lissajou;
// DemoPatch demo;
// SplashPatch splash;
PresetDisplayPatch preset;
// why is last patch not enabling?
// add polar coordinates plotting
Patch* patches[] = {&preset};
#define PRESET_COUNT 2
// Patch* patches[] = {&scope, &lissajou, &splash};

extern uint16_t adc_values[4];

uint8_t currentPatch = 0;
void changePatch(uint8_t pid){
  if(pid < PRESET_COUNT && pid != currentPatch){
    currentPatch = pid;
    screen.fill(BLACK);
    patches[currentPatch]->reset();
  }
}

static int16_t encoders[2] = {INT16_MAX/2, INT16_MAX/2};
static int16_t deltas[2] = {0, 0};
void encoderChanged(uint8_t encoder, int32_t value){
  // // todo: debounce
  // // pass encoder change event to patch
  int32_t delta = value - encoders[encoder];
  encoders[encoder] = value;
  // if(encoder == 0){
  //   if(delta > 0){
  //     if(currentPatch == NOF_PATCHES-1)
  // 	changePatch(0);
  //     else
  // 	changePatch(currentPatch+1);
  //   }else if(delta < 0){
  //     if(currentPatch == 0)
  // 	changePatch(NOF_PATCHES-1);
  //     else
  // 	changePatch(currentPatch-1);
  //   }
  // }else if(encoder == 1){
  //   patches[currentPatch]->encoderChanged(encoder, delta);
  // }
  deltas[encoder] = delta;
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
  // setPin(SW1_GPIO_Port, SW1_Pin);
  // setPin(SW2_GPIO_Port, SW2_Pin);
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  screen.setBuffer(pv->pixels);
  if(deltas[0]){
    patches[currentPatch]->encoderChanged(0, deltas[0]);
    deltas[0] = 0;
  }
  if(deltas[1]){
    patches[currentPatch]->encoderChanged(1, deltas[1]);
    deltas[1] = 0;
  }
  
  patches[currentPatch]->processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
