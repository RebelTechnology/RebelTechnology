/**
 * MAX11300 on SPI1
 * TLC5946 on SPI2
 * Digital Bus on USART1
 */
#define USART_BAUDRATE               115200
#define USART_PERIPH                 USART1

#define MAX_CS_Pin GPIO_Pin_4
#define MAX_CS_GPIO_Port GPIOA
#define MAX_SCLK_Pin GPIO_Pin_5
#define MAX_SCLK_GPIO_Port GPIOA
#define MAX_DOUT_Pin GPIO_Pin_6
#define MAX_DOUT_GPIO_Port GPIOA
#define MAX_DIN_Pin GPIO_Pin_7
#define MAX_DIN_GPIO_Port GPIOA
#define TLC_BLANK_Pin GPIO_Pin_12
#define TLC_BLANK_GPIO_Port GPIOB
#define TLC_SCLK_Pin GPIO_Pin_13
#define TLC_SCLK_GPIO_Port GPIOB
#define TLC_SOUT_Pin GPIO_Pin_14
#define TLC_SOUT_GPIO_Port GPIOB
#define TLC_SIN_Pin GPIO_Pin_15
#define TLC_SIN_GPIO_Port GPIOB
#define TLC_MODE_Pin GPIO_Pin_8
#define TLC_MODE_GPIO_Port GPIOA
#define TLC_GSCLK_Pin GPIO_Pin_9
#define TLC_GSCLK_GPIO_Port GPIOA
#define TLC_XLAT_Pin GPIO_Pin_10
#define TLC_XLAT_GPIO_Port GPIOA
#define TLC_XERR_Pin GPIO_Pin_11
#define TLC_XERR_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_Pin_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_Pin_14
#define SWCLK_GPIO_Port GPIOA
