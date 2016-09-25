/* simple USB Midi IN device driver */
/* inspired from mbed implementation */
/* TODO: sysex support */

#include "usbd_midi.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"

static uint8_t  USBD_Midi_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);
static uint8_t  USBD_Midi_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);
static uint8_t  USBD_Midi_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);
static uint8_t  *USBD_Midi_GetCfgDesc (uint16_t *length);
static uint8_t  *USBD_Midi_GetDeviceQualifierDesc (uint16_t *length);
static uint8_t  USBD_Midi_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t  USBD_Midi_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t  USBD_Midi_EP0_RxReady (USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Midi_EP0_TxReady (USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Midi_SOF (USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Midi_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t  USBD_Midi_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);


USBD_ClassTypeDef  USBD_Midi_ClassDriver = 
{
  USBD_Midi_Init,
  USBD_Midi_DeInit,
  USBD_Midi_Setup,
  USBD_Midi_EP0_TxReady,  
  USBD_Midi_EP0_RxReady,
  USBD_Midi_DataIn,
  USBD_Midi_DataOut,
  USBD_Midi_SOF,
  USBD_Midi_IsoINIncomplete,
  USBD_Midi_IsoOutIncomplete,      
  USBD_Midi_GetCfgDesc,
  USBD_Midi_GetCfgDesc, 
  USBD_Midi_GetCfgDesc,
  USBD_Midi_GetDeviceQualifierDesc,
};

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif

static uint8_t USBD_Midi_CfgDesc[USB_MIDI_CONFIG_DESC_SIZ] =
{
  /* Configuration 1 */
  0x09,                                 /* bLength */
  0x02,                                 /* bDescriptorType */
  LOBYTE(USB_MIDI_CONFIG_DESC_SIZ),       /* wTotalLength */
  HIBYTE(USB_MIDI_CONFIG_DESC_SIZ),       /* wTotalLength */
  0x02,                                 /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue */
  0x00,                                 /* iConfiguration */
  0x80,                                 /* bmAttributes: BUS Powered */
  0x32,                                 /* bMaxPower = 100 mA*/
  /* 09 bytes */
  
  /* Standard AC Interface Descriptor */
  0x09,                                 /* bLength */
  0x04,                                 /* bDescriptorType */
  0x00,                                 /* bInterfaceNumber */
  0x00,                                 /* bAlternateSetting */
  0x00,                                 /* bNumEndpoints */
  0x01,                                 /* bInterfaceClass */
  0x01,                                 /* bInterfaceSubClass */
  0x00,                                 /* bInterfaceProtocol */
  0x00,                                 /* iInterface */
  /* 09 bytes */
  
  /* Class-specific AC Interface Descriptor */
  0x09,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x01,                                 /* bDescriptorSubtype */
  0x00,                                 /* bcdADC */
  0x01,                                 /* bcdADC */
  0x09,                                 /* wTotalLength */
  0x00,					/* wTotalLength */
  0x01,                                 /* bInCollection */
  0x01,                                 /* baInterfaceNr */
  /* 09 bytes */
  
  /* Standard MS Interface Descriptor */
  /* MIDI Adapter Standard MS Interface Descriptor */
  0x09,                                 /* bLength */
  0x04,                                 /* bDescriptorType */
  0x01,                                 /* bInterfaceNumber */
  0x00,                                 /* bAlternateSetting */
  0x02,                                 /* bNumEndpoints */
  0x01,                                 /* bInterfaceClass */
  0x03,                                 /* bInterfaceSubClass */
  0x00,                                 /* bInterfaceProtocol */
  0x00,                                 /* iInterface */
  /* 09 bytes */
  
  /* Class-specific MS Interface Descriptor */
  /* MIDI Adapter Class-specific MS Interface Descriptor */
  0x07,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x01,                                 /* bDescriptorSubtype */
  0x00,                                 /* bcdADC */
  0x01,                                 /* bcdADC */
  0x41,                                 /* wTotalLength */
  0x00,                                 /* wTotalLength */
  /* 07 bytes */
  
  /* MIDI Adapter MIDI IN Jack Descriptor (Embedded) */
  0x06,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x02,                                 /* bDescriptorSubtype */
  0x01,                                 /* bJackType */
  0x01,					/* bJackID */
  0x00,                                 /* iJack */
  /* 06 bytes */
  
  /* MIDI Adapter MIDI IN Jack Descriptor (External) */
  0x06,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x02,                                 /* bDescriptorSubtype */
  0x02,                                 /* bJackType */
  0x02,					/* bJackID */
  0x00,                                 /* iJack */
  /* 06 bytes */

  /* MIDI Adapter MIDI OUT Jack Descriptor (Embedded) */
  0x09,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x03,                                 /* bDescriptorSubtype */
  0x01,                                 /* bJackType */
  0x03,					/* bJackID */
  0x01,                                 /* bNrInputPins */
  0x02,                                 /* BaSourceID */
  0x01,                                 /* BaSourcePin */
  0x00,                                 /* iJack */
  /* 09 bytes */

  /* MIDI Adapter MIDI OUT Jack Descriptor (External) */
  0x09,                                 /* bLength */
  0x24,                                 /* bDescriptorType */
  0x03,                                 /* bDescriptorSubtype */
  0x02,                                 /* bJackType */
  0x04,					/* bJackID */
  0x01,                                 /* bNrInputPins */
  0x01,                                 /* BaSourceID */
  0x01,                                 /* BaSourcePin */
  0x00,                                 /* iJack */
  /* 09 bytes */

  /* MIDI Adapter Standard Bulk OUT Endpoint Descriptor */
  0x09,                                 /* bLength */
  0x05,                                 /* bDescriptorType */
  MIDI_OUT_EP,                          /* bEndpointAddress */
  0x02,                                 /* bmAttributes */
  0x40,					/* wMaxPacketSize */
  0x00,                                 /* wMaxPacketSize */
  0x00,                                 /* bInterval */
  0x00,                                 /* bRefresh */
  0x00,                                 /* bSynchAddress */
  /* 09 bytes */

  /* MIDI Adapter Class-specific Bulk OUT Endpoint Descriptor */
  0x05,                                 /* bLength */
  0x25,                                 /* bDescriptorType */
  0x01,                                 /* bDescriptorSubtype */
  0x01,                                 /* bNumEmbMIDIJack */
  0x01,					/* BaAssocJackID */
  /* 05 bytes */

  /* MIDI Adapter Standard Bulk IN Endpoint Descriptor */
  0x09,                                 /* bLength */
  0x05,                                 /* bDescriptorType */
  MIDI_IN_EP,                           /* bEndpointAddress */
  0x02,                                 /* bmAttributes */
  0x40,					/* wMaxPacketSize */
  0x00,                                 /* wMaxPacketSize */
  0x00,                                 /* bInterval */
  0x00,                                 /* bRefresh */
  0x00,                                 /* bSynchAddress */
  /* 09 bytes */

  /* MIDI Adapter Class-specific Bulk IN Endpoint Descriptor */
  0x05,                                 /* bLength */
  0x25,                                 /* bDescriptorType */
  0x01,                                 /* bDescriptorSubtype */
  0x01,                                 /* bNumEmbMIDIJack */
  0x03					/* BaAssocJackID */
  /* 05 bytes */
  };

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4   
#endif
/* USB Standard Device Descriptor */
static uint8_t USBD_Midi_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

/**
  * @}
  */ 

/** @defgroup USBD_Midi_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_Midi_Init
  *         Initialize the Midi interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_Midi_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{

  static USBD_Midi_HandleTypeDef classData;
  pdev->pClassData = &classData;
/* USBD_malloc(sizeof (USBD_Midi_HandleTypeDef)); */

  if (pdev->pClassData == NULL)
  {
    return USBD_FAIL;
  }
  else
  {
   USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;

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

  return USBD_OK;
  }
}

/**
  * @brief  USBD_Midi_Init
  *         DeInitialize the Midi layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_Midi_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
  USBD_LL_CloseEP(pdev,
      MIDI_IN_EP);
  USBD_LL_CloseEP(pdev,
      MIDI_OUT_EP);
  return USBD_OK;
}

/**
  * @brief  USBD_Midi_Setup
  *         Handle the Midi specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_Midi_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
#if 1
  uint16_t len = USB_MIDI_CONFIG_DESC_SIZ;
  uint8_t ret = USBD_OK;
  USBD_Midi_HandleTypeDef* hmidi = (USBD_Midi_HandleTypeDef*)pdev->pClassData;
  switch (req->bmRequest & USB_REQ_TYPE_MASK){
    /* AUDIO Class Requests -------------------------------*/
  case USB_REQ_TYPE_CLASS :    
    switch (req->bRequest){
    /* case AUDIO_REQ_GET_CUR: */
    /*   AUDIO_Req_GetCurrent(pdev, req); // Left over from USB-audio. Delete me if not needed */
    /*   break; */
    /* case AUDIO_REQ_SET_CUR: */
    /*   AUDIO_Req_SetCurrent(pdev, req); // Left over from USB-audio. Delete me if not needed */
    /*   break; */
    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
    }
    break;
    /* Standard Requests -------------------------------*/
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest){
    case USB_REQ_GET_DESCRIPTOR: 
      if( (req->wValue >> 8) == AUDIO_DESCRIPTOR_TYPE){
	uint8_t  *pbuf = USBD_Midi_CfgDesc + 18;
	len = MIN(USB_MIDI_CONFIG_DESC_SIZ , req->wLength);
	USBD_CtlSendData (pdev, pbuf, len);
      }
      break;
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&(hmidi->alt_setting),
                        /* (uint8_t *)&usbd_audio_AltSet, */
                        1);
      break;
    case USB_REQ_SET_INTERFACE :
      if((uint8_t)(req->wValue) <= USBD_MAX_NUM_INTERFACES){
        hmidi->alt_setting = (uint8_t)(req->wValue);
      }else{
        /* Call the error management function (command will be nacked */
        USBD_CtlError(pdev, req);
      }
      break;      
    default :
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;     
    }
  }
  return ret;

