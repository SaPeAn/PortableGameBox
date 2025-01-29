/******************************************************************************/
//      
//    OLED display 1.3 inches
//    Controller - SH1106
//    I2C interface
//
/******************************************************************************/


#include "drv_led130_I2C.h"
#include "display_data.h"
#include "drv_I2C.h"

#define DEV_ADDR       0x78

void Led130Init(void){
  I2C_init();
  Led130Set(23, 0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0x8D, 0x10, 0x20, 0x00, 0xA0, 0xC0, 0xDA, 0x12, 0x81, 0x9F, 0xd9, 0xDB, 0x40, 0xA4, 0xA6);
  Led130Set(1, 0xAF);
  Led130Clear();
}

void Led130Set(uint8 N, ...)
{
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x00);
  va_list arg;
  va_start(arg, N);
  for(uint8 i = 0; i < N; i++) I2C_WriteByte(va_arg(arg,uint8));
  va_end(arg);
  I2C_Stop();
}

void Led130Clear(void)
{
  uint8 pg = 1, cl = 2;
  for(uint8 j = 0; j < 8; j++)
  {
    Led130Set(3, 0xB0 | j, 0x00 | (0xF & cl), 0x10 | (cl >> 4));
    I2C_Start();
    I2C_WriteByte(DEV_ADDR);
    I2C_WriteByte(0x40);
    for(uint16 i = 0; i < 128; i++) 
    {
      I2C_WriteByte(0x00);
    }
    I2C_Stop();
  }
}

void Led130Full(void)
{
  uint8 pg = 1, cl = 2;
  for(uint8 j = 0; j < 8; j++)
  {
    Led130Set(3, 0xB0 | j, 0x00 | (0xF & cl), 0x10 | (cl >> 4));
    I2C_Start();
    I2C_WriteByte(DEV_ADDR);
    I2C_WriteByte(0x40);
    for(uint16 i = 0; i < 128; i++) 
    {
      I2C_WriteByte(0xFF);
    }
    I2C_Stop();
  }
}

void Led130PrintSmb8x5(uint8 smb, uint8 StartPage, uint8 StartColumn)
{
  Led130Set(3, 0xB0 | StartPage, 0x00 | (0xF & (StartColumn + 2)), 0x10 | ((StartColumn + 2) >> 4));
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint16 i = 0; i < 5; i++) I2C_WriteByte(char_8x5[smb][i]);
  I2C_Stop();
}

uint8 Led130PrintStr8x5(uint8* str, uint8 StartPage, uint8 StartColumn)
{
  uint8 i = 0;
  while(str[i])
  {
    if(str[i] == '\n') {
      StartPage +=1; 
      StartColumn = 0;
    } 
    else {
      Led130PrintSmb8x5(str[i], StartPage, StartColumn);
      StartColumn += 6;
    }
    if(StartColumn > 121) {
      StartPage +=1; 
      StartColumn = 0;
    }
    if(StartPage > 7) break;
    i++;
  } 
  return i;
}

void Led130PrintClock(uint8 hour, uint8 min, uint8 sec)
{
  uint8 secL = sec%10;
  uint8 minL = min%10;
  uint8 hourL = hour%10;
  sec /= 10;
  min /= 10;
  hour /= 10;
  uint8 cl_digits[8] = {hour, hourL, 10, min, minL, 10, sec, secL};
  Led130Set(6, 0x22, 6, 7, 0x21, 0, 95);
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint8 j = 0; j < 8; j++) 
    for(uint8 i = 0; i < 24; i++) 
      I2C_WriteByte(clock_dig[cl_digits[j]][i]);
  I2C_Stop();
}

void Led130PrintBat(uint8 level, uint8 stPage, uint8 stCol) // level = 0, 1, 2, 3, 4, 5, 6, 7, 8
{
  stCol = stCol + 2;
  for(uint8 i = 0; i < 64; i++) {
    if(i % 2) Led130Set(3, ((stCol+i/2)  & 0x0F), 0x10 | ((stCol+i/2) >> 4), 0xB0 | (stPage + 1));
    else Led130Set(3, ((stCol+i/2)  & 0x0F), 0x10 | ((stCol+i/2) >> 4), 0xB0 | (stPage));
    I2C_Start();
    I2C_WriteByte(DEV_ADDR);
    I2C_WriteByte(0x40); 
    I2C_WriteByte(battary[8-level][i]);
    I2C_Stop();
  }
 
}

void Led130PrintBender(uint8 StartPage, uint8 StartColumn)
{
  StartColumn = StartColumn + 2;
  for(uint16 i = 0; i < 84; i++) 
  { 
    for(uint8 j = 0; j < 6; j++)
    {
      Led130Set(3, 0xB0 | (StartPage + j), 0x00 | (0xF & (StartColumn + i)), 0x10 | ((StartColumn + i) >> 4));
      I2C_Start();
      I2C_WriteByte(DEV_ADDR);
      I2C_WriteByte(0x40); 
      I2C_WriteByte(bender[i*6 + j]);
      I2C_Stop();
    }
  }
}
