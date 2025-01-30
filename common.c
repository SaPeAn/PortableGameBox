#include "common.h"
#include <stdlib.h>


void Delay_ms(uint32 ms)
{
  uint32 temp = timestamp;
  while((timestamp - temp) < ms);
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
