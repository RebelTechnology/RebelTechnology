#include "Codec.h"
#include "cs4272.h"
#include "errorhandlers.h"
#include "device.h"

#define CODEC_BUFFER_HALFSIZE (CODEC_BUFFER_SIZE/2)
#define CODEC_BUFFER_QUARTSIZE (CODEC_BUFFER_SIZE/4)
static uint32_t txbuf[CODEC_BUFFER_SIZE];
static uint32_t rxbuf[CODEC_BUFFER_SIZE];

extern "C" {
SAI_HandleTypeDef hsai_BlockA1;
SAI_HandleTypeDef hsai_BlockB1;
DMA_HandleTypeDef hdma_sai1_a;
DMA_HandleTypeDef hdma_sai1_b;
SPI_HandleTypeDef hspi4;
}

#if 0
// SAI_HandleTypeDef hsai_BlockA1;
// SAI_HandleTypeDef hsai_BlockB1;

// #define hsai_BlockRx hsai_BlockA1
// #define hsai_BlockTx hsai_BlockB1

extern "C" {
  // void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai);
  void MX_SPI4_Init();
  void MX_SAI1_Init();
  SPI_HandleTypeDef hspi4;
  SAI_HandleTypeDef hsai_BlockRx;
  SAI_HandleTypeDef hsai_BlockTx;
  DMA_HandleTypeDef hdma_sai1_rx;
  DMA_HandleTypeDef hdma_sai1_tx;
  static int SAI1_client = 0;
}

/* SPI4 init function */
/* CS4271 control interface */
void MX_SPI4_Init(void)
{
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  // hspi4.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
#ifdef CODEC_SOFT_CS
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_DISABLED;
#else
  hspi4.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLED;
#endif
  // hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  // CS4271 max SPI baud rate 6MHz
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; // 3.375MHz
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  hspi4.Init.CRCPolynomial = 7;
  hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  HAL_SPI_Init(&hspi4);

}

/* SAI1 init function */
void MX_SAI1_Init(void)
{
  HAL_StatusTypeDef ret;

  HAL_SAI_DeInit(&hsai_BlockRx); // added
  hsai_BlockRx.Instance = SAI1_Block_B;
  hsai_BlockRx.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockRx.Init.AudioMode = SAI_MODESLAVE_RX;
  hsai_BlockRx.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_MCKDIV; // added
  hsai_BlockRx.Init.DataSize = SAI_DATASIZE_24;
  hsai_BlockRx.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockRx.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE; // was: SAI_CLOCKSTROBING_FALLINGEDGE;
  hsai_BlockRx.Init.Synchro = SAI_SYNCHRONOUS;
  hsai_BlockRx.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLED;
  hsai_BlockRx.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockRx.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockRx.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockRx.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockRx.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  hsai_BlockRx.FrameInit.FrameLength = 64; // was: 24;
  hsai_BlockRx.FrameInit.ActiveFrameLength = 32; // was: 1;
  hsai_BlockRx.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION; // was: SAI_FS_STARTFRAME;
  // I2S Standard format
  hsai_BlockRx.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockRx.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT; // was: SAI_FS_FIRSTBIT;
  // I2S LSB format
  // hsai_BlockRx.FrameInit.FSPolarity = SAI_FS_ACTIVE_HIGH;
  // hsai_BlockRx.FrameInit.FSOffset = SAI_FS_FIRSTBIT; // was: SAI_FS_FIRSTBIT;

  hsai_BlockRx.SlotInit.FirstBitOffset = 0;
  hsai_BlockRx.SlotInit.SlotSize = SAI_SLOTSIZE_32B; // was: SAI_SLOTSIZE_DATASIZE;
  hsai_BlockRx.SlotInit.SlotNumber = 2; // was: 1;
  hsai_BlockRx.SlotInit.SlotActive = SAI_SLOTACTIVE_ALL;
  ret = HAL_SAI_Init(&hsai_BlockRx);
  if(ret != HAL_OK)
    error(CONFIG_ERROR, "failed to initialise sai rx");

  HAL_SAI_DeInit(&hsai_BlockTx);
  hsai_BlockTx.Instance = SAI1_Block_A;
  hsai_BlockTx.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockTx.Init.AudioMode = SAI_MODESLAVE_TX;
  hsai_BlockTx.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_MCKDIV; 
  hsai_BlockTx.Init.DataSize = SAI_DATASIZE_24;
  hsai_BlockTx.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockTx.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;
  hsai_BlockTx.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockTx.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLED;
  hsai_BlockTx.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockTx.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockTx.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockTx.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockTx.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  hsai_BlockTx.FrameInit.FrameLength = 64;
  hsai_BlockTx.FrameInit.ActiveFrameLength = 32;
  hsai_BlockTx.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
  // I2S Standard format
  hsai_BlockTx.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockTx.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;
  hsai_BlockTx.SlotInit.FirstBitOffset = 0;
  hsai_BlockTx.SlotInit.SlotSize = SAI_SLOTSIZE_32B;
  hsai_BlockTx.SlotInit.SlotNumber = 2;
  hsai_BlockTx.SlotInit.SlotActive = SAI_SLOTACTIVE_ALL;
  ret = HAL_SAI_Init(&hsai_BlockTx);
  if(ret != HAL_OK)
    error(CONFIG_ERROR, "failed to initialise sai tx");
}

