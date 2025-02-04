
/*------------------------------INCLUDES--------------------------------------*/
#include <xc.h>
#include "config.h"
#include "common.h"
#include "drv_lcdST7565_SPI.h"
#include "ufo_battle.h"
#include "drv_swi2cRTC.h"
/*----------------------------------------------------------------------------*/

/*---------------------------------INTERRAPTS---------------------------------*/
void __interrupt() systemTime_int(void)
{
  if (TMR1IE && TMR1IF)
  {
    Nop();
    TMR1H = 217;
    TMR1L -= 3;
    TMR1IF = 0;
    timestamp++;
    Nop();
    return;
  }
}
/*----------------------------------------------------------------------------*/

/*-----------------------------------MAIN-------------------------------------*/
void main(void) 
{
/*-------------------------------Initialization-------------------------------*/
  commoninit();
  timersinit();
  Interrupt_init();
  randinit();
  LCD_Init();
  LCD_Erase();
  initbuttons();
  CMCON = 0b11000111;
  swi2cinit();
  BrightPWM(bright);
/*----------------------------------------------------------------------------*/
  uint8 tempval = 0;
  uint8 stringtemp[6];
  uint8 RTCdata[7] = {0, 0, 0, 0, 0, 0, 0};
  uint8 RTCgetdat[7];
/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  { 
    testbuttons();
    
    if(B1.BtnON) 
    {
      B1.BtnON = 0; 
      
      for(uint8 i = 0; i < 7; i++) {
      u16_to_str(stringtemp, RTCdata[i], DISABLE);
      LCD_printStr8x5(stringtemp, i, 2);
      }
      
      static uint8 i = 0;
      if(i < 10) for(uint8 j = 0; j < 7; j++) RTCdata[j]++;
      else i = 0;
      i++;
      RTCsenddata(RTCgetdata);
    } 
    
    if(B2.BtnON) 
    {
      B2.BtnON = 0;
      RTCgetdata(RTCgetdat);
      for(uint8 i = 0; i < 7; i++) {
      u16_to_str(stringtemp, RTCgetdat[i], DISABLE);
      LCD_printStr8x5(stringtemp, i, 37);
      }
    }
    
    if(B3.BtnON)
    {
      B3.BtnON = 0;
      static uint8 k = 0;
      if(k >= 7) k = 0;
      swi2cstart();
      swi2cwritebyte(0xA2);
      swi2cwritebyte(0x02 + k);
      swi2cstop();
      swi2cstart();
      swi2cwritebyte(0xA3);
      tempval =  swi2creadbyte();
      swi2cstop();
      u16_to_str(stringtemp, tempval, DISABLE);
      LCD_printStr8x5(stringtemp, k, 72);
      k++;
    }
    
    
    //ufobattle_init();
    //ufobattle_start();

 
  }
/*----------------------------------------------------------------------------*/
  //return;
}