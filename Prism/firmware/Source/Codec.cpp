#include "Codec.h"
#include "cs4272.h"
#include "errorhandlers.h"
#include "mxconstants.h"

extern "C" {
  void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai);
  static void MX_SPI2_Init();
  static void MX_SAI1_Init();
  SPI_HandleTypeDef hspi2;
  SAI_HandleTypeDef hsai_BlockRx;
  SAI_HandleTypeDef hsai_BlockTx;
  DMA_HandleTypeDef hdma_sai1_rx;
  DMA_HandleTypeDef hdma_sai1_tx;
  static int SAI1_client = 0;
}

/* SPI2 init function */
/* CS4271 control interface */
void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  // hspi2.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  // hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  // hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  // CS4271 max SPI baud rate 6MHz
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; // 3.375MHz
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  // hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLED;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLED;
  HAL_SPI_Init(&hspi2);

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
  hsai_BlockRx.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockRx.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT; // was: SAI_FS_FIRSTBIT;
  hsai_BlockRx.SlotInit.FirstBitOffset = 0;
  hsai_BlockRx.SlotInit.SlotSize = SAI_SLOTSIZE_32B; // was: SAI_SLOTSIZE_DATASIZE;
  hsai_BlockRx.SlotInit.SlotNumber = 2; // was: 1;
  hsai_BlockRx.SlotInit.SlotActive = SAI_SLOTACTIVE_ALL;
  ret = HAL_SAI_Init(&hsai_BlockRx);
  if(ret != HAL_OK)
    error(CONFIG_ERROR, "failed to initialise sai rx");
  
  HAL_SAI_DeInit(&hsai_BlockTx); // added
  hsai_BlockTx.Instance = SAI1_Block_A;
  hsai_BlockTx.Init.AudioMode = SAI_MODESLAVE_TX;
  hsai_BlockTx.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_MCKDIV; // added
  hsai_BlockTx.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockTx.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLED;
  hsai_BlockTx.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockTx.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockTx.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockTx.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockTx.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  ret = HAL_SAI_InitProtocol(&hsai_BlockTx, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_24BIT, 2);
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

void Codec::reset(){
  MX_SAI1_Init();
  MX_SPI2_Init();

  __HAL_SAI_ENABLE(&hsai_BlockRx);
  __HAL_SAI_ENABLE(&hsai_BlockTx);
  for(int i=0; i<CS_BUFFER_SIZE; ++i)
    txbuf[i] = i*0xfff;
  codec_init(&hspi2);

}

void Codec::bypass(bool doBypass){
  codec_bypass(doBypass);
}

void Codec::stop(){
  HAL_SAI_DMAStop(&hsai_BlockRx);
  HAL_SAI_DMAStop(&hsai_BlockTx);
}

void Codec::start(){
  HAL_StatusTypeDef ret;
  ret = HAL_SAI_Receive_DMA(&hsai_BlockRx, (uint8_t*)rxbuf, 1024);
  assert_param(ret == HAL_OK);
  ret = HAL_SAI_Transmit_DMA(&hsai_BlockTx, (uint8_t*)txbuf, 1024);
  assert_param(ret == HAL_OK);
    // if(!usedma){
    //   ret = HAL_SAI_Receive(&hsai_BlockRx, (uint8_t*)rxbuf, 1024, 1000);
    //   assert_param(ret == HAL_OK);
    //   ret = HAL_SAI_Transmit(&hsai_BlockTx, (uint8_t*)rxbuf, 1024, 1000);
    //   assert_param(ret == HAL_OK);
    // }
}
