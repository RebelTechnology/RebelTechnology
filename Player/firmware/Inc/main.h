#include "stm32f7xx_hal.h"
#include "usb_device.h"
#include "usb_host.h"

// _____ Variables _________________________________________________________
ADC_HandleTypeDef hadc1;
DAC_HandleTypeDef hdac;
DMA2D_HandleTypeDef hdma2d;
I2C_HandleTypeDef hi2c1;
RNG_HandleTypeDef hrng;
SAI_HandleTypeDef hsai_BlockA1;
SAI_HandleTypeDef hsai_BlockB1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi5;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;
SDRAM_HandleTypeDef hsdram1;

// _____ Protoypes _________________________________________________________7
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_DAC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C1_Init(void);
static void MX_RNG_Init(void);
static void MX_SAI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI5_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
void MX_USB_HOST_Process(void);



