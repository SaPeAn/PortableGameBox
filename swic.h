
#ifndef SWIC_H
#define	SWIC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "common.h"
    
void swicinit(void);
void swicstart(void);
void swicstop(void);
uint8 swicwritebyte(uint8);


#ifdef	__cplusplus
}
#endif

#endif	/* SWIC_H */