#else
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL;     
    }
  }
  return USBD_OK;
#endif
}


/**
  * @brief  USBD_Midi_GetCfgDesc 
  *         return configuration descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_Midi_GetCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_Midi_CfgDesc);
  return USBD_Midi_CfgDesc;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Midi_DeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (USBD_Midi_DeviceQualifierDesc);
  return USBD_Midi_DeviceQualifierDesc;
}

extern USBD_HandleTypeDef hUsbDeviceHS;
static volatile int midi_tx_lock = 0;
void midi_tx_usb_buffer(uint8_t* buf, uint32_t len) {
  if(hUsbDeviceHS.dev_state == USBD_STATE_CONFIGURED){
    while(midi_tx_lock);
    midi_tx_lock = 1;
    USBD_LL_Transmit(&hUsbDeviceHS, MIDI_IN_EP, buf, len);
  }
}

/**
  * @brief  USBD_Midi_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_Midi_DataIn (USBD_HandleTypeDef *pdev, 
				  uint8_t epnum)
{
    midi_tx_lock = 0;

  /* USBD_LL_Transmit(pdev, MIDI_IN_EP, buf, size); */


  return USBD_OK;
}

/**
  * @brief  USBD_Midi_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_Midi_EP0_RxReady (USBD_HandleTypeDef *pdev)
{

  return USBD_OK;
}
/**
  * @brief  USBD_Midi_EP0_TxReady
  *         handle EP0 TRx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_Midi_EP0_TxReady (USBD_HandleTypeDef *pdev)
{

  return USBD_OK;
}
/**
  * @brief  USBD_Midi_SOF
  *         handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_Midi_SOF (USBD_HandleTypeDef *pdev)
{

  return USBD_OK;
}
/**
  * @brief  USBD_Midi_IsoINIncomplete
  *         handle data ISO IN Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_Midi_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{

  return USBD_OK;
}
/**
  * @brief  USBD_Midi_IsoOutIncomplete
  *         handle data ISO OUT Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_Midi_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum)
{

  return USBD_OK;
}
/**
  * @brief  USBD_Midi_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_Midi_DataOut (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
   USBD_Midi_HandleTypeDef *hmidi = (USBD_Midi_HandleTypeDef*) pdev->pClassData;

  /* Get the received data buffer and update the counter */

