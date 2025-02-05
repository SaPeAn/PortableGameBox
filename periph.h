
#ifndef INIT_PERIPH_H
#define	INIT_PERIPH_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "common.h"
    
btn_t B1;
btn_t B2;
btn_t B3;
btn_t B4;

uint8 ox, oy; //joystick coordinates
uint8 bright = 200;
    
void initbuttons(void);    
void Interrupt_init(void);
void timersinit(void);
uint8 adc_getval_an0(void);
uint8 adc_getval_an1(void);
uint8 adc_getval_an2(void);
void testbuttons(void);
void initbuttons(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INIT_PERIPH_H */

