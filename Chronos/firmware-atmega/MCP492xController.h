#ifndef _MCP492XCONTROLLER_H_
#define _MCP492XCONTROLLER_H_

#include <stdint.h>

#define DAC_A_B_BIT  _BV(7)
#define DAC_BUF_BIT  _BV(6)   // 0 = unbuffered, 1 = buffered
#define DAC_GA_BIT   _BV(5)   // 0 = 2x gain,    1 = 1x gain
#define DAC_SHDN_BIT _BV(4)

class MCP492xController {

public:
  void init(uint8_t _cs, uint8_t _transfer_bits);

  void send(uint8_t data);

  void send(uint8_t high, uint8_t low);

  void send(uint16_t data);

private:
  uint8_t cs;
  uint8_t transfer_bits;
};

#endif /* _MCP492XCONTROLLER_H_ */
