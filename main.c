
/*------------------------------INCLUDES--------------------------------------*/
#include <xc.h>
#include "config.h"
#include "common.h"
#include "drv_lcdST7565_SPI.h"
#include "ufo_battle.h"
#include "drv_swi2cRTC.h"
#include "mainmenu.h"
#include "scheduler.h"
/*----------------------------------------------------------------------------*/

/*---------------------------------INTERRAPTS---------------------------------*/
void __interrupt() systemTick_int(void)
{
  if (TMR1IE && TMR1IF)
  {
    TMR1H = 217;
    TMR1L -= 3;
    TMR1IF = 0;
    timestamp++;
    SchedPeriodIncr();
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
  LCD_init();
  LCD_bufupload_buferase();
  initbuttons();
  swi2cinit();
  BrightPWMgen(brightPWM);
  ufobattle_init();
/*----------------------------------------------------------------------------*/

/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  {
    MainMenu();
  }
/*----------------------------------------------------------------------------*/
}