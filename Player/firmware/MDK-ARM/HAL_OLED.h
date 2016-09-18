#include "stm32f7xx_hal.h"

// _____ Defines _______________________________________________________________________
#define pRST_Set()	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET)
#define pDC_Set()		HAL_GPIO_WritePin(OLED_DC_GPIO_Port, 	OLED_DC_Pin, 	GPIO_PIN_SET)
#define pCS_Set()		HAL_GPIO_WritePin(OLED_CS_GPIO_Port, 	OLED_CS_Pin, 	GPIO_PIN_SET)

#define pRST_Clr()	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET)
#define pDC_Clr()		HAL_GPIO_WritePin(OLED_DC_GPIO_Port, 	OLED_DC_Pin, 	GPIO_PIN_RESET)
#define pCS_Clr()		HAL_GPIO_WritePin(OLED_CS_GPIO_Port, 	OLED_CS_Pin, 	GPIO_PIN_RESET)

#define OLED_DAT	1
#define OLED_CMD	0

// _____ Prototypes ____________________________________________________________________
void OLED_writeCMD(const uint8_t* data, uint16_t length);
void OLED_writeDAT(const uint8_t* data, uint16_t length);
uint8_t OLED_getPixel(uint8_t x, uint8_t y);
void OLED_setPixel(uint8_t x, uint8_t y);
void OLED_clearPixel(uint8_t x, uint8_t y);
void OLED_togglePixel(uint8_t x, uint8_t y);
void OLED_Refresh(void);
void OLED_ClearScreen(void);
void OLED_Config(void);
void NopDelay(uint32_t nops);

// _____ Variables _____________________________________________________________________
extern unsigned char OLED_Buffer[1024];

static const uint8_t OLED_initSequence[] = 
{
	0xfd, 0x12, 	// Command lock
	0xae, 				// Display off
	0xd5, 0xa0, 	// Clock divide ratio / Oscillator Frequency
	0xa8, 0x3f, 	// Multiplex ratio
	0xd3, 0x00, 	// Display offset
	0x40, 				// Start line
	0xa1, 				// segment re-map
	0xc8, 				// scan direction
	0xda, 0x12, 	// COM pins
	0x81, 0xcf, 	// Current control
	0xd9, 0x22, 	// Pre-charge period
	0xdb, 0x34, 	// VCOMH deselect level
	0xa4, 				// Entire display on/off
	0xa6, 				// Normal / inverse display
	0x20, 0x01,   // Vertical addressing mode
	0xaf, 				// Display on
};
