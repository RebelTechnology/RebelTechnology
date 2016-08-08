#include "midi.h"
#include "serial.h"
#include "MidiReader.hpp"
#include "MidiWriter.hpp"
#include "stm32f1xx_hal.h"

static uint8_t rxbuffer[256];
MidiReader reader(rxbuffer, 256);
MidiWriter writer(0);

void midi_setup(){
  serial_setup(31250);
}

void midi_send_cc(uint8_t ch, uint8_t cc, uint8_t value){
  writer.controlChange(ch, cc, value);
}
