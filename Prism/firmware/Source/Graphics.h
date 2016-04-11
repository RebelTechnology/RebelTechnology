#ifndef _Graphics_h_
#define _Graphics_h_
#include <stdint.h>
#include "stm32f7xx_hal.h"

#ifdef SSD1331
#define OLED_WIDTH			96
#define OLED_HEIGHT			64
#elif defined SEPS114A
#define OLED_WIDTH			96
#define OLED_HEIGHT			96
#endif

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include "Adafruit_GFX.h"

class Graphics : public Adafruit_GFX {
public:
  // 4 or 5 wire configuration
  /* SSD1331(uint8_t CS, uint8_t RS, uint8_t RST); */
  Graphics() : Adafruit_GFX(OLED_WIDTH, OLED_HEIGHT), hspi(NULL) {}
  void begin(SPI_HandleTypeDef *spi);
  void display();
  uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
  uint16_t getPixel(uint16_t x, uint16_t y);
  void drawPixel(uint16_t x, uint16_t y, uint16_t color);
  // void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  // void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  // void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor);
  void fillScreen(uint16_t color);
  void fade(uint16_t steps);
  void zero();
  /* void clear(); */
  void on();
  void off();
  /* void lock(); */
  /* void unlock(); */
  uint16_t getHeight(){
    return OLED_HEIGHT;
  }
  uint16_t getWidth(){
    return OLED_WIDTH;
  }
  bool isReady(); // true if last screen update has been sent
  void complete(); // call after finishing a screen update
protected:
  void goTo(int x, int y);
  //experimental
  void setBrightness(uint8_t val);
  //in case it's needed
  void writeData(uint8_t data);
  /* void setBitrate(uint32_t n); //speed for the SPI interface   */

   void spiwrite(uint8_t data);
   void spiwrite(const uint8_t* data, size_t size);
private:
  /* volatile bool	reversal; */
  /* volatile bool	filling; */
  /* bool	_inited; */
  void writeCommand(uint8_t c);
  void writeCommand(uint8_t reg, uint8_t value);
  void writeCommands(const uint8_t* cmd, uint8_t length);
  void setRegister(uint8_t reg, uint8_t val);
  /* bool	reversalTool(bool rev);//helper */
  /* bool	fillTool(bool fillState);//helper */
  /* void	hdwre_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled = false); */
  void	chipInit();
  void	commonInit();
  uint8_t _cs,_rs,_rst;
  SPI_HandleTypeDef *hspi;
};

#endif /* _Graphics_h_ */
