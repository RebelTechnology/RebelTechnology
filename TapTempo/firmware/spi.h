#ifndef _SPI_H_
#define _SPI_H_

#include <inttypes.h>

void spi_init();
/* void spi_transfer(uint8_t working); */
void spi_out(uint8_t high, uint8_t low);

#endif /* _SPI_H_ */
