// $Id: mios32_config.h 2029 2014-08-09 20:13:05Z tk $
/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/doc/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

/* #define MIOS32_MIDI_USBH_DEBUG 1 */

#define MIOS32_UART_NUM 2
/* #define MIOS32_USB_MIDI_NUM_PORTS 1 */
/* #define MIOS32_IIC_BS_NUM 0 */

/* #define MIOS32_UART0_BAUDRATE 31250 */
#define MIOS32_UART0_BAUDRATE 115200
#define MIOS32_UART0_TX_OD 0
#define MIOS32_UART1_BAUDRATE 31250
#define MIOS32_UART1_TX_OD 1

#define MIOS32_DONT_USE_SRIO
#define MIOS32_DONT_USE_SPI
#define MIOS32_DONT_USE_DIN
#define MIOS32_DONT_USE_DOUT
#define MIOS32_DONT_USE_ENC
#define MIOS32_DONT_USE_MF
#define MIOS32_DONT_USE_AIN
#define MIOS32_DONT_USE_IIC_BS
/* #define MIOS32_DONT_USE_USB */
#define MIOS32_DONT_USE_OSC
#define MIOS32_DONT_USE_COM
#define MIOS32_DONT_USE_LCD

// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "LilBug v001"
#define MIOS32_LCD_BOOT_MSG_LINE2 "Rebel Technology"

// Following settings allow to customize the USB device descriptor
#define MIOS32_USB_VENDOR_STR   "midibox.org" // you will see this in the USB device description
#define MIOS32_USB_PRODUCT_STR  "LIL-BUG" // you will see this in the MIDI device list

#define MIOS32_USB_MIDI_NUM_PORTS 2           // we provide 2 USB ports

#endif /* _MIOS32_CONFIG_H */
