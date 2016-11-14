/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define CS_SCK_Pin GPIO_PIN_2
#define CS_SCK_GPIO_Port GPIOE
#define CS_SDOUT_Pin GPIO_PIN_3
#define CS_SDOUT_GPIO_Port GPIOE
#define CS_LRCK_Pin GPIO_PIN_4
#define CS_LRCK_GPIO_Port GPIOE
#define CS_SCKE5_Pin GPIO_PIN_5
#define CS_SCKE5_GPIO_Port GPIOE
#define CS_SDA_Pin GPIO_PIN_6
#define CS_SDA_GPIO_Port GPIOE
#define EXTSPI_nCS_Pin GPIO_PIN_15
#define EXTSPI_nCS_GPIO_Port GPIOC
#define EXTSPI_SCK_Pin GPIO_PIN_7
#define EXTSPI_SCK_GPIO_Port GPIOF
#define EXTSPI_MISO_Pin GPIO_PIN_8
#define EXTSPI_MISO_GPIO_Port GPIOF
#define EXTSPI_MOSI_Pin GPIO_PIN_9
#define EXTSPI_MOSI_GPIO_Port GPIOF
#define ADC4_Pin GPIO_PIN_10
#define ADC4_GPIO_Port GPIOF
#define ADC3_Pin GPIO_PIN_1
#define ADC3_GPIO_Port GPIOC
#define ADC2_Pin GPIO_PIN_2
#define ADC2_GPIO_Port GPIOC
#define ADC1_Pin GPIO_PIN_3
#define ADC1_GPIO_Port GPIOC
#define PWM1_Pin GPIO_PIN_0
#define PWM1_GPIO_Port GPIOA
#define PWM2_Pin GPIO_PIN_1
#define PWM2_GPIO_Port GPIOA
#define FLASH_SCK_Pin GPIO_PIN_5
#define FLASH_SCK_GPIO_Port GPIOA
#define FLASH_MISO_Pin GPIO_PIN_6
#define FLASH_MISO_GPIO_Port GPIOA
#define FLASH_MOSI_Pin GPIO_PIN_7
#define FLASH_MOSI_GPIO_Port GPIOA
#define FLASH_HOLD_Pin GPIO_PIN_4
#define FLASH_HOLD_GPIO_Port GPIOC
#define FLASH_NCS_Pin GPIO_PIN_5
#define FLASH_NCS_GPIO_Port GPIOC
#define PWM3_Pin GPIO_PIN_1
#define PWM3_GPIO_Port GPIOB
#define CS_SDIN_Pin GPIO_PIN_6
#define CS_SDIN_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
