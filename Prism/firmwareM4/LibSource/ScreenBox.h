#ifndef __StompBox_h__
#define __StompBox_h__

#include "basicmaths.h"
#include "FloatArray.h"
#include "PatchParameter.h"
#include "SmoothValue.h"
#include "StompBox.h"

typedef uint16_t Colour;

class PixelBuffer {
public:
  void copy(const PixelBuffer& other);
  Colour* getPixels();
  int getWidth();
  int getHeight();
};

class VideoBuffer {
public:
  ~VideoBuffer();
  void setPixel(int x, int y, Colour c);
  Colour getPixel(int x, int y, Colour c);
  void drawLine(int fromX, int fromY, int toX, int toY, Colour c);
  void drawVerticalLine(int x, int y, int length, Colour c);
  void drawHorizontalLine(int x, int y, int length, Colour c);
  void drawRectangle(int x, int y, int width, int height, Colour c);
  void fillRectangle(int x, int y, int width, int height, Colour c);
  void setOrigin(int absoluteX, int absoluteY);
  void setFont(int font, int size);
  void print(int x, int y, const char* text);
  void fill(Colour c);
  void invert();
  void clear();
  void clear(int x, int y, int width, int height);
  int getWidth();
  int getHeight();
  void draw(int x, int y, VideoBuffer& pixels);
  static VideoBuffer* create(int width, int height);
};

class VideoPatch : public Patch {
public:
  virtual void process(VideoBuffer& video, AudioBuffer& audio) = 0;
};

#endif // __StompBox_h__
