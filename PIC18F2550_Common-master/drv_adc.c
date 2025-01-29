#include "drv_adc.h"
#include <pic18f2550.h>
#include "common.h"



void adc_init()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;
  ADCON2 = 0b00001010;
  ADCON0 = 0b00000001;
}

uint8 adc_getval_an0()
{
  ADCON0 |= 0b00000010;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an1()
{
  ADCON0 |= 0b00000010;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an2()
{
  ADCON0 |= 0b00000010;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}


