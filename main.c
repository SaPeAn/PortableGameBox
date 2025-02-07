
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

void MainMenu(void)
{
  while(CFlags.MenuFl)
  {
    checkjoydir();
    if(joystick.joydown == 1)
    {
        joystick.joydown = 0;
        CFlags.menupos--;
        if(CFlags.menupos == 4) CFlags.menupos = 1;
    }
    
    if(joystick.joyup == 1)
    {
        joystick.joyup == 0;
        CFlags.menupos++;
        if(CFlags.menupos == 0) CFlags.menupos = 3;
    }
    
    if(CFlags.menupos == 1)
    {
        print_menu_pointer(1, 10);
        LCD_printStr8x5("ÈÃÐÀ", 2, 25);
        LCD_printStr8x5("ÍÀÑÒÎÉÊÀ", 4, 25);
        LCD_printStr8x5("ÒÅÑÒ", 6, 25);
        RTCgetdata(rtcbcd.rtcdata);
        rtcbcdtoraw();
        LCD_PrintClockAndDate(0, 26);batcheck();
        print_bat_level(batlvl, 0, 105); 
        BrightPWMgen(brightPWM);
        getbrightlvl();
        LCD_printbrightnes(0, 0);
        delay_ms(50);
        LCD_Erase();
    }
    if(CFlags.menupos == 2)
    {
        print_menu_pointer(3, 10);
        LCD_printStr8x5("ÈÃÐÀ", 2, 25);
        LCD_printStr8x5("ÍÀÑÒÎÉÊÀ", 4, 25);
        LCD_printStr8x5("ÒÅÑÒ", 6, 25);
        RTCgetdata(rtcbcd.rtcdata);
        rtcbcdtoraw();
        LCD_PrintClockAndDate(0, 26);batcheck();
        print_bat_level(batlvl, 0, 105); 
        BrightPWMgen(brightPWM);
        getbrightlvl();
        LCD_printbrightnes(0, 0);
        delay_ms(50);
        LCD_Erase();
    }
    if(CFlags.menupos == 3)
    {
        print_menu_pointer(5, 10);
        LCD_printStr8x5("ÈÃÐÀ", 2, 25);
        LCD_printStr8x5("ÍÀÑÒÎÉÊÀ", 4, 25);
        LCD_printStr8x5("ÒÅÑÒ", 6, 25);
        RTCgetdata(rtcbcd.rtcdata);
        rtcbcdtoraw();
        LCD_PrintClockAndDate(0, 26);batcheck();
        print_bat_level(batlvl, 0, 105); 
        BrightPWMgen(brightPWM);
        getbrightlvl();
        LCD_printbrightnes(0, 0);
        delay_ms(50);
        LCD_Erase();
    }
  }
}

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
  swi2cinit();
  BrightPWMgen(brightPWM);
  
  CFlags.MenuFl = 1;
  CFlags.menupos = 1;
/*----------------------------------------------------------------------------*/
  uint8 tmpval = 0;
  uint8 tmpstr[6];
/*-------------------------------MAIN CYCLE-----------------------------------*/
#define CODE_BLOCK   1
  while(1)
  { 
#if (CODE_BLOCK == 0) 
    testbuttons();
    
    
    if(B2.BtnON)
    {
      B2.BtnON = 0;
      rtcrawtobcd();
      RTCsenddata(rtcbcd.rtcdata);
      for(uint8 i = 0; i < 7; i++)
      {
      tmpval = rtcraw.rtcdata[i];
      u16_to_str(tmpstr, tmpval, DISABLE);
      LCD_printStr8x5(tmpstr, i, 0);
      }
    }
    
    if(B1.BtnON)
    {
      B1.BtnON = 0;
      RTCgetdata(rtcbcd.rtcdata);
      rtcbcdtoraw();
      for(uint8 i = 0; i < 7; i++)
      {
      tmpval = rtcraw.rtcdata[i];
      u16_to_str(tmpstr, tmpval, DISABLE);
      LCD_printStr8x5(tmpstr, i, 35);
      }
    }
#endif
    
#if (CODE_BLOCK == 1)    
  ufobattle_init();
  ufobattle_start();
#endif
    
#if (CODE_BLOCK == 2)    
  
  MainMenu(); 
  
  
  
  
#endif
 
  }
/*----------------------------------------------------------------------------*/
  //return;
}