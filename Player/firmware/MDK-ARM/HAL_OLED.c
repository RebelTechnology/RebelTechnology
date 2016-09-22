// _____ Includes ______________________________________________________________________
#include "stm32f7xx_hal.h"
#include "HAL_OLED.h"
#include <string.h>

// _____ Variables _____________________________________________________________________
static const uint8_t OLED_initSequence[] = 
{
	0xfd, 0x12, 	// Command lock
	0xae, 				// Display off
	0xd5, 0xa0, 	// Clock divide ratio / Oscillator Frequency
	0xa8, 0x3f, 	// Multiplex ratio
	0xd3, 0x00, 	// Display offset
	0x40, 				// Start line
	0xa1, 				// segment re-map
	0xc8, 				// scan direction
	0xda, 0x12, 	// COM pins
	0x81, 0xcf, 	// Current control
	0xd9, 0x22, 	// Pre-charge period
	0xdb, 0x34, 	// VCOMH deselect level
	0xa4, 				// Entire display on/off
	0xa6, 				// Normal / inverse display
	0x20, 0x01,   // Vertical addressing mode
	0xaf, 				// Display on
};
static unsigned char* OLED_Buffer;
static SPI_HandleTypeDef* OLED_SPIInst;
	
// _____ Functions _____________________________________________________________________
void OLED_writeCMD(const uint8_t* data, uint16_t length)
{
	pCS_Clr();	// CS low
	pDC_Clr();	// DC low		
	
	// Send Data	
	HAL_SPI_Transmit(OLED_SPIInst, (uint8_t*)data, length, 1000);
	
	pCS_Set();	// CS high
}

void OLED_writeDAT(const uint8_t* data, uint16_t length)
{
	pCS_Clr();	// CS low
	pDC_Set();	// DC high
	
	// Send Data
	HAL_SPI_Transmit(OLED_SPIInst, (uint8_t*)data, length, 1000);
	
	pCS_Set();	// CS high
}

void OLED_Refresh(void)
{
	// Write entire buffer to OLED
	OLED_writeDAT(OLED_Buffer, 1024);
}

void OLED_ClearScreen(void)
{
	// Clear contents of OLED buffer
	memset(OLED_Buffer, 0, 1024);
}

// Configuration
void OLED_Config(SPI_HandleTypeDef* spi, unsigned char* buffer){
	GPIO_InitTypeDef GPIO_InitStruct;
	OLED_SPIInst = spi;
	OLED_Buffer = buffer;
		
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

	OLED_SPIInst->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	OLED_SPIInst->Init.FirstBit = SPI_FIRSTBIT_MSB;
	OLED_SPIInst->Init.TIMode = SPI_TIMODE_DISABLED;
	OLED_SPIInst->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	OLED_SPIInst->Init.CRCPolynomial = 7;
	OLED_SPIInst->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	HAL_SPI_Init(OLED_SPIInst);
	
	// Initialisation
	pRST_Clr();
	NopDelay(2000);
	pRST_Set();
	
	NopDelay(20000);
	OLED_writeCMD(OLED_initSequence, sizeof OLED_initSequence);
	NopDelay(20000);
	
}

// Buffer pixel checking and manipulation
uint8_t OLED_getPixel(uint8_t x, uint8_t y)
{
	uint8_t  ucByteOffset = 0;
	uint16_t usiArrayLoc = 0;
	
		// Determine array location
		usiArrayLoc = (y/8)+(x*8);
		
		// Determine byte offset
		ucByteOffset = y-((uint8_t)(y/8)*8);
		
		// Return bit state from buffer
		return OLED_Buffer[usiArrayLoc] & (1 << ucByteOffset);
}

void OLED_setPixel(uint8_t x, uint8_t y)
{
	uint8_t  ucByteOffset = 0;
	uint16_t usiArrayLoc = 0;
	
	if (x<128 && y<64)
	{	
		// Determine array location
		usiArrayLoc = (y/8)+(x*8);
		
		// Determine byte offset
		ucByteOffset = y-((uint8_t)(y/8)*8);
		
		// Set pixel in buffer
		OLED_Buffer[usiArrayLoc] |= (1 << ucByteOffset);
	}
}

void OLED_clearPixel(uint8_t x, uint8_t y)
{
	uint8_t  ucByteOffset = 0;
	uint16_t usiArrayLoc = 0;
	
	if (x<128 && y<64)
	{	
		// Determine array location
		usiArrayLoc = (y/8)+(x*8);
		
		// Determine byte offset
		ucByteOffset = y-((uint8_t)(y/8)*8);
	
		// Clear pixel in buffer
		OLED_Buffer[usiArrayLoc] &= ~(1 << ucByteOffset);
	}
}

void OLED_togglePixel(uint8_t x, uint8_t y)
{
	uint8_t  ucByteOffset = 0;
	uint16_t usiArrayLoc = 0;
	
	if (x<128 && y<64)
	{	
		// Determine array location
		usiArrayLoc = (y/8)+(x*8);
		
		// Determine byte offset
		ucByteOffset = y-((uint8_t)(y/8)*8);
		
		// Toggle pixel in buffer
		OLED_Buffer[usiArrayLoc] ^= (1 << ucByteOffset);
	}
}

// Delay 
void NopDelay(uint32_t nops)
{
	uint32_t nopcount = nops, nop = 0;
	
	while (nop < nopcount)	
	{
		nop++;
	}
}
