
#define SSD1331_COLORORDER_RGB
// #define SSD1331_COLORORDER_BGR

#if defined SSD1331_COLORORDER_RGB && defined SSD1331_COLORORDER_BGR
  #error "RGB and BGR can not both be defined for SSD1331_COLORODER."
#endif

#define _DLY_LINE			400
#define _DLY_FILL			800
// list of the registers
#define _CMD_DRAWLINE 		0x21
#define _CMD_DRAWRECT 		0x22
#define _CMD_DRAWCOPY 		0x23 //--
#define _CMD_DIMWINDOW 		0x24 //--
#define _CMD_CLRWINDOW 		0x25 //--
#define _CMD_FILL 			0x26
#define _CMD_PHASEPERIOD 	0x12 //--
#define _CMD_SETCOLUMN 		0x15 
#define _CMD_SETROW    		0x75 
#define _CMD_CONTRASTA 		0x81 
#define _CMD_CONTRASTB 		0x82 
#define _CMD_CONTRASTC		0x83 
#define _CMD_MASTERCURRENT 	0x87 
#define _CMD_SETREMAP 		0xA0 
#define _CMD_STARTLINE 		0xA1 
#define _CMD_DISPLAYOFFSET 	0xA2 
#define _CMD_NORMALDISPLAY 	0xA4
#define _CMD_DISPLAYALLON  	0xA5
#define _CMD_DISPLAYALLOFF 	0xA6
#define _CMD_INVERTDISPLAY 	0xA7
#define _CMD_SETMULTIPLEX  	0xA8
#define _CMD_SETMASTER 		0xAD
#define _CMD_DISPLAYOFF 	0xAE
#define _CMD_DISPLAYON     	0xAF
#define _CMD_POWERMODE 		0xB0
#define _CMD_PRECHARGE 		0xB1
#define _CMD_CLOCKDIV 		0xB3
#define _CMD_GRAYSCALE 		0xB8
#define _CMD_PRECHARGEA 	0x8A 
#define _CMD_PRECHARGEB 	0x8B 
#define _CMD_PRECHARGEC 	0x8C 
#define _CMD_PRECHARGELEVEL     0xBB 
#define _CMD_VCOMH 		0xBE
#define	_CMD_VPACOLORLVL	0xBB
#define	_CMD_VPBCOLORLVL	0xBC
#define	_CMD_VPCCOLORLVL	0xBD
#define _CMD_NOP		0xE3
#define OLED_MW			(OLED_WIDTH-1)
#define OLED_MH			(OLED_HEIGHT-1)

// #include "cmsis_os.h"
#include "stm32f7xx_hal.h"
#include "mxconstants.h"
#include "gpio.h"
#include "SSD1331.h"
#include "FreeRTOS.h"

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
uint8_t currentscreen = 0;
static Colour pixels[2][OLED_HEIGHT][OLED_WIDTH];

void SSD1331::begin(SPI_HandleTypeDef *spi) {
  hspi = spi;
  off();
  commonInit();
  chipInit();
  fillScreen(BLACK);
  // display();
  // clear();
  on();
}

void SSD1331::zero() {
  // uint8_t cmd[] = {_CMD_SETCOLUMN, 0, OLED_MW, _CMD_SETROW, 0 ,OLED_MH };
  uint8_t cmd[] = {0x15, 0, OLED_MW, 0x75, 0 ,OLED_MH };
  writeCommands(cmd, 6);
}

void SSD1331::goTo(int x, int y) {
  assert_param(x < OLED_WIDTH && y < OLED_HEIGHT);
  uint8_t cmd[] = {_CMD_SETCOLUMN,(uint8_t)x,OLED_MW,_CMD_SETROW,(uint8_t)y,OLED_MH};
  writeCommands(cmd, 6);
}

uint16_t SSD1331::Color565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;
  return c;
}

bool byteswap = false;
void SSD1331::drawPixel(int16_t x, int16_t y, uint16_t c){
  assert_param(x < OLED_WIDTH && y < OLED_HEIGHT);
  if(byteswap)
    pixels[currentscreen][y][x] = __REV16(c);
  else
    pixels[currentscreen][y][x] = c;
}

// #include "screen.h"
// volatile bool done;
// void callback(){
//   //  pinSetFast(_cs);
//   setCS();
//   done = true;
// }

