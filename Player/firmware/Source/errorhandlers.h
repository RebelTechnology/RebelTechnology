#include <stdint.h>

#define ASSERT(cond, msg) do{if(!(cond))setErrorMessage(PROGRAM_ERROR, msg);}while(0)

#ifdef __cplusplus
 extern "C" {
#endif

   void error(int8_t code, const char* reason);
   int8_t getErrorStatus();
   const char* getErrorMessage();
   void setErrorStatus(int8_t err);
   void setErrorMessage(int8_t err, const char* msg);
   void setParameterValues(uint16_t* values, int size);

#define NO_ERROR            0x00
#define HARDFAULT_ERROR     0x10
#define BUS_ERROR           0x20
#define MEM_ERROR           0x30
#define NMI_ERROR           0x40
#define USAGE_ERROR         0x50
#define PROGRAM_ERROR       0x60
#define CONFIG_ERROR        0x70

#ifdef __cplusplus
}
#endif
