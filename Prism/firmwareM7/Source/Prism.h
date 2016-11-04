#ifndef __PRISM_H
#define __PRISM_H

#include "ProgramVector.h"

#ifdef __cplusplus
 extern "C" {
#endif

   void encoderChanged(uint8_t encoder, int32_t value);
   void setup(ProgramVector* pv);
   void processBlock(ProgramVector* pv);
   void setParameterValue(uint8_t pid, int16_t value);

#ifdef __cplusplus
}
#endif

#endif /* __PRISM_H */
