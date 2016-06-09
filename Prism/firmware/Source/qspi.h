#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "mxconstants.h"

/* N25Q512A Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE                      25 /// todo: what unit? bytes?
#define QSPI_PAGE_SIZE                       256

#ifdef __cplusplus
 extern "C" {
#endif

void qspi_erase(uint32_t address, uint32_t size);
void qspi_read(uint32_t address, uint8_t* buffer, uint32_t size);
void qspi_write(uint32_t address, uint8_t* buffer, uint32_t size);

#ifdef USE_QSPI_FLASH
void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi);
#endif /* USE_QSPI_FLASH */

#ifdef __cplusplus
}
#endif
