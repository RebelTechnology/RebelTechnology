#ifndef __Codec_h
#define __Codec_h

#include <stdint.h>

class Codec {
 public:
  void reset();
  void start();
  void stop();
  void bypass(bool doBypass);
  void clear();
  void txrx();
  void set(uint32_t value);
  void ramp(uint32_t max);
  uint32_t getMin();
  uint32_t getMax();
  float getAvg();
 private:
};

extern Codec codec;
#endif /* __Codec_h */
