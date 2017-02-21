#!/bin/bash
git checkout Src/usbd_desc.c Src/usb_host.c Src/usb_device.c Inc/FreeRTOSConfig.h Inc/usb_host.h Middlewares/Third_Party/FreeRTOS
rm Src/usbd_audio_if.c
