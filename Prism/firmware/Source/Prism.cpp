#include "mxconstants.h"
#include "SampleBuffer.hpp"
#include "Prism.h"
#include "SSD1331.h"
#include "StompBox.h"

bool dobypass = true;
bool dowave = true;
bool dooffset = true;

extern SSD1331 screen;

volatile int32_t encoder1;
volatile int32_t encoder2;
extern uint16_t adc_values[4];

#include "ScopePatch.hpp"
#include "LissajouPatch.hpp"
#include "DemoPatch.hpp"
#include "SplashPatch.hpp"

SampleBuffer samples;
ScopePatch scope;
LissajouPatch lissajou;
DemoPatch demo;
SplashPatch splash;
Patch* patches[4] = {&scope, &lissajou, &splash, &demo};

uint8_t currentPatch = 1;
void changePatch(uint8_t pid){
  if(pid < 3 && pid != currentPatch){
    currentPatch = pid;
    screen.fillScreen(BLACK);
    patches[currentPatch]->reset();
  }
}

void encoderChanged(int encoder, int32_t value){
  switch(encoder){
  case 0:
    if(value > encoder1){
      if(currentPatch == 3)
	changePatch(0);
      else
	changePatch(currentPatch+1);
    }else if(value < encoder1){
      if(currentPatch == 0)
	changePatch(3);
      else
	changePatch(currentPatch-1);
    }
    encoder1 = value;
    break;
  case 1:
    if(value > 64)
      encoderReset(encoder, 64);
    else if(value < 4)
      encoderReset(encoder, 4);
    else
      encoder2 = value;
    break;
  }  
}

void setup(ProgramVector* pv){
  pv->checksum = sizeof(ProgramVector);
  pv->hardware_version = PRISM_HARDWARE;
  pv->parameters_size = 2;
  pv->parameters = adc_values;
  pv->audio_bitdepth = 24;
  pv->audio_samplingrate = 48000;
  pv->buttons = 0;
  pv->registerPatch = NULL;
  pv->registerPatchParameter = NULL;
  pv->cycles_per_block = 0;
  pv->heap_bytes_used = 0;
  pv->programReady = NULL;
  pv->programStatus = NULL;
  pv->serviceCall = NULL;
  pv->message = NULL;

#ifdef DEBUG_MEM
#ifdef ARM_CORTEX
  size_t before = xPortGetFreeHeapSize();
#endif
#endif
// #include "patch.cpp"
#ifdef DEBUG_MEM
#ifdef ARM_CORTEX
  pv->heap_bytes_used = before - xPortGetFreeHeapSize();
#endif
#endif

  encoderReset(1, 4);
  changePatch(0);
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  patches[currentPatch]->processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
