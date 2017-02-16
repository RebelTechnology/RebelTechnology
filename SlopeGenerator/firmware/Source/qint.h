#ifndef __QINT_H__
#define __QINT_H__

#include <stdint.h>

typedef int16_t q15_t;
typedef int32_t q31_t;
typedef int64_t q63_t;

#define Q15_MIN INT16_MIN
#define Q15_MAX INT16_MAX
#define Q31_MIN INT32_MIN
#define Q31_MAX INT32_MAX

#define Q15_MUL_Q15(a,b) (__SSAT(((q31_t)a*b)>>15, 16))
#define Q31_MUL_Q31(a,b) (__SSAT(((q63_t)a*b)>>30, 32))
#define Q15_DIV_Q15(a,b) (((q31_t)a<<15)/b) /* non-rounding */
#define Q15_RECIPROCAL(a) (((q31_t)Q15_MAX<<15)/a)

#endif /* defined(__QINT_H__) */
