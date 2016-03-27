#ifndef __PRISM_H
#define __PRISM_H

#include "ProgramVector.h"

#ifdef __cplusplus
 extern "C" {
#endif

   void encoderChanged(int encoder, int32_t value);
   void setup(ProgramVector* pv);
   void processBlock(ProgramVector* pv);

#ifdef __cplusplus
}
#endif

#endif /* __PRISM_H */
