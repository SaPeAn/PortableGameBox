#include "ufo_battle.h"
#include "drv_lcdST7565_SPI.h"
#include "drv_swi2cRTC.h"
#include "display_data.h"
#include "scheduler.h"

//------------------------------Game objects------------------------------------

typedef struct {
  uint8 en;
  uint8 ln;
  uint8 cl;
}tBullet;

typedef struct{
  uint8  state;  // 0 - Comet disable; 1 - Comet enable; 2 - Comet distroed
  uint8  ln;
  uint8  cl;
  uint8  distr_ttl_count;
}tComet;

typedef struct{
  uint8 en;
  uint8 ln;
  uint8 cl;
  uint8 animation_count;
}tCoin;
//------------------------------------------------------------------------------  

//------------------------------Game vars & init--------------------------------

#define BULLET_MAX   20
#define COMET_MAX 20
#define COIN_MAX 20
#define COMET_DISTR_TTL  2
#define COIN_ANIMCOUNT  16
tBullet Bullet[BULLET_MAX] = {0};
tComet Comet[COMET_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};
uint8 Max_Bullet = BULLET_MAX;
uint8 Max_Comet = COMET_MAX;
uint8 Max_Coin = COIN_MAX;
uint32 counter = 0;

uint8 StartFl = 0;

void ufobattle_init(void)
{
  Gamer.health = 24;
  Gamer.energy = 4;
  Gamer.energymax = 24;
  Gamer.energy_regenperiod = 150;
  Gamer.gasmask_fl = 0;
  Gamer.bombs = 0;
  Gamer.money = 0;
  Gamer.ln = 16;
  Gamer.cl = 0;
}
/*******************************************************************************
 *                              SECONDARY FUNCTIONS
 * *****************************************************************************
 */
void createcoin(tComet Comet)
{
  static uint8 i = 0;
  if(getrand(2) < 2) return;
  if(Coin[i].en == 0)
  {
    Coin[i].en = 1;
    Coin[i].cl = Comet.cl;
    Coin[i].ln = Comet.ln;
    Coin[i].animation_count = COIN_ANIMCOUNT;
  }
  i++;
  if(i >= Max_Coin) i = 0;
}

