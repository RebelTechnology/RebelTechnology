
// _____ HAL CV IO ______

/* Includes ------------------------------------------------------------------*/
#include "HAL_CV_IO.h"

void CV_Out_A (DAC_HandleTypeDef* hdac, unsigned short millivolts)
{
	uint16_t usiDACValue = millivolts / 1;
	
	HAL_DAC_SetValue(hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, usiDACValue);
}

void CV_Out_B (DAC_HandleTypeDef* hdac, unsigned short millivolts)
{
	uint16_t usiDACValue = millivolts / 1;
	
	HAL_DAC_SetValue(hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, usiDACValue);
}

unsigned short CV_In_A (ADC_HandleTypeDef* hadc)
{
	HAL_ADC_GetValue(hadc);
	return 0;
}

unsigned short CV_IN_B (ADC_HandleTypeDef* hadc)
{
	HAL_ADC_GetValue(hadc);
	return 0;
}


void CV_IO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Configure DAC Output Pins
	GPIO_InitStruct.Pin   = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		// Configure ADC Input Pins
	GPIO_InitStruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	  
}
