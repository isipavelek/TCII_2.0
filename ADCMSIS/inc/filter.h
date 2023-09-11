
/*
===============================================================================
 Name        : filter.h
 Author      : Israel Pavelek, Cesar Fuoco
 Version     : 1.0
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifndef LOWPASS_H_
#define LOWPASS_H_

#include <stdint.h>

#define PROM_TAP_NUM 32
#define LOWPASS_TAP_NUM 10//49
#define BIQUAD1_TAP_NUM 5

#define SAMPLES_PER_BLOCK 128

extern int32_t lowpass_taps[];
extern int32_t biquad1_taps[];
extern int32_t prom_taps[];

extern float float_lowpass_taps[];


#endif /* LOWPASS_H_ */
