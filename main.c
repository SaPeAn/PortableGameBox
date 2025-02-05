
/*------------------------------INCLUDES--------------------------------------*/
#include <xc.h>
#include "config.h"
#include "common.h"
#include "drv_lcdST7565_SPI.h"
#include "ufo_battle.h"
#include "drv_swi2cRTC.h"
/*----------------------------------------------------------------------------*/

/*---------------------------------INTERRAPTS---------------------------------*/
void __interrupt() systemTick_int(void)
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
  SPI_init();
  LCD_Init();
  LCD_Erase();
  initbuttons();
  CMCON = 0b11000111;
  swi2cinit();
  BrightPWM(brightPWM);
/*----------------------------------------------------------------------------*/
  uint8 tempval = 0;
  uint8 stringtemp[6];
  rtcraw.rtcpar.year = 25;
  rtcraw.rtcpar.month = 1;
  rtcraw.rtcpar.day = 5;
  rtcraw.rtcpar.weekday = 3;
  rtcraw.rtcpar.hour = 22;
  rtcraw.rtcpar.min = 16;
  rtcraw.rtcpar.sec = 0;
/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  { 
    
#if 0 
    testbuttons();
    
    
    if(B2.BtnON)
    {
      B2.BtnON = 0;
      rtcrawtobcd();
      RTCsenddata(rtcbcd.rtcdata);
      for(uint8 i = 0; i < 7; i++)
      {
      tempval = rtcraw.rtcdata[i];
      u16_to_str(stringtemp, tempval, DISABLE);
      LCD_printStr8x5(stringtemp, i, 0);
      }
    }
    
    if(B1.BtnON)
    {
      B1.BtnON = 0;
      RTCgetdata(rtcbcd.rtcdata);
      rtcbcdtoraw();
      for(uint8 i = 0; i < 7; i++)
      {
      tempval = rtcraw.rtcdata[i];
      u16_to_str(stringtemp, tempval, DISABLE);
      LCD_printStr8x5(stringtemp, i, 35);
      }
    }
    
    
    
#endif
    
    ufobattle_init();
    ufobattle_start();

 
  }
/*----------------------------------------------------------------------------*/
  //return;
}