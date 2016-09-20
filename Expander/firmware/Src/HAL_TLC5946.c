#include "stm32f1xx_hal.h"
#include "HAL_MAX11300.h"
 
SPI_HandleTypeDef* MAX11300_SPIConfig;
 
//_____ Functions _____________________________________________________________________________________________________
void MAX11300_ConfigPort(unsigned char port, unsigned short config)
{
    unsigned char rgData[3] = "";
     
    rgData[0]  = (ADDR_CFGbase+port)<<1 | SPI_Write;
    rgData[1]  = port;
    rgData[1] |= (config&0xFF00)>>8;
    rgData[2]  = (config&0x00FF);
     
    pbarCS(0);
    HAL_SPI_Transmit(MAX11300_SPIConfig, rgData, sizeof rgData, 100);
    pbarCS(1);
}
 
unsigned char MAX11300_GetPortMode(unsigned char port)
{
    unsigned char ucRtnValue = 0;
     
     
    pbarCS(0);
     
    pbarCS(1);
     
    return ucRtnValue;
}
 
unsigned short MAX11300_ReadADC(unsigned char port)
{
    unsigned char usiRtnValue = 0;
         
    pbarCS(0);
     
    pbarCS(1);
     
    return usiRtnValue;
}
 
void MAX11300_SetDAC(unsigned char port, unsigned short value)
{
    unsigned char rgData[3] = "";
     
    rgData[0]  = (ADDR_DACbase+port)<<1 | SPI_Write;
    rgData[1]  = port;
    rgData[1] |= (value&0xFF00)>>8;
    rgData[2]  = (value&0x00FF);
     
    pbarCS(0);
    HAL_SPI_Transmit(MAX11300_SPIConfig, rgData, sizeof rgData, 100);
    pbarCS(1);
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
