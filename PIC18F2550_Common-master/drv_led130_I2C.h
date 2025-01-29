
#ifndef DRV_LED130_I2C_H
#define	DRV_LED130_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
   
#include "common.h"
#include <stdarg.h>

void Led130Init(void);
void Led130Set(uint8, ...);
void Led130Clear(void);
void Led130Full(void);
void Led130PrintSmb8x5(uint8, uint8, uint8);
uint8 Led130PrintStr8x5(uint8*, uint8, uint8);
void Led130PrintClock(uint8, uint8, uint8);
void Led130PrintBat(uint8,uint8, uint8);
void Led130PrintBender(uint8,uint8);




#ifdef	__cplusplus
}
#endif

#endif	/* DRV_LED130_I2C_H */

