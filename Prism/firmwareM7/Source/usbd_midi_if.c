#include "usbd_midi_if.h"
#include "midi.h"

extern USBD_HandleTypeDef hUsbDeviceHS;
USBD_Midi_ItfTypeDef USBD_Midi_fops = {
  midi_rx_usb_buffer,
};

void midi_tx_usb_buffer(uint8_t* buf, uint32_t len) {
  USBD_LL_Transmit(&hUsbDeviceHS, MIDI_IN_EP, buf, len);
}