void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai)
{
  GPIO_InitTypeDef GPIO_InitStruct;
/* SAI1 */
    if(hsai->Instance==SAI1_Block_A)
    {
    /* Peripheral clock enable */
    if (SAI1_client == 0)
    {
      __SAI1_CLK_ENABLE();
    }
    SAI1_client ++;
    
    /**SAI1_A_Block_A GPIO Configuration    
    PE4     ------> SAI1_FS_A
    PE5     ------> SAI1_SCK_A
    PE6     ------> SAI1_SD_A 
    */
    GPIO_InitStruct.Pin = CS_LRCK_Pin|CS_SCLK_Pin|CS_SDIN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* Peripheral DMA init*/
    
    hdma_sai1_tx.Instance = DMA2_Stream1;
    hdma_sai1_tx.Init.Channel = DMA_CHANNEL_0;
    hdma_sai1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sai1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sai1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    /* hdma_sai1_tx.Init.Mode = DMA_NORMAL; */
    hdma_sai1_tx.Init.Mode = DMA_CIRCULAR;
    hdma_sai1_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    /* hdma_sai1_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE; */
    hdma_sai1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_sai1_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_sai1_tx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_sai1_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hdma_sai1_tx);

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
    __HAL_LINKDMA(hsai,hdmarx,hdma_sai1_tx);
    __HAL_LINKDMA(hsai,hdmatx,hdma_sai1_tx);

    }
    if(hsai->Instance==SAI1_Block_B)
    {
      /* Peripheral clock enable */
      if (SAI1_client == 0)
      {
      __SAI1_CLK_ENABLE();
      }
    SAI1_client ++;
    
    /**SAI1_B_Block_B GPIO Configuration    
    PE3     ------> SAI1_SD_B 
    */
    GPIO_InitStruct.Pin = CS_SDOUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
    HAL_GPIO_Init(CS_SDOUT_GPIO_Port, &GPIO_InitStruct);

    /* Peripheral DMA init*/
    
    hdma_sai1_rx.Instance = DMA2_Stream4;
    hdma_sai1_rx.Init.Channel = DMA_CHANNEL_1;
    hdma_sai1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sai1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sai1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    /* hdma_sai1_rx.Init.Mode = DMA_NORMAL; */
    hdma_sai1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_sai1_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    /* hdma_sai1_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE; */
    hdma_sai1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_sai1_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_sai1_rx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_sai1_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hdma_sai1_rx);

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
    __HAL_LINKDMA(hsai,hdmarx,hdma_sai1_rx);
    __HAL_LINKDMA(hsai,hdmatx,hdma_sai1_rx);
    }
}
void HAL_SAI_MspDeInit(SAI_HandleTypeDef* hsai)
{

/* SAI1 */
    if(hsai->Instance==SAI1_Block_A)
    {
    SAI1_client --;
    if (SAI1_client == 0)
      {
      /* Peripheral clock disable */ 
       __SAI1_CLK_DISABLE();
      }
    
    /**SAI1_A_Block_A GPIO Configuration    
    PE4     ------> SAI1_FS_A
    PE5     ------> SAI1_SCK_A
    PE6     ------> SAI1_SD_A 
    */
    HAL_GPIO_DeInit(GPIOE, CS_LRCK_Pin|CS_SCLK_Pin|CS_SDIN_Pin);

    HAL_DMA_DeInit(hsai->hdmarx);
    HAL_DMA_DeInit(hsai->hdmatx);
    }
    if(hsai->Instance==SAI1_Block_B)
    {
    SAI1_client --;
      if (SAI1_client == 0)
      {
      /* Peripheral clock disable */
      __SAI1_CLK_DISABLE();
      }
    
    /**SAI1_B_Block_B GPIO Configuration    
    PE3     ------> SAI1_SD_B 
    */
    HAL_GPIO_DeInit(CS_SDOUT_GPIO_Port, CS_SDOUT_Pin);

    HAL_DMA_DeInit(hsai->hdmarx);
    HAL_DMA_DeInit(hsai->hdmatx);
    }
}
#endif

