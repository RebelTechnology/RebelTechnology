#define SSD1309
#define OLED_DMA

#ifdef SSD1331
#define OLED_WIDTH			96
#define OLED_HEIGHT			64
#elif defined SEPS114A
#define OLED_WIDTH			96
#define OLED_HEIGHT			96
#elif defined SSD1309
#define OLED_WIDTH			128
#define OLED_HEIGHT			64
#endif


#define OLED_RST_Pin GPIO_PIN_2
#define OLED_RST_GPIO_Port GPIOC
#define OLED_MOSI_Pin GPIO_PIN_1
#define OLED_MOSI_GPIO_Port GPIOC
#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define OLED_SPI SPI2
#define OLED_DC_Pin GPIO_PIN_3
#define OLED_DC_GPIO_Port GPIOC
#define OLED_SCK_Pin GPIO_PIN_10
#define OLED_SCK_GPIO_Port GPIOB
