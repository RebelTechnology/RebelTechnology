#ifndef __Codec_h
#define __Codec_h

#include <stdint.h>

class Codec {
 public:
  void reset();
  void start();
  void stop();
  void bypass(bool doBypass);
 private:
#define CS_BUFFER_SIZE   1024
uint32_t txbuf[CS_BUFFER_SIZE];
uint32_t rxbuf[CS_BUFFER_SIZE];
};

#endif /* __Codec_h */
