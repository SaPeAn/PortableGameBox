
#ifndef SWIC_H
#define	SWIC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "common.h"
    
void swi2cinit(void);
void swi2cstart(void);
void swi2cstop(void);
uint8 swi2cwritebyte(uint8);
uint8 swi2creadbyte(void);
void RTCgetdata(uint8*);
void RTCsenddata(uint8*);

#ifdef	__cplusplus
}
#endif

#endif	/* SWIC_H */

