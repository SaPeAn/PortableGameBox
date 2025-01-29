#include <pic18f2550.h>
#include "drv_soft_spitx.h"

#define   SDO          PORTCbits.RC0
#define   SCL          PORTCbits.RC1
#define   CS           PORTCbits.RC2
#define   SDO_tris     TRISCbits.RC0
#define   SCL_tris     TRISCbits.RC1
#define   CS_tris      TRISCbits.RC2
#define   DELAY_CYCL   4

void delayspi(uint8 del)
{
  while(--del);
}

void SW_SPITX_init(void)
{
  SDO_tris = 0;
  SCL_tris = 0;
  CS_tris = 0;
  CS = 1;
  SCL = 1;
}

void SW_SPI_sendbyte(uint8 bt)
{
  CS = 0;
  for(uint8 i = 8; i > 0; i--)
  {
    SCL = 0;
    SDO = (bt >> (i-1)) & 0x01;
    delayspi(DELAY_CYCL);
    SCL = 1;    
  }
  CS = 1;
}
