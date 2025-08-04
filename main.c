
/*------------------------------INCLUDES--------------------------------------*/
#include <xc.h>
#include <xc8debug.h>
#include "config.h"
#include "common.h"
#include "drv_LCD_ST7565_SPI.h"
#include "ufo_battle.h"
#include "drv_RTC_I2C.h"
#include "mainmenu.h"
#include "scheduler.h"
#include "display_data.h"
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
  /*void printsprite(void){
    static int8 startln = -40;
    static int8 startcl = -10;
    LCD_printsprite(startln, startcl, &bombshards_sprite[2]);
    startln += 1;
    if(startln > 10) {startln = -40; startcl += 15;}
    if(startcl > 100) startcl = 0;
    LCD_bufupload_buferase();
  }*/
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
/*----------------------------------------------------------------------------*/
  uint8 adr = 0;
  uint8 byte = 0;
  uint8 str[6];

  //SchedAddEvent(printsprite, 300);
/*-------------------------------MAIN CYCLE-----------------------------------*/
  while(1)
  {
    MainMenu();
    //SchedEventProcess();
  }
/*----------------------------------------------------------------------------*/
}