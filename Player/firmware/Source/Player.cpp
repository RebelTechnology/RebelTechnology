extern "C" {
#include "stm32f7xx_hal.h"
#include "HAL_Triggers.h"
#include "HAL_Encoders.h"
#include "HAL_CV_IO.h"
#include "usb_device.h"
#include "usb_host.h"
#include "mxconstants.h"
}
#include "Graphics.h"

extern "C" {
  void setup(void);
  void run(void);
}
extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;
extern SPI_HandleTypeDef hspi2;

#define OLED_HEIGHT 64
#define OLED_WIDTH 128
#define OLED_DATA_LENGTH (OLED_WIDTH*OLED_HEIGHT/8)
Graphics graphics;
static uint16_t pixelbuffer[OLED_DATA_LENGTH];

void setup(void){
// Product Specific Initialisation
  Triggers_Config();
  Encoders_Config();
  CV_IO_Config();
  CV_Out_A(&hdac, 0);
  CV_Out_B(&hdac, 0);
  graphics.begin(&hspi2);
}

void run(void){
  for(;;){
    MX_USB_HOST_Process();
    if(dodisplay){
      // if(dodisplay && graphics.isReady()){
      graphics.display(pixelbuffer, OLED_DATA_LENGTH);
    }
  }
}
