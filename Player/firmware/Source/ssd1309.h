
void Graphics::zero() {
  /* uint8_t cmd[] = { 0x15, 0, OLED_MW, 0x75, 0, OLED_MH }; */
  /* writeCommands(cmd, sizeof(cmd)); */
}

void Graphics::chipInit() {
  static const uint8_t initSequence[] = {
    0xfd, 0x12, // Command lock
    0xae, // Display off
    0xd5, 0xa0, // Clock divide ratio / Oscillator Frequency
    0xa8, 0x3f, // Multiplex ratio
    0xd3, 0x00, // Display offset
    0x40, // Start line
    0xa1, // segment re-map
    0xc8, // scan direction
    0xda, 0x12, // COM pins
    0x81, 0xcf, // Current control
    0xd9, 0x22, // Pre-charge period
    0xdb, 0x34, // VCOMH deselect level
    0xa4, // Entire display on/off
    0xa6, // Normal / inverse display
    0xaf, // Display on
  };
  writeCommands(initSequence, sizeof(initSequence));
}

void Graphics::off() {
  writeCommand(0xae);
}

void Graphics::on() {
  writeCommand(0xaf);
}
