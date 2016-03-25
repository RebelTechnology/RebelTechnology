#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

#include <stdint.h>
#include <stddef.h>

/* #include "application.h" */

#define swap(a, b) { int16_t t = a; a = b; b = t; }
typedef bool boolean;

class Adafruit_GFX { // : public Print {

 public:

  Adafruit_GFX(uint16_t w, uint16_t h); // Constructor

  // This MUST be defined by the subclass:
  virtual void drawPixel(uint16_t x, uint16_t y, uint16_t color) = 0;

  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void
    drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color),
    drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color),
    drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color),
    drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color),
    fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color),
    fillScreen(uint16_t color),
    invertDisplay(boolean i);

  // These exist only with Adafruit_GFX (no subclass overrides)
  void
    drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color),
    drawCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername,
      uint16_t color),
    fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color),
    fillCircleHelper(uint16_t x0, uint16_t y0, uint16_t r, uint8_t cornername,
      uint16_t delta, uint16_t color),
    drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
      uint16_t x2, uint16_t y2, uint16_t color),
    fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
      uint16_t x2, uint16_t y2, uint16_t color),
    drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h,
      uint16_t radius, uint16_t color),
    fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h,
      uint16_t radius, uint16_t color),
    drawBitmap(uint16_t x, uint16_t y, const uint8_t *bitmap,
      uint16_t w, uint16_t h, uint16_t color),
    drawChar(uint16_t x, uint16_t y, unsigned char c, uint16_t color,
      uint16_t bg, uint8_t size),
    setCursor(uint16_t x, uint16_t y),
    setTextColor(uint16_t c),
    setTextColor(uint16_t c, uint16_t bg),
    setTextSize(uint8_t s),
    setTextWrap(boolean w),
    setRotation(uint8_t r);

  size_t write(uint8_t);
  void print(const char* str);
  void print(int num);
  void print(float num);

  uint16_t
    height(void),
    width(void);

  uint8_t getRotation(void);

 protected:
  const uint16_t
    WIDTH, HEIGHT;   // This is the 'raw' display w/h - never changes
  uint16_t
    _width, _height, // Display w/h as modified by current rotation
    cursor_x, cursor_y;
  uint16_t
    textcolor, textbgcolor;
  uint8_t
    textsize,
    rotation;
  boolean
    wrap; // If set, 'wrap' text at right edge of display
};

#endif // _ADAFRUIT_GFX_H

