#include "drv_adc.h"
#include <xc.h>


void adc_init()
{  
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b10010010;
      
}

uint8 adc_getval_an0()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00000001;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an1()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00000101;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an2()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00001001;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

