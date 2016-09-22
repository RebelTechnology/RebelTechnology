#include "stm32f1xx_hal.h"
#include "HAL_MAX11300.h"
 
SPI_HandleTypeDef* MAX11300_SPIConfig;
 
//_____ Functions _____________________________________________________________________________________________________
// Port and Chip Setup
void MAX11300_setPortMode(uint8_t port, uint16_t config)
{
	uint8_t rgData[3] = "";
     
	// separate config into two bytes
	rgData[0] = (ADDR_CFGbase+port)<<1 | SPI_Write;
	rgData[1] = (config&0xFF00)>>8;
	rgData[2] = (config&0x00FF);
     
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, rgData, sizeof rgData, 100);
	pbarCS(1);
	
	Nop_delay(1000);
}

uint16_t MAX11300_readPortMode(uint8_t port)
{
	uint8_t ucAddress, rgRtnData[2] = "";
	uint16_t usiRtnValue = 0;
	 
	ucAddress = (ADDR_CFGbase+port)<<1 | SPI_Read;
	
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, &ucAddress, 1, 100);
	HAL_SPI_Receive(MAX11300_SPIConfig, rgRtnData, 2, 100);
	pbarCS(1);
	
	usiRtnValue  = rgRtnData[0]<<8;
	usiRtnValue += rgRtnData[1];
	
	return usiRtnValue;
}

void MAX11300_setDeviceControl(uint16_t config)
{
	uint8_t rgData[3] = "";
	
	rgData[0] = (ADDR_DevCont)<<1 | SPI_Write;
	rgData[1] = (config&0xFF00)>>8;
	rgData[2] = (config&0x00FF);
	
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, rgData, sizeof rgData, 100);
	pbarCS(1);
	
	Nop_delay(10000);
}

// ADC Functions
uint16_t MAX11300_readADC(uint8_t port)
{
	uint8_t ucAddress=0, rgRtnData[2] = "";
	uint16_t usiRtnValue = 0;
	 
	ucAddress = (ADDR_ADCbase+port)<<1 | SPI_Read;
	
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, &ucAddress, 1, 100);
	HAL_SPI_Receive(MAX11300_SPIConfig, rgRtnData, 2, 100);
	pbarCS(1);
	
	usiRtnValue  = rgRtnData[0]<<8;
	usiRtnValue += rgRtnData[1];
	
	return usiRtnValue & 0xFFF;
}
 
// DAC Functions
void MAX11300_setDAC(uint8_t port, uint16_t value)
{
	uint8_t rgData[3] = "";
	 
	rgData[0] = (ADDR_DACbase+port)<<1 | SPI_Write;
	rgData[1] = (value&0xFF00)>>8;
	rgData[2] = (value&0x00FF);
	 
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, rgData, sizeof rgData, 100);
	pbarCS(1);
}

uint16_t MAX11300_readDAC(uint8_t port)
{
	uint8_t ucAddress, rgRtnData[2] = "";
	uint16_t usiRtnValue = 0;
	 
	ucAddress = (ADDR_DACbase+port)<<1 | SPI_Read;
	
	pbarCS(0);
	HAL_SPI_Transmit(MAX11300_SPIConfig, &ucAddress, 1, 100);
	HAL_SPI_Receive(MAX11300_SPIConfig, rgRtnData, 2, 100);
	pbarCS(1);
	
	usiRtnValue  = rgRtnData[0]<<8;
	usiRtnValue += rgRtnData[1];
	
	return usiRtnValue & 0xFFF;
}
 
//_____ Initialisaion _________________________________________________________________________________________________
void MAX11300_init (SPI_HandleTypeDef *spiconfig)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, MAX_CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : MAX_CS_Pin */
	GPIO_InitStruct.Pin = MAX_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(MAX_CS_GPIO_Port, &GPIO_InitStruct);
	 
	MAX11300_SPIConfig = spiconfig;
}

void Nop_delay(uint32_t nops)
{
	while (nops--){}
}

