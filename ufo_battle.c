#include "ufo_battle.h"
#include "drv_lcdST7565_SPI.h"
#include "drv_swi2cRTC.h"
#include "display_data.h"

//------------------------------Game stucts-----------------------
typedef struct {
  uint8 en;
  uint8 ln;
  uint8 cl;
} ufo_t;

typedef struct {
  uint8 en;
  uint8 ln;
  uint8 cl;
} bullet_t;

typedef struct{
  uint8  stat;  // 0 - enemy disable; 1 - enemy enable; 2 - enemy distroed
  uint8  ln;
  uint8  cl;
  uint32 timer;
  uint8  N;
}comet_t;

 
//---------------------------------------------------------  
//------------------------------Game vars-----------------------
ufo_t Tar = {1, 32, 0};
#define PIU_MAX   16
#define COMET_MAX 8
bullet_t Piu[PIU_MAX] = {0};
comet_t Comet[COMET_MAX] = {0};
uint8 Max_Piu = 3;
uint8 Max_Comet = 5;
uint32 TimeComet = 100;
uint32 counter = 0; 

uint8 StartFl = 0;
//----------------------------------------------------------------

void ufobattle(void)
{
  Gamer.health = 24;
  Gamer.energy = 24;
  Gamer.gasmask_fl = 1;
  Gamer.bombs = 0;
  Gamer.money = 0;
  LCD_printgamestatbar(&Gamer);
  randinit();
  
  while(!StartFl && CFlags.RunGameFl)
  {      
    Tar.en = 1;
    TestBtn(&B1); TestBtn(&B2);
    if(B2.BtnON){B2.BtnON = 0; StartFl = 1;}
    if(B1.BtnON){B1.BtnON = 0; CFlags.RunGameFl = 0; CFlags.MenuFl = 1;}

    if(timestamp - counter > 150){
      LCD_erase();
      //LCD_printcometa(getrand(6), getrand(100));
      counter = timestamp;
    }
    
    LCD_printgamestatbar(&Gamer);
    LCD_printsprite(8, 0, magazin_sprite);
    
    LCD_printbutselhint(5, 2, 89);
    LCD_printstr8x5("вых.вх", 6, 86);
    delay_ms(50);
  }

  while(StartFl && CFlags.RunGameFl)
  {
    TestBtn(&B2);
    TestBtn(&B4);
    ox = adc_getval_an0();
    oy = adc_getval_an1();

    if(oy > 150 && oy <= 180){Tar.ln-=1; if(Tar.ln < 8) Tar.ln = 8;}
    if(oy > 180 && oy <= 210){Tar.ln-=2; if(Tar.ln < 8) Tar.ln = 8;}
    if(oy > 210){Tar.ln-=4; if(Tar.ln < 8) Tar.ln = 8;}
    if(oy < 100 && oy >= 70){Tar.ln+=1; if(Tar.ln > 48) Tar.ln = 48;}
    if(oy < 70 && oy >= 30){Tar.ln+=2; if(Tar.ln > 48) Tar.ln = 48;}
    if(oy < 30){Tar.ln+=4; if(Tar.ln > 48) Tar.ln = 48;}
    if(ox > 150 && ox <= 180){Tar.cl += 1; if(Tar.cl > 94) Tar.cl = 94;}
    if(ox > 180 && ox <= 210){Tar.cl += 2; if(Tar.cl > 94) Tar.cl = 94;}
    if(ox > 210){Tar.cl += 4; if(Tar.cl > 94) Tar.cl = 94;}
    if(ox < 100 && ox >= 70){Tar.cl -= 1; if(Tar.cl > 100) Tar.cl = 0;}
    if(ox < 70 && ox >= 30){Tar.cl -= 2; if(Tar.cl > 100) Tar.cl = 0;}
    if(ox < 30){Tar.cl -= 4; if(Tar.cl > 100) Tar.cl = 0;}
    


    if(B2.BtnON || B2.HoldON || B2.StuckON){ 
      B2.BtnON = 0; 
      for(uint8 i = 0; i < Max_Piu; i++) {
        if(!Piu[i].en && Tar.en) 
        {
          Piu[i].en = 1; 
          Piu[i].ln = Tar.ln; 
          Piu[i].cl = Tar.cl + 28;
          Sounds(400);
          break;
        }
      }
    }
    if(B4.BtnON || B4.HoldON || B4.StuckON){ 
      B4.BtnON = 0; 
      StartFl = 0;
    }

    //--------COMET GENERATOR-------------------------
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(Comet[i].stat == 0 && ((timestamp - TimeComet) > 1000))
      {
        TimeComet = timestamp;
        Comet[i].stat = 1;
        Comet[i].cl = 100;
        Comet[i].ln = getrand(40) + 8;
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
        if(     (Comet[i].cl <= Piu[j].cl) && (Comet[i].ln < (Piu[j].ln + 6)) && 
                ((Comet[i].ln + 10) > Piu[j].ln) && Comet[i].stat == 1 && 
                Piu[j].en)
        {
          Comet[i].stat = 2;
          Piu[j].en = 0;
          Sounds(500);
        }
      }
    }

    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(     (Comet[i].cl <= (Tar.cl+25)) && ((Comet[i].cl + 23) >= Tar.cl) && 
              ((Comet[i].ln + 15) > Tar.ln) && (Comet[i].ln < (Tar.ln + 15)) && 
              (Comet[i].stat == 1) && Tar.en)
      {
        Comet[i].stat = 2;
        Tar.en = 0;
      }
    }
    LCD_erase();
    
    //----------COMET PRINT-------------------------------
    for(uint8 i = 0; i < Max_Comet; i++) 
    {
      if(Comet[i].stat == 1) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, cometa_sprite);
      }
      if(Comet[i].stat == 2) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, distr_cometa_sprite);
        delay_ms(10);
      }
    }
    if(Tar.en) {
      LCD_printsprite(Tar.ln, Tar.cl, gamer_sprite);
    }
    //--------PRINT BULLET---------------
    for(uint8 i = 0; i < Max_Piu; i++)
    {
      if(Piu[i].en){
        LCD_printsprite(Piu[i].ln, Piu[i].cl, bullet_sprite);
        Piu[i].cl += 8;
        if(Piu[i].cl > 120) {
          Piu[i].en = 0;
          Piu[i].cl = 0;
        }
      }
    }
    //-----------------------------------------

    batcheck();
    delay_ms(25);
  }
}