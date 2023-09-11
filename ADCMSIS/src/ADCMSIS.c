/*
===============================================================================
 Name        : ADCMSIS.c
 Author      : Israel Pavelek, Cesar Fuoco
 Version     : 1.0
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <filter.h>
#include "adc.h"
#include "dac.h"
#include "arm_math.h"

typedef enum{
	TALKTHROUGH,
	FIRLP,
	BIQUAD1,
	PROM
}filter_type_t;

filter_type_t filter = FIRLP;  //Función que ejecuta


extern uint8_t procesar;
extern uint8_t estado;
extern bool flag;
extern uint16_t index;

arm_fir_instance_q31 SLP;
arm_biquad_casd_df1_inst_q31  SBIQUAD1;
arm_fir_instance_q31 SPROM;
q31_t prom_state[PROM_TAP_NUM+SAMPLES_PER_BLOCK-1];
q31_t lowpass_state[LOWPASS_TAP_NUM+SAMPLES_PER_BLOCK-1];
q31_t biquad1_state[BIQUAD1_TAP_NUM+SAMPLES_PER_BLOCK-1];

//Ping Pong Buffers
q31_t InputA[SAMPLES_PER_BLOCK];
q31_t InputB[SAMPLES_PER_BLOCK];
q31_t OutputA[SAMPLES_PER_BLOCK];
q31_t OutputB[SAMPLES_PER_BLOCK];

void adc_to_q31(int32_t bufferIN[], q31_t bufferOUT[],uint32_t samples){
	for(uint32_t i=0;i<samples;i++){
		bufferOUT[i]=(bufferIN[i]<<20);

	}


}

void q31_to_dac(q31_t bufferIN[],int32_t bufferOUT[],uint32_t samples){
	for(uint32_t i=0;i<samples;i++){
		bufferOUT[i]=(bufferIN[i]>>20);


	}

}

int main(void) {

    SystemCoreClockUpdate();
    Board_Init();
    Board_LED_Set(0, true);

    //Inicializa los filtros
   // arm_fir_init_q31(&SLP,LOWPASS_TAP_NUM,lowpass_taps,lowpass_state,SAMPLES_PER_BLOCK);
    arm_biquad_cascade_df1_init_q31	(&SBIQUAD1,1,biquad1_taps,biquad1_state,0);
    arm_float_to_q31(float_lowpass_taps, lowpass_taps,LOWPASS_TAP_NUM);
    arm_fir_init_q31(&SPROM,PROM_TAP_NUM,prom_taps,prom_state,SAMPLES_PER_BLOCK);

	//Inicializa ADC y DAC
    adcInit();
	dacInit();

	while(true){
		if(procesar){
			procesar=false;
			switch (filter){
				case TALKTHROUGH:
						for(uint8_t i=0;i<SAMPLES_PER_BLOCK;i++){
							if(estado)OutputA[i]=InputA[i];
							else OutputB[i]=InputB[i];
						}
						break;
				case BIQUAD1:

						break;

				case FIRLP:
						if(estado){
							adc_to_q31(InputA,InputA,SAMPLES_PER_BLOCK);
							arm_fir_q31(&SPROM,InputA, OutputA, SAMPLES_PER_BLOCK);
							q31_to_dac(OutputA,OutputA,SAMPLES_PER_BLOCK);
						}else {
							adc_to_q31(InputB,InputB,SAMPLES_PER_BLOCK);
							arm_fir_q31(&SPROM,InputB, OutputB, SAMPLES_PER_BLOCK);
							q31_to_dac(OutputB,OutputB,SAMPLES_PER_BLOCK);
						}
						break;

				case PROM:
						if(estado){
							arm_fir_q31(&SLP,InputA, OutputA, SAMPLES_PER_BLOCK);
						}
						else {
							arm_fir_q31(&SLP,InputB, OutputB , SAMPLES_PER_BLOCK);
						}
						break;

			}

		}else{
			if(flag){
				if(!estado)dacWrite(OutputA[index]);
				else dacWrite(OutputB[index]);
			}

		}
	}
}

void MAfilter(q31_t * pSrc,q31_t * pDst,uint32_t blockSize){


}
