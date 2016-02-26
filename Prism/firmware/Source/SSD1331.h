#ifndef _SSD1331H_
#define _SSD1331H_

#include <stdint.h>

#define OLED_WIDTH			96	
#define OLED_HEIGHT			64	

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

class SSD1331 : public Adafruit_GFX {
public:
  // 4 or 5 wire configuration
  /* SSD1331(uint8_t CS, uint8_t RS, uint8_t RST); */
  SSD1331() : Adafruit_GFX(OLED_WIDTH, OLED_HEIGHT), hspi(NULL) {}
  void begin(SPI_HandleTypeDef *spi);
  void display();
  uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  // void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  // void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  // void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor);
  void fillScreen(int16_t color);
  void zero();
  void clear();
  void on();
  void off();
  void lock();
  void unlock();
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
  void setBitrate(uint32_t n);//speed for the SPI interface  
private:
  /* volatile bool	reversal; */
  /* volatile bool	filling; */
  /* bool	_inited; */
  void	writeCommand(uint8_t c);
  void	writeCommands(const uint8_t* cmd, uint8_t length);
  void	setRegister(uint8_t reg, uint8_t val);
  void	spiwrite(uint8_t data);
  void	spiwrite(const uint8_t* data, size_t size);
  /* bool	reversalTool(bool rev);//helper */
  /* bool	fillTool(bool fillState);//helper */
  /* void	hdwre_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled = false); */
  void	chipInit();
  void	commonInit();
  uint8_t _cs,_rs,_rst;
  SPI_HandleTypeDef *hspi;
};
#endif
