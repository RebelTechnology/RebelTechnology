#include "audio.h"
#include "CodecController.h"

CodecController codec;
ApplicationSettings settings;

void audio_init(void){
  codec.setup();
  codec.init(settings);
  codec.start();
}

uint16_t* source;
uint16_t* dest;

volatile bool doProcessAudio = false;
void audioCallback(uint16_t *src, uint16_t *dst, uint16_t sz){
#ifdef DEBUG_AUDIO
  togglePin(GPIOA, GPIO_Pin_7); // PA7 DEBUG
#endif
  /* if(doProcessAudio) */
  /*   collision = true; */
  source = src;
  dest = dst;
  doProcessAudio = true;
}
