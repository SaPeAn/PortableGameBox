#ifndef LED096_H
#define	LED096_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "common.h"
#include <stdarg.h>

void Led096Init(void);
void Led096Set(uint8, ...);
void Led096Clear(void);
void Led096Full(void);
void Led096PrintSmb8x5(uint8, uint8, uint8);
uint8 Led096PrintStr8x5(uint8*, uint8, uint8);
void Led096PrintClock(uint8, uint8, uint8);
void Led096PrintBat(uint8);
void Led096PrintBender(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LED096_H */

