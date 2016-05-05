#ifndef __ScreenBuffer_h__
#define __ScreenBuffer_h__

#include "StompBox.h"

typedef uint16_t Colour;

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

class PixelBuffer {
public:
  void copy(const PixelBuffer& other);
  Colour* getPixels();
  int getWidth();
  int getHeight();
};

class ScreenBuffer {
private:
  int width;
  int height;
  Colour** pixels;

  uint16_t textcolor, textbgcolor;
  uint16_t cursor_x, cursor_y;  
  uint8_t textsize;
public:
  // ScreenBuffer(int w, int h, Colour** buffer) : width(w), height(h), pixels(buffer){}
  // ScreenBuffer();
  ScreenBuffer(int w, int h);
  void setBuffer(uint16_t** buffer){
    pixels = buffer;
  }
  Colour getPixel(int x, int y);
  void setPixel(int x, int y, Colour c);
  void drawLine(int fromX, int fromY, int toX, int toY, Colour c);
  void drawVerticalLine(int x, int y, int length, Colour c);
  void drawHorizontalLine(int x, int y, int length, Colour c);
  void drawRectangle(int x, int y, int width, int height, Colour c);
  void fillRectangle(int x, int y, int width, int height, Colour c);
  // void setOrigin(int absoluteX, int absoluteY);
  // void setFont(int font, int size);
  void print(int x, int y, const char* text);
  void fill(Colour c);
  void invert();
  void fade(uint16_t steps);
  void clear();
  void clear(int x, int y, int width, int height);
  inline int getWidth(){
    return width;
  }
  inline int getHeight(){
    return height;
  }
  void draw(int x, int y, ScreenBuffer& pixels);
  static ScreenBuffer* create(int width, int height);

  void drawChar(uint16_t x, uint16_t y, unsigned char c, Colour fg, uint16_t bg, uint8_t size);		
  void setCursor(uint16_t x, uint16_t y);
  void setTextColour(Colour c);
  void setTextColour(Colour fg, Colour bg);
  void setTextSize(uint8_t s);
  // void setTextWrap(bool w);

  size_t write(uint8_t);
  void print(const char* str);
  void print(int num);
  void print(float num);

protected:
  void drawFastVLine(int x, int y, int h, Colour color);
  void drawFastHLine(int x, int y, int h, Colour color);
};

class VideoPatch : public Patch {
public:
  virtual void processVideo(ScreenBuffer& video, AudioBuffer& audio) = 0;
};

#endif // __ScreenBuffer_h__
