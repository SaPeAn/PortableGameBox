
#ifndef DRV_SOFT_SPI_H
#define	DRV_SOFT_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "common.h"
    
//void delayspi(uint8);    
void SW_SPITX_init(void);
void SW_SPI_sendbyte(uint8);


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_SOFT_SPI_H */

