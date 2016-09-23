/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"
#include "cmsis_os.h"
#include "mxconstants.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */
#if 0 // see bus.cpp
#include "errorhandlers.h"
void serial_rx_callback(uint8_t c);
#endif
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_HS;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_sai1_rx;
extern DMA_HandleTypeDef hdma_sai1_tx;
extern DMA_HandleTypeDef hdma_spi1_tx;
extern UART_HandleTypeDef huart1;

/******************************************************************************/
/*            Cortex-M7 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE END SysTick_IRQn 0 */
  osSystickHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

#if 0 // see bus.cpp
/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
  UART_HandleTypeDef *huart = &huart1;
  uint32_t isrflags   = READ_REG(huart->Instance->ISR);
  /* uint32_t cr1its     = READ_REG(huart->Instance->CR1); */
  /* uint32_t cr3its     = READ_REG(huart->Instance->CR3); */
  uint32_t errorflags = (isrflags & (uint32_t)(USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE));
  /* uint16_t uhMask = huart->Mask; */
  /* If no error occurs */
  if(errorflags == RESET){
    /* UART in mode Receiver ---------------------------------------------------*/
    if(((isrflags & USART_ISR_RXNE) != RESET)) // && ((cr1its & USART_CR1_RXNEIE) != RESET))
      /* serial_rx_callback((uint8_t)(huart->Instance->RDR & (uint8_t)uhMask)); */
      serial_rx_callback((uint8_t)(huart->Instance->RDR));
  }else{
    /* If some errors occur */
    /* if((errorflags != RESET) && ((cr3its & (USART_CR3_EIE | USART_CR1_PEIE)) != RESET)){ */
      /* UART parity error interrupt occurred -------------------------------------*/
    if(((isrflags & USART_ISR_PE) != RESET)) //  && ((cr1its & USART_CR1_PEIE) != RESET))
      {
	__HAL_UART_CLEAR_IT(huart, UART_CLEAR_PEF);
	setErrorMessage(UART_ERROR, "uart parity error");
	huart->ErrorCode |= HAL_UART_ERROR_PE;
      }
    /* UART frame error interrupt occurred --------------------------------------*/
    if(((isrflags & USART_ISR_FE) != RESET)) // && ((cr3its & USART_CR3_EIE) != RESET))
      {
	__HAL_UART_CLEAR_IT(huart, UART_CLEAR_FEF);
	setErrorMessage(UART_ERROR, "uart frame error");
	huart->ErrorCode |= HAL_UART_ERROR_FE;
      }
    /* UART noise error interrupt occurred --------------------------------------*/
    if(((isrflags & USART_ISR_NE) != RESET)) // && ((cr3its & USART_CR3_EIE) != RESET))
      {
	__HAL_UART_CLEAR_IT(huart, UART_CLEAR_NEF);
	setErrorMessage(UART_ERROR, "uart noise error");
	huart->ErrorCode |= HAL_UART_ERROR_NE;
      }    
    /* UART Over-Run interrupt occurred -----------------------------------------*/
    if(((isrflags & USART_ISR_ORE) != RESET)) //  &&
      // (((cr1its & USART_CR1_RXNEIE) != RESET) || ((cr3its & USART_CR3_EIE) != RESET)))
      {
	__HAL_UART_CLEAR_IT(huart, UART_CLEAR_OREF);
	__HAL_UART_FLUSH_DRREGISTER(huart);
	setErrorMessage(UART_ERROR, "uart overrun");
	huart->ErrorCode |= HAL_UART_ERROR_ORE;
      }
  }
  /* USER CODE END USART1_IRQn 0 */
  /* HAL_UART_IRQHandler(&huart1); */
  /* USER CODE BEGIN USART1_IRQn 1 */
  /* USER CODE END USART1_IRQn 1 */
}
#endif

/**
* @brief This function handles DMA2 stream0 global interrupt.
*/
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */
  // ADC DMA
  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */
  if(__HAL_DMA_GET_FLAG(&hdma_adc1,  __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_adc1)))
    __HAL_DMA_CLEAR_FLAG(&hdma_adc1, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_adc1));
  if(__HAL_DMA_GET_FLAG(&hdma_adc1,  __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_adc1)))
    __HAL_DMA_CLEAR_FLAG(&hdma_adc1, __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_adc1));
  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
