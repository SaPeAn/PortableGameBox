
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
void setdatetime(void)
{
  while(1)
  {
    LCD_printstr8x5("Ì‡ÊÏËÚÂ", 1, 5);
    LCD_printbutselhint(1, 2, 5);
    LCD_printstr8x5("‰Îˇ ‚˚ıÓ‰‡", 6, 5);
    TestBtn(&B1);
    if(B1.BtnON){B1.BtnON = 0; return;}
  }
}

void testscreen(void)
{
  while(1)
  {
    RTCgetdata(rtcbcd.rtcdata);
    rtcbcdtoraw();    
    uint8 day[4] = {dig_to_smb((rtcbcd.rtcpar.day & 0x30) >> 4), dig_to_smb(rtcbcd.rtcpar.day & 0x0F), '.', '\0'};
    uint8 temp[6];
    u16_to_str(temp, (rtcraw.rtcpar.month +1), DISABLE);
    uint8 month[4] = {temp[3], temp[4], '.', '\0'}; 
    uint8 year[5] = {'2', '0', dig_to_smb((rtcbcd.rtcpar.year & 0xF0) >> 4), dig_to_smb(rtcbcd.rtcpar.year & 0x0F), '\0'};
    LCD_printstr8x5(day, 0, 2);
    LCD_printstr8x5(month, 0, 18);
    LCD_printstr8x5(year, 0, 34);
    uint8 hour[4] = {dig_to_smb((rtcbcd.rtcpar.hour & 0x30) >> 4), dig_to_smb(rtcbcd.rtcpar.hour & 0x0F), ':', '\0'};
    uint8 min[4] = {dig_to_smb((rtcbcd.rtcpar.min & 0x70) >> 4), dig_to_smb(rtcbcd.rtcpar.min & 0x0F), ':', '\0'};
    uint8 sec[3] = {dig_to_smb((rtcbcd.rtcpar.sec & 0x70) >> 4), dig_to_smb(rtcbcd.rtcpar.sec & 0x0F), '\0'};
    LCD_printstr8x5(hour, 0, 62);
    LCD_printstr8x5(min, 0, 80);
    LCD_printstr8x5(sec, 0, 98);
    
    batcheck();
    getjoypos();
    LCD_printstr8x5("¡‡Ú. = ", 2, 2);
    u16_to_str(temp, Ubat, DISABLE);
    LCD_printstr8x5(temp, 2, 44);
    LCD_printstr8x5("ﬂÍ. = ", 3, 2);
    u16_to_str(temp, brightPWM, DISABLE);
    LCD_printstr8x5(temp, 3, 44);
    LCD_printstr8x5("ƒÊ. X = ", 5, 2);
    u16_to_str(temp, ox, DISABLE);
    LCD_printstr8x5(temp, 5, 50);
    LCD_printstr8x5("ƒÊ. Y = ", 6, 2);
    u16_to_str(temp, oy, DISABLE);
    LCD_printstr8x5(temp, 6, 50);
  
    LCD_printbutselhint(1, 2, 89);
    LCD_printstr8x5("‚˚ıÓ‰", 6, 86);
    TestBtn(&B1);
    if(B1.BtnON) {B1.BtnON = 0; return;}
  }
}
  
