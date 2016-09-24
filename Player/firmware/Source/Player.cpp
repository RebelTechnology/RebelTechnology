extern "C" {
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "HAL_Triggers.h"
#include "HAL_Encoders.h"
#include "HAL_CV_IO.h"
#include "usb_device.h"
#include "usb_host.h"
}
#include "device.h"
#include "Graphics.h"
#include "Codec.h"
#include "ProgramVector.h"
#include "ScreenBuffer.h"
#include "SampleBuffer.hpp"

extern "C" {
  void setup(void);
  void run(void);
}
extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;
extern SPI_HandleTypeDef hspi2;

#include "usbh_MIDI.h"
extern USBH_HandleTypeDef hUsbHostFS;

#define RX_BUFF_SIZE   64  /* Max Received data 64 bytes */
static uint8_t USBHOST_RX_Buffer[RX_BUFF_SIZE]; // MIDI reception buffer

// #define OLED_HEIGHT 64
// #define OLED_WIDTH 128
#define OLED_DATA_LENGTH (OLED_WIDTH*OLED_HEIGHT/8)
Graphics graphics;
static uint8_t pixelbuffer[OLED_DATA_LENGTH];
static bool dodisplay = true;
Codec codec;
ProgramVector programVector;
ScreenBuffer screen(OLED_WIDTH, OLED_HEIGHT);
SampleBuffer samples;

#include "SplashPatch.hpp"
SplashPatch splash;
Patch* patches[] = {&splash};
uint8_t currentPatch = 0;

volatile bool doProcessAudio = false;
uint32_t dropouts = 0;
extern "C" {
  void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size){
    if(!doProcessAudio){
      programVector.audio_input = rx;
      programVector.audio_output = tx;
      programVector.audio_blocksize = size;
      doProcessAudio = true;
    }else{
      dropouts++;
    }
  }
}

void updateProgramVector(ProgramVector* pv){
  pv->checksum = PROGRAM_VECTOR_CHECKSUM_V13;
  pv->hardware_version = PLAYER_HARDWARE;
  pv->parameters_size = 2;
  pv->parameters = NULL; // adc_values;
  pv->audio_bitdepth = 24;
  pv->audio_samplingrate = 48000;
  pv->buttons = 0;
  pv->registerPatch = NULL;
  pv->registerPatchParameter = NULL;
  pv->cycles_per_block = 0;
  pv->heap_bytes_used = 0;
  pv->programReady = NULL;
  pv->programStatus = NULL;
  pv->serviceCall = NULL;
  pv->message = NULL;
  pv->pixels = pixelbuffer;
  pv->screen_width = OLED_WIDTH;
  pv->screen_height = OLED_HEIGHT;
}

void setup(void){
  // memset(pixelbuffer, 0xAA, 1024);

// Product Specific Initialisation
  Triggers_Config();
  Encoders_Config();
  CV_IO_Config();
  CV_Out_A(&hdac, 0);
  CV_Out_B(&hdac, 0);
  updateProgramVector(&programVector);
  // codec.reset();
  graphics.begin(&hspi2);
  // codec.start();
  // codec.ramp(1<<23);

  patches[currentPatch]->reset();

  doProcessAudio = true;

  // USBH_MIDI_Receive(&hUSBHostFS, USBHOST_RX_Buffer, RX_BUFF_SIZE); // just once at the beginning, start the first reception
}

void processBlock(ProgramVector* pv){
  // samples.split(pv->audio_input, pv->audio_blocksize);
  screen.setBuffer(pv->pixels);
  patches[currentPatch]->processAudio(samples);
  // screen.setTextSize(1);
  // screen.print(0, screen.getHeight()-8, "Rebel Technology");
  // samples.comb(pv->audio_output);
}

void run(void){
  for(;;){
    MX_USB_HOST_Process();
    if(doProcessAudio){
      processBlock(&programVector);
      if(dodisplay){
      // if(dodisplay && graphics.isReady()){
	graphics.display(programVector.pixels, OLED_WIDTH*OLED_HEIGHT);
	// swap pixelbuffer
	// programVector.pixels = pixelbuffer[swappb];
	// swappb = !swappb;
      }
      // doProcessAudio = false;
    }
  }
}

  void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost){
    uint16_t numberOfPackets;
    uint8_t *ptr = USBHOST_RX_Buffer;
    // midi_package_t pack;
    numberOfPackets = USBH_MIDI_GetLastReceivedDataSize(phost) / 4; //each USB midi package is 4 bytes long

    USBH_MIDI_Receive(phost, USBHOST_RX_Buffer, RX_BUFF_SIZE); // start a new reception
  }

  void USBH_MIDI_TransmitCallback(USBH_HandleTypeDef *phost){
  }

extern "C" {
  void delay(uint32_t ms){
    osDelay(ms);
  }
}

