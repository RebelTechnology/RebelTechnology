
// _____ HAL Triggers ______

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "HAL_OLED.h"
#include <string.h>

/* unsigned char OLED_Buffer[1024]; */

SPI_HandleTypeDef* OLED_SPIInst;
	
void OLED_writeData(uint16_t type, const uint8_t* data, uint16_t length)
{
	pCS_Clr();
	
	if (type)	{pDC_Set();} else {pDC_Clr();}													// Update DC Pin
	HAL_SPI_Transmit(OLED_SPIInst, (uint8_t*)data, length, 1000);
	
	pCS_Set();
}

/* void OLED_Refresh(void) */
/* { */
/* 	OLED_writeData(OLED_DAT, OLED_Buffer, sizeof OLED_Buffer); */
/* } */

/* void OLED_ClearScreen(void) */
/* { */
/* 	memset(OLED_Buffer, 0, sizeof OLED_Buffer); */
/* } */

void OLED_Config(SPI_HandleTypeDef* spi){
  OLED_SPIInst = spi;
  
	GPIO_InitTypeDef GPIO_InitStruct;
		
	// Configure RST and DC Pins
	GPIO_InitStruct.Pin   = OLED_RST_Pin | OLED_DC_Pin;					
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	// Configure CS Pin
	GPIO_InitStruct.Pin   = OLED_CS_Pin;					
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(OLED_CS_GPIO_Port, &GPIO_InitStruct);
	
	// Set up SPI	
	OLED_SPIInst->Instance = SPI2;
	OLED_SPIInst->Init.Mode = SPI_MODE_MASTER;
	OLED_SPIInst->Init.Direction = SPI_DIRECTION_2LINES;
	OLED_SPIInst->Init.DataSize = SPI_DATASIZE_8BIT;
	OLED_SPIInst->Init.CLKPolarity = SPI_POLARITY_LOW;
	OLED_SPIInst->Init.CLKPhase = SPI_PHASE_1EDGE;
	OLED_SPIInst->Init.NSS = SPI_NSS_SOFT;
	OLED_SPIInst->Init.NSSPMode = SPI_NSS_PULSE_DISABLED;

	OLED_SPIInst->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	OLED_SPIInst->Init.FirstBit = SPI_FIRSTBIT_MSB;
	OLED_SPIInst->Init.TIMode = SPI_TIMODE_DISABLED;
	OLED_SPIInst->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	OLED_SPIInst->Init.CRCPolynomial = 7;
	OLED_SPIInst->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	HAL_SPI_Init(OLED_SPIInst);
	
	// Initialisation
	pRST_Clr();
	NopDelay(200000);
	pRST_Set();
	
	NopDelay(20000000);
	OLED_writeData(OLED_CMD, OLED_initSequence, sizeof OLED_initSequence);
	NopDelay(20000000);
	
}

void NopDelay(uint32_t nops)
{
	uint32_t nopcount = nops, nop = 0;
	
	while (nop < nopcount)	
	{
		nop++;
	}
}