void MainMenu(void)
{
  //--------------------START MENU-------------------
  if(CFlags.MenuFl)
  {
    checkjoydir();
    TestBtn(&B2);
    if(B2.BtnON) 
    {
      B2.BtnON = 0;
      switch(CFlags.coursorpos) { 
        case 1: CFlags.MenuFl = 0; CFlags.RunGameFl = 1; CFlags.coursorpos = 1; break;
        case 2: CFlags.MenuFl = 0; CFlags.MenuSettingsFl = 1; CFlags.coursorpos = 1; break;
        case 3: testscreen(); break;
      }
    }
    if(joystick.joydown == 1)
    {
      joystick.joydown = 0;
      CFlags.coursorpos++;
      if(CFlags.coursorpos == 4) CFlags.coursorpos = 1;
    }
    if(joystick.joyup == 1)
    {
      joystick.joyup = 0;
      CFlags.coursorpos--;
      if(CFlags.coursorpos == 0) CFlags.coursorpos = 3;
    }
    
    if(CFlags.coursorpos == 1) LCD_printmenucoursor(2, 4);
    if(CFlags.coursorpos == 2) LCD_printmenucoursor(4, 4);
    if(CFlags.coursorpos == 3) LCD_printmenucoursor(6, 4);
    
    LCD_printstr8x5("»√–¿", 2, 19);
    LCD_printstr8x5("Õ¿—“–Œ… ¿", 4, 19);
    LCD_printstr8x5("“≈—“", 6, 19);
    
    LCD_printbutselhint(0, 2, 89);
    LCD_printstr8x5("‚ıÓ‰", 6, 93);
  }  
  //-------------------------------------------------
  
  //--------------------SETTINGS---------------------
  if(CFlags.MenuSettingsFl)
  {
    checkjoydir();
    TestBtn(&B1); TestBtn(&B2);
    if(B2.BtnON) 
    {
      B2.BtnON = 0;
      switch(CFlags.coursorpos) { 
        case 1: Nop(); break;
        case 2: setdatetime(); break;
        case 3: testscreen(); break;
      }
    }
    if(B1.BtnON) 
    {
      B1.BtnON = 0;
      CFlags.MenuSettingsFl = 0;
      CFlags.MenuFl = 1;
      CFlags.coursorpos = 2;
    }
    if(joystick.joydown == 1)
    {
      joystick.joydown = 0;
      CFlags.coursorpos++;
      if(CFlags.coursorpos == 4) CFlags.coursorpos = 1;
    }
    if(joystick.joyup == 1)
    {
      joystick.joyup = 0;
      CFlags.coursorpos--;
      if(CFlags.coursorpos == 0) CFlags.coursorpos = 3;
    }
    
    if(CFlags.coursorpos == 1) {
      TestBtn(&B3); TestBtn(&B4);
      if(B3.BtnON || B3.HoldON || B3.StuckON) {B3.BtnON = 0; decbright();}
      if(B4.BtnON || B4.HoldON || B4.StuckON) {B4.BtnON = 0; incbright();}      
      LCD_printmenucoursor(2, 4);
      LCD_printbutselhint(4, 2, 89);
      LCD_printstr8x5("‚˚ı.", 6, 86);
      LCD_printstr8x5("-  +", 1, 93);
    }
    if(CFlags.coursorpos == 2) {
      LCD_printmenucoursor(4, 4);
      LCD_printbutselhint(5, 2, 89);
      LCD_printstr8x5("‚˚ı.‚ı.", 6, 86);
    }
    if(CFlags.coursorpos == 3) {
      LCD_printmenucoursor(6, 4);
      LCD_printbutselhint(5, 2, 89);
      LCD_printstr8x5("‚˚ı.‚ı.", 6, 86);
    }
    LCD_printstr8x5("ﬂ– Œ—“‹", 2, 19);
    LCD_printstr8x5("ƒ¿“¿/¬–≈Ãﬂ", 4, 19);
    LCD_printstr8x5("“≈—“", 6, 19); 
  }
  //-------------------------------------------------

  //----------------------GAME-----------------------
  if(CFlags.RunGameFl)
  {
    ufobattle();
  }
  //-------------------------------------------------
  
  LCD_printclockanddate(0, 26);
  LCD_printbatlevel(batlvl, 0, 105);
  LCD_printbrightnes(0, 0);
  
  /*
  LCD_printhorline(125, 10, 1);
  LCD_printhorline(125, 60, 1);
  LCD_printvertline(51, 10, 80);
  LCD_printvertline(51, 10, 0);
  LCD_printvertline(51, 10, 126);
  */

  batcheck();
  BrightPWMgen(brightPWM);
  getbrightlvl();
  RTCgetdata(rtcbcd.rtcdata);
  rtcbcdtoraw();
  delay_ms(50);
  LCD_erase();
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
/*----------------------------------------------------------------------------*/
  uint8 tmpval = 0x0F;
  uint8 tmpstr[6];
/*-------------------------------MAIN CYCLE-----------------------------------*/
#define CODE_BLOCK   2
  while(1)
  { 
    TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4);
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
  
  MainMenu(); 
  
#endif
 
  }
/*----------------------------------------------------------------------------*/
  //return;
}