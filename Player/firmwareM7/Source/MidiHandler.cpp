#include <string.h>
#include "MidiHandler.h"
#include "MidiStatus.h"
#include "OpenWareMidiControl.h"
#include "FirmwareLoader.hpp"
#include "ApplicationSettings.h"
#include "errorhandlers.h"
#include "Codec.h"

static FirmwareLoader loader;
extern "C" {
  void encoderChanged(uint8_t encoder, int32_t value);
}

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
  if(channel != MIDI_OMNI_CHANNEL && channel != getChannel(status))
    return;
  if(pid == 0 && loader.isReady()){
    program.loadDynamicProgram(loader.getData(), loader.getSize());
    loader.clear();
    program.startProgram(true);
  }else{
    program.loadProgram(pid);
    program.resetProgram(true);
  }
}

void MidiHandler::handleControlChange(uint8_t status, uint8_t cc, uint8_t value){
  if(channel != MIDI_OMNI_CHANNEL && channel != getChannel(status))
    return;
  switch(cc){
  case 21: {
    static uint8_t last = 0;
    encoderChanged(0, (value-last)*3);
    last = value;
    break;
  }
  case 22: {
    static uint8_t last = 0;
    encoderChanged(1, (value-last)*3);
    last = value;
    break;
  }
  }
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

void MidiHandler::updateCodecSettings(){
  // codec.softMute(true);
  // codec.stop();
  // codec.init(settings);
  // codec.start();
  // program.resetProgram(true);
  // midi_set_input_channel(settings.midi_input_channel);
  // midi_set_output_channel(settings.midi_output_channel);
}

void MidiHandler::handleConfigurationCommand(uint8_t* data, uint16_t size){
  if(size < 4)
    return;
  char* p = (char*)data;
  int32_t value = strtol(p+2, NULL, 16);
  if(strncmp(SYSEX_CONFIGURATION_AUDIO_RATE, p, 2) == 0){
    settings.audio_samplingrate = value;
  }else if(strncmp(SYSEX_CONFIGURATION_AUDIO_BLOCKSIZE, p, 2) == 0){
    settings.audio_blocksize = value;
  }else if(strncmp(SYSEX_CONFIGURATION_AUDIO_BITDEPTH, p, 2) == 0){
    settings.audio_bitdepth = value;
  }else if(strncmp(SYSEX_CONFIGURATION_AUDIO_DATAFORMAT, p, 2) == 0){
    settings.audio_dataformat = value;
  }else if(strncmp(SYSEX_CONFIGURATION_CODEC_PROTOCOL, p, 2) == 0){
    settings.audio_codec_protocol = (I2SProtocol)value;
  }else if(strncmp(SYSEX_CONFIGURATION_CODEC_MASTER, p, 2) == 0){
    settings.audio_codec_master = value;
  }else if(strncmp(SYSEX_CONFIGURATION_CODEC_SWAP, p, 2) == 0){
    settings.audio_codec_swaplr = value;
  }else if(strncmp(SYSEX_CONFIGURATION_CODEC_BYPASS, p, 2) == 0){
    settings.audio_codec_bypass = value;
    codec.bypass(value);
  }else if(strncmp(SYSEX_CONFIGURATION_CODEC_HALFSPEED, p, 2) == 0){
    settings.audio_codec_halfspeed = value;
    // settings.audio_codec_halfspeed = (p[2] == '1' ? true : false);
  }else if(strncmp(SYSEX_CONFIGURATION_PC_BUTTON, p, 2) == 0){
    settings.program_change_button = value;
  }else if(strncmp(SYSEX_CONFIGURATION_INPUT_OFFSET, p, 2) == 0){
    settings.input_offset = value;
  }else if(strncmp(SYSEX_CONFIGURATION_INPUT_SCALAR, p, 2) == 0){
    settings.input_scalar = value;
  }else if(strncmp(SYSEX_CONFIGURATION_OUTPUT_OFFSET, p, 2) == 0){
    settings.output_offset = value;
  }else if(strncmp(SYSEX_CONFIGURATION_OUTPUT_SCALAR, p, 2) == 0){
    settings.output_scalar = value;
  }else if(strncmp(SYSEX_CONFIGURATION_MIDI_INPUT_CHANNEL, p, 2) == 0){
    settings.midi_input_channel = value;
  }else if(strncmp(SYSEX_CONFIGURATION_MIDI_OUTPUT_CHANNEL, p, 2) == 0){
    settings.midi_output_channel = value;
  }
  updateCodecSettings();
}

void MidiHandler::handleFirmwareUploadCommand(uint8_t* data, uint16_t size){
  int32_t ret = loader.handleFirmwareUpload(data, size);
  if(ret > 0){
    // firmware upload complete: wait for run or store
    // setLed(NONE); todo!
  }else if(ret == 0){
    // toggleLed(); todo!
  }// else error
}

void MidiHandler::handleFirmwareRunCommand(uint8_t* data, uint16_t size){
  if(loader.isReady()){
    program.loadDynamicProgram(loader.getData(), loader.getSize());
    loader.clear();
    program.startProgram(true);
  }else{
    error(PROGRAM_ERROR, "No program to run");
  }      
}

void MidiHandler::handleFirmwareFlashCommand(uint8_t* data, uint16_t size){
  if(loader.isReady() && size == 5){
    uint32_t checksum = loader.decodeInt(data);
    if(checksum == loader.getChecksum()){
      program.saveProgramToFlash(-1, loader.getData(), loader.getSize());
      loader.clear();
    }else{
      error(PROGRAM_ERROR, "Invalid FLASH checksum");
    }
  }else{
    error(PROGRAM_ERROR, "Invalid FLASH command");
  }
}

void MidiHandler::handleFirmwareStoreCommand(uint8_t* data, uint16_t size){
  if(loader.isReady() && size == 5){
    uint32_t slot = loader.decodeInt(data);
    // if(slot > 0 && slot <= MAX_NUMBER_OF_PATCHES+MAX_NUMBER_OF_RESOURCES){
    //   program.saveToFlash(slot, loader.getData(), loader.getSize());
    if(slot > 0 && slot <= MAX_NUMBER_OF_PATCHES){
      program.saveProgramToFlash(slot, loader.getData(), loader.getSize());
      loader.clear();
    }else{
      error(PROGRAM_ERROR, "Invalid program slot");
    }
  }else{
    error(PROGRAM_ERROR, "No program to store");
  }
}

void MidiHandler::handleSysEx(uint8_t* data, uint16_t size){
  if(size < 5 || data[1] != MIDI_SYSEX_MANUFACTURER)     
    return;
  if(data[2] != MIDI_SYSEX_DEVICE && data[2] != (MIDI_SYSEX_OWL_DEVICE | channel))
    // not for us
    return; // if channel == OMNI && data[2] == 0xff this message will also be processed
  switch(data[3]){
  case SYSEX_CONFIGURATION_COMMAND:
    handleConfigurationCommand(data+4, size-5);
    break;
  // case SYSEX_DFU_COMMAND:
  //   jump_to_bootloader();
  //   break;
  case SYSEX_FIRMWARE_UPLOAD:
    handleFirmwareUploadCommand(data+1, size-2);
    break;
  case SYSEX_FIRMWARE_RUN:
    handleFirmwareRunCommand(data+4, size-5);
    break;
  case SYSEX_FIRMWARE_STORE:
    handleFirmwareStoreCommand(data+4, size-5);
    break;
  case SYSEX_FIRMWARE_FLASH:
    handleFirmwareFlashCommand(data+4, size-5);
    break;
  default:
    error(PROGRAM_ERROR, "Invalid SysEx Message");
    break;
  }
}

int8_t MidiHandler::getChannel(uint8_t status){
  return status & MIDI_CHANNEL_MASK;
}
