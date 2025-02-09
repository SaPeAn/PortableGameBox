/******************************************************************************/
//      
//    RTC/calendar - PCF8563
//    
//    
//    sofrware I2C
//    
/******************************************************************************/


#include <xc.h>
#include "drv_swi2cRTC.h"

#define      SCLO        LATAbits.LA5
#define      SDAO        LATCbits.LC0
#define      SCLI        PORTAbits.RA5
#define      SDAI        PORTCbits.RC0
#define      SCLDIR      TRISAbits.RA5
#define      SDADIR      TRISCbits.RC0
#define      IN           1
#define      OUT          0

#define      DELAY       swi2cdelay(DEL_CYCLE)
#define      DEL_CYCLE   5


uint8 swi2cdelay(uint8 del)
{
  while(del--); 
  return 0;
}

void swi2cinit(void)
{
  SCLDIR = IN;
  SDADIR = IN;
  SDAO = 0;
  SCLO = 0;
}

void swi2cstart(void)
{
  SDADIR = OUT;
  DELAY;
  SCLDIR = OUT;
  DELAY;
}

void swi2cstop(void)
{
  SCLDIR = IN;
  DELAY;
  SDADIR = IN;
  DELAY;
}

uint8 swi2cwritebyte(uint8 byte)
{
  for(uint8 i = 0; i < 8; i++)
  { 
    if(((byte << i) & 128)) SDADIR = IN;
    else SDADIR = OUT;
    DELAY;
    SCLDIR = IN;
    DELAY;
    SCLDIR = OUT;
    DELAY;
  }
  SDADIR = IN;
  DELAY;
  SCLDIR = IN;
  uint8 j = 25;
  while(!SCLI) {
    if(!(j--)) {
      j = 2;         // error 2 - SCL not free
      break;
    }
  } 
  DELAY;
  if(SDAI) {SCLDIR = OUT; DELAY; return 0;} 
  else {SCLDIR = OUT; DELAY; return 1;}  
}

uint8 swi2creadbyte(void)
{
  uint8 byte = 0;
  for(uint8 i = 0; i < 8; i++)
  {
    SDADIR = IN;
    SCLDIR = IN;
    uint8 j = 25;
    while(!SCLI) {
      if(!(j--)) {
        j = 2;                // error 2 - SCL not free
        break;
      }
    }
    if(SDAI) byte |= (128 >> i);
    DELAY;
    SCLDIR = OUT;
    DELAY;
  }
  SCLDIR = IN;
  uint8 k = 25;
  while(!SCLI) {
    if(!(k--)) {
      k = 2;                // error 2 - SCL not free
      break;
    }
  }
  SDADIR = OUT;
  DELAY;
  SCLDIR = OUT;
  DELAY;
  return byte;
}

void RTCgetdata(uint8* RTCarr)
{ 
  swi2cstart();
  swi2cwritebyte(0xA2);
  swi2cwritebyte(0x02);
  swi2cstop();  
  for(uint8 i = 0; i < 7; i++) {
    swi2cstart();
    swi2cwritebyte(0xA3);
    RTCarr[i] = swi2creadbyte();
    swi2cstop();
  }
}

void RTCsenddata(uint8* RTCarr)
{  
  swi2cstart();
  swi2cwritebyte(0xA2);
  swi2cwritebyte(0x02);
  for(uint8 i = 0; i < 7; i++) {
    swi2cwritebyte(RTCarr[i]);
  }
  swi2cstop();
}
