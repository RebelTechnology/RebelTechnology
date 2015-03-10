#ifndef _AUDIO_H
#define _AUDIO_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

   void audio_init(void);
   void audioCallback(uint16_t *src, uint16_t *dst, uint16_t sz);

#ifdef __cplusplus
}
#endif

#endif /* _AUDIO_H */
