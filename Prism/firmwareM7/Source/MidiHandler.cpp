#include <string.h>
// #include "device.h"
// #include "owlcontrol.h"
// #include "MidiStatus.h"
// #include "OpenWareMidiControl.h"
// #include "MidiController.h"
// #include "CodecController.h"
// #include "ApplicationSettings.h"
// #include "FirmwareLoader.hpp"
// #include "ProgramManager.h"
// #include "Owl.h"
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
  // switch(cc){
  //   if(cc >= PATCH_PARAMETER_AA && cc <= PATCH_PARAMETER_BH)
  //     setParameter(PARAMETER_AA+(cc-PATCH_PARAMETER_AA), value<<5);
  //   break;
  // }
  // switch(cc){
  // case PATCH_PARAMETER_E:    
}

void MidiHandler::handleSysEx(uint8_t* data, uint16_t size){}
