#ifndef _MACROS_H_
#define _MACROS_H_

#define _BV(bit) (1 << (bit))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
/* #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) */
/* #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) */
/* #define radians(deg) ((deg)*DEG_TO_RAD) */
/* #define degrees(rad) ((rad)*RAD_TO_DEG) */
/* #define sq(x) ((x)*(x)) */

#endif /* _MACROS_H_ */