void Codec::ramp(uint32_t max){
  uint32_t incr = max/CODEC_BUFFER_SIZE;
  for(int i=0; i<CODEC_BUFFER_SIZE; ++i)
    txbuf[i] = i*incr;
}

void Codec::reset(){
  // HAL_SAI_MspInit() is called from HAL_SAI_Init() in MX_SAI1_Init()
  // MX_SAI1_Init();
  // MX_SPI4_Init();

  __HAL_SAI_ENABLE(&hsai_BlockA1);
  __HAL_SAI_ENABLE(&hsai_BlockB1);
  codec_init(&hspi4);

  // configure i2s mode for DAC and ADC, hp filters off
  codec_write(0x01, (1<<3) | (1<<5) | 1);
  codec_write(0x06, (1<<4) | (1<<1) | 1) ;
  // codec_write(0x01, (1<<3) | (1<<5));
  // codec_write(0x06, (1<<4));
}

void Codec::clear(){
  set(0);
}

void Codec::txrx(){
  HAL_SAI_DMAStop(&hsai_BlockA1);
  HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t*)rxbuf, CODEC_BUFFER_SIZE);
}

uint32_t Codec::getMin(){
  uint32_t min = txbuf[0];
  for(int i=1; i<CODEC_BUFFER_SIZE; ++i)
    if(txbuf[i] < min)
      min  = txbuf[i];
  return min;
}

uint32_t Codec::getMax(){
  uint32_t max = txbuf[0];
  for(int i=1; i<CODEC_BUFFER_SIZE; ++i)
    if(txbuf[i] > max)
      max  = txbuf[i];
  return max;
}

float Codec::getAvg(){
  float avg = 0;
  for(int i=0; i<CODEC_BUFFER_SIZE; ++i)
    avg += txbuf[i];
  return avg / CODEC_BUFFER_SIZE;
}

void Codec::set(uint32_t value){
  for(int i=0; i<CODEC_BUFFER_SIZE; ++i)
    txbuf[i] = value;
}

void Codec::bypass(bool doBypass){
  codec_bypass(doBypass);
}

void Codec::stop(){
  HAL_SAI_DMAStop(&hsai_BlockA1);
  HAL_SAI_DMAStop(&hsai_BlockB1);
}

void Codec::start(){
  HAL_StatusTypeDef ret;
  ret = HAL_SAI_Receive_DMA(&hsai_BlockB1, (uint8_t*)rxbuf, CODEC_BUFFER_SIZE);
  assert_param(ret == HAL_OK);
  ret = HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t*)txbuf, CODEC_BUFFER_SIZE);
  assert_param(ret == HAL_OK);
}

extern "C" {

// void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai){
// }

extern void audioCallback(uint32_t* rx, uint32_t* tx, uint16_t size);

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai){
  audioCallback(rxbuf+CODEC_BUFFER_HALFSIZE, txbuf+CODEC_BUFFER_HALFSIZE, CODEC_BUFFER_QUARTSIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai){
  audioCallback(rxbuf, txbuf, CODEC_BUFFER_QUARTSIZE);
}

void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai){
  error(CONFIG_ERROR, "SAI DMA Error");
}

}
