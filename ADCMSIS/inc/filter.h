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

#define PROM_TAP_NUM 32
#define LOWPASS_TAP_NUM 2//49
#define BIQUAD1_TAP_NUM 5

#define SAMPLES_PER_BLOCK 128

extern int lowpass_taps[];
extern int biquad1_taps[];
extern int prom_taps[];

#endif /* LOWPASS_H_ */
