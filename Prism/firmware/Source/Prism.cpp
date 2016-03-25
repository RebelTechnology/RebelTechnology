#include "mxconstants.h"
#include "SampleBuffer.hpp"
#include "Prism.h"
#include "SSD1331.h"
#include "StompBox.h"

bool dobypass = true;
bool dowave = true;
bool dooffset = true;

extern SSD1331 screen;

extern volatile int32_t encoder1;
extern volatile int32_t encoder2;
extern uint16_t adc_values[4];
extern int32_t encoder3;

#include "ScopePatch.hpp"
#include "LissajouPatch.hpp"

SampleBuffer samples;
// ScopePatch patch;
LissajouPatch patch;
void setup(ProgramVector* pv){
#ifdef DEBUG_MEM
#ifdef ARM_CORTEX
  size_t before = xPortGetFreeHeapSize();
#endif
#endif
// #include "patch.cpp"
#ifdef DEBUG_MEM
  // todo xPortGetFreeHeapSize() before and after
  // extern uint32_t total_heap_used;
  // pv->heap_bytes_used = total_heap_used;
#ifdef ARM_CORTEX
  getProgramVector()->heap_bytes_used = before - xPortGetFreeHeapSize();
#endif
#endif
  // samples = new SampleBuffer(getBlockSize());
  // samples = new SampleBuffer();
  // patch = new ScopePatch();
}

void processBlock(ProgramVector* pv){
  samples.split(pv->audio_input, pv->audio_blocksize);
  patch.processAudio(samples);
  // processor.setParameterValues(pv->parameters);
  // processor.patch->processAudio(*buffer);
  samples.comb(pv->audio_output);
}
