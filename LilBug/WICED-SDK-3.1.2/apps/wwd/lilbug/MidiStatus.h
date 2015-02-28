#ifndef _MidiStatus_h_
#define _MidiStatus_h_

enum MidiStatus {
  STATUS_BYTE			= 0x80,
  NOTE_OFF			= 0x80,
  NOTE_ON			= 0x90,
  POLY_KEY_PRESSURE		= 0xA0,
  CONTROL_CHANGE		= 0xB0,
  PROGRAM_CHANGE		= 0xC0,
  CHANNEL_PRESSURE		= 0xD0,
  PITCH_BEND_CHANGE		= 0xE0,
  SYSTEM_COMMON			= 0xF0,
  SYSEX				= 0xF0,
  TIME_CODE_QUARTER_FRAME       = 0xF1,
  SONG_POSITION_PTR             = 0xF2,
  SONG_SELECT                   = 0xF3,
  RESERVED_F4                   = 0xF4,
  RESERVED_F5                   = 0xF5,
  TUNE_REQUEST                  = 0xF6,
  SYSEX_EOX                     = 0xF7,		
  SYSTEM_REAL_TIME		= 0xF8,
  TIMING_CLOCK		        = 0xF8,
  RESERVED_F9                   = 0xF9,
  START                         = 0xFA,
  CONTINUE                      = 0xFB,
  STOP                          = 0xFC,
  RESERVED_FD                   = 0xFD,
  ACTIVE_SENSING                = 0xFE,
  SYSTEM_RESET                  = 0xFF,
  MIDI_CHANNEL_MASK		= 0x0F,
  MIDI_STATUS_MASK		= 0xF0
};

#endif /* _MidiStatus_h_ */