uint8_t screenstatus = 0x00;
// bit is clear if buffer is ready to write to
bool SSD1331::isReady(){
  return (screenstatus & currentscreen) == 0;
}

void SSD1331::complete(){
  screenstatus |= currentscreen;
}

bool dozero = false;
void SSD1331::display(){
  // if((screenstatus & currentscreen) == 0)
  //   return;
  if(dozero)
    zero();   // goTo(0, 0);
  setDC();
  // clearCS();
  // display the buffer which is not currently written to
  uint8_t screen = currentscreen ? 1 : 0;
  spiwrite((uint8_t*)pixels[screen], sizeof(pixels));
  screenstatus &= ~currentscreen;
  currentscreen = screen;
  // setCS();
}

// void SSD1331::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c){
//   if(x+w < OLED_WIDTH && y+h < OLED_HEIGHT){
//     while(h-- != 0)
//       wmemset(&pixels[x][y++], c, sizeof(Colour)*w);
//   }
// }

void SSD1331::fillScreen(int16_t c) {
  for(int i=0; i<OLED_HEIGHT*OLED_WIDTH; ++i)
    pixels[currentscreen][0][i] = c;
}

// void SSD1331::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
//   if(x+w < OLED_WIDTH && y < OLED_HEIGHT)
//     wmemset(&pixels[y][x], c, sizeof(Colour)*w);
// }

//not tested
void SSD1331::setBrightness(uint8_t val){
  writeCommand(_CMD_MASTERCURRENT);
  if (val < 0x17) {
    writeData(val);
  } else {
    writeData(0x0F);
  }
}

void SSD1331::setRegister(const uint8_t reg,uint8_t val){
  uint8_t cmd[2] = {reg,val};
  writeCommands(cmd,2);
}

#define OLED_TIMEOUT 1000
void SSD1331::spiwrite(const uint8_t* data, size_t size){
  // while(hspi->State != HAL_SPI_STATE_READY);
  // HAL_SPI_Transmit_DMA(hspi, data, size);
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
#else
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  while(hspi->State != HAL_SPI_STATE_READY);
  HAL_StatusTypeDef ret = HAL_SPI_Transmit(hspi, (uint8_t*)data, size, OLED_TIMEOUT);
  assert_param(ret == HAL_OK);
  setCS();
#endif
}

inline void SSD1331::spiwrite(uint8_t c){
  // while(hspi->State != HAL_SPI_STATE_READY);
  // HAL_SPI_Transmit_DMA(hspi, &c, 1);
  spiwrite(&c, 1);
  // while(hspi->State != HAL_SPI_STATE_READY);
  // HAL_StatusTypeDef ret = HAL_SPI_Transmit(hspi, &c, 1, OLED_TIMEOUT);
  // assert_param(ret == HAL_OK);
}
	
void SSD1331::writeCommand(uint8_t c){
  clearDC();
  // clearCS();
  spiwrite(c);
  // setCS();
}

void SSD1331::writeCommands(const uint8_t *cmd, uint8_t length){
  clearDC();
  // clearCS();
  spiwrite(cmd, length);
  // setCS();
}
	
void SSD1331::writeData(uint8_t c){
  setDC();
  // clearCS();
  spiwrite(c);
  // setCS();
}

/* Initialize PIN, direction and stuff related to hardware on CPU */
void SSD1331::commonInit(){
  // with clock speed 8MHz a screen update takes 25mS
  // 30MHz: 16mS
  setCS();
  clearPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
  delay(10);
  setPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
  delay(10);
}

void SSD1331::off() {
  writeCommand(_CMD_DISPLAYOFF);
}

void SSD1331::on() {
  writeCommand(_CMD_DISPLAYON);
}

void SSD1331::clear() {
  uint8_t cmd[] = {0x25, 0x00, 0x00, OLED_MW, OLED_MH};
  writeCommands(cmd, 5);
}

void SSD1331::lock() {
  uint8_t cmd[] = {0xfd, 0x04};
  writeCommands(cmd, 2);
}

void SSD1331::unlock() {
  uint8_t cmd[] = {0xfd, 0x00};
  writeCommands(cmd, 2);
}

