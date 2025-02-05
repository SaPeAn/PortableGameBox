
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
  LCD_Init();
  LCD_Erase();
  initbuttons();
  CMCON = 0b11000111;
  swi2cinit();
  BrightPWM(bright);
/*----------------------------------------------------------------------------*/
  uint8 tempval = 0;
  uint8 stringtemp[6];
  rtcraw.rtcpar.year = 25;
  rtcraw.rtcpar.month = 2;
  rtcraw.rtcpar.day = 4;
  rtcraw.rtcpar.weekday = 3;
  rtcraw.rtcpar.hour = 20;
  rtcraw.rtcpar.min = 34;
  rtcraw.rtcpar.sec = 0;
/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  { 
    
#if 1 
    testbuttons();
    
    
    if(B2.BtnON)
    {
      B2.BtnON = 0;
      rtcraw.rtcpar.hour = 23;
      rtcraw.rtcpar.min = 59;
      rtcraw.rtcpar.sec = 58;
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
    
    //ufobattle_init();
    //ufobattle_start();

 
  }
/*----------------------------------------------------------------------------*/
  //return;
}