
/*------------------------------INCLUDES--------------------------------------*/
#include <xc.h>
#include "config.h"
#include "common.h"
#include "drv_lcdST7565_SPI.h"
#include "ufo_battle.h"
#include "swic.h"
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
  swicinit();
  BrightPWM(bright);
/*----------------------------------------------------------------------------*/
  uint8 tempval = 0;
  uint8 stringtemp[6];
  u16_to_str(stringtemp, tempval, DISABLE);
  LCD_printStr8x5(stringtemp, 1, 20);
  
/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  { 
    testbuttons();
    
    if(B1.BtnON) 
    {
      B1.BtnON = 0;
      
      swicstart();
      tempval = swicwritebyte(0xA3);
      swicstop();
      
      u16_to_str(stringtemp, tempval, DISABLE);
      LCD_printStr8x5(stringtemp, 3, 20);
      Sounds(1500);
      BrightPWM(20);
    } 
    
    if(B2.BtnON) 
    {
      B2.BtnON = 0;
      Sounds(500);
      BrightPWM(200);
    }
    //ufobattle_init();
    //ufobattle_start();

 
  }
/*----------------------------------------------------------------------------*/
  //return;
}