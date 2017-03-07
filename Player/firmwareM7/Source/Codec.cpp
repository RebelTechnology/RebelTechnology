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
  ASSERT(ret == HAL_OK, "Failed to start SAI RX DMA");
  ret = HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t*)txbuf, CODEC_BUFFER_SIZE);
  ASSERT(ret == HAL_OK, "Failed to start SAI TX DMA");
}

void Codec::pause(){
  HAL_SAI_DMAPause(&hsai_BlockB1);
  HAL_SAI_DMAPause(&hsai_BlockA1);
}

void Codec::resume(){
  HAL_SAI_DMAResume(&hsai_BlockB1);
  HAL_SAI_DMAResume(&hsai_BlockA1);
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
