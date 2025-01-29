#include "xc.h"
#include "drv_usart.h"


void USART_init()
{
TRISC = 0x80; 
TRISC = 0x40;
BRG16 = 0;
SPBRG=24;
TX9  = 0;
TXEN = 1;
SYNC = 0;
BRGH = 1;
TX9D = 0;
SPEN = 1;
CREN = 1;
RX9D = 0;
}

void testSendUSART(uint32 systemtime, uint8 i)
{
  static uint32 testUSARTtime;
  if((systemtime - testUSARTtime) > 200)
  {
    testUSARTtime = systemtime;
    TXREG = i;
  }
}