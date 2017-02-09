
// _____ HAL Encoders ______

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "HAL_Encoders.h"

void _Encoder_A_Switch(void)
{

	
}

void _Encoder_B_Switch(void)
{

	
}

unsigned char _Encoder_A_Value(void)
{
	
	return 0;
}

unsigned char _Encoder_B_Value(void)
{
	
	return 0;
}


void Encoders_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Configure ENC A Switch Input Pin
	GPIO_InitStruct.Pin   = GPIO_PIN_14;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	// Configure ENC B Switch Input Pin
	GPIO_InitStruct.Pin   = GPIO_PIN_4;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// Configure ENC Data Inputs
	GPIO_InitStruct.Pin   		= GPIO_PIN_6 | GPIO_PIN_7;	// ENCA_L, ENCA_R
	GPIO_InitStruct.Mode  		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull  		= GPIO_PULLUP;
	GPIO_InitStruct.Alternate = 2;												// AF_TIM3
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin   		= GPIO_PIN_15;							// ENCB_L
	GPIO_InitStruct.Mode  		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull  		= GPIO_PULLUP;
	GPIO_InitStruct.Alternate = 1;												// AF_TIM2
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin   		= GPIO_PIN_3;								// ENC_R
	GPIO_InitStruct.Mode  		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull  		= GPIO_PULLUP;
	GPIO_InitStruct.Alternate = 1;												// AF_TIM2
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// Switch interrupts
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0x0F, 0x00);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0x00);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

