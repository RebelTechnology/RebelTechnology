#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "Pixi.h"
#include "bus.h"
#include "gpio.h"
#include "clock.h"
#include "message.h"
#include "OpenWareMidiControl.h"
#include "device.h"
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif

/**
 * MAX channel index goes from 0 at top left, to 8 at bottom right, to 15 at top right.
 * LED channel index is the inverse of MAX channel index.
 */

extern "C" {
#include "HAL_TLC5946.h"
  void setup(void);
  void run(void);
extern SPI_HandleTypeDef hspi2;
}

#define HYSTERESIS_DELTA 3
#define USE_TLC

enum ChannelMode {
  ADC_5TO5,
  ADC_0TO10,
  ADC_10TO0,
  DAC_MODE,
  DAC_5TO5,
  DAC_0TO10,
  DAC_10TO0,
  CHANNEL_MODES
};

uint8_t cc_values[16] = {0};
volatile ChannelMode cfg[16];
volatile int dac[16];
volatile int adc[16];

#define USE_TEMP
#ifdef USE_TEMP
volatile float temp[3] = {0};
#endif

void setLed(uint8_t ch, int16_t value);
void configureChannel(uint8_t ch, ChannelMode mode);
void setDAC(uint8_t ch, int16_t value);
void setADC(uint8_t ch, int16_t value);
uint8_t getChannelIndex(uint8_t ch);

Pixi pixi;
void setup(){
  setPin(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin); // bring BLANK high to turn LEDs off

// #ifdef DEBUG_PINS
//   configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
// #endif

  TLC5946_init(&hspi2);
  TLC5946_Refresh_DC();

  int delayms = 1;
  for(int i=0; i<8192; ++i){
    for(int ch=0; ch<16; ++ch)
      setLed(ch, i&0x0fff);
    TLC5946_Refresh_GS();
    HAL_Delay(delayms);
  }
  // configureDigitalOutput(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin);

  pixi.begin();

  int pixi_id = pixi.config();
  for(int ch=0; ch<16; ++ch){
    adc[ch] = 0;
    dac[ch] = 0;
    cfg[ch] = ADC_0TO10; // ADC_5TO5;
  }
  for(int ch=0; ch<16; ++ch)
    configureChannel(ch, cfg[ch]);

  bus_setup();
}

void configureChannel(uint8_t ch, ChannelMode mode){
  switch(mode){
  case ADC_5TO5:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_5N_TO_5P, ADC_MODE_CONT);
    break;
  case ADC_0TO10:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_ADC_P, 0, CH_0_TO_10P, ADC_MODE_CONT);
    break;
  case DAC_5TO5:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_DAC, 0, CH_5N_TO_5P, 0);
    break;
  case DAC_0TO10:
    pixi.configChannel(CHANNEL_0+ch, CH_MODE_DAC, 0, CH_0_TO_10P, 0);
    break;
  default:
    debug << "Invalid mode [" << mode << "]\r\n";
    return;
    break;
  }
  cfg[ch] = mode;
}

void setLed(uint8_t ch, int16_t value){
#ifdef USE_TLC
  // note that LED channel index is inverse of MAX channel index
  if(cfg[ch] == DAC_5TO5 || cfg[ch] == ADC_5TO5)
    TLC5946_SetOutput_GS(15-ch, max(0, min(4095, abs(value-2048)*2)));
  else
    TLC5946_SetOutput_GS(15-ch, max(0, min(4095, value)));
#endif
}

void setDAC(uint8_t ch, int16_t value){
  if(cfg[ch] < DAC_MODE){
    // auto configure to output
    if(value < 0){
      configureChannel(ch, DAC_5TO5);
    }else{
      configureChannel(ch, DAC_0TO10);
    }
  }
  if(cfg[ch] == DAC_5TO5)
    value += 2048;
  if(dac[ch] != value){
    dac[ch] = value;
    setLed(ch, value);
  }
}

void setADC(uint8_t ch, int16_t value){
  if(adc[ch] != value){
    adc[ch] = value;
    setLed(ch, value);
  }
}

uint8_t getChannelIndex(uint8_t ch){
  if(ch > 7)
    ch = 23-ch;
  return ch;
}

void run(){
  for(;;){
    bus_status();
#ifdef USE_TEMP
    temp[0] = pixi.readTemperature ( TEMP_CHANNEL_INT );
    temp[1] = pixi.readTemperature ( TEMP_CHANNEL_EXT0 );
    temp[2] = pixi.readTemperature ( TEMP_CHANNEL_EXT1 );
#endif
    for(int ch=0; ch<16; ++ch){
      if(cfg[ch] < DAC_MODE){
	setADC(ch, pixi.readAnalog(ch));
	uint8_t cc = adc[ch] >> 5;
	if(abs(cc - cc_values[ch]) > HYSTERESIS_DELTA){
	  bus_tx_parameter(getChannelIndex(PARAMETER_AA+ch), adc[ch]);
	  cc_values[ch] = cc;
	}
      }else if(cfg[ch] > DAC_MODE){
	pixi.writeAnalog(ch, dac[ch]);
      }
    }
#ifdef USE_TLC
    TLC5946_Refresh_GS();
#endif
  }
}

void bus_rx_parameter(uint8_t pid, int16_t value){
  debug << "rx parameter [" << pid << "][" << value << "]\r\n" ;
  if(pid >= PARAMETER_AA && pid <= PARAMETER_BH){
    uint8_t ch = getChannelIndex(pid-PARAMETER_AA);
    setDAC(ch, value);
  }
}

void bus_rx_command(uint8_t cmd, int16_t data){
  if(cmd == BUS_CMD_CONFIGURE_IO){
    uint8_t ch = getChannelIndex(data>>8);
    ChannelMode mode = (ChannelMode)(data&0xff);
    debug << "rx command [" << cmd << "][" << ch << "][" << mode << "]\r\n" ;
    if(ch < 16){
      configureChannel(ch, mode);
      bus_tx_message("Configured channel");
    }
  }
}

void bus_rx_button(uint8_t bid, int16_t value){
  debug << "rx button [" << bid << "][" << value << "]\r\n" ;
}

void bus_rx_message(const char* msg){
  debug << "rx msg [" << msg << "]\r\n" ;
}

void bus_rx_data(const uint8_t* data, uint16_t size){
  debug << "rx data [" << size << "]\r\n" ;
}
