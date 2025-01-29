
/*------------------------------INCLUDES--------------------------------------*/
#include "config.h"
#include "common.h"
#include <stdlib.h>
#include "init_periph.h"
//#include "drv_7seg.h"
#include "drv_buttons.h"
//#include "drv_led130_I2C.h"
//#include "drv_led096_I2C.h"
//#include "drv_I2C.h"
#include "drv_lcdST7565_SPI.h"
//#include "drv_usart.h"

/*----------------------------------------------------------------------------*/

/*----------------------------GLOBAL VARIABLES--------------------------------*/
uint32 mainTimeCounter = 0;
uint32 countTime = 0;
uint32 counter = 0;
uint16 countPeriod = 1000;
uint8  countDirect = 1;
uint8  countOn = 0;
uint8 Array[] = "Hello, World!!!!";

typedef struct {
uint8 USART_buf[100];
uint8 BufMax;
uint8 WritePos;
} UART_DATA;
UART_DATA UBuf = {0};

typedef struct{
  uint8 sec;
  uint8 min;
  uint8 hour;
} systime;
systime Time;
/*----------------------------------------------------------------------------*/   

/*-------------------------------Funcs for MAIN-------------------------------*/
uint16 GetPrd(void)
{
  static int i = 1;
  uint16 prd;
  if(i == 4) i = 0;
  switch (i) {
    case 0: prd = 1000; break;
    case 1: prd = 100; break;
    case 2: prd = 10; break;
    case 3: prd = 1; break;
  }
  i++;
  return prd;  
}
void Counting(uint16 cPrd, uint8 cOn, uint8 cDirect, uint32 counterMax){
  static uint32 cTime = 0;
  if(((timestamp - cTime) >= cPrd) && (cOn)) { 
    cTime = timestamp;
    if(cDirect)  mainTimeCounter++;
    if(!cDirect) mainTimeCounter--;
      }
    if(mainTimeCounter > counterMax && countDirect) mainTimeCounter = 0;
    if(mainTimeCounter > counterMax && !countDirect) mainTimeCounter = counterMax;
    }
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
  
  if(RCIE && RCIF)
  {
    RCIF = 0;
    UBuf.USART_buf[UBuf.WritePos] = RCREG;
    UBuf.WritePos++;
    if(UBuf.BufMax < 100) UBuf.BufMax++;
    if(UBuf.WritePos > 99) UBuf.WritePos = 0;
    return;
  }
}
/*----------------------------------------------------------------------------*/

/*-----------------------------------MAIN-------------------------------------*/
void main(void) 
{
/*-------------------------------Initialization-------------------------------*/
  TMR0_init();
  TMR1_init();
  Interrupt_init();
  randinit();
  //USART_init();
  //Delay_ms(100);           // need for LED096
  LCD_Init();
  LCD_Erase();
  //Led096Init();
  //Led130Init();
  //Led130Full();
  btn_t B6 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 5, &timestamp);
  btn_t B2 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 5, &timestamp);
  btn_t B3 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 5, &timestamp);
  btn_t B4 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 6, &timestamp);
  btn_t B5 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 6, &timestamp);
  btn_t B1 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 6, &timestamp);
  btn_t B7 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 7, &timestamp);
  btn_t B8 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 7, &timestamp);
  btn_t B9 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 7, &timestamp);
/*----------------------------------------------------------------------------*/
  
/*--------------------------------ПЕРЕМЕННЫЕ----------------------------------*/
  uint8 prntClk = 1;
  
/*----------------------------------------------------------------------------*/
//------------------------------Game stucts-----------------------
  typedef struct {
    uint8 en;
    uint8 pg;
    uint8 cl;
  } ufo_t;
  
  typedef struct {
    uint8 en;
    uint8 pg;
    uint8 cl;
  } bullet_t;
  
  typedef struct{
    uint8  stat;  // 0 - enemy disable; 1 - enemy enable; 2 - enemy distroed
    uint8  pg;
    uint8  cl;
    uint32 timer;
    uint8  N;
  }comet_t;

//---------------------------------------------------------  
//------------------------------Game vars-----------------------
  ufo_t Tar = {1, 3, 0};
  #define PIU_MAX   16
  #define COMET_MAX 8
  bullet_t Piu[PIU_MAX] = {0};
  comet_t Comet[COMET_MAX] = {0};
  uint8 Max_Piu = 1;
  uint8 Max_Comet = 4;
  uint8 KillCounter = 0;
  uint8 StartFl = 0;
  uint8 ScoreLb[] = "SCORE: ";
  uint8 Score[4];
//---------------------------------------------------------

