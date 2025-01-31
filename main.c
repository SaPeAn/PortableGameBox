
/*------------------------------INCLUDES--------------------------------------*/
#include "config.h"
#include "common.h"
#include "init_periph.h"
#include "drv_buttons.h"
#include "drv_I2C.h"
#include "drv_lcdST7565_SPI.h"
#include "drv_adc.h"
/*----------------------------------------------------------------------------*/

/*----------------------------GLOBAL VARIABLES--------------------------------*/
uint32 counter = 0;
/*----------------------------------------------------------------------------*/   

/*-------------------------------Funcs for MAIN-------------------------------*/

void BrightPWM(uint8 duty_cycle)
{
  PR2 = 0xFF;
  CCPR2L = duty_cycle;
  T2CON = 0b00000100;
  CCP2CON = 0b00001100;
}

void Sounds(uint16 delay)
{
  uint16 j;
  for(uint8 i = 0; i < 100; i++)
  {  
    PORTCbits.RC2 = 1;
    j = delay;
    while(j--);
    PORTCbits.RC2 = 0;
    j = delay;
    while(j--);
  }
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
  LCD_Init();
  LCD_Erase();
  
  TRISB &= 0b11110111; // for Brightness
  TRISC &= 0b11111011; // for Sounds
  PORTCbits.RC2 = 0;
  
  btn_t B1 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 6, &timestamp);
  btn_t B2 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 7, &timestamp);
  btn_t B3 = CreateBtn(&TRISB, &PORTB, &LATB, 5, 6, &timestamp);
  btn_t B4 = CreateBtn(&TRISB, &PORTB, &LATB, 5, 7, &timestamp);
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
  uint32 TimeComet = 100;
  uint16 KillCounter = 0;
  uint8 StartFl = 0;
  uint8 ScoreLb[] = "SCORE: ";
  uint8 Score[6];
//---------------------------------------------------------
  uint8 ox, oy, batlvl;
  uint8 tempstr[6];
  uint8 bright = 200;
/*-------------------------------MAIN LOOP------------------------------------*/
  while(1)
  { 
     
#if 1
    while(!StartFl)
    {      
      Tar.en = 1;
      TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4);
      batlvl = adc_getval_an2();
      if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; bright +=10; if(bright >= 240) bright = 240; Sounds(400);}
      if(B3.BtnON  || B3.HoldON || B3.StuckON){B3.BtnON = 0; bright -=10; if(bright <= 10) bright = 10; Sounds(400);}
      
      
      if(timestamp - counter > 500){
        LCD_Erase();
        print_cometa(getrand(6), getrand(100));
        counter = timestamp;
      }
      if(B1.BtnON){B1.BtnON = 0; StartFl = 1; Sounds(400);}
      
      #if 1 // print clock
      Time.hour = (uint8)(timestamp/3600000);
      Time.min = (uint8)((timestamp%3600000)/60000);
      Time.sec = (uint8)((timestamp%60000)/1000);
      LCD_PrintClock(Time.hour, Time.min, Time.sec);
      #endif
      
      print_bat_level(batlvl, 0, 105);
      BrightPWM(bright);
      Delay_ms(100);
    }
    
    while(StartFl)
    {
      TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4);
      ox = adc_getval_an0();
      oy = adc_getval_an1();

      if(oy > 150){Tar.pg--; if(Tar.pg == 255) Tar.pg = 0;}
      if(oy < 100){Tar.pg++; if(Tar.pg == 7) Tar.pg = 6;}
      if(ox > 150){Tar.cl += 8; if(Tar.cl > 100) Tar.cl = 100;}
      if(ox < 100){Tar.cl -= 8; if(Tar.cl > 100) Tar.cl = 0;}


      if(B1.BtnON || B1.HoldON || B1.StuckON){ 
        B1.BtnON = 0; 
        for(uint8 i = 0; i < Max_Piu; i++) {
          if(!Piu[i].en && Tar.en) 
          {
            Piu[i].en = 1; 
            Piu[i].pg = Tar.pg + 1; 
            Piu[i].cl = Tar.cl + 28;
            Sounds(400);
            break;
          }
        }
      }

      //--------COMET GENERATOR-------------------------

      for(uint8 i = 0; i < Max_Comet; i++)
      {
        if(Comet[i].stat == 0 && ((timestamp - TimeComet) > 1000))
        {
          TimeComet = timestamp;
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
      
      if(!Tar.en) {StartFl = 0; Sounds(900);}
      //------------COLLISION--------------
      for(uint8 j = 0; j < Max_Piu; j++)
      {
        for(uint8 i = 0; i < Max_Comet; i++)
        {
          if((Comet[i].cl <= Piu[j].cl && (Comet[i].pg == Piu[j].pg || (Comet[i].pg + 1) == Piu[j].pg)) && Comet[i].stat == 1 && Comet[i].stat == 1 && Piu[j].en)
          {
            Comet[i].stat = 2;
            Piu[j].en = 0;
            KillCounter++;
            Sounds(600);
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
      LCD_Erase();
      
      
      
      switch(KillCounter)
      {
        case 20: Max_Piu = 2; break;
        case 50: Max_Piu = 4; break;
        case 100: Max_Piu = 8; Max_Comet = 6; break;
      }
      
      
      //----------COMET PRINT-------------------------------
      for(uint8 i = 0; i < Max_Comet; i++) 
      {
        if(Comet[i].stat == 1) print_cometa(Comet[i].pg, Comet[i].cl);
        if(Comet[i].stat == 2) {
          print_distr_cometa(Comet[i].pg, Comet[i].cl);
          Delay_ms(10);
        }
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
      u16_to_str(Score, KillCounter, DISABLE);
      LCD_printStr8x5(ScoreLb, 0, 37);
      LCD_printStr8x5(Score, 0, 73);
      
      Delay_ms(50);
    }
#endif
 
  }
/*----------------------------------------------------------------------------*/
  //return;
}