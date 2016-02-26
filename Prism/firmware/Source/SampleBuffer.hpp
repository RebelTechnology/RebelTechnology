#ifndef __SAMPLEBUFFER_H__
#define __SAMPLEBUFFER_H__

// #ifdef ARM_CORTEX
// #include "arm_math.h"
// #endif //ARM_CORTEX

#define AUDIO_MAX_BLOCK_SIZE (CS_BUFFER_SIZE/4)

// class SampleBuffer : public AudioBuffer {
class SampleBuffer {
protected:
  float left[AUDIO_MAX_BLOCK_SIZE];
  float right[AUDIO_MAX_BLOCK_SIZE];
  uint16_t size;
public:
  void split(uint32_t* input, uint16_t blocksize){
    assert_param((blocksize & 0x3) == 0);
    size = blocksize;
    float* l = left;
    float* r = right;
    uint32_t cnt = size >> 1u; // *2/4
    while(cnt > 0u){
      *l++ = (float)(int32_t)((*input++)<<8) / 2147483648.0f;
      *r++ = (float)(int32_t)((*input++)<<8) / 2147483648.0f;
      *l++ = (float)(int32_t)((*input++)<<8) / 2147483648.0f;
      *r++ = (float)(int32_t)((*input++)<<8) / 2147483648.0f;
      cnt--;
    }
  }
  void comb(uint32_t* output){
    uint32_t* dest = output;
    int32_t tmp;
    // Seems CS4271 ADC samples are signed, DAC are unsigned. I2S Standard mode.
    // Also appears that setting any of the high bits causes a
    for(int i=0; i<size; ++i){
      // tmp = (int32_t)(left[i] * 0x800000);
      // *dest++ = (uint32_t)(tmp+0x800000);
      // tmp = (int32_t)(right[i] * 0x800000);
      // *dest++ = (uint32_t)(tmp+0x800000);
      tmp = (uint32_t)((int32_t)(right[i] * 2147483648.0f));
      *dest++ = tmp>>8;
      tmp = (uint32_t)((int32_t)(right[i] * 2147483648.0f));
      *dest++ = tmp>>8;
    }
    // float* l = left;
    // float* r = right;
    // uint32_t cnt = size >> 1u; // *2/4
    // while(cnt > 0u){
    //   // *output++ = ((uint32_t)(*l++ * 2147483648.0f))>>8;
    //   // *output++ = ((uint32_t)(*r++ * 2147483648.0f))>>8;
    //   // *output++ = ((uint32_t)(*l++ * 2147483648.0f))>>8;
    //   // *output++ = ((uint32_t)(*r++ * 2147483648.0f))>>8;
    //   *output++ = ((uint32_t)(*l++ * 8388608.0f));
    //   *output++ = ((uint32_t)(*r++ * 8388608.0f));
    //   *output++ = ((uint32_t)(*l++ * 8388608.0f));
    //   *output++ = ((uint32_t)(*r++ * 8388608.0f));
    //   cnt--;
    // }
  }
  void set(float value){
    for(int i=0; i<size; ++i){
      left[i] = value;
      right[i] = value;
    }
  }
  void clear(){
    set(0);
    // memset(left, 0, getSize()*sizeof(float));
    // memset(right, 0, getSize()*sizeof(float));
  }
  // inline FloatArray getSamples(int channel){
  //   return channel == 0 ? FloatArray(left, size) : FloatArray(right, size);
  // }
  inline float* getSamples(int channel){
    return channel == 0 ? left : right;
  }
  inline int getChannels(){
    return 2;
  }
  // void setSize(uint16_t sz){
  // // size is set by split()
  //   if(sz <= AUDIO_MAX_BLOCK_SIZE)
  //     size = sz;
  // }
  inline int getSize(){
    return size;
  }
};

#endif // __SAMPLEBUFFER_H__
