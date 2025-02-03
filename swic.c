#include <xc.h>

#include "swic.h"

#define      SCL_O        LATAbits.LA5
#define      SDA_O        LATCbits.LC0
#define      SCL_I        PORTAbits.RA5
#define      SDA_I        PORTCbits.RC0
#define      SCL_DIR      TRISAbits.RA5
#define      SDA_DIR      TRISCbits.RC0
#define      IN           1
#define      OUT          0
uint8 delay = 25;

void swicdelay(uint8 del)
{
  while(del--);  
}

void swicinit(void)
{
  SCL_DIR = IN;
  SDA_DIR = IN;
}

void swicstart(void)
{
  SDA_O = 0;
  SDA_DIR = OUT;
  swicdelay(delay);
  SCL_O = 0;
  SCL_DIR = OUT;
  swicdelay(delay);
}

void swicstop(void)
{
  SCL_O = 1;
  swicdelay(delay);
  SDA_O = 1;
  swicdelay(delay);
}

uint8 swicwritebyte(uint8 byte)
{
  for(uint8 i = 0; i < 8; i++)
  { 
    SDA_O = (byte >> i) & 1;
    swicdelay(delay);
    SCL_O = 1;
    swicdelay(delay);
    SCL_O = 0;
    swicdelay(delay);
  }
  SDA_DIR = IN;
  swicdelay(delay);
  SCL_O = 1;
  swicdelay(delay);
  uint8 tmp = SDA_I;
  SCL_O = 0;
  swicdelay(delay);
  SDA_DIR = OUT;
  if(tmp == 0) return 1; 
  else return 0;
}
