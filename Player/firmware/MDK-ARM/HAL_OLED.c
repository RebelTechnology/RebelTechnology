
// _____ HAL Triggers ______

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "HAL_OLED.h"

SPI_HandleTypeDef OLED_SPIInst;
	
	
void OLED_writeByte(unsigned short type, unsigned char byte)
{
	// Update DC Pin
	if (type)	{pDC_Set;} else {pDC_Clr;}	
	
	
	
}

void OLED_Refresh(void)
{


}

void OLED_ClearScreen(void)
{

}

void OLED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		
	// Configure RST and DC Pins
	GPIO_InitStruct.Pin   = OLED_RST_Pin | OLED_DC_Pin;					
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	// Set up SPI
  OLED_SPIInst.Instance = SPI2;
  OLED_SPIInst.Init.Mode = SPI_MODE_MASTER;
  OLED_SPIInst.Init.Direction = SPI_DIRECTION_2LINES;
  OLED_SPIInst.Init.DataSize = SPI_DATASIZE_8BIT;
  OLED_SPIInst.Init.CLKPolarity = SPI_POLARITY_LOW;
  OLED_SPIInst.Init.CLKPhase = SPI_PHASE_1EDGE;
  OLED_SPIInst.Init.NSS = SPI_NSS_SOFT;
  OLED_SPIInst.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  OLED_SPIInst.Init.FirstBit = SPI_FIRSTBIT_MSB;
  OLED_SPIInst.Init.TIMode = SPI_TIMODE_DISABLED;
  OLED_SPIInst.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  OLED_SPIInst.Init.CRCPolynomial = 7;
  OLED_SPIInst.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  OLED_SPIInst.Init.NSSPMode = SPI_NSS_PULSE_ENABLED;
  HAL_SPI_Init(&OLED_SPIInst);
	
	// Initialisation
	
	
}
