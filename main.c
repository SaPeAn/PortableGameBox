
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
    checkbuttons();
    
    if(B1.BtnON) {}
    
    if(joystick.joydown == 1)
    {
        joystick.joydown = 0;
        CFlags.menupos++;
        if(CFlags.menupos == 4) CFlags.menupos = 1;
    }
    
    if(joystick.joyup == 1)
    {
        joystick.joyup = 0;
        CFlags.menupos--;
        if(CFlags.menupos == 0) CFlags.menupos = 3;
    }
    LCD_printbutselhint(1, 2, 90);
    LCD_printstr8x5("¬Œ…“»", 7, 95);
    LCD_printstr8x5("»√–¿", 2, 25);
    LCD_printstr8x5("Õ¿—“Œ… ¿", 4, 25);
    LCD_printstr8x5("“≈—“", 6, 25);
    LCD_printclockanddate(0, 26);
    if(CFlags.menupos == 1) LCD_printmenupointer(2, 10);
    if(CFlags.menupos == 2) LCD_printmenupointer(4, 10);
    if(CFlags.menupos == 3) LCD_printmenupointer(6, 10);
    LCD_printbatlevel(batlvl, 0, 105);
    LCD_printbrightnes(0, 0);
    
    batcheck();
    BrightPWMgen(brightPWM);
    getbrightlvl();
    RTCgetdata(rtcbcd.rtcdata);
    rtcbcdtoraw();
    delay_ms(50);
    LCD_erase();
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
  LCD_init();
  LCD_erase();
  initbuttons();
  swi2cinit();
  BrightPWMgen(brightPWM);
  
  CFlags.MenuFl = 1;
  CFlags.menupos = 1;
/*----------------------------------------------------------------------------*/
  uint8 tmpval = 0x0F;
  uint8 tmpstr[6];
/*-------------------------------MAIN CYCLE-----------------------------------*/
#define CODE_BLOCK   2
  while(1)
  { 
    checkbuttons();
#if (CODE_BLOCK == 0) 
    checkbuttons();
    
    
    if(B2.BtnON)
    {
      B2.BtnON = 0;
      rtcrawtobcd();
      RTCsenddata(rtcbcd.rtcdata);
      for(uint8 i = 0; i < 7; i++)
      {
      tmpval = rtcraw.rtcdata[i];
      u16_to_str(tmpstr, tmpval, DISABLE);
      LCD_printstr8x5(tmpstr, i, 0);
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
      LCD_printstr8x5(tmpstr, i, 35);
      }
    }
#endif
    
#if (CODE_BLOCK == 1)    
  ufobattle_init();
  ufobattle_start();
#endif
    
#if (CODE_BLOCK == 2)    
  
  //MainMenu(); 
  LCD_printvertline(tmpval, 5, 28);
  LCD_printhortline(tmpval, 5, 29);
  
  if(B1.BtnON){B1.BtnON = 0; tmpval++;}
  if(B2.BtnON){B2.BtnON = 0; tmpval--;}
  delay_ms(50);
  LCD_erase();
#endif
 
  }
/*----------------------------------------------------------------------------*/
  //return;
}