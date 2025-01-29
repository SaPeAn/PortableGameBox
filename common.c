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

void u8_to_str(uint8* str, uint8 num)
{ 
  str[0] = num/100;
  str[1] = (num%100)/10;
  str[2] = num%10;
  if(num > 99)
  {
    for(uint8 i = 0; i < 3; i++) {
    str[i] = dig_to_smb(str[i]);
    }
    str[3] = '\0';
  }
  if((num > 9) && (num < 100))
  {
    for(uint8 i = 0; i < 2; i++) {
    str[i] = dig_to_smb(str[i+1]);
    }
    str[2] = '\0';
  }
  if(num < 10)
  {
    str[0] = dig_to_smb(str[2]);
    str[1] = '\0';
  }
}
