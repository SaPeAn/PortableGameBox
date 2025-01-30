#ifndef DRV_ADC_H
#define	DRV_ADC_H

#include "common.h"

#ifdef	__cplusplus
extern "C" {
#endif


void adc_init(void);
uint8 adc_getval_an0(void);
uint8 adc_getval_an1(void);
uint8 adc_getval_an2(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_ADC_H */