static const uint8_t initSequence[] = {
  0xae, 0xa0, 0x76, 0xa1, 0x00, 0xa2, 0x00, 0xa4, 0xa8, 0x3f, 0xad, 0x8e,
  0xb0, 0x0b, 0xb1, 0x31, 0xb3, 0xf0, 0x8a, 0x64, 0x8b, 0x78, 0x8c, 0x64, 0xbb, 0x3a,
  0xbe, 0x3e, 0x87, 0x06, 0x81, 0x91, 0x82, 0x50, 0x83, 0x7d, // 0xaf display on
  0x2e // deactivate scrolling
};
bool faststart = true;
void SSD1331::chipInit() {
  //set SSD chip registers
  if(faststart){
  writeCommands(initSequence, sizeof(initSequence));
  }else{
    uint8_t cmd[33];
    writeCommand(_CMD_DISPLAYOFF);  	
    writeCommand(_CMD_SETREMAP); 	
    /* Set Re-map & Data Format (A0h)
     * A[0] = 0 for horizontal address increment
     * A[1] = 0 for left to right mapping (set to 1 to mirror screen)
     * A[2] RGB Mapping
     * A[3] COM Left / Right Remap
     * COM Scan Direction Remap (A[4])
     * Odd Even Split of COM pins (A[5])
     * Display color mode (A[7:6])
     * 0x74: 0b01110100
     */
    // writeCommand(0b00000000);
    // writeCommand(0x72);
    writeCommand(0x76); // mirror screen
    setRegister(_CMD_FILL,0x01);
    setRegister(_CMD_STARTLINE,0x00);//default 0x00	
    setRegister(_CMD_DISPLAYOFFSET,0x01);//default 0x00
    setRegister(_CMD_PHASEPERIOD,0b10110001);
    setRegister(_CMD_SETMULTIPLEX,0x3F);
    setRegister(_CMD_SETMASTER,0x8E);
    setRegister(_CMD_POWERMODE,0x0B);
    setRegister(_CMD_PRECHARGE,0x31);//0x1F - 0x31
    setRegister(_CMD_CLOCKDIV,0xF0);
    setRegister(_CMD_PRECHARGEA,0x64);
    setRegister(_CMD_PRECHARGEB,0x78);
    setRegister(_CMD_PRECHARGEC,0x64);
    setRegister(_CMD_PRECHARGELEVEL,0x3A);//0x3A - 0x00
    setRegister(_CMD_VCOMH,0x3E);//0x3E - 0x3F
    setRegister(_CMD_MASTERCURRENT,0x06);//0x06 - 0x0F
    setRegister(_CMD_CONTRASTA,0x91);//0xEF - 0x91
    setRegister(_CMD_CONTRASTB,0x50);//0x11 - 0x50
    setRegister(_CMD_CONTRASTC,0x7D);//0x48 - 0x7D
    //setRegister(_CMD_VPACOLORLVL,0x40);
    //setRegister(_CMD_VPBCOLORLVL,0x40);
    //setRegister(_CMD_VPCCOLORLVL,0x40);
    cmd[0] = _CMD_GRAYSCALE;
    cmd[1] =  0x01; cmd[2] =  0x03; cmd[3] =  0x05; cmd[4] =  0x07; cmd[5] =  0x0A; cmd[6] =  0x0D; cmd[7] =  0x10; cmd[8] =  0x13;
    cmd[9] =  0x16; cmd[10] = 0x19; cmd[11] = 0x1C; cmd[12] = 0x20; cmd[13] = 0x24; cmd[14] = 0x28; cmd[15] = 0x2C; cmd[16] = 0x30;
    cmd[17] = 0x34; cmd[18] = 0x38; cmd[19] = 0x3C; cmd[20] = 0x40; cmd[21] = 0x44; cmd[22] = 0x48; cmd[23] = 0x4C; cmd[24] = 0x50;
    cmd[25] = 0x54; cmd[26] = 0x58; cmd[27] = 0x5C; cmd[28] = 0x60; cmd[29] = 0x64; cmd[30] = 0x68; cmd[31] = 0x6C; cmd[32] = 0x70;
    writeCommands(cmd, 33);
    writeCommand(_CMD_NORMALDISPLAY);
    writeCommand(_CMD_DISPLAYON);
    // filling = true;
    // reversal = false;
  }
}
