#include "common.h"
#include <stdlib.h>

uint8 clamp(uint8 val, uint8 min, uint8 max)
{
  if(val > max) val = max;
  if(val < min) val = min;
  return val;
}

void delay_ms(uint32 ms)
{
  uint32 temp = timestamp;
  while((timestamp - temp) < ms);
}

uint8 getbatlvl(uint8 Ubat)
{
  uint8 lvl = (239 - Ubat) / 8;
  static uint8 Umax = 240;
  static uint8 Umin = 228;
  static uint8 reslvl = 0;
  if(Ubat <= 180) return 100; // bat to low, immediately shotdown code - 100
  Ubat = clamp(Ubat, 192, 240);
  if((Ubat <= Umax) && (Ubat >= Umin)) return reslvl;
  else 
    switch(lvl)
    {
      case 0: Umin = 228; Umax = 240; reslvl = 0; break;
      case 1: Umin = 220; Umax = 236; reslvl = 1; break;
      case 2: Umin = 212; Umax = 228; reslvl = 2; break;
      case 3: Umin = 204; Umax = 220; reslvl = 3; break;
      case 4: Umin = 196; Umax = 212; reslvl = 4; break;
      case 5: Umin = 192; Umax = 204; reslvl = 5; break;
    }
}

void gettime(systime_t* tm)
{ 
  tm->hour = (uint8)(timestamp/3600000);
  tm->min = (uint8)((timestamp%3600000)/60000);
  tm->sec = (uint8)((timestamp%60000)/1000);
}

void randinit(void)
{
  srand((uint8)timestamp);
}

uint8 getrand(uint8 N)
{
  return (rand() % (N + 1));
}

uint8 dig_to_smb(uint8 dig)
{
  switch (dig)
  {
    case 0: return '0';
    case 1: return '1'; 
    case 2: return '2';
    case 3: return '3'; 
    case 4: return '4';
    case 5: return '5'; 
    case 6: return '6'; 
    case 7: return '7'; 
    case 8: return '8';
    case 9: return '9';
  }
  return 0;
}

void u16_to_str(uint8* str, uint16 num, uint8 ZF)
{ 
  str[0] = dig_to_smb(num/10000);
  num %= 10000;
  str[1] = dig_to_smb(num/1000);
  num %= 1000;
  str[2] = dig_to_smb(num/100);
  num %= 100;
  str[3] = dig_to_smb(num/10);
  str[4] = dig_to_smb(num%10);
  str[5] = '\0';  
  if(ZF)
  {
    int j = 0;
    for(int i = 0; i < 6; i++)
    {
      if((str[i] == '0') && !j) continue;
      str[j] = str[i];
      j++;
    }
  }
}
