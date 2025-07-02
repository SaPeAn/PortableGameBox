#include "ufo_battle.h"
#include "drv_lcdST7565_SPI.h"
#include "drv_swi2cRTC.h"
#include "display_data.h"
#include "scheduler.h"

//------------------------------Game stucts-----------------------

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
  uint8  distr_ttl;
}comet_t;

 
//---------------------------------------------------------  
//------------------------------Game vars-----------------------

#define PIU_MAX   10
#define COMET_MAX 10
#define DISTRCOMET_TTL 2
bullet_t Piu[PIU_MAX] = {0};
comet_t Comet[COMET_MAX] = {0};
uint8 Max_Piu = PIU_MAX;
uint8 Max_Comet = COMET_MAX;
uint32 TimeComet = 100;
uint32 counter = 0; 

uint8 StartFl = 0;

/*******************************************************************************
 *                              EVENTS DESCRIPTION
 * *****************************************************************************
 */
void checkbnjk(void)  //Test buttons and joystick
{
  TestBtn(&B1);
  TestBtn(&B2);
  TestBtn(&B3);
  TestBtn(&B4);
  ox = adc_getval_an0();
  oy = adc_getval_an1();
} 

void guneregen(void)  //Energy regen
{
  if(Gamer.energy <= Gamer.energymax) Gamer.energy++;  
}

void gamermove(void)
{
    if(oy > 140 && oy <= 200){Gamer.ln-=1; if(Gamer.ln < 8) Gamer.ln = 8;}
    if(oy > 200 && oy <= 250){Gamer.ln-=2; if(Gamer.ln < 8) Gamer.ln = 8;}
    if(oy > 250){Gamer.ln-=4; if(Gamer.ln < 8) Gamer.ln = 8;}
    if(oy < 120 && oy >= 60){Gamer.ln+=1; if(Gamer.ln > 48) Gamer.ln = 48;}
    if(oy < 60 && oy >= 10){Gamer.ln+=2; if(Gamer.ln > 48) Gamer.ln = 48;}
    if(oy < 10){Gamer.ln+=4; if(Gamer.ln > 48) Gamer.ln = 48;}
    if(ox > 140 && ox <= 200){Gamer.cl += 1; if(Gamer.cl > 94) Gamer.cl = 94;}
    if(ox > 200 && ox <= 250){Gamer.cl += 2; if(Gamer.cl > 94) Gamer.cl = 94;}
    if(ox > 250){Gamer.cl += 4; if(Gamer.cl > 94) Gamer.cl = 94;}
    if(ox < 120 && ox >= 60){Gamer.cl -= 1; if(Gamer.cl > 100) Gamer.cl = 0;}
    if(ox < 60 && ox >= 10){Gamer.cl -= 2; if(Gamer.cl > 100) Gamer.cl = 0;}
    if(ox < 10){Gamer.cl -= 4; if(Gamer.cl > 100) Gamer.cl = 0;}
}

void cometmove(void)
{
    for(uint8 i = 0; i < Max_Comet; i++)
    {
        if(Comet[i].stat == 1){
            Comet[i].cl -= 1;
            if(Comet[i].cl > 100) Comet[i].stat = 0;
        }
    }
}

void bulletmove(void)
{
    for(uint8 i = 0; i < Max_Piu; i++)
    {
      if(Piu[i].en){
        Piu[i].cl += 1;
        if(Piu[i].cl > 120) {
          Piu[i].en = 0;
          Piu[i].cl = 0;
        }
      }
    }
}

void systemtasks(void)
{
    if(B4.BtnON || B4.HoldON || B4.StuckON){ 
      B4.BtnON = 0; 
      StartFl = 0;
    }
    batcheck();
}

void updatescreen(void){
    LCD_erase_bufuploud();
}

void bullet_comet_collision(void)
{
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
          //Sounds(500);
        }
      }
    }
}

void gamer_comet_collision(void)
{
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(     (Comet[i].cl <= (Gamer.cl+29)) && ((Comet[i].cl + 25) >= Gamer.cl) && 
              ((Comet[i].ln + 15) > Gamer.ln) && (Comet[i].ln < (Gamer.ln + 15)) && 
              (Comet[i].stat == 1) && (Gamer.health > 0))
      {
        Comet[i].stat = 2;
        Gamer.health -= 2;
        //Sounds(600);
      }
    }
    
    //Gamer's death hendler
    if(Gamer.health <= 0) {
        //Sounds(600); 
        StartFl = 0;
    }
}

