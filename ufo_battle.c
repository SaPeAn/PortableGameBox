#include "ufo_battle.h"
#include "drv_LCD_ST7565_SPI.h"
#include "drv_RTC_I2C.h"
#include "display_data.h"
#include "scheduler.h"

/*******************************************************************************
 *                        SCHEDULER EVENT HANDLERS
 * *****************************************************************************
 */
void gameprogress(uint8 period)
{
  static uint8 counter = 0;
  if(counter == period)
  {
    Game.level_progress++;
    if(Game.level_progress > Game.Const1){}
    if(Game.level_progress > Game.Const2){}
    if(Game.level_progress > Game.Const3){}
  }
  else{counter = 0;}
  counter++;
}

void createevilstar(void) {
  static uint8 i = 0;
  if (EvilStar[i].state == 0) {
    EvilStar[i].state = 1;
    EvilStar[i].cl = 127;
    EvilStar[i].ln = getrand(40) + 8;
  }
  i++;
  if (i >= EVILSTAR_MAX) i = 0;
}

void createcoin(tEvilStar* Evil_Star) {
  static uint8 i = 0;
  if (getrand(2) < 2) return;
  if (Coin[i].state == 0) {
    Coin[i].state = 1;
    Coin[i].cl = Evil_Star->cl;
    Coin[i].ln = Evil_Star->ln;
    Coin[i].animation_count = COIN_ANIMATION_PERIOD;
  }
  i++;
  if (i >= COIN_MAX) i = 0;
}

void createbullet(void) {
  if (B2.BtnON || B2.HoldON || B2.StuckON) {
    B2.BtnON = 0;
    static uint8 i = 0;
    if (!Bullet[i].state && (Gamer.health > 0) && (Gamer.energy >= 2)) {
      Gamer.energy -= BULLET_ENERGY_COST;
      Bullet[i].state = 1;
      Bullet[i].ln = Gamer.ln;
      Bullet[i].cl = Gamer.cl + 28;
      Sounds(400);
    }
    i++;
    if (i >= BULLET_MAX) i = 0;
  }
}

void gunregen(void) //Energy regen
{
  if (Gamer.energy < Gamer.energymax) Gamer.energy++;
}

void movgamer(void) 
{
  if (joystick.oy > 140 && joystick.oy <= 210){Gamer.ln -= 2; if(Gamer.ln < 8) Gamer.ln = 8;}
  if (joystick.oy > 210 && joystick.oy <= 250){Gamer.ln -= 4;if(Gamer.ln < 8) Gamer.ln = 8;}
  if (joystick.oy > 250){Gamer.ln -= 8; if(Gamer.ln < 8)Gamer.ln = 8;}
  if (joystick.oy < 120 && joystick.oy >= 50){Gamer.ln += 2; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.oy < 50 && joystick.oy >= 10){Gamer.ln += 4; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.oy < 10){Gamer.ln += 8; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.ox > 140 && joystick.ox <= 210){Gamer.cl += 2; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox > 210 && joystick.ox <= 250){Gamer.cl += 4; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox > 250){Gamer.cl += 8; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox < 120 && joystick.ox >= 50){Gamer.cl -= 2; if(Gamer.cl < -8)Gamer.cl = -8;}
  if (joystick.ox < 50 && joystick.ox >= 10){Gamer.cl -= 4; if(Gamer.cl < -8) Gamer.cl = -8;}
  if (joystick.ox < 10){Gamer.cl -= 8; if(Gamer.cl < -8)Gamer.cl = -8;}
}

void movevilstar(void) {
  for (uint8 i = 0; i < EVILSTAR_MAX; i++) {
    if (EvilStar[i].state == 1) {
      EvilStar[i].cl--;
      if ((EvilStar[i].cl < -29)) EvilStar[i].state = 0;
    }
  }
}

void movbullet(void) {
  for (uint8 i = 0; i < BULLET_MAX; i++) {
    if (Bullet[i].state) {
      Bullet[i].cl += 1;
      if (Bullet[i].cl > 126) {
        Bullet[i].state = 0;
        Bullet[i].cl = 0;
      }
    }
  }
}

void movcoin(void) {
  for (uint8 i = 0; i < COIN_MAX; i++) {
    if (Coin[i].state == 1) {
      Coin[i].cl -= 1;
      if (Coin[i].cl < -9) Coin[i].state = 0;
    }
  }
}

