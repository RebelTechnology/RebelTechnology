
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

typedef uint16_t Colour;
static Colour pixels[OLED_HEIGHT][OLED_WIDTH];

#include "seps114a.h"

void Graphics::begin(SPI_HandleTypeDef *spi) {
  hspi = spi;
  // off();
  commonInit();
  chipInit();
  // fillScreen(BLACK);
  // display();
  // clear();
  seps114a_bg();
  // on();
}

// void SSD1331::goTo(int x, int y) {
//   assert_param(x < OLED_WIDTH && y < OLED_HEIGHT);
//   uint8_t cmd[] = {_CMD_SETCOLUMN,(uint8_t)x,OLED_MW,_CMD_SETROW,(uint8_t)y,OLED_MH};
//   writeCommands(cmd, 6);
// }

uint16_t Graphics::Color565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;
  return c;
}

uint16_t Graphics::getPixel(uint16_t x, uint16_t y){
  if(x >= OLED_WIDTH || y >= OLED_HEIGHT)
    return 0;
  return pixels[y][x];
}

void Graphics::drawPixel(uint16_t x, uint16_t y, uint16_t c){
  // assert_param(x < OLED_WIDTH && y < OLED_HEIGHT);
  if(x >= OLED_WIDTH || y >= OLED_HEIGHT)
    return;
  pixels[y][x] = c;
}

// #include "screen.h"
// volatile bool done;
// void callback(){
//   //  pinSetFast(_cs);
//   setCS();
//   done = true;
// }

// uint8_t screenstatus = 0x00;
// // bit is clear if buffer is ready to write to
// bool Graphics::isReady(){
//   return (screenstatus & currentscreen) == 0;
// }

// void Graphics::complete(){
//   screenstatus |= currentscreen;
// }

bool dozero = false;
void Graphics::display(){
  // if((screenstatus & currentscreen) == 0)
  //   return;
  if(!dozero)
    return;
  zero();   // goTo(0, 0);
  setDC();
  spiwrite((uint8_t*)pixels, sizeof(pixels));

  // // display the buffer which is not currently written to
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

void Graphics::fade(uint16_t steps){
  for(int i=0; i<OLED_HEIGHT*OLED_WIDTH; ++i)
    pixels[0][i] = 
      (((pixels[0][i] & RED) >> steps) & RED) | 
      (((pixels[0][i] & GREEN) >> steps) & GREEN) |
      (((pixels[0][i] & BLUE) >> steps) & BLUE);
}

void Graphics::fillScreen(uint16_t c) {
  for(int i=0; i<OLED_HEIGHT*OLED_WIDTH; ++i)
    pixels[0][i] = c;
}

// void Graphics::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
//   if(x+w < OLED_WIDTH && y < OLED_HEIGHT)
//     wmemset(&pixels[y][x], c, sizeof(Colour)*w);
// }

// //not tested
// void Graphics::setBrightness(uint8_t val){
//   writeCommand(_CMD_MASTERCURRENT);
//   if (val < 0x17) {
//     writeData(val);
//   } else {
//     writeData(0x0F);
//   }
// }

// void Graphics::setRegister(const uint8_t reg,uint8_t val){
//   uint8_t cmd[2] = {reg,val};
//   writeCommands(cmd,2);
// }

#define OLED_TIMEOUT 1000
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
  while(hspi->State != HAL_SPI_STATE_READY);
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

  void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
    setCS();
  }

  void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
    setCS();
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
  spiwrite(cmd, length);
}
	
void Graphics::writeData(uint8_t c){
  setDC();
  spiwrite(c);
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

void Graphics::off() {
#ifdef SSD1331
  // writeCommand(_CMD_DISPLAYOFF);
  writeCommand(0xae);
#elif defined SEPS114A
  uint8_t cmd[] = {0x02, 0x00};
  writeCommands(cmd, sizeof(cmd));
#endif
}

void Graphics::on() {
#ifdef SSD1331
  // writeCommand(_CMD_DISPLAYON);
  writeCommand(0xaf);
#elif defined SEPS114A
  uint8_t cmd[] = {0x02, 0x01};
  writeCommands(cmd, sizeof(cmd));
#endif
}

// void Graphics::clear() {
//   uint8_t cmd[] = {0x25, 0x00, 0x00, OLED_MW, OLED_MH};
//   writeCommands(cmd, 5);
// }

// void Graphics::lock() {
//   uint8_t cmd[] = {0xfd, 0x04};
//   writeCommands(cmd, 2);
// }

// void Graphics::unlock() {
//   uint8_t cmd[] = {0xfd, 0x00};
//   writeCommands(cmd, 2);
// }
