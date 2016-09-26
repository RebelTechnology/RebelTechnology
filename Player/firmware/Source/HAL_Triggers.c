
// _____ HAL Triggers ______

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "HAL_Triggers.h"

void _Trigger_IN_A(void)
{
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))		// Rising Edge
	{
	
	}
	else																				// Falling Edge
	{
	
	}
}

void _Trigger_IN_B(void)
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2))		// Rising Edge
	{
	
	}
	else																				// Falling Edge
	{
	
	}
}

void Trigger_OUT_A(uint8_t state)
{
	if (!state)	{HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);}
	else				{HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);}
}

void Trigger_OUT_B(uint8_t state)
{
	if (!state)	{HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);}
	else				{HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);}
}

void Triggers_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// Configure Input Pins
	GPIO_InitStruct.Pin   = GPIO_PIN_10 | GPIO_PIN_11;		// TR_IN_A & TR_IN_B
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	// Configure Output Pins
	GPIO_InitStruct.Pin   = GPIO_PIN_12;				// TR_OUT_A
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin   = GPIO_PIN_2;				// TR_OUT_B
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
