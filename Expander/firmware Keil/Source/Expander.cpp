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

extern "C" {
#include "HAL_TLC5946.h"
  void setup(void);
  void run(void);
extern SPI_HandleTypeDef hspi2;
}

#define HYSTERESIS_DELTA 3
#define USE_TLC

Pixi pixi;
void setup(){
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_L_PORT, TOGGLE_R_PIN_B, true);
  // RCC_APB2PeriphClockCmd(TOGGLE_R_CLOCK, ENABLE);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_A, true);
  // configureDigitalInput(TOGGLE_R_PORT, TOGGLE_R_PIN_B, true);
//   configureDigitalOutput(TRIGGER_OUTPUT_PORT, TRIGGER_OUTPUT_PIN);
// #ifdef DEBUG_PINS
//   configureDigitalOutput(GPIOB, GPIO_Pin_10); // debug
// #endif

  TLC5946_init(&hspi2);

  // configureDigitalOutput(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin);
  setPin(TLC_BLANK_GPIO_Port, TLC_BLANK_Pin); // bring BLANK high to turn LEDs off

  // clock_setup();
  pixi.begin();
  bus_setup();
}

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
  ch = 15-ch;
    // if(ch < 8)
    //   ch = 15-ch;
    // else
    //   ch = 15-ch;
    if(cfg[ch] == DAC_5TO5 || cfg[ch] == ADC_5TO5)
      TLC5946_SetOutput_GS(ch, max(0, min(4095, abs(value-2048)*2)));
    else
      TLC5946_SetOutput_GS(ch, max(0, min(4095, value)));
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

void run(){
  int pixi_id = pixi.config();
  for(int ch=0; ch<16; ++ch){
    adc[ch] = 0;
    dac[ch] = 2048;
    cfg[ch] = ADC_5TO5;
  }
  for(int ch=0; ch<16; ++ch)
    configureChannel(ch, cfg[ch]);
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
	  bus_tx_parameter(PARAMETER_AA+ch, adc[ch]);
	  cc_values[ch] = cc;
	}
      }else if(cfg[ch] > DAC_MODE){
	pixi.writeAnalog(ch, dac[ch]);
      }
    }
#ifdef USE_TLC
    TLC5946_Refresh();
#endif
  }
}

void bus_rx_parameter(uint8_t pid, int16_t value){
  debug << "rx parameter [" << pid << "][" << value << "]\r\n" ;
  if(pid >= PARAMETER_AA && pid <= PARAMETER_BH){
    uint8_t ch = pid-PARAMETER_AA;
    setDAC(ch, value);
  }
}

void bus_rx_command(uint8_t cmd, int16_t data){
  if(cmd == BUS_CMD_CONFIGURE_IO){
    uint8_t ch = data>>8;
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
