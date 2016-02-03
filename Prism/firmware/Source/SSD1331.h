#ifndef _SSD1331H_
#define _SSD1331H_

#include <stdint.h>

#define OLED_WIDTH			96	
#define OLED_HEIGHT			64	

class SSD1331 {
public:
  // 4 or 5 wire configuration
  /* SSD1331(uint8_t CS, uint8_t RS, uint8_t RST); */
  SSD1331(){}
  void begin(SPI_HandleTypeDef *spi);
  void display();
  uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  // void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  // void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  // void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor);
  void fillScreen(int16_t color);
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
  void	writeCommands(uint8_t *cmd, uint8_t length);
  void	setRegister(const uint8_t reg, uint8_t val);
  void	spiwrite(uint8_t data);
  void	spiwrite(uint8_t* data, size_t size);
  /* bool	reversalTool(bool rev);//helper */
  /* bool	fillTool(bool fillState);//helper */
  /* void	hdwre_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, bool filled = false); */
  void	chipInit();
  void	commonInit();
  uint8_t _cs,_rs,_rst;
  SPI_HandleTypeDef *hspi;
};
#endif
