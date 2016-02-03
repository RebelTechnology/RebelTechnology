/******************************************************************************
* Sine loopback test for SuperAudioBoard
* Copyright (c) 2015 RF William Hollender, whollender@gmail.com
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
********************************************************************************/

#include "cs4272.h"
#include "gpio.h"
#include "mxconstants.h"
#include "stm32f7xx_hal.h"

void delay(uint32_t millisec);

#define CS_TIMEOUT 1000

uint8_t cs_txbuf[1024];
uint8_t cs_rxbuf[1024];
SPI_HandleTypeDef* hspi;
SAI_HandleTypeDef* hsaia;
SAI_HandleTypeDef* hsaib;

void codec_write(uint8_t reg, uint8_t data)
{
	// For CS4272 all data is written between single
	// start/stop sequence
	
	uint8_t buf[2];
	
	buf[0] = reg;
	buf[1] = data;

	/* i2c_write(CODEC_ADDR,2,buf); */
	HAL_SPI_Transmit(hspi, buf, 2, CS_TIMEOUT);

}

uint8_t codec_read(uint8_t reg)
{
	// No waveform demo for read,
	// so assume first write MAP,
	// then rep-start (or stop and start),
	// the read
	
	/* i2c_write(CODEC_ADDR,1,&reg); */
        HAL_SPI_Transmit(hspi, &reg, 1, CS_TIMEOUT);

	uint8_t buf;
	/* if(i2c_read(CODEC_ADDR,1,&buf) != 1) */
	if(HAL_SPI_Receive(hspi, &buf, 1, CS_TIMEOUT) != HAL_OK)
	{
		return 0;
	}

	return buf;
}

void codec_init(SAI_HandleTypeDef* saiA, SAI_HandleTypeDef* saiB, SPI_HandleTypeDef* spi){
	// Setup Initial Codec
  /* HAL_SAI_Receive_DMA() */
  hspi = spi;
  hsaia = saiA;
  hsaib = saiB;

	delay(100);

	// Setup Reset pin (GPIO)
	// Right now assuming that we're using Teensy pin 2
	// which is Port D pin 0
	
	// Setup Pin muxing for GPIO (alt 1)
	/* PORTD_PCR0 = PORT_PCR_MUX(1); */

	// Setup pin for digital out
	/* GPIOD_PDDR |= (1 << 0); */

	// Make sure pin is cleared (still driving reset)
	/* GPIOD_PCOR = (1 << 0); */
	clearPin(CS_RST_GPIO_Port, CS_RST_Pin);

	delay(1);
	
	// Release Reset (drive pin high)
	/* GPIOD_PSOR = (1 << 0); */
	setPin(CS_RST_GPIO_Port, CS_RST_Pin);
	
	// Wait for ~2-5ms (1-10 ms time window spec'd in datasheet)
	delay(2);
	
	// Set power down and control port enable as spec'd in the 
	// datasheet for control port mode
	codec_write(CODEC_MODE_CTRL2, CODEC_MODE_CTRL2_POWER_DOWN
			| CODEC_MODE_CTRL2_CTRL_PORT_EN);
	
	// Further setup
	delay(1);

	// Set ratio select for MCLK=512*LRCLK (BCLK = 64*LRCLK), and master mode
	codec_write(CODEC_MODE_CONTROL, CODEC_MC_RATIO_SEL(3) | CODEC_MC_MASTER_SLAVE);

	delay(10);
	
	// Release power down bit to start up codec
	// TODO: May need other bits set in this reg
	codec_write(CODEC_MODE_CTRL2, CODEC_MODE_CTRL2_CTRL_PORT_EN);
	
	// Wait for everything to come up
	delay(10);

	HAL_SAI_Receive_DMA(hsaia, cs_rxbuf, sizeof(cs_rxbuf));
	HAL_SAI_Transmit_DMA(hsaib, cs_txbuf, sizeof(cs_txbuf));
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai){
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai){
}
