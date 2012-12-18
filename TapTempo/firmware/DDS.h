#ifndef _DDS_H_
#define _DDS_H_

#include <stdint.h>

class DDS {
public:
  void init();
  uint8_t getValue();
  void setFrequency(double freq);

private:
  volatile uint16_t accumulator;   // phase accumulator
  volatile uint16_t tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
