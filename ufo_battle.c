#include "ufo_battle.h"
#include "drv_lcdST7565_SPI.h"

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
uint8 ScoreLb[] = "SCORE: ";
uint8 Score[6];
uint32 counter = 0; 


void ufobattle_init(void)
{
  while(!StartFl)
  {      
    Tar.en = 1;
    testbuttons();
    if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; brightPWM +=10; if(brightPWM >= 240) brightPWM = 240; Sounds(400);}
    if(B3.BtnON  || B3.HoldON || B3.StuckON){B3.BtnON = 0; brightPWM -=10; if(brightPWM <= 10) brightPWM = 10; Sounds(400);}


    if(timestamp - counter > 500){
      LCD_Erase();
      print_cometa(getrand(6), getrand(100));
      counter = timestamp;
    }
    if(B1.BtnON){B1.BtnON = 0; StartFl = 1; Sounds(400);}

    #if 1 // print clock
    gettime();
    LCD_PrintClockAndDate();
    #endif

    batcheck();
    print_bat_level(batlvl, 0, 105); 
    BrightPWM(brightPWM);
    delay_ms(100);
  }
}

void ufobattle_start(void)
{
  while(StartFl)
  {
    testbuttons();
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

    if(!Tar.en) {Sounds(600); StartFl = 0;}
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
          Sounds(500);
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
        delay_ms(10);
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
    batcheck();
    delay_ms(50);
  }
}