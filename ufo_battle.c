#include "ufo_battle.h"
#include "drv_LCD_ST7565_SPI.h"
#include "drv_RTC_I2C.h"
#include "display_data.h"
#include "scheduler.h"

//------------------------------Game objects------------------------------------
enum gMenuPTR{
  GAME_MENU_START = 1,
  GAME_MENU_LOAD = 2,
  GAME_MENU_EXIT = 3
};
enum gMenuPTR GameMenuPTR = 1;

enum gPausePTR{
  GAME_PAUSE_SAVE = 1,
  GAME_PAUSE_RETURN = 2,
  GAME_PAUSE_EXIT = 3
};
enum gPausePTR GamePausePTR = 1;

enum gSaveLoadPTR{
  GAME_SAVELOAD_GAME1 = 1,
  GAME_SAVELOAD_GAME2 = 2,
  GAME_SAVELOAD_EXIT = 3
};
enum gSaveLoadPTR GameSaveLoadPTR = 1;
#define   SAVE     0
#define   LOAD     1

typedef struct {
  uint8 en;
  uint8 ln;
  uint8 cl;
}tBullet;

typedef struct{
  uint8  state;  // 0 - Comet disable; 1 - Comet enable; 2 - Comet distroed
  uint8  ln;
  int8   cl;
  uint8  distr_ttl_count;
  uint8  damage;
}tEvilStar;

