#include <string.h>
// #include "device.h"
#include "StompBox.h"
#include "MidiStatus.h"
#include "OpenWareMidiControl.h"
// #include "MidiController.h"
// #include "CodecController.h"
// #include "ApplicationSettings.h"
// #include "FirmwareLoader.hpp"
// #include "ProgramManager.h"
#include "Prism.h"
#include "MidiHandler.h"

MidiHandler::MidiHandler(){
  // memset(midi_values, 0, NOF_PARAMETERS*sizeof(uint16_t));
}

void MidiHandler::handlePitchBend(uint8_t status, uint16_t value){
  // setParameter(PARAMETER_G, ((int16_t)value - 8192)>>1);
}

void MidiHandler::handleNoteOn(uint8_t status, uint8_t note, uint8_t velocity){
  // setButton(MIDI_NOTE_BUTTON+note, velocity<<5);
}

void MidiHandler::handleNoteOff(uint8_t status, uint8_t note, uint8_t velocity){
  // setButton(MIDI_NOTE_BUTTON+note, 0);
}

void MidiHandler::handleProgramChange(uint8_t status, uint8_t pid){
}

void MidiHandler::handleControlChange(uint8_t status, uint8_t cc, uint8_t value){
  if(getChannel(status) == channel){
    if(cc >= PATCH_PARAMETER_A && cc <= PATCH_PARAMETER_E)
      setParameterValue(PARAMETER_A+(cc-PATCH_PARAMETER_A), value*4096/127);
    else if(cc >= PATCH_PARAMETER_AA && cc <= PATCH_PARAMETER_BH)
      setParameterValue(PARAMETER_AA+(cc-PATCH_PARAMETER_AA), value*4096/127);
  }
  // switch(cc){
  // case PATCH_PARAMETER_E:    
}

void MidiHandler::handleSysEx(uint8_t* data, uint16_t size){}

int8_t MidiHandler::getChannel(uint8_t status){
  return status & MIDI_CHANNEL_MASK;
}
