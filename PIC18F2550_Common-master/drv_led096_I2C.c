/******************************************************************************/
//      
//    OLED display 0.96 inches
//    Controller - SSD1306
//    I2C interface
//
/******************************************************************************/

#include "drv_led096_I2C.h"
#include "display_data.h"
#include "drv_I2C.h"

#define DEV_ADDR       0x78


void Led096Init(void)
{
  I2C_init();
  Led096Set(8, 0xD5, 0xF0, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x01);
  Led096Clear();
}

void Led096Set(uint8 N, ...)
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

void Led096Clear(void)
{
  Led096Set(6, 0x22, 0, 7, 0x21, 0, 127); // select all screen area
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint16 i = 0; i < 1024; i++) I2C_WriteByte(0x00);
  I2C_Stop();
}

void Led096Full(void)
{
  Led096Set(6, 0x22, 0, 7, 0x21, 0, 127); // select all screen area
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
   I2C_WriteByte(0x40);
  for(uint16 i = 0; i < 1024; i++) I2C_WriteByte(0xFF);
  I2C_Stop();
}

void Led096PrintSmb8x5(uint8 smb, uint8 StartPage, uint8 StartColumn)
{
  Led096Set(6, 0x22, StartPage, StartPage, 0x21, StartColumn, (StartColumn+5));
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint16 i = 0; i < 5; i++) I2C_WriteByte(char_8x5[smb][i]);
  I2C_Stop();
}

uint8 Led096PrintStr8x5(uint8* str, uint8 StartPage, uint8 StartColumn)
{
  uint8 i = 0;
  while(str[i])
  {
    if(str[i] == '\n') {
      StartPage +=1; 
      StartColumn = 0;
    } 
    else {
      Led096PrintSmb8x5(str[i], StartPage, StartColumn);
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

void Led096PrintClock(uint8 hour, uint8 min, uint8 sec)
{
  uint8 secL = sec%10;
  uint8 minL = min%10;
  uint8 hourL = hour%10;
  sec /= 10;
  min /= 10;
  hour /= 10;
  uint8 cl_digits[8] = {hour, hourL, 10, min, minL, 10, sec, secL};
  Led096Set(6, 0x22, 6, 7, 0x21, 0, 95);
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint8 j = 0; j < 8; j++) 
    for(uint8 i = 0; i < 24; i++) 
      I2C_WriteByte(clock_dig[cl_digits[j]][i]);
  I2C_Stop();
}

void Led096PrintBat(uint8 level) // level = 0, 1, 2, 3, 4, 5, 6, 7, 8
{
  Led096Set(6, 0x22, 6, 7, 0x21, 96, 127);
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);
  for(uint8 i = 0; i < 64; i++) I2C_WriteByte(battary[8-level][i]);
  I2C_Stop();
}

void Led096PrintBender(void)
{
  Led096Set(6, 0x22, 0, 5, 0x21, 22, 127);
  I2C_Start();
  I2C_WriteByte(DEV_ADDR);
  I2C_WriteByte(0x40);  
  for(uint16 i = 0; i < 504; i++) I2C_WriteByte(bender[i]);
  I2C_Stop();
}