/*******************************************************************************
 *                              EVENT DESCRIPTIONS
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

void createcomet(void)
{
  static uint8 i = 0;
    if(Comet[i].state == 0)
    {
      Comet[i].state = 1;
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
        if(!Bullet[i].en && (Gamer.health > 0) && (Gamer.energy >= 2)) 
        {
          Gamer.energy -= 2;
          Bullet[i].en = 1; 
          Bullet[i].ln = Gamer.ln; 
          Bullet[i].cl = Gamer.cl + 28;
          Sounds(400);
        }
        i++;
        if(i >= Max_Bullet) i = 0;
    }
}

void systemtasks(void)
{
  if(B4.BtnON || B4.HoldON || B4.StuckON){ // Exit button pressed
    B4.BtnON = 0; 
    StartFl = 0;  
  }
  batcheck();
}

void gunregen(void)  //Energy regen
{
  if(Gamer.energy <= Gamer.energymax) Gamer.energy++;  
}

void movgamer(void)
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

void movcomet(void)
{
  for(uint8 i = 0; i < Max_Comet; i++)
  {
    if(Comet[i].state == 1){
        Comet[i].cl -= 1;
        if(Comet[i].cl > 100) Comet[i].state = 0;
    }
  }
}

void movbullet(void)
{
  for(uint8 i = 0; i < Max_Bullet; i++)
  {
    if(Bullet[i].en){
      Bullet[i].cl += 1;
      if(Bullet[i].cl > 120) {
        Bullet[i].en = 0;
        Bullet[i].cl = 0;
      }
    }
  }
}

void movcoin(void)
{
  for(uint8 i = 0; i < Max_Coin; i++)
  {
    if(Coin[i].en == 1){
        Coin[i].cl -= 1;
        if(Coin[i].cl > 100) Coin[i].en = 0;
    }
  }
}

void bullet_comet_collision(void)
{
  for(uint8 j = 0; j < Max_Bullet; j++)
  {
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(     (Comet[i].cl <= Bullet[j].cl) && (Comet[i].ln < (Bullet[j].ln + 6)) && 
              ((Comet[i].ln + 10) > Bullet[j].ln) && Comet[i].state == 1 && 
              Bullet[j].en)
      {
        Comet[i].state = 2;
        Bullet[j].en = 0;
        Sounds(500);
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
            (Comet[i].state == 1) && (Gamer.health > 0))
    {
      Comet[i].state = 2;
      Gamer.health -= 2;
      Sounds(600);
    }
  }

  //Gamer's death hendler
  if(Gamer.health <= 0) {
    Sounds(600); 
    StartFl = 0;
  }
}

void gamer_coin_collision(void)
{
  for(uint8 i = 0; i < Max_Coin; i++)
  {
    if(     (Coin[i].cl <= (Gamer.cl+29)) && ((Coin[i].cl + 8) >= Gamer.cl) && 
            ((Coin[i].ln + 8) > Gamer.ln) && (Coin[i].ln < (Gamer.ln + 15)) && 
            (Coin[i].en == 1) && (Gamer.health > 0))
    {
      Coin[i].en = 0;
      Gamer.money += 1;
      Sounds(300);
    }
  }
}

void drawcomet(void)
{
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(Comet[i].state == 1) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, comet_sprite);
      }
      if(Comet[i].state == 2) {
        LCD_printsprite(Comet[i].ln, Comet[i].cl, distr_comet_sprite);
        if(Comet[i].distr_ttl_count++ >= COMET_DISTR_TTL){
            Comet[i].distr_ttl_count = 0;
            Comet[i].state = 0;
            createcoin(Comet[i]);
        }
      }
    }
}

void drawcoin(void)
{
    for(uint8 i = 0; i < Max_Coin; i++) 
    {
      if(Coin[i].en == 1) {
        Coin[i].animation_count--;
        if(Coin[i].animation_count >= (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln + 1, Coin[i].cl, coin_sprite);
        if(Coin[i].animation_count < (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln - 1, Coin[i].cl, coin_sprite);
        if(Coin[i].animation_count == 0) Coin[i].animation_count = COIN_ANIMCOUNT;
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
    for(uint8 i = 0; i < Max_Bullet; i++)
    {
      if(Bullet[i].en){
        LCD_printsprite(Bullet[i].ln, Bullet[i].cl, bullet_sprite);
      }
    }
}

void drawinfo(void)
{
    //Status bar
    LCD_printgamestatbar(&Gamer);
}

void updatescreen(void){
  LCD_bufupload_buferase();
}

/*******************************************************************************
 *                              MAIN ENTRY                            
 *******************************************************************************
 */
void ufobattle(void)
{
  randinit();
  
  AddEvent(systemtasks, 500);
  AddEvent(gunregen, Gamer.energy_regenperiod);
  AddEvent(checkbnjk, 50);
  
  AddEvent(createcomet, 1000);
  AddEvent(createbullet, 100);
  
  AddEvent(movgamer, 40);
  AddEvent(movbullet, 5);
  AddEvent(movcomet, 20);
  AddEvent(movcoin, 20);
  
  AddEvent(bullet_comet_collision, 100);
  AddEvent(gamer_comet_collision, 100);
  AddEvent(gamer_coin_collision, 100);
  
  AddEvent(drawcomet, 75);
  AddEvent(drawcoin, 75);
  AddEvent(drawgamer, 75);
  AddEvent(drawbullet, 75);
  AddEvent(drawinfo, 75);
  
  AddEvent(updatescreen, 75);

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
      LCD_bufupload_buferase();
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
    EventProcess();
  }
  RemoveAllEvents();
}