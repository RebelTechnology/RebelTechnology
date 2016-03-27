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

SampleBuffer samples;
ScopePatch scope;
LissajouPatch lissajou;
Patch* patches[2] = {&scope, &lissajou};

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
}

volatile int currentPatch = 0;
void encoderChanged(int encoder, int32_t value){
  switch(encoder){
  case 0:
    if(value != encoder1)
      currentPatch = (currentPatch == 0) ? 1 : 0;
    // if(value > encoder_values[0]){
    //   if(currentPatch > 0)
    // 	currentPatch = 1;
    //   else
    // 	currentPatch = 0;
    // 	}else if(value < encoder_values[0])
    encoder1 = value;
    break;
  case 1:
    encoder2 = value;
    break;
  }  
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  patches[currentPatch]->processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