/*-------------------------------MAIN LOOP------------------------------------*/
  while(1)
  { 
    
    
#if 1
    while(!StartFl)
    {
      Tar.en = 1;
      TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4); 
      TestBtn(&B5); TestBtn(&B6); TestBtn(&B7); TestBtn(&B8);
      
      
      if(timestamp - counter > 500){
        LCD_Erase();
        print_cometa(getrand(6), getrand(100));
        counter = timestamp;
      }
      if(B1.BtnON){B1.BtnON = 0; StartFl = 1;}
      
      #if 1 // print clock
      Counting(1000, 1, 1, 359999);
      Time.hour = (uint8)(mainTimeCounter/3600);
      Time.min = (uint8)((mainTimeCounter%3600)/60);
      Time.sec = (uint8)(mainTimeCounter%60);
      if(prntClk) LCD_PrintClock(Time.hour, Time.min, Time.sec);
      #endif
    
    }
    
    while(StartFl)
    {
      //----------COMET PRINT-------------------------------
      for(uint8 i = 0; i < Max_Comet; i++) 
      {
        if(Comet[i].stat == 1) print_cometa(Comet[i].pg, Comet[i].cl);
        if(Comet[i].stat == 2) print_distr_cometa(Comet[i].pg, Comet[i].cl);
      }

      u8_to_str(Score, KillCounter);
      LCD_printStr8x5(ScoreLb, 0, 37);
      LCD_printStr8x5(Score, 0, 73);
      
      switch(KillCounter)
      {
        case 20: Max_Piu = 2; break;
        case 50: Max_Piu = 4; break;
        case 100: Max_Piu = 8; Max_Comet = 6; break;
      }

      if(Tar.en) print_ufo(Tar.pg, Tar.cl);

      //--------PRINT BULLET---------------
      for(uint8 i = 0; i < Max_Piu; i++)
      {
        if(Piu[i].en){
          print_piu(Piu[i].pg, Piu[i].cl);
          Piu[i].cl += 8;
          if(Piu[i].cl > 120) {
            Piu[i].en = 0;
            Piu[i].cl = 0;
          }
        }
      }
      //-----------------------------------------

      TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4); 
      TestBtn(&B5); TestBtn(&B6); TestBtn(&B7); TestBtn(&B8);

      if(B2.BtnON || B2.HoldON || B2.StuckON){B2.BtnON = 0; Tar.pg--; if(Tar.pg == 255) Tar.pg = 0;}
      if(B8.BtnON || B8.HoldON || B8.StuckON){B8.BtnON = 0; Tar.pg++; if(Tar.pg == 7) Tar.pg = 6;}
      if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; Tar.cl += 8; if(Tar.cl > 100) Tar.cl = 100;}
      if(B6.BtnON || B6.HoldON || B6.StuckON){B6.BtnON = 0; Tar.cl -= 8; if(Tar.cl > 100) Tar.cl = 0;}


      if(B1.BtnON || B1.HoldON || B1.StuckON){ 
        B1.BtnON = 0; 
        for(uint8 i = 0; i < Max_Piu; i++) {
          if(!Piu[i].en && Tar.en) 
          {
            Piu[i].en = 1; 
            Piu[i].pg = Tar.pg + 1; 
            Piu[i].cl = Tar.cl + 28;
            break;
          }
        }
      }

      //--------COMET GENERATOR-------------------------

      for(uint8 i = 0; i < Max_Comet; i++)
      {
        if(Comet[i].stat == 0 && ((timestamp - mainTimeCounter) > 1000))
        {
          mainTimeCounter = timestamp;
          Comet[i].stat = 1;
          Comet[i].cl = 100;
          Comet[i].pg = getrand(6);
        }
      }
      //--------------------------------------------------
      //----------COMET MOV-------------------------------
      for(uint8 i = 0; i < Max_Comet; i++)
      { 
        if((timestamp - Comet[i].timer) > 200)
        {
          Comet[i].timer = timestamp;
          Comet[i].cl -= 8;
          if(Comet[i].cl > 100 || Comet[i].stat == 2) Comet[i].stat = 0;
        }
      }
      
      if(!Tar.en) {StartFl = 0; Delay_ms(300);}
      //------------COLLISION--------------
      for(uint8 j = 0; j < Max_Piu; j++)
      {
        for(uint8 i = 0; i < Max_Comet; i++)
        {
          if((Comet[i].cl <= Piu[j].cl && (Comet[i].pg == Piu[j].pg || (Comet[i].pg + 1) == Piu[j].pg)) && Comet[i].stat == 1 && Comet[i].stat == 1 && Piu[j].en)
          {
            Comet[i].stat = 2;
            Piu[j].en = 0;
            if(KillCounter <= 254) KillCounter++;
          }
        }
      }

      for(uint8 i = 0; i < Max_Comet; i++)
      {
        if(Comet[i].cl <= (Tar.cl+26) && (Comet[i].pg == Tar.pg || (Comet[i].pg + 1) == Tar.pg || Comet[i].pg == (Tar.pg + 1)) && Comet[i].stat == 1 && Tar.en)
        {
          Comet[i].stat = 2;
          Tar.en = 0;
        }
      }

      Delay_ms(50);
      LCD_Erase();
    }
#endif
    

    
    
  }
/*----------------------------------------------------------------------------*/
  //return;
}