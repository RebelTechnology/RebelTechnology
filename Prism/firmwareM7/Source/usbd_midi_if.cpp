#include "midi.h"
#include "usbd_midi.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"
#include "usbd_midi_if.h"
#include "midi.h"
#include "SerialBuffer.hpp"

// static SerialBuffer<MIDI_DATA_OUT_PACKET_SIZE> rxbuffer;
// static SerialBuffer<MIDI_DATA_IN_PACKET_SIZE> txbuffer;
static SerialBuffer<256> txbuffer;

USBD_Midi_ItfTypeDef USBD_Midi_fops = {
  midi_rx_usb_buffer,
};

// extern USBD_HandleTypeDef hUsbDeviceHS;
// void midi_tx_usb_buffer(uint8_t* buf, uint32_t len) {
//   if(hUsbDeviceHS.dev_state == USBD_STATE_CONFIGURED){
//     USBD_HandleTypeDef *pdev = &hUsbDeviceHS;
//     USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*)pdev->pClassData;
//     while(hmidi->TxState);
//     hmidi->TxState = 1;
//     USBD_LL_Transmit(&hUsbDeviceHS, MIDI_IN_EP, buf, len);
//   }
// }

extern USBD_HandleTypeDef hUsbDeviceHS;
void midi_tx_usb_buffer(uint8_t* buf, uint32_t len) {
  USBD_HandleTypeDef *pdev = &hUsbDeviceHS;
  if(pdev->dev_state == USBD_STATE_CONFIGURED){
    txbuffer.push(buf, len);
    USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;
    if(hmidi->TxState == 0){
      hmidi->TxState = 1;
      uint16_t available = MIN(MIDI_DATA_IN_PACKET_SIZE, txbuffer.getContiguousReadCapacity());
      USBD_LL_Transmit(pdev, MIDI_IN_EP, txbuffer.getReadHead(), available);
      txbuffer.incrementReadHead(available);
    }
  }
}

/**
 * @brief  USBD_Midi_Init
 *         Initialize the Midi interface
 * @param  pdev: device instance
 * @param  cfgidx: Configuration index
 * @retval status
 */
uint8_t  USBD_Midi_Init (USBD_HandleTypeDef *pdev, 
			 uint8_t cfgidx){
  static USBD_Midi_HandleTypeDef classData;
  pdev->pClassData = &classData;

  USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;
  hmidi->TxState = 0;

  /* Open the in EP */
  USBD_LL_OpenEP(pdev,
		 MIDI_IN_EP,
		 USBD_EP_TYPE_BULK,
		 MIDI_DATA_IN_PACKET_SIZE
		 );

  /* Open the out EP */
  USBD_LL_OpenEP(pdev,
		 MIDI_OUT_EP,
		 USBD_EP_TYPE_BULK,
		 MIDI_DATA_OUT_PACKET_SIZE
		 );

  /* Prepare Out endpoint to receive next packet */
  USBD_LL_PrepareReceive(pdev,
			 MIDI_OUT_EP,
			 hmidi->rxBuffer,
			 MIDI_DATA_OUT_PACKET_SIZE);
			 // rxbuffer.getWriteHead(),
			 // rxbuffer.getContiguousWriteCapacity());
  return USBD_OK;
}

/**
 * @brief  USBD_Midi_DataIn
 *         handle data IN Stage
 * @param  pdev: device instance
 * @param  epnum: endpoint index
 * @retval status
 */
uint8_t  USBD_Midi_DataIn (USBD_HandleTypeDef *pdev, 
			   uint8_t epnum){
  USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*)pdev->pClassData;
  // if(epnum == MIDI_IN_EP)
    hmidi->TxState = 0;

  // if(epnum == MIDI_IN_EP){
  //   USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;
  //   uint16_t available = MIN(MIDI_DATA_IN_PACKET_SIZE, txbuffer.getContiguousReadCapacity());
  //   if(available){
  //     USBD_LL_Transmit(pdev, MIDI_IN_EP, txbuffer.getReadHead(), available);
  //     txbuffer.incrementReadHead(available);
  //   }else{
  //     hmidi->TxState = 0;
  //   }
  // }
  return USBD_OK;
}

/**
 * @brief  USBD_Midi_DataOut
 *         handle data OUT Stage
 * @param  pdev: device instance
 * @param  epnum: endpoint index
 * @retval status
 */
uint8_t  USBD_Midi_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum){
  USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;

  /* Get the received data buffer and update the counter */

  //  USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;
  hmidi->rxLen = USBD_LL_GetRxDataSize (pdev, epnum);

  uint8_t *buf = hmidi->rxBuffer;

  for (uint32_t i=0; i<hmidi->rxLen; i+=4) {
    midi_rx_usb_buffer(buf+i, 4);
    // ((USBD_Midi_ItfTypeDef *)pdev->pUserData)->Receive(buf+i, 4);
    // send blocks of 4 bytes to midi_rx_usb_buffer
  }

  USBD_LL_PrepareReceive(pdev,
  			 MIDI_OUT_EP,
  			 hmidi->rxBuffer,
  			 MIDI_DATA_OUT_PACKET_SIZE);


  // rxbuffer.incrementWriteHead(USBD_LL_GetRxDataSize (pdev, epnum));
  // USBD_LL_PrepareReceive(pdev,
  // 			 MIDI_OUT_EP,
  // 			 rxbuffer.getWriteHead(),
  // 			 rxbuffer.getContiguousWriteCapacity());

  return USBD_OK;
}