void bullet_evilstar_collision(void) {
  for (uint8 j = 0; j < BULLET_MAX; j++) {
    for (uint8 i = 0; i < EVILSTAR_MAX; i++) {
      if ((EvilStar[i].cl <= Bullet[j].cl) && (EvilStar[i].ln < (Bullet[j].ln + 6)) &&
              ((EvilStar[i].ln + 10) > Bullet[j].ln) && EvilStar[i].state == 1 &&
              Bullet[j].state) {
        EvilStar[i].state = 2;
        Bullet[j].state = 0;
        Sounds(500);
      }
    }
  }
}

void gamer_evilstar_collision(void) {
  for (uint8 i = 0; i < EVILSTAR_MAX; i++) {
    if ((EvilStar[i].cl <= (Gamer.cl + 29)) && ((EvilStar[i].cl + 25) >= Gamer.cl) &&
            ((EvilStar[i].ln + 15) > Gamer.ln) && (EvilStar[i].ln < (Gamer.ln + 15)) &&
            (EvilStar[i].state == 1) && (Gamer.health > 0)) {
      EvilStar[i].state = 2;
      Gamer.health -= 4;
      Sounds(600);
    }
  }

  //Gamer's death handler
  if (Gamer.health <= 0) {
    Sounds(600);
    stopgamehandler();
  }
}

void gamer_coin_collision(void) {
  for (uint8 i = 0; i < COIN_MAX; i++) {
    if ((Coin[i].cl <= (Gamer.cl + 29)) && ((Coin[i].cl + 8) >= Gamer.cl) &&
            ((Coin[i].ln + 8) > Gamer.ln) && (Coin[i].ln < (Gamer.ln + 15)) &&
            (Coin[i].state == 1) && (Gamer.health > 0)) {
      Coin[i].state = 0;
      Gamer.money += 1;
      Sounds(300);
    }
  }
}

void drawevilstar(void) {
  for (uint8 i = 0; i < EVILSTAR_MAX; i++) {
    if (EvilStar[i].state == 1) {
      LCD_printsprite(EvilStar[i].ln, EvilStar[i].cl, &evilstar_sprite);
    }
    if (EvilStar[i].state == 2) {
      LCD_printsprite(EvilStar[i].ln, EvilStar[i].cl, &distr_evilstar_sprite);
      if (EvilStar[i].distr_ttl_count++ >= EVILSTAR_DISTR_TTL) {
        EvilStar[i].distr_ttl_count = 0;
        EvilStar[i].state = 0;
        createcoin(&EvilStar[i]);
      }
    }
  }
}

void drawcoin(void) {
  for (uint8 i = 0; i < COIN_MAX; i++) {
    if (Coin[i].state == 1) {
      Coin[i].animation_count--;
      if (Coin[i].animation_count >= (COIN_ANIMATION_PERIOD / 2)) LCD_printsprite(Coin[i].ln + 1, Coin[i].cl, &coin_sprite);
      if (Coin[i].animation_count < (COIN_ANIMATION_PERIOD / 2)) LCD_printsprite(Coin[i].ln - 1, Coin[i].cl, &coin_sprite);
      if (Coin[i].animation_count == 0) Coin[i].animation_count = COIN_ANIMATION_PERIOD;
    }
  }
}

void drawgamer(void) {
  if ((Gamer.health > 0)) {
    if (Gamer.gasmask_fl) LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_gas_sprite);
    else LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_sprite);
  }
}

void drawbullet(void) {
  for (uint8 i = 0; i < BULLET_MAX; i++) {
    if (Bullet[i].state) {
      LCD_printsprite(Bullet[i].ln, Bullet[i].cl, &bullet_sprite);
    }
  }
}

void drawinfo(void) {
  LCD_printgamestatbar(&Gamer);
}

void screenupdate(void) {
  LCD_bufupload_buferase();
}

//Background smallstars animation
void createsmallstar(uint8 create_period)
{
  static uint8 j = 0;
  static uint8 k = 0;
  if(k == 0) k = create_period;
  if(k == create_period)
  {
    if(SmallStar[j].state == 0){
      SmallStar[j].state = getrand(1) + 1;
      SmallStar[j].ln = getrand(60);
      SmallStar[j].cl = 127;
    }
    j++;
    if(j >= SMALLSTAR_MAX) j = 0;
  }
  k--;
}

void movesmallstar(uint8 move_period)
{
  static uint8 l = 0;
  if(l == 0) l = move_period;
  if(l == move_period) {
    for(uint8 i = 0; i < SMALLSTAR_MAX; i++)
    {
      SmallStar[i].cl -= 1;
      if(SmallStar[i].cl < 1) SmallStar[i].state = 0;
    }
  }
  l--;
}

