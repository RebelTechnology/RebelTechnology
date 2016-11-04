#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
// #include "fatfs.h"

/* USER CODE BEGIN Includes */
#include "Graphics.h"
#include "Codec.h"
#include "qspi.h"
#include "errorhandlers.h"
#include "Prism.h"
#include "ProgramVector.h"
#include "bus.h"
#include "midi.h"
#ifdef USE_USB
#include "usb_device.h"
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

DMA2D_HandleTypeDef hdma2d;

QSPI_HandleTypeDef hqspi;

RNG_HandleTypeDef hrng;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

osThreadId screenTaskHandle;
#ifdef USE_SCREEN
Graphics graphics;
#endif
#ifdef USE_CODEC
Codec codec;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
extern "C"{
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
#ifdef USE_DMA2D
static void MX_DMA2D_Init(void);
#endif
#ifdef USE_QSPI_FLASH
static void MX_QUADSPI_Init(void);
#endif
#ifdef USE_RNG
static void MX_RNG_Init(void);
#endif
// static void MX_SAI1_Init(void);
static void MX_SPI1_Init(void);
// static void MX_SPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
#ifdef USE_UART
static void MX_USART1_UART_Init(void);
#endif
#ifdef USE_USB
static void MX_USB_OTG_HS_USB_Init(void);
#endif

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void StartScreenTask(void const * argument);
void readadc();

}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

#ifdef USE_CACHE
  /* Enable I-Cache-------------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache-------------------------------------------------------------*/
  SCB_EnableDCache();
#endif
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
#ifdef USE_DMA2D
  MX_DMA2D_Init();
#endif
#ifdef USE_QSPI_FLASH
  MX_QUADSPI_Init();
#endif
#ifdef USE_RNG
  MX_RNG_Init();
#endif
  // MX_SAI1_Init();
  MX_SPI1_Init();
  // MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
#ifdef USE_UART
  MX_USART1_UART_Init();
#endif
#ifdef USE_USB
  MX_USB_OTG_HS_USB_Init();
#endif

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  osThreadDef(screenTask, StartScreenTask, osPriorityNormal, 0, 128);
  screenTaskHandle = osThreadCreate(osThread(screenTask), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;

#ifdef MCU_CLOCK_168MHZ
  // 168MHz
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
#else
  // 216MHz
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
#endif

  HAL_RCC_OscConfig(&RCC_OscInitStruct);

#ifdef USE_OVERDRIVE
  HAL_PWREx_ActivateOverDrive();
#endif

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SAI1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 100;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION12b;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  hadc1.Init.DMAContinuousRequests = ENABLE;
#if defined ADC_IT
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
// #elif defined ADC_DMA
//   hadc1.Init.EOCSelection = DISABLE;
//   hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
#else
  hadc1.Init.EOCSelection = DISABLE;
#endif
  HAL_ADC_Init(&hadc1);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES; // 3CYCLES - 480CYCLES
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = 3;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = 4;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

/* DMA2D init function */
#ifdef USE_DMA2D
void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = CM_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  HAL_DMA2D_Init(&hdma2d);
  HAL_DMA2D_ConfigLayer(&hdma2d, 1);
}
#endif

/* QUADSPI init function */
#ifdef USE_QSPI_FLASH
void MX_QUADSPI_Init(void)
{
  // hqspi.Instance = QUADSPI;
  // hqspi.Init.ClockPrescaler = 255;
  // hqspi.Init.FifoThreshold = 1;
  // hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  // hqspi.Init.FlashSize = 1;
  // hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  // hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  // HAL_QSPI_Init(&hqspi);

  /* ClockPrescaler set to 2, so QSPI clock = 216MHz / (2+1) = 72MHz */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 2;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = QSPI_FLASH_SIZE;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  HAL_QSPI_DeInit(&hqspi);
  HAL_QSPI_Init(&hqspi);
}
#endif

/* RNG init function */
#ifdef USE_RNG
void MX_RNG_Init(void)
{
  hrng.Instance = RNG;
  HAL_RNG_Init(&hrng);
}
#endif

/* SPI1 init function */
/* OLED SPI */
void MX_SPI1_Init(void)
{
  hspi1.Instance = OLED_SPI;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  // SPI mode 0
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
#ifdef OLED_SOFT_CS
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLED;
#else
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLED;
#endif
  hspi1.Init.BaudRatePrescaler = OLED_SPI_PRESCALER;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  HAL_SPI_Init(&hspi1);
}

