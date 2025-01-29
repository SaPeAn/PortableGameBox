#include "drv_7seg.h"
#include <xc.h>


uint8 n_count;

typedef struct{
  volatile uint8*  indPort;
  volatile uint8*  switchingPort;
  uint8            comPortBit; 
  uint8            symbol[8];
  uint8            dotFl[8]; 
} disp_t;

void DigToSeg (uint8 seg, uint8 dotFl)
{
  switch (seg)
  {
    case 1: PORTB = (uint8) (0b11111001 & ((dotFl == 1) ? 127 : 255)); break;
    case 2: PORTB = (uint8) (0b10100100 & ((dotFl == 1) ? 127 : 255)); break;
    case 3: PORTB = (uint8) (0b10110000 & ((dotFl == 1) ? 127 : 255)); break;
    case 4: PORTB = (uint8) (0b10011001 & ((dotFl == 1) ? 127 : 255)); break;
    case 5: PORTB = (uint8) (0b10010010 & ((dotFl == 1) ? 127 : 2551)); break;
    case 6: PORTB = (uint8) (0b10000010 & ((dotFl == 1) ? 127 : 255)); break;
    case 7: PORTB = (uint8) (0b11111000 & ((dotFl == 1) ? 127 : 255)); break;
    case 8: PORTB = (uint8) (0b10000000 & ((dotFl == 1) ? 127 : 255)); break;
    case 9: PORTB = (uint8) (0b10010000 & ((dotFl == 1) ? 127 : 255)); break;
    case 0: PORTB = (uint8) (0b11000000 & ((dotFl == 1) ? 127 : 255)); break;
    case 'A': PORTB = (uint8) (0b10001000 & ((dotFl == 1) ? 127 : 255)); break;
    case 'C': PORTB = (uint8) (0b10001000 & ((dotFl == 1) ? 127 : 255)); break;
    case 'E': PORTB = (uint8) (0b10001000 & ((dotFl == 1) ? 127 : 255)); break;
    case 'F': PORTB = (uint8) (0b10001000 & ((dotFl == 1) ? 127 : 255)); break;
  }
}

void Display (uint16 val)
{
  uint8 Low, Mid, High; 
  Low =(uint8) (val % 10);
  Mid =(uint8) (val % 100 / 10);
  High =(uint8) (val / 100);
  if(n_count == 0)
  {
    PORTA = 0b11111110;
    DigToSeg(Low,0);
  }
  if(n_count == 1)
  {
    PORTA = 0b11111101;
    DigToSeg(Mid,0);
  }
  if(n_count == 2)
  {
    PORTA = 0b11111011;
    DigToSeg(High,0);
  }
  n_count++;
  if(n_count == 3) n_count = 0;
}