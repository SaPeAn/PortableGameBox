
#ifndef DRV_SOFT_SPI_H
#define	DRV_SOFT_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "common.h"
void SoftSPI_init(uint8*, uint8, uint8, uint8, uint8);
uint8 SoftSPI_RxTx(uint8);


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_SOFT_SPI_H */

