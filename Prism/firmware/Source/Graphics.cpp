// #include "cmsis_os.h"
#include "stm32f7xx_hal.h"
#include "mxconstants.h"
#include "gpio.h"
#include "Graphics.h"
#include "FreeRTOS.h"
#include "errorhandlers.h"

extern "C" void delay(uint32_t millisec);

#ifdef OLED_SOFT_CS
#define setCS()    setPin(OLED_CS_GPIO_Port, OLED_CS_Pin)
#define clearCS()  clearPin(OLED_CS_GPIO_Port, OLED_CS_Pin)
#else
#define setCS()    
#define clearCS()
#endif

#define setDC()   setPin(OLED_DC_GPIO_Port, OLED_DC_Pin)
#define clearDC() clearPin(OLED_DC_GPIO_Port, OLED_DC_Pin)

// static Colour** pixels;

#if defined SEPS114A
#include "seps114a.h"
#elif defined SSD1331
#include "ssd1331.h"
#endif

void Graphics::begin(SPI_HandleTypeDef *spi) {
  hspi = spi;
  // off();
  commonInit();
  chipInit();
  delay(10);
  // display();
  // clear();
  // on();
  zero();
}

// Colour Graphics::Color565(uint8_t r, uint8_t g, uint8_t b) {
//   Colour c;
//   c = r >> 3;
//   c <<= 6;
//   c |= g >> 2;
//   c <<= 5;
//   c |= b >> 3;
//   return c;
// }

// Colour Graphics::getPixel(uint16_t x, uint16_t y){
//   if(x >= OLED_WIDTH || y >= OLED_HEIGHT)
//     return 0;
//   return pixels[y][x];
// }

// void Graphics::drawPixel(uint16_t x, uint16_t y, Colour c){
//   // assert_param(x < OLED_WIDTH && y < OLED_HEIGHT);
//   if(x >= OLED_WIDTH || y >= OLED_HEIGHT)
//     return;
//   pixels[y][x] = c;
// }

bool dozero = false;
// void Graphics::display(uint16_t** pixels, uint16_t width, uint16_t height){
void Graphics::display(uint16_t** pixels){
  if(dozero)
    zero();
  setDC();
  spiwrite((uint8_t*)pixels, OLED_WIDTH*OLED_HEIGHT);
  // spiwrite((uint8_t*)pixels, width*height);

  // // display the buffer which is not currently written to
  // if((screenstatus & currentscreen) == 0)
  //   return;
  // uint8_t screen = currentscreen ? 1 : 0;
  // spiwrite((uint8_t*)pixels[screen], sizeof(pixels));
  // screenstatus &= ~currentscreen;
  // currentscreen = screen;
}

// void Graphics::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c){
//   if(x+w < OLED_WIDTH && y+h < OLED_HEIGHT){
//     while(h-- != 0)
//       wmemset(&pixels[x][y++], c, sizeof(Colour)*w);
//   }
// }

// void Graphics::fade(uint16_t steps){
//   for(int i=0; i<OLED_HEIGHT*OLED_WIDTH; ++i)
//     pixels[0][i] = 
//       (((pixels[0][i] & RED) >> steps) & RED) | 
//       (((pixels[0][i] & GREEN) >> steps) & GREEN) |
//       (((pixels[0][i] & BLUE) >> steps) & BLUE);
// }

// void Graphics::fillScreen(uint16_t c) {
//   for(int i=0; i<OLED_HEIGHT*OLED_WIDTH; ++i)
//     pixels[0][i] = c;
// }

// void Graphics::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
//   if(x+w < OLED_WIDTH && y < OLED_HEIGHT)
//     wmemset(&pixels[y][x], c, sizeof(Colour)*w);
// }

// void Graphics::setRegister(const uint8_t reg,uint8_t val){
//   uint8_t cmd[2] = {reg,val};
//   writeCommands(cmd,2);
// }

#define OLED_TIMEOUT 1000
void Graphics::spiwritesync(const uint8_t* data, size_t size){
  while(hspi->State != HAL_SPI_STATE_READY);
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  HAL_StatusTypeDef ret = HAL_SPI_Transmit(hspi, (uint8_t*)data, size, OLED_TIMEOUT);
  assert_param(ret == HAL_OK);
  setCS();
}

volatile bool dmaready = true;
void Graphics::spiwrite(const uint8_t* data, size_t size){
#ifdef OLED_BITBANG
  vPortEnterCritical();
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  for(unsigned int i=0; i<size; ++i){
    char c = data[i];
    for(uint8_t bit = 0x80; bit; bit >>= 1){
      if(c & bit)
	setPin(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin);
      else
	clearPin(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin);
      setPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
      clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
    }
  }
  setCS();
  vPortExitCritical();
#elif defined OLED_DMA
  // while(!dmaready);
  while(hspi->State != HAL_SPI_STATE_READY);
  dmaready = false;
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  HAL_StatusTypeDef ret = HAL_SPI_Transmit_DMA(hspi, (uint8_t*)data, size);
  assert_param(ret == HAL_OK);
#elif defined OLED_IT
  while(hspi->State != HAL_SPI_STATE_READY);
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  HAL_StatusTypeDef ret = HAL_SPI_Transmit_IT(hspi, (uint8_t*)data, size);
  assert_param(ret == HAL_OK);
#else
  while(hspi->State != HAL_SPI_STATE_READY);
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  HAL_StatusTypeDef ret = HAL_SPI_Transmit(hspi, (uint8_t*)data, size, OLED_TIMEOUT);
  assert_param(ret == HAL_OK);
  setCS();
#endif
}

#if defined OLED_IT || defined OLED_DMA
extern DMA_HandleTypeDef hdma_spi1_tx;
extern "C" {
  void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi){
    ASSERT(0, "SPI Error");
  }

  static unsigned int missedcalls = 0;
  void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    if(__HAL_DMA_GET_FLAG(&hdma_spi1_tx,  __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx))){
      setCS();
      dmaready = true;
    }else{
      missedcalls++;
    }
  }

}
#endif

inline void Graphics::spiwrite(uint8_t c){
  spiwrite(&c, 1);
}
	
void Graphics::writeCommand(uint8_t c){
  clearDC();
  spiwrite(c);
}

void Graphics::writeCommand(uint8_t reg, uint8_t value){
  clearDC();
  spiwrite(reg);
  setDC();
  spiwrite(value);
}

void Graphics::writeCommands(const uint8_t *cmd, uint8_t length){
  clearDC();
  // writing with DMA appears to trigger a TC callback too soon
  spiwritesync(cmd, length);
}

/* Initialize PIN, direction and stuff related to hardware on CPU */
void Graphics::commonInit(){
  // with clock speed 8MHz a screen update takes 25mS
  // 30MHz: 16mS
  setCS();
  clearPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
  delay(10);
  setPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
  delay(10);
}

// void Graphics::clear() {
//   uint8_t cmd[] = {0x25, 0x00, 0x00, OLED_MW, OLED_MH};
//   writeCommands(cmd, 5);
// }
