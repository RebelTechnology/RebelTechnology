#ifndef _DDS_H_
#define _DDS_H_

#include <stdint.h>

class DDS {
public:
  void init();
  uint16_t getValue();
  void setFrequency(double freq);

private:
  volatile uint32_t accumulator;   // phase accumulator
  volatile uint32_t tuning;  // dds tuning word
};


#endif /* _DDS_H_ */