typedef struct{
  uint8 en;
  uint8 ln;
  int8   cl;
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
tEvilStar Evil_Star[COMET_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};
uint8 Max_Bullet = BULLET_MAX;
uint8 Max_Comet = COMET_MAX;
uint8 Max_Coin = COIN_MAX;
uint32 counter = 0;

enum gamestate{
    game_running = 1,
    game_paused = 2,
    game_stopped = 3,
    game_exiting = 4    
};

enum gamestate gamestate = game_stopped;

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
 *                              EVENT DESCRIPTIONS
 * *****************************************************************************
 */
void check_btn_jstk(void)  //Test buttons and joystick
{
  TestBtn(&B1);
  TestBtn(&B2);
  TestBtn(&B3);
  TestBtn(&B4);
  joystick.ox = adc_getval_an0();
  joystick.oy= adc_getval_an1();
  checkjoydir();
}

void createevilstar(void)
{
  static uint8 i = 0;
    if(Evil_Star[i].state == 0)
    {
      Evil_Star[i].state = 1;
      Evil_Star[i].cl = 126;
      Evil_Star[i].ln = getrand(40) + 8;
    }
  i++;
  if(i >= Max_Comet) i = 0;
}

void createcoin(tEvilStar Evil_Star)
{
  static uint8 i = 0;
  if(getrand(2) < 2) return;
  if(Coin[i].en == 0)
  {
    Coin[i].en = 1;
    Coin[i].cl = Evil_Star.cl;
    Coin[i].ln = Evil_Star.ln;
    Coin[i].animation_count = COIN_ANIMCOUNT;
  }
  i++;
  if(i >= Max_Coin) i = 0;
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
  check_btn_jstk();
  ClickBtnFunc(&B4,gamepausemenu);
  batcheck();
}

void gunregen(void)  //Energy regen
{
  if(Gamer.energy <= Gamer.energymax) Gamer.energy++;  
}

void movgamer(void)
{
  if(joystick.oy > 140 && joystick.oy <= 210){Gamer.ln-=1; if(Gamer.ln < 8) Gamer.ln = 8;}
  if(joystick.oy > 210 && joystick.oy <= 250){Gamer.ln-=2; if(Gamer.ln < 8) Gamer.ln = 8;}
  if(joystick.oy > 250){Gamer.ln-=4; if(Gamer.ln < 8) Gamer.ln = 8;}
  if(joystick.oy < 120 && joystick.oy >= 50){Gamer.ln+=1; if(Gamer.ln > 48) Gamer.ln = 48;}
  if(joystick.oy < 50 && joystick.oy >= 10){Gamer.ln+=2; if(Gamer.ln > 48) Gamer.ln = 48;}
  if(joystick.oy < 10){Gamer.ln+=4; if(Gamer.ln > 48) Gamer.ln = 48;}
  if(joystick.ox > 140 && joystick.ox <= 210){Gamer.cl += 1; if(Gamer.cl > 94) Gamer.cl = 94;}
  if(joystick.ox > 210 && joystick.ox <= 250){Gamer.cl += 2; if(Gamer.cl > 94) Gamer.cl = 94;}
  if(joystick.ox > 250){Gamer.cl += 4; if(Gamer.cl > 94) Gamer.cl = 94;}
  if(joystick.ox < 120 && joystick.ox >= 50){Gamer.cl -= 1; if(Gamer.cl < -8) Gamer.cl = -8;}
  if(joystick.ox < 50 && joystick.ox >= 10){Gamer.cl -= 2; if(Gamer.cl < -8) Gamer.cl = -8;}
  if(joystick.ox < 10){Gamer.cl -= 4; if(Gamer.cl < -8) Gamer.cl = -8;}
}

void movevilstar(void)
{
  for(uint8 i = 0; i < Max_Comet; i++)
  {
    if(Evil_Star[i].state == 1){
        Evil_Star[i].cl --;
        if((Evil_Star[i].cl < -29) ) Evil_Star[i].state = 0;
    }
  }
}

void movbullet(void)
{
  for(uint8 i = 0; i < Max_Bullet; i++)
  {
    if(Bullet[i].en){
      Bullet[i].cl += 1;
      if(Bullet[i].cl > 127) {
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
        if(Coin[i].cl < -9) Coin[i].en = 0;
    }
  }
}

void bullet_evilstar_collision(void)
{
  for(uint8 j = 0; j < Max_Bullet; j++)
  {
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(     (Evil_Star[i].cl <= Bullet[j].cl) && (Evil_Star[i].ln < (Bullet[j].ln + 6)) && 
              ((Evil_Star[i].ln + 10) > Bullet[j].ln) && Evil_Star[i].state == 1 && 
              Bullet[j].en)
      {
        Evil_Star[i].state = 2;
        Bullet[j].en = 0;
        Sounds(500);
      }
    }
  }
}

void gamer_evilstar_collision(void)
{
  for(uint8 i = 0; i < Max_Comet; i++)
  {
    if(     (Evil_Star[i].cl <= (Gamer.cl+29)) && ((Evil_Star[i].cl + 25) >= Gamer.cl) && 
            ((Evil_Star[i].ln + 15) > Gamer.ln) && (Evil_Star[i].ln < (Gamer.ln + 15)) && 
            (Evil_Star[i].state == 1) && (Gamer.health > 0))
    {
      Evil_Star[i].state = 2;
      Gamer.health -= 4;
      Sounds(600);
    }
  }

  //Gamer's death hendler
  if(Gamer.health <= 0) {
    Sounds(600); 
    gamestate = game_stopped;
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

void drawevilstar(void)
{
    for(uint8 i = 0; i < Max_Comet; i++)
    {
      if(Evil_Star[i].state == 1) {
        LCD_printsprite(Evil_Star[i].ln, Evil_Star[i].cl, &evilstar_sprite);
      }
      if(Evil_Star[i].state == 2) {
        LCD_printsprite(Evil_Star[i].ln, Evil_Star[i].cl, &distr_evilstar_sprite);
        if(Evil_Star[i].distr_ttl_count++ >= COMET_DISTR_TTL){
            Evil_Star[i].distr_ttl_count = 0;
            Evil_Star[i].state = 0;
            createcoin(Evil_Star[i]);
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
        if(Coin[i].animation_count >= (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln + 1, Coin[i].cl, &coin_sprite);
        if(Coin[i].animation_count < (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln - 1, Coin[i].cl, &coin_sprite);
        if(Coin[i].animation_count == 0) Coin[i].animation_count = COIN_ANIMCOUNT;
      }
    }
}

void drawgamer(void)
{
    if((Gamer.health > 0)) {
      if(Gamer.gasmask_fl) LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_gas_sprite);
      else LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_sprite);
    }
}

void drawbullet(void)
{
    for(uint8 i = 0; i < Max_Bullet; i++)
    {
      if(Bullet[i].en){
        LCD_printsprite(Bullet[i].ln, Bullet[i].cl, &bullet_sprite);
      }
    }
}

void drawinfo(void)
{
    //Status bar
    LCD_printgamestatbar(&Gamer);
}

void screenupdate(void){
  LCD_bufupload_buferase();
}

void check_collision(void)
{
  bullet_evilstar_collision();
  gamer_evilstar_collision();
  gamer_coin_collision();
}

void draw_and_screenupdate(void)
{
  drawevilstar();
  drawcoin();
  drawgamer();
  drawbullet();
  drawinfo();  
  screenupdate();
}

void move_enemy_objects(void)
{
  movevilstar();
  movcoin();
}
/*******************************************************************************
 *                              GAME MAIN MENU                            
 *******************************************************************************
 */
void gamemainmenu(void)
{
  while(gamestate == game_stopped)
  {
    check_btn_jstk();
    if(joystick.down){joystick.down = 0; GameMenuPTR++; if(GameMenuPTR > 3) GameMenuPTR = 3;}
    if(joystick.up){joystick.up = 0; GameMenuPTR--; if(GameMenuPTR < 1) GameMenuPTR = 1;}

    switch(GameMenuPTR)
    {
      case GAME_MENU_START:
        LCD_printmenucoursor(2, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          gamestate = game_running;
        }
        break;
      case GAME_MENU_LOAD:
        LCD_printmenucoursor(4, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          gamesaveloadmenu(LOAD);
        }
        break;
      case GAME_MENU_EXIT:
        LCD_printmenucoursor(6, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          CFlags.RunGameFl = 0; CFlags.MenuFl = 1; RemoveAllEvents(); return;
        }
        break;      
    }
    
    LCD_printstr8x5("ÃÀËÀÊÒÈ×ÅÑÊÈÉ ÇÂÅÇÄÅÖ", 0, 0);
    LCD_printstr8x5("ÍÎÂÀß ÈÃÐÀ", 2, 19);
    LCD_printstr8x5("ÇÀÃÐÓÇÈÒÜ ÈÃÐÓ", 4, 19);
    LCD_printstr8x5("ÂÛÉÒÈ", 6, 19);
    LCD_bufupload_buferase();
    delay_ms(50);
  }
}
/*******************************************************************************
 *                              GAME PAUSE MENU                            
 *******************************************************************************
 */
void gamepausemenu(void)
{
  SaveEventCounter();
  while(1)
  {
    check_btn_jstk();
    if(joystick.down){joystick.down = 0; GamePausePTR++; if(GamePausePTR > 3) GamePausePTR = 3;}
    if(joystick.up){joystick.up = 0; GamePausePTR--; if(GamePausePTR < 1) GamePausePTR = 1;}

    switch(GamePausePTR)
    {
      case GAME_PAUSE_SAVE:
        LCD_printmenucoursor(2, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          gamesaveloadmenu(SAVE);
        }
        break;
      case GAME_PAUSE_RETURN:
        LCD_printmenucoursor(4, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          return;
        }
        break;
      case GAME_PAUSE_EXIT:
        LCD_printmenucoursor(6, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          gamestate = game_stopped;
          return;
        }
        break;
    }
    LCD_printstr8x5("ÏÀÓÇÀ", 0, 5);
    LCD_printstr8x5("ÑÎÕÐÀÍÈÒÜ", 2, 19);
    LCD_printstr8x5("ÂÅÐÍÓÒÜÑß Ê ÈÃÐÅ", 4, 19);
    LCD_printstr8x5("ÂÛÉÒÈ", 6, 19);
    LCD_bufupload_buferase();
    delay_ms(50);
  }
  LoadEventCounter();
}
/*******************************************************************************
 *                              GAME SAVE/LOAD MENU                            
 *******************************************************************************
 */
void gamesaveloadmenu(uint8 safe_load)
{
  while(1)
  {
    check_btn_jstk();
    if(joystick.down){joystick.down = 0; GameSaveLoadPTR++; if(GameSaveLoadPTR > 3) GameSaveLoadPTR = 3;}
    if(joystick.up){joystick.up = 0; GameSaveLoadPTR--; if(GameSaveLoadPTR < 1) GameSaveLoadPTR = 1;}

    switch(GameSaveLoadPTR)
    {
      case GAME_SAVELOAD_GAME1:
        LCD_printmenucoursor(2, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
        }
        break;
      case GAME_SAVELOAD_GAME2:
        LCD_printmenucoursor(4, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
        }
        break;
      case GAME_SAVELOAD_EXIT:
        LCD_printmenucoursor(6, 4);
        if(B2.BtnON){
          B2.BtnON = 0;
          return;
        }
        break; 
    }
    if(safe_load == SAVE) LCD_printstr8x5("ÑÎÕÐÀÍÅÍÈÅ ÈÃÐÛ", 0, 5);
    else LCD_printstr8x5("ÇÀÃÐÓÇÊÀ ÈÃÐÛ", 0, 5);
    LCD_printstr8x5("ÑÎÕÐ.ÈÃÐÀ 1", 2, 19);
    LCD_printstr8x5("ÑÎÕÐ.ÈÃÐÀ 2", 4, 19);
    LCD_printstr8x5("ÍÀÇÀÄ", 6, 19);
    LCD_bufupload_buferase();
    delay_ms(50);
  }
}
/*******************************************************************************
 *                              MAIN ENTRY                            
 *******************************************************************************
 */
void ufobattle(void)
{
  ufobattle_init();
  randinit();
  
  AddEvent(systemtasks, 50);
  AddEvent(gunregen, Gamer.energy_regenperiod);
  
  AddEvent(createevilstar, 800);
  AddEvent(createbullet, 100);
  
  AddEvent(movgamer, 40);
  AddEvent(movbullet, 5);
  AddEvent(move_enemy_objects, 18);
  
  AddEvent(check_collision, 100);
  
  AddEvent(draw_and_screenupdate, 100);

  
  
  while(CFlags.RunGameFl)
  {
/*******************************************************************************
 *                              STARTUP CYCLE                            
 *******************************************************************************
 */
   gamemainmenu();
  /*******************************************************************************
   *                              MAIN LEVEL CYCLE                            
   *******************************************************************************
   */
    while(gamestate == game_running)
    { 
      EventProcess();
    }
  }
  RemoveAllEvents();
}