* @brief This function handles DMA2 stream1 global interrupt.
*/
void DMA2_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream1_IRQn 0 */
  // SAI TX: memory to peripheral/codec 
  static int counter = 0;
  counter++;
  /* USER CODE END DMA2_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sai1_tx);
  /* USER CODE BEGIN DMA2_Stream1_IRQn 1 */
  if(__HAL_DMA_GET_FLAG(&hdma_sai1_tx, DMA_FLAG_TCIF1_5))
    __HAL_DMA_CLEAR_FLAG(&hdma_sai1_tx, DMA_FLAG_TCIF1_5); // transfer complete
  if(__HAL_DMA_GET_FLAG(&hdma_sai1_tx, DMA_FLAG_HTIF1_5))
    __HAL_DMA_CLEAR_FLAG(&hdma_sai1_tx, DMA_FLAG_HTIF1_5); // half transfer complete
  /* USER CODE END DMA2_Stream1_IRQn 1 */
}

#ifdef OLED_SOFT_CS
#define setCS()    setPin(OLED_CS_GPIO_Port, OLED_CS_Pin)
#define clearCS()  clearPin(OLED_CS_GPIO_Port, OLED_CS_Pin)
#else
#define setCS()    
#define clearCS()
#endif
extern SPI_HandleTypeDef hspi1;

/**
* @brief This function handles DMA2 stream3 global interrupt.
*/
static int otxcounter = 0;
void DMA2_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream3_IRQn 0 */
  // SPI1_TX OLED TX
  otxcounter++;
  /* USER CODE END DMA2_Stream3_IRQn 0 */

  // calling the HAL IRQ handler triggers a TC callback too soon
  HAL_DMA_IRQHandler(&hdma_spi1_tx);

  /* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

  if(__HAL_DMA_GET_FLAG(&hdma_spi1_tx,  __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx)))
    __HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx));
  if(__HAL_DMA_GET_FLAG(&hdma_spi1_tx,  __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_spi1_tx)))
    __HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx, __HAL_DMA_GET_HT_FLAG_INDEX(&hdma_spi1_tx));

  /* if(__HAL_DMA_GET_FLAG(&hdma_spi1_tx,  __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx))){ */
  /*   __HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx)); */
  /*   setCS();     */
  /*   /\* Update error code *\/ */
  /*   hdma_spi1_tx.ErrorCode |= HAL_DMA_ERROR_NONE; */
  /*   /\* Change the DMA state *\/ */
  /*   hdma_spi1_tx.State = HAL_DMA_STATE_READY_MEM0; */
  /*   /\* Process Unlocked *\/ */
  /*   __HAL_UNLOCK(&hdma_spi1_tx); */
  /*   hspi1.TxXferCount = 0; */
  /*   hspi1.State = HAL_SPI_STATE_READY; */
  /* } */

  /* user CODE END DMA2_Stream3_IRQn 1 */
}

/**
* @brief This function handles DMA2 stream4 global interrupt.
*/
void DMA2_Stream4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream4_IRQn 0 */
  // SAI RX: peripheral/codec to memory
  static int counter = 0;
  counter++;
  /* USER CODE END DMA2_Stream4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sai1_rx);
  /* USER CODE BEGIN DMA2_Stream4_IRQn 1 */
  if(__HAL_DMA_GET_FLAG(&hdma_sai1_rx, DMA_FLAG_TCIF0_4))
    __HAL_DMA_CLEAR_FLAG(&hdma_sai1_rx, DMA_FLAG_TCIF0_4); // transfer complete
  if(__HAL_DMA_GET_FLAG(&hdma_sai1_rx, DMA_FLAG_HTIF0_4))
    __HAL_DMA_CLEAR_FLAG(&hdma_sai1_rx, DMA_FLAG_HTIF0_4); // half transfer complete
  /* USER CODE END DMA2_Stream4_IRQn 1 */
}

/**
* @brief This function handles USB On The Go HS global interrupt.
*/
void OTG_HS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_HS_IRQn 0 */

  /* USER CODE END OTG_HS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
  /* USER CODE BEGIN OTG_HS_IRQn 1 */

  /* USER CODE END OTG_HS_IRQn 1 */
}

/* USER CODE BEGIN 1 */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

void TIM1_CC_IRQHandler(void){
  HAL_TIM_IRQHandler(&htim1);
}

void TIM3_IRQHandler(void){
  HAL_TIM_IRQHandler(&htim3);
}

extern ADC_HandleTypeDef hadc1;

void ADC_IRQHandler(void){
  HAL_ADC_IRQHandler(&hadc1);
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