void drawsmallstar(void)
{
  for(uint8 i = 0; i < SMALLSTAR_MAX; i++)
  {
    if(SmallStar[i].state) {
      LCD_printsprite(SmallStar[i].ln, SmallStar[i].cl, &smallstar_sprite[SmallStar[i].state - 1]);
    }
  }
}
//EVENT CHECKER
void getevent(void)
{
    
    if (joystick.down) {
      joystick.down = 0;
      gameevent = EVENT_JOYDOWN;
    }
    if (joystick.up){
      joystick.up = 0;
      gameevent = EVENT_JOYUP;
    }
    if (joystick.left) {
      joystick.left = 0;
      gameevent = EVENT_JOYLEFT; 
    }
    if (joystick.right){
      joystick.right = 0;
      gameevent = EVENT_JOYRIGHT;
    }
    if (B1.BtnON) {
      B1.BtnON = 0;
      gameevent = EVENT_B2PRESS;
    }
    if (B2.BtnON) {
      B2.BtnON = 0;
      gameevent = EVENT_B2PRESS;
    }if (B3.BtnON) {
      B3.BtnON = 0;
      gameevent = EVENT_B3PRESS;
    }
    if (B4.BtnON) {
      B4.BtnON = 0;
      gameevent = EVENT_B4PRESS;
    }
}
//--------------------------COMBINED SCHEDULER EVENTS---------------------------
void move_enemy_objects(void) {
  movevilstar();
  movcoin();
}

void rungame_events_period100ms(void) {
  movgamer();
  createbullet();
  bullet_evilstar_collision();
  gamer_evilstar_collision();
  gamer_coin_collision();
  drawevilstar();
  drawcoin();
  drawgamer();
  drawbullet();
  drawinfo();
}

void system_events_period100ms(void) {
  check_btn_jstk();
  batcheck();
  createsmallstar(SMALLSTAR_CREATE_PER);
  gameprogress(PRD_GAMEPROGRESS);
  drawsmallstar();
  screenupdate();
}
void system_events_period25ms(void) {
  movesmallstar(SMALLSTAR_MOVE_PER);
}

/*******************************************************************************
 *                              GAME MENU HANDLERS                            
 *******************************************************************************
 */
void startnewgame(void)
{
  gamestate = STATE_STARTNEWGAME;
  if(GAME_STORY_STRING_NUM < 4)
  {
    if(GAME_STORY_STRING_NUM == 3) LCD_printstr8x5(gamestory_string[GAME_STORY_STRING_NUM], 3, 0);
    else LCD_printstr8x5(gamestory_string[GAME_STORY_STRING_NUM], 0, 0);
    LCD_printstr8x5((uint8*)"äàëåå...", 7, 78);
    if(!B1.BtnON && !B2.BtnON && !B3.BtnON && !B4.BtnON)
    {
      B1.BtnON = 0;
      B2.BtnON = 0;
      B3.BtnON = 0;
      B4.BtnON = 0;
      GAME_STORY_STRING_NUM++;
    }
  }
  else
  {
    Gamer.health = 24;
    Gamer.energy = 2;
    Gamer.energymax = 2;
    Gamer.gasmask_fl = 0;
    Gamer.bombs = 0;
    Gamer.money = 0;
    Gamer.ln = 16;
    Gamer.cl = 0;
    SchedAddEvent(gunregen, PRD_GAMER_ENERGYREGEN);
    SchedAddEvent(createevilstar, PRD_EVELSTAR_CREATE);
    SchedAddEvent(movbullet, 5);
    SchedAddEvent(move_enemy_objects, PRD_ENEMY_MOVE);
    SchedAddEvent(rungame_events_period100ms, 100);
    SchedResumeEvent(transition_table[gamestate][gameevent]);
    gamestate = STATE_GAMERUN;
  }
}

void savegame(uint8 slot) 
{
}

void loadgame(uint8 slot)
{
}

void resumegamehandler(void)
{
  SchedResumeEvent(gunregen);
  SchedResumeEvent(createevilstar);
  SchedResumeEvent(movbullet);
  SchedResumeEvent(move_enemy_objects);
  SchedResumeEvent(rungame_events_period100ms);
  gamestate = STATE_GAMERUN;
}

void rungame(void)
{
  
}

void stopgamehandler(void)
{
  SchedRemoveEvent(gunregen);
  SchedRemoveEvent(createevilstar);
  SchedRemoveEvent(movbullet);
  SchedRemoveEvent(move_enemy_objects);
  SchedRemoveEvent(rungame_events_period100ms);
  for(uint8 i = 0; i < EVILSTAR_MAX; i++) EvilStar[i].state = 0;
  for(uint8 i = 0; i < COIN_MAX; i++) Coin[i].state = 0;
  for(uint8 i = 0; i < BULLET_MAX; i++) Bullet[i].state = 0;
  GAME_STORY_STRING_NUM = 0;
  gamestate = STATE_MMSTARTNEWGAME;
}

