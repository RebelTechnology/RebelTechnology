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

#define CS_SCL_Pin GPIO_PIN_2
#define CS_SCL_GPIO_Port GPIOE
#define CS_SDOUT_Pin GPIO_PIN_3
#define CS_SDOUT_GPIO_Port GPIOE
#define CS_LRCK_Pin GPIO_PIN_4
#define CS_LRCK_GPIO_Port GPIOE
#define CS_SCLK_Pin GPIO_PIN_5
#define CS_SCLK_GPIO_Port GPIOE
#define CS_SDA_Pin GPIO_PIN_6
#define CS_SDA_GPIO_Port GPIOE
#define Flash_CS_Pin GPIO_PIN_6
#define Flash_CS_GPIO_Port GPIOF
#define Flash_CLK_Pin GPIO_PIN_7
#define Flash_CLK_GPIO_Port GPIOF
#define Flash_MISO_Pin GPIO_PIN_8
#define Flash_MISO_GPIO_Port GPIOF
#define Flash_MOSI_Pin GPIO_PIN_9
#define Flash_MOSI_GPIO_Port GPIOF
#define OLED_MOSI_Pin GPIO_PIN_1
#define OLED_MOSI_GPIO_Port GPIOC
#define OLED_RST_Pin GPIO_PIN_2
#define OLED_RST_GPIO_Port GPIOC
#define OLED_DC_Pin GPIO_PIN_3
#define OLED_DC_GPIO_Port GPIOC
#define CV_IN_A_Pin GPIO_PIN_0
#define CV_IN_A_GPIO_Port GPIOA
#define CV_IN_B_Pin GPIO_PIN_1
#define CV_IN_B_GPIO_Port GPIOA
#define CS_SDIN_Pin GPIO_PIN_2
#define CS_SDIN_GPIO_Port GPIOB
#define OLED_SCK_Pin GPIO_PIN_10
#define OLED_SCK_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define CS_CS_Pin GPIO_PIN_9
#define CS_CS_GPIO_Port GPIOG
#define CS_RST_Pin GPIO_PIN_10
#define CS_RST_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

#define USB_DM_Pin GPIO_PIN_14
#define USB_DP_Pin GPIO_PIN_15

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