/* TIM1 init function */
/* SwEncoder ch1 and ch2 */
void MX_TIM1_Init(void)
{

  TIM_Encoder_InitTypeDef sConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  HAL_TIM_Encoder_Init(&htim1, &sConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

}

/* TIM3 init function */
/* Encoder ch1 and ch2 */
void MX_TIM3_Init(void)
{

  TIM_Encoder_InitTypeDef sConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xffff;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  HAL_TIM_Encoder_Init(&htim3, &sConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = USART_BAUDRATE;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  // huart1.Init.WordLength = UART_WORDLENGTH_7B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  // huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  // huart1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  // HAL_MultiProcessor_Init(&huart1, 0, UART_WAKEUPMETHOD_IDLELINE);
  // ASSERT(HAL_UART_DeInit(&huart1) == HAL_OK);
  // ASSERT(HAL_UART_Init(&huart1) == HAL_OK);
  HAL_UART_Init(&huart1);

}

/* USB_OTG_HS init function */
void MX_USB_OTG_HS_USB_Init(void)
{
#ifdef USE_USB
  MX_USB_DEVICE_Init();
#endif
}

/** 
  * Enable DMA controller clock
  */
void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
#ifdef OLED_DMA
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
#endif
  HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PB12   ------> USB_OTG_HS_ID
     PB14   ------> USB_OTG_HS_DM
     PB15   ------> USB_OTG_HS_DP
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOE_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();

#ifdef OLED_SOFT_CS
  /*Configure GPIO pin : OLED_CS_Pin */
  GPIO_InitStruct.Pin = OLED_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(OLED_CS_GPIO_Port, &GPIO_InitStruct);
#endif

  /*Configure GPIO pin : OLED_RST_Pin */
  GPIO_InitStruct.Pin = OLED_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(OLED_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW1_Pin */
  GPIO_InitStruct.Pin = SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : OLED_DC_Pin */
  GPIO_InitStruct.Pin = OLED_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(OLED_DC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_RST_Pin */
  GPIO_InitStruct.Pin = CS_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(CS_RST_GPIO_Port, &GPIO_InitStruct);

#ifdef CODEC_SOFT_CS
  /*Configure GPIO pin : CS_CS_Pin */
  GPIO_InitStruct.Pin = CS_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(CS_CS_GPIO_Port, &GPIO_InitStruct);
#endif

  /*Configure GPIO pin : SW2_Pin */
  GPIO_InitStruct.Pin = SW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW2_GPIO_Port, &GPIO_InitStruct);

#ifdef OLED_BITBANG

  /*Configure GPIO pin : OLED_SCK_Pin */
  GPIO_InitStruct.Pin = OLED_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(OLED_SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OLED_MOSI_Pin */
  GPIO_InitStruct.Pin = OLED_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(OLED_MOSI_GPIO_Port, &GPIO_InitStruct);
#endif
}

/* USER CODE BEGIN 4 */

extern "C" {
  void delay(uint32_t ms){
    osDelay(ms);
  }
}

ProgramVector programVector;
// ProgramVector pv;

uint16_t adc_values[NOF_PARAMETERS];
volatile bool doProcessAudio = false;
uint32_t dropouts = 0;
extern "C" {
  void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size){
    if(!doProcessAudio){
      programVector.audio_input = rx;
      programVector.audio_output = tx;
      programVector.audio_blocksize = size;
      doProcessAudio = true;
    }else{
      dropouts++;
    }
  }
}

#ifdef USE_QSPI_FLASH
uint8_t qspitx[128] = "hello and welcome once again";
uint8_t qspirx[128];
#endif
bool dotxrx = false;
bool dodisplay = true;
static uint16_t pixelbuffer[2][OLED_HEIGHT*OLED_WIDTH];
int swappb = 0;

void updateProgramVector(ProgramVector* pv){
  pv->checksum = sizeof(ProgramVector);
  pv->hardware_version = PRISM_HARDWARE;
  pv->parameters_size = NOF_PARAMETERS;
  pv->parameters = adc_values;
  pv->audio_bitdepth = 24;
  pv->audio_samplingrate = 48000;
  pv->buttons = 0;
  pv->registerPatch = NULL;
  pv->registerPatchParameter = NULL;
  pv->cycles_per_block = 0;
  pv->heap_bytes_used = 0;
  pv->programReady = NULL;
  pv->programStatus = NULL;
  pv->serviceCall = NULL;
  pv->message = NULL;
  pv->pixels = pixelbuffer[0];
  pv->screen_width = OLED_WIDTH;
  pv->screen_height = OLED_HEIGHT;
}

void StartScreenTask(void const * argument)
{
#ifdef USE_QSPI_FLASH
  /* Enable write operations ------------------------------------------- */
  QSPI_WriteEnable(&hqspi);
  qspi_erase(0, 128);
  osDelay(1000);
  qspi_write(0, qspitx, 29);
  osDelay(1000);
  qspi_read(0, qspirx, 29);
  osDelay(1000);
#endif

  HAL_StatusTypeDef ret;

#ifdef USE_ADC
#ifdef ADC_DMA
  ret = HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 4);
  ASSERT(ret == HAL_OK, "adc1 dma start failed");
#elif defined ADC_IT
  ret = HAL_ADC_Start_IT(&hadc1);
  ASSERT(ret == HAL_OK, "adc1 it start failed");
#endif
  // ret = HAL_ADC_Start(&hadc1);
  // ASSERT(ret == HAL_OK, "adc1 start failed");
#endif

#ifdef USE_ENCODERS
  __HAL_TIM_SetCounter(&htim1, INT16_MAX/2);
  __HAL_TIM_SetCounter(&htim3, INT16_MAX/2);
  ret = HAL_TIM_Encoder_Start_IT(&htim1, 0);
  ASSERT(ret == HAL_OK, "tim1 encoder start failed");
  ret = HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
  ASSERT(ret == HAL_OK, "tim3 encoder start failed");    
#endif

#ifdef USE_UART
  bus_setup();
#endif

#ifdef USE_CODEC
  codec.reset();
#endif

#ifdef USE_SCREEN
  graphics.begin(&hspi1);
#endif

  updateProgramVector(&programVector);
  setup(&programVector);

#ifdef USE_CODEC
  codec.start();
  if(dotxrx){
    // make sure functions are compiled in
    codec.bypass(false);
    codec.ramp(1<<23);
    codec.set(0);
    codec.stop();
    codec.clear();
    codec.txrx();
  }
#endif

  for(;;){
    if(doProcessAudio){
      processBlock(&programVector);
      if(dodisplay){
      // if(dodisplay && graphics.isReady()){
	graphics.display(programVector.pixels, OLED_WIDTH*OLED_HEIGHT);
	// swap pixelbuffer
	programVector.pixels = pixelbuffer[swappb];
	swappb = !swappb;
      }

#ifdef USE_ADC
#if !defined ADC_DMA && !defined ADC_IT
      readadc();
#endif
#endif
      doProcessAudio = false;
    }
#ifndef USE_CODEC
    // doProcessAudio will never be true
    processBlock(&programVector);
    // while(!graphics.isReady()); // wait
    graphics.display(programVector.pixels, OLED_WIDTH*OLED_HEIGHT);
    // swap pixelbuffer
    programVector.pixels = pixelbuffer[swappb];
    swappb = !swappb;
    // this is only used for rack mount so we'll skip adc
#endif
#ifdef USE_UART
  bus_status();
#endif
  }
}

/* USER CODE END 4 */

void readadc(){
  HAL_StatusTypeDef ret;
  ret = HAL_ADC_Start(&hadc1);
  ASSERT(ret == HAL_OK, "adc1 start failed");
  if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    adc_values[0] = HAL_ADC_GetValue(&hadc1);
  if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    adc_values[1] = HAL_ADC_GetValue(&hadc1);
  // if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
  //   adc_values[2] = HAL_ADC_GetValue(&hadc1);
  // if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
  //   adc_values[3] = HAL_ADC_GetValue(&hadc1);
  ret = HAL_ADC_Stop(&hadc1);
  ASSERT(ret == HAL_OK, "adc1 stop failed");
}

void encoderReset(uint8_t encoder, int32_t value){
  if(encoder == 0)
    __HAL_TIM_SetCounter(&htim1, value);
  else if(encoder == 1)
    __HAL_TIM_SetCounter(&htim3, value);
}

extern "C" {
  void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    if(htim == &htim1)
      encoderChanged(0, __HAL_TIM_GET_COUNTER(&htim1));
    else if(htim == &htim3)
      encoderChanged(1, __HAL_TIM_GET_COUNTER(&htim3));
  }

  void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
#ifdef ADC_IT
    static int counter = 0;
    adc_values[counter] = HAL_ADC_GetValue(hadc);
    if(counter++ == 4)
      counter =  0;
#endif
  }

  void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc){
    ASSERT(0, "adc error callback");
  }

  void Error_Handler(void){
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    for(;;);
    /* USER CODE END Error_Handler */ 
  }

}
