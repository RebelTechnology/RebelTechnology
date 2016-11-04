#ifndef __StompBox_h__
#define __StompBox_h__

#include "basicmaths.h"
#include "FloatArray.h"
class PatchProcessor;

enum PatchParameterId {
  PARAMETER_A,
  PARAMETER_B,
  PARAMETER_C,
  PARAMETER_D,
  PARAMETER_E,
  PARAMETER_F,
  PARAMETER_G,
  PARAMETER_H,

  PARAMETER_AA,
  PARAMETER_AB,
  PARAMETER_AC,
  PARAMETER_AD,
  PARAMETER_AE,
  PARAMETER_AF,
  PARAMETER_AG,
  PARAMETER_AH,

  PARAMETER_BA,
  PARAMETER_BB,
  PARAMETER_BC,
  PARAMETER_BD,
  PARAMETER_BE,
  PARAMETER_BF,
  PARAMETER_BG,
  PARAMETER_BH,

  PARAMETER_CA,
  PARAMETER_CB,
  PARAMETER_CC,
  PARAMETER_CD,
  PARAMETER_CE,
  PARAMETER_CF,
  PARAMETER_CG,
  PARAMETER_CH,

  PARAMETER_DA,
  PARAMETER_DB,
  PARAMETER_DC,
  PARAMETER_DD,
  PARAMETER_DE,
  PARAMETER_DF,
  PARAMETER_DG,
  PARAMETER_DH,
};

enum PatchButtonId {
  BYPASS_BUTTON,
  PUSHBUTTON,
  GREEN_BUTTON,
  RED_BUTTON,
  MIDI_NOTE_BUTTON = 0x80 // values over 127 are mapped to note numbers
};

enum PatchChannelId {
  LEFT_CHANNEL = 0,
  RIGHT_CHANNEL = 1
};

class AudioBuffer {
public:
  virtual ~AudioBuffer();
  virtual FloatArray getSamples(int channel) = 0;
  virtual int getChannels() = 0;
  virtual int getSize() = 0;
  virtual void clear() = 0;
  static AudioBuffer* create(int channels, int samples);
};

class Patch {
public:
  Patch();
  virtual ~Patch();
  void registerParameter(PatchParameterId pid, const char* name, const char* description = "");
  float getParameterValue(PatchParameterId pid);
  bool isButtonPressed(PatchButtonId bid);
  int getSamplesSinceButtonPressed(PatchButtonId bid);
  void setButton(PatchButtonId bid, bool pressed);
  int getBlockSize();
  double getSampleRate();
  AudioBuffer* createMemoryBuffer(int channels, int samples);
  float getElapsedBlockTime();
  int getElapsedCycles();
public:
  virtual void reset(){};
  virtual void encoderChanged(uint8_t encoder, int32_t dir){};
  /* virtual void processVideo(VideoBuffer&); */
  virtual void processAudio(AudioBuffer&) = 0;
private:
  PatchProcessor* processor;
};

#endif // __StompBox_h__
