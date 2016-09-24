#define SSD1331
/* #define SEPS114A */

/* #define USE_CACHE */
/* #define USE_ADC */
/* #define ADC_DMA */
/* #define ADC_IT */
#define USE_ENCODERS
#define USE_SCREEN
#define OLED_SOFT_CS
/* #define OLED_DMA */
/* #define OLED_IT */
/* #define OLED_BITBANG */
/* #define USE_CODEC */
#define CODEC_SOFT_CS
#define CODEC_BLOCKSIZE 1024
/* #define CODEC_BLOCKSIZE 2048 // 23.4 FPS */
/* #define USE_OVERDRIVE // 216MHz */
/* #define QSPI_FLASH_SIZE (128*1024) */
/* #define USE_QSPI_FLASH */
/* #define USE_DMA2D */
/* #define USE_RNG */
#define MCU_CLOCK_168MHZ
#define USE_UART
#define USART_BAUDRATE               460800
#define USART_PERIPH                 USART1
#define USE_USB
#define MIDI_MAX_MESSAGE_SIZE        260

// MCOT096064 max recommended SPI speed 6.6MHz
// MCOT096096AY-RGBM max 5MHz
/* #define OLED_SPI_PRESCALER SPI_BAUDRATEPRESCALER_16  // 6.75MHz */
#define OLED_SPI_PRESCALER SPI_BAUDRATEPRESCALER_32  // 3.375MHz
/* #define OLED_SPI_PRESCALER SPI_BAUDRATEPRESCALER_64  // 1.6875MHz */
/* #define OLED_SPI_PRESCALER SPI_BAUDRATEPRESCALER_128 // 843.75kHz */

#define CODEC_BUFFER_SIZE (4*CODEC_BLOCKSIZE)
#ifdef SSD1331
#define OLED_WIDTH			96
#define OLED_HEIGHT			64
#elif defined SEPS114A
#define OLED_WIDTH			96
#define OLED_HEIGHT			96
#endif

#define QSPI_D2_Pin GPIO_PIN_2
#define QSPI_D2_GPIO_Port GPIOE
#define CS_SDOUT_Pin GPIO_PIN_3
#define CS_SDOUT_GPIO_Port GPIOE
#define CS_LRCK_Pin GPIO_PIN_4
#define CS_LRCK_GPIO_Port GPIOE
#define CS_SCLK_Pin GPIO_PIN_5
#define CS_SCLK_GPIO_Port GPIOE
#define CS_SDIN_Pin GPIO_PIN_6
#define CS_SDIN_GPIO_Port GPIOE
#define CS_SDA_Pin GPIO_PIN_1
#define CS_SDA_GPIO_Port GPIOC
#define ADC0_Pin GPIO_PIN_0
#define ADC0_GPIO_Port GPIOA
#define ADC1_Pin GPIO_PIN_1
#define ADC1_GPIO_Port GPIOA
#define OLED_RST_Pin GPIO_PIN_6
#define OLED_RST_GPIO_Port GPIOA
#define QSPI_CLK_Pin GPIO_PIN_2
#define QSPI_CLK_GPIO_Port GPIOB
#define SWENC_A_Pin GPIO_PIN_9
#define SWENC_A_GPIO_Port GPIOE
#define SW1_Pin GPIO_PIN_10
#define SW1_GPIO_Port GPIOE
#define SWENC_B_Pin GPIO_PIN_11
#define SWENC_B_GPIO_Port GPIOE
#define CS_SCL_Pin GPIO_PIN_10
#define CS_SCL_GPIO_Port GPIOB
#define USB_ID_Pin GPIO_PIN_12
#define USB_ID_GPIO_Port GPIOB
#define USB_VBUS_Pin GPIO_PIN_13
#define USB_VBUS_GPIO_Port GPIOB
#define USB_DM_Pin GPIO_PIN_14
#define USB_DM_GPIO_Port GPIOB
#define USB_DP_Pin GPIO_PIN_15
#define USB_DP_GPIO_Port GPIOB
#define QSPI_D0_Pin GPIO_PIN_11
#define QSPI_D0_GPIO_Port GPIOD
#define QSPI_D1_Pin GPIO_PIN_12
#define QSPI_D1_GPIO_Port GPIOD
#define QSPI_D3_Pin GPIO_PIN_13
#define QSPI_D3_GPIO_Port GPIOD
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOC
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOC
#define UART_TX_Pin GPIO_PIN_9
#define UART_TX_GPIO_Port GPIOA
#define UART_RX_Pin GPIO_PIN_10
#define UART_RX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWDCLK_Pin GPIO_PIN_14
#define SWDCLK_GPIO_Port GPIOA
#define OLED_MOSI_Pin GPIO_PIN_7
#define OLED_MOSI_GPIO_Port GPIOA
#define OLED_CS_Pin GPIO_PIN_15
#define OLED_CS_GPIO_Port GPIOA
#define OLED_SPI SPI1
#define OLED_DC_Pin GPIO_PIN_10
#define OLED_DC_GPIO_Port GPIOC
#define OLED_SCK_Pin GPIO_PIN_3
#define OLED_SCK_GPIO_Port GPIOB
#define CS_CS_Pin GPIO_PIN_4
#define CS_CS_GPIO_Port GPIOB
#define CS_RST_Pin GPIO_PIN_5
#define CS_RST_GPIO_Port GPIOB
#define QSPI_NCS_Pin GPIO_PIN_6
#define QSPI_NCS_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_9
#define SW2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