void exitgame(void)
{
  CFlags.RunGameFl = 0;
  CFlags.MenuFl = 1;
  SchedRemoveAllEvents();
}

void loadslot1(void){
  loadgame(SLOT1);
  gamestate = STATE_GAMERUN;
}
void loadslot2(void){
  loadgame(SLOT2);    
  gamestate = STATE_GAMERUN;
}
void saveslot1(void){
  savegame(SLOT1);
}
void saveslot2(void){
  savegame(SLOT2);
}

void displaymainmenu(void)
{
  LCD_printstr8x5((uint8*)"ÃÀËÀÊÒÈ×ÅÑÊÈÉ ÇÂÅÇÄÅÖ", 0, 0);
  LCD_printstr8x5((uint8*)"ÍÎÂÀß ÈÃÐÀ", 2, 19);
  LCD_printstr8x5((uint8*)"ÇÀÃÐÓÇÈÒÜ ÈÃÐÓ", 4, 19);
  LCD_printstr8x5((uint8*)"ÂÛÉÒÈ", 6, 19);
}

void magazenter(void)
{
  
}

void displaypausemenu(void)
{
  LCD_printstr8x5((uint8*)"ÏÀÓÇÀ", 0, 5);
  LCD_printstr8x5((uint8*)"ÑÎÕÐÀÍÈÒÜ", 2, 19);
  LCD_printstr8x5((uint8*)"ÂÅÐÍÓÒÜÑß Ê ÈÃÐÅ", 4, 19);
  LCD_printstr8x5((uint8*)"ÂÛÉÒÈ", 6, 19);
}
void displayloadmenu(void)
{
  LCD_printstr8x5((uint8*)"ÇÀÃÐÓÇÊÀ ÈÃÐÛ", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"ÍÀÇÀÄ", 6, 19);
}
void displaysavemenu(void)
{
  LCD_printstr8x5((uint8*)"ÑÎÕÐÀÍÅÍÈÅ ÈÃÐÛ", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"ÍÀÇÀÄ", 6, 19);
}
//--------------------------GAME MENU STATES-------------------------------                           
void mmstartnewgame(void) {
  gamestate = STATE_MMSTARTNEWGAME;
  LCD_printmenucoursor(2, 4);
  displaymainmenu();
}
void mmloadgame(void){
  gamestate = STATE_MMLOADGAME;
  LCD_printmenucoursor(4, 4);
  displaymainmenu();
}
void mmexitgame(void){
  gamestate = STATE_MMEXIT;
  LCD_printmenucoursor(6, 4);
  displaymainmenu();
}
void lmslot1(void){
  gamestate = STATE_LMSLOT1;
  LCD_printmenucoursor(2, 4);
  displayloadmenu();
}
void lmslot2(void){
  gamestate = STATE_LMSLOT2;
  LCD_printmenucoursor(4, 4);
  displayloadmenu();
}
void lmreturn(void){
  gamestate = STATE_LMRETURN;
  LCD_printmenucoursor(6, 4);
  displayloadmenu();
}
void pmsave(void){
  gamestate = STATE_PMSAVE;
  SchedPauseEvent(gunregen);
  SchedPauseEvent(createevilstar);
  SchedPauseEvent(movbullet);
  SchedPauseEvent(move_enemy_objects);
  SchedPauseEvent(rungame_events_period100ms);
  LCD_printmenucoursor(2, 4);
  displaypausemenu();
}
void pmreturn(void){
  gamestate = STATE_PMRETURN;
  LCD_printmenucoursor(4, 4);
  displaypausemenu();
}
void pmexit(void){
  gamestate = STATE_PMEXIT;
  LCD_printmenucoursor(6, 4);
  displaypausemenu();
}
void smslot1(void){
  gamestate = STATE_SMSLOT1;
  LCD_printmenucoursor(2, 4);
  displaysavemenu();
}
void smslot2(void){
  gamestate = STATE_SMSLOT2;
  LCD_printmenucoursor(4, 4);
  displaysavemenu();
}
void smreturn(void){
  gamestate = STATE_SMRETURN;
  LCD_printmenucoursor(6, 4);
  displaysavemenu();
}

/*******************************************************************************
 *                              MAIN ENTRY - GAME CYCLE                     
 *******************************************************************************
 */
void ufobattle(void)
{
  randinit();
  SchedAddEvent(system_events_period25ms, 25);
  SchedAddEvent(system_events_period100ms, 100);
  SchedAddEvent(transition_table[gamestate][gameevent], 100);
  gamestate = STATE_MMSTARTNEWGAME;
    
  while (CFlags.RunGameFl)
  {
    SchedEventProcess();
  }
}