#include <string.h>
#include "MidiHandler.h"

MidiHandler::MidiHandler(){
  // memset(midi_values, 0, NOF_PARAMETERS*sizeof(uint16_t));
}

void MidiHandler::handlePitchBend(uint8_t status, uint16_t value){
}

void MidiHandler::handleNoteOn(uint8_t status, uint8_t note, uint8_t velocity){
}

void MidiHandler::handleNoteOff(uint8_t status, uint8_t note, uint8_t velocity){
}

void MidiHandler::handleProgramChange(uint8_t status, uint8_t pid){
}

void MidiHandler::handleControlChange(uint8_t status, uint8_t cc, uint8_t value){
}

void MidiHandler::handleSysEx(uint8_t* data, uint16_t size){
}

void MidiHandler::handleSystemRealTime(uint8_t cmd){
}

void MidiHandler::handleSystemCommon(uint8_t cmd1, uint8_t cmd2){
}

void MidiHandler::handleSystemCommon(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3){
}

void MidiHandler::handleChannelPressure(uint8_t status, uint8_t value){
}

void MidiHandler::handlePolyKeyPressure(uint8_t status, uint8_t note, uint8_t value){
}