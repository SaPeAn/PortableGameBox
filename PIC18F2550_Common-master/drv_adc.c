#include "drv_adc.h"
#include <pic18f2550.h>



void adc_init(void)
{
  TRISA |= 0b00000111;  // PortA 0-2 pins as inputs
  ADCON1 = 0b00001100;  // Vref+ - Vdd; Vref- - Vss; Enable AN0-AN2 analog inputs
  ADCON2 = 0b00001010;  // Right justified data; Acquisition time = 2Tad; Tad = 32/Fosc
}

uint8 adc_getval_an0(void)
{
  ADCON0 = 0b00000011;
  while(ADCON0bits.GODONE);
  ADCON0 = 0b00000000;
  return ADRESH;  
}

uint8 adc_getval_an1(void)
{
  ADCON0 = 0b00000111;
  while(ADCON0bits.GODONE);
  ADCON0 = 0b00000000;
  return ADRESH;  
}

uint8 adc_getval_an2(void)
{
  ADCON0 = 0b00001011;
  while(ADCON0bits.GODONE);
  ADCON0 = 0b00000000;
  return ADRESH;  
}


