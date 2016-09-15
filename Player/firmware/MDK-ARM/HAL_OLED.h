
#define pRST_Set	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET);
#define pDC_Set		HAL_GPIO_WritePin(OLED_DC_GPIO_Port, 	OLED_DC_Pin, 	GPIO_PIN_SET);

#define pRST_Clr	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
#define pDC_Clr		HAL_GPIO_WritePin(OLED_DC_GPIO_Port, 	OLED_DC_Pin, 	GPIO_PIN_RESET);

#define OLED_DAT	1
#define OLED_CMD	0

void OLED_writeByte(unsigned short address, unsigned char byte);
unsigned char OLED_readByte(unsigned char address);
void OLED_Refresh(void);
void OLED_ClearScreen(void);
void OLED_Config(void);

unsigned char OLED_Buffer[1024];
