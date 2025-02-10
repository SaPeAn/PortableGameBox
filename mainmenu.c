#include "drv_swi2cRTC.h"
#include "drv_lcdST7565_SPI.h"
#include "common.h"
#include "ufo_battle.h"


void setdatetime(void)
{
  uint8 selectpos = 0;
  RTCgetdata(rtcbcd.rtcdata);
  rtcbcdtoraw();
  while(1)
  {  
    checkjoydir();
    TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4);
    
    if(B2.BtnON){
      B2.BtnON = 0;
      RTCsenddata(rtcbcd.rtcdata);
    }
    
    if(B1.BtnON){
      B1.BtnON = 0;
      return;
    }
    
    if(joystick.right == 1)
    {
      joystick.right = 0;
      selectpos++;
      if(selectpos == 7) selectpos = 0;
    }
    if(joystick.left == 1)
    {
      joystick.left = 0;
      selectpos--;
      if(selectpos == 255) selectpos = 5;
    }
        
    uint8 day[4] = {dig_to_smb((rtcbcd.rtcpar.day & 0x30) >> 4), dig_to_smb(rtcbcd.rtcpar.day & 0x0F), '.', '\0'};
    uint8 temp[6];    
    u16_to_str(temp, ((((rtcbcd.rtcpar.month & 0x10) >> 4) * 10) + (rtcbcd.rtcpar.month & 0x0F)), DISABLE);
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
    LCD_printweekday(rtcbcd.rtcpar.weekday, 0, 115);
    
    switch(selectpos)
    {
      case 0: 
        LCD_erasestring(128, 1, 0); 
        LCD_printhorline(12, 8, 2); 
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.day--; if(rtcraw.rtcpar.day > 31) rtcraw.rtcpar.day = 31;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.day++; if(rtcraw.rtcpar.day > 31) rtcraw.rtcpar.day = 0;}
      break;
      case 1: 
        LCD_erasestring(128, 1, 0); 
        LCD_printhorline(12, 8, 18);
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.month--; if(rtcraw.rtcpar.month > 12) rtcraw.rtcpar.month = 12;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.month++; if(rtcraw.rtcpar.month > 12) rtcraw.rtcpar.month = 0;}
      break;
      case 2: 
        LCD_erasestring(128, 1, 0); 
        LCD_printhorline(24, 8, 34); 
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.year--; if(rtcraw.rtcpar.year > 99) rtcraw.rtcpar.year = 99;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.year++; if(rtcraw.rtcpar.year > 99) rtcraw.rtcpar.year = 0;}
      break;
      case 3: 
        LCD_erasestring(128, 1, 0); 
        LCD_printhorline(12, 8, 62);
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.hour--; if(rtcraw.rtcpar.hour > 23) rtcraw.rtcpar.hour = 23;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.hour++; if(rtcraw.rtcpar.hour > 23) rtcraw.rtcpar.hour = 0;}
      break;
      case 4: 
        LCD_erasestring(128, 1, 0); 
        LCD_printhorline(12, 8, 80); 
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.min--; if(rtcraw.rtcpar.min > 59) rtcraw.rtcpar.min = 59;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.min++; if(rtcraw.rtcpar.min > 59) rtcraw.rtcpar.min = 0;}
      break;
      case 5: 
        LCD_erasestring(128, 1, 0);
        LCD_printhorline(12, 8, 98);
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.sec--; if(rtcraw.rtcpar.sec > 59) rtcraw.rtcpar.sec = 59;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.sec++; if(rtcraw.rtcpar.sec > 59) rtcraw.rtcpar.sec = 0;}
      break;
      case 6: 
        LCD_erasestring(128, 1, 0);
        LCD_printhorline(12, 8, 115);
        if(B3.BtnON || B3.HoldON || B3.StuckON){B3.BtnON = 0; rtcraw.rtcpar.weekday--; if(rtcraw.rtcpar.weekday > 6) rtcraw.rtcpar.weekday = 6;}
        if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; rtcraw.rtcpar.weekday++; if(rtcraw.rtcpar.weekday > 6) rtcraw.rtcpar.weekday = 0;}
      break;
    }
    
    LCD_printbutselhint(7, 3, 40);
    LCD_printbutselhint(6, 2, 89);
    LCD_printstr8x5("‚˚ı.|", 6, 86);
    LCD_printstr8x5("ÒÓı.", 7, 95);
    LCD_printstr8x5("-  +", 1, 93); 
    
    rtcrawtobcd();
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
    u16_to_str(temp, ((((rtcbcd.rtcpar.month & 0x10) >> 4) * 10) + (rtcbcd.rtcpar.month & 0x0F)), DISABLE);
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
    if(joystick.down == 1)
    {
      joystick.down = 0;
      CFlags.coursorpos++;
      if(CFlags.coursorpos == 4) CFlags.coursorpos = 1;
    }
    if(joystick.up == 1)
    {
      joystick.up = 0;
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
        case 1: break;
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
    if(joystick.down == 1)
    {
      joystick.down = 0;
      CFlags.coursorpos++;
      if(CFlags.coursorpos == 4) CFlags.coursorpos = 1;
    }
    if(joystick.up == 1)
    {
      joystick.up = 0;
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