void createcomet(void)
{
    static uint8 i = 0;
      if(Comet[i].stat == 0)
      {
        Comet[i].stat = 1;
        Comet[i].cl = 100;
        Comet[i].ln = getrand(40) + 8;
      }
    i++;
    if(i >= Max_Comet) i = 0;
}

void createbullet(void)
{
    if(B2.BtnON || B2.HoldON || B2.StuckON)
    { 
        B2.BtnON = 0;
        static uint8 i = 0;
        if(!Piu[i].en && (Gamer.health > 0) && (Gamer.energy >= 2)) 
        {
          Gamer.energy -= 2;
          Piu[i].en = 1; 
          Piu[i].ln = Gamer.ln; 
          Piu[i].cl = Gamer.cl + 28;
          //Sounds(400);
        }
        i++;
        if(i >= Max_Piu) i = 0;
    }
}

void drawcomet(void)
{
    for(uint8 i = 0; i < Max_Comet; i++) 
    {
      if(Comet[i].stat == 1) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, cometa_sprite);
      }
      if(Comet[i].stat == 2) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, distr_cometa_sprite);
        if(Comet[i].distr_ttl++ >= DISTRCOMET_TTL)  {
            Comet[i].distr_ttl = 0; 
            Comet[i].stat = 0;
        }
      }
    }
}

void drawgamer(void)
{
    if((Gamer.health > 0)) {
      if(Gamer.gasmask_fl) LCD_printsprite(Gamer.ln, Gamer.cl, gamer_gas_sprite);
      else LCD_printsprite(Gamer.ln, Gamer.cl, gamer_sprite);
    }
}

void drawbullet(void)
{
    for(uint8 i = 0; i < Max_Piu; i++)
    {
      if(Piu[i].en){
        LCD_printsprite(Piu[i].ln, Piu[i].cl, bullet_sprite);
      }
    }
}

void drawinfo(void)
{
    //Status bar
    LCD_printgamestatbar(&Gamer);
}
/*******************************************************************************
 *                              MAIN ENTRY                            
 *******************************************************************************
 */
void ufobattle(void)
{
  Gamer.health = 24;
  Gamer.energy = 4;
  Gamer.energymax = 24;
  Gamer.energy_regenperiod = 350;
  Gamer.gasmask_fl = 0;
  Gamer.bombs = 0;
  Gamer.money = 0;
  randinit();
  
  AddEvent(guneregen, Gamer.energy_regenperiod);
  AddEvent(checkbnjk, 50);
  
  AddEvent(gamermove, 50);
  AddEvent(bulletmove, 20);
  AddEvent(cometmove, 35);
  
  AddEvent(bullet_comet_collision, 100);
  AddEvent(gamer_comet_collision, 100);
  AddEvent(createcomet, 1000);
  AddEvent(createbullet, 250);
  AddEvent(drawcomet, 75);
  AddEvent(drawgamer, 75);
  AddEvent(drawbullet, 75);
  AddEvent(drawinfo, 75);
  
  AddEvent(updatescreen, 75);
  
  AddEvent(systemtasks, 500);
  
/*******************************************************************************
 *                              STARTUP CYCLE                            
 *******************************************************************************
 */
  while(!StartFl && CFlags.RunGameFl)
  {
    TestBtn(&B1); TestBtn(&B2);
    if(B2.BtnON){B2.BtnON = 0; StartFl = 1;}
    if(B1.BtnON){B1.BtnON = 0; CFlags.RunGameFl = 0; CFlags.MenuFl = 1;}

    if(timestamp - counter > 150){
      LCD_erase_bufuploud();
      counter = timestamp;
    }
    LCD_printbutselhint(5, 2, 89);
    LCD_printstr8x5("вых.вх", 6, 86);
    delay_ms(50);
  }
  
/*******************************************************************************
 *                              MAIN LEVEL CYCLE                            
 *******************************************************************************
 */
  while(StartFl && CFlags.RunGameFl)
  { 
    ProcessTimerEvent();
  }
}