//  USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;
   hmidi->rxLen = USBD_LL_GetRxDataSize (pdev, epnum);
  /* Forward the data to the user callback. */
//  ((MIDI_IF_Prop_TypeDef *)pdev->pUserData)->pIf_MidiRx((uint8_t*)&USB_Rx_Buffer, USB_Rx_Cnt);
//  APP_fops->pIf_MidiRx((uint8_t*)&USB_Rx_Buffer, USB_Rx_Cnt);

uint8_t *buf = hmidi->rxBuffer;

for (uint32_t i=0; i<hmidi->rxLen; i+=4) {
  ((USBD_Midi_ItfTypeDef *)pdev->pUserData)->Receive(buf+i, 4);
  // send blocks of 4 bytes to midi_rx_usb_buffer
}

//  ((USBD_Midi_ItfTypeDef *)pdev->pUserData)->Receive(hmidi->rxBuffer,hmidi->rxLen);

  USBD_LL_PrepareReceive(pdev,
                       MIDI_OUT_EP,
                       hmidi->rxBuffer,
                       MIDI_DATA_OUT_PACKET_SIZE);

  return USBD_OK;
}

/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Midi_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_Midi_DeviceQualifierDesc);
  return USBD_Midi_DeviceQualifierDesc;
}



/**
* @brief  USBD_CDC_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: CD  Interface callback
  * @retval status
  */
uint8_t  USBD_Midi_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                      USBD_Midi_ItfTypeDef *fops)
{
  uint8_t  ret = USBD_FAIL;
  
  if(fops != NULL)
  {
    pdev->pUserData= fops;
    ret = USBD_OK;    
  }
  
  return ret;
}
