#include "ufo_battle.h"
#include "drv_LCD_ST7565_SPI.h"
#include "drv_RTC_I2C.h"
#include "display_data.h"
#include "scheduler.h"

/*******************************************************************************
 *                        SCHEDULER GAME EVENT HANDLERS
 * *****************************************************************************
 */
void gameprogress(uint8 period)
{
  static uint8 counter = 0;
  if(counter == period)
  {
    Game.level_progress++;
    if(Game.level_progress == Game.Const1)
    {
      menuevent = EVENT_ENTERMAGAZ;
    }
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
  if ((B2.BtnON || B2.HoldON || B2.StuckON) && (Gamer.health > 0)) {
    B2.BtnON = 0;
    static uint8 i = 0;
    if (!Bullet[i].state && (Gamer.health > 0) && (Gamer.energy >= 2)) {
      Gamer.energy -= BULLET_ENERGY_COST;
      Bullet[i].state = 1;
      Bullet[i].ln = Gamer.ln;
      Bullet[i].cl = Gamer.cl + 24;
      Sounds(400);
    }
    i++;
    if (i >= BULLET_MAX) i = 0;
  }
}

void gunregen(void) //Energy regen
{
  if ((Gamer.energy < Gamer.energymax) && (Gamer.health > 0)) Gamer.energy++;
}

void movgamer(void) 
{
  if(Gamer.health > 0)
  {
    if (joystick.oy > 140 && joystick.oy <= 210){Gamer.ln -= 1; if(Gamer.ln < 8) Gamer.ln = 8;}
    if (joystick.oy > 210 && joystick.oy <= 250){Gamer.ln -= 2;if(Gamer.ln < 8) Gamer.ln = 8;}
    if (joystick.oy > 250){Gamer.ln -= 5; if(Gamer.ln < 8)Gamer.ln = 8;}
    if (joystick.oy < 120 && joystick.oy >= 50){Gamer.ln += 1; if(Gamer.ln > 48)Gamer.ln = 48;}
    if (joystick.oy < 50 && joystick.oy >= 10){Gamer.ln += 2; if(Gamer.ln > 48)Gamer.ln = 48;}
    if (joystick.oy < 10){Gamer.ln += 5; if(Gamer.ln > 48)Gamer.ln = 48;}
    if (joystick.ox > 140 && joystick.ox <= 210){Gamer.cl += 1; if(Gamer.cl > 94)Gamer.cl = 94;}
    if (joystick.ox > 210 && joystick.ox <= 250){Gamer.cl += 2; if(Gamer.cl > 94)Gamer.cl = 94;}
    if (joystick.ox > 250){Gamer.cl += 5; if(Gamer.cl > 94)Gamer.cl = 94;}
    if (joystick.ox < 120 && joystick.ox >= 50){Gamer.cl -= 1; if(Gamer.cl < -8)Gamer.cl = -8;}
    if (joystick.ox < 50 && joystick.ox >= 10){Gamer.cl -= 2; if(Gamer.cl < -8) Gamer.cl = -8;}
    if (joystick.ox < 10){Gamer.cl -= 5; if(Gamer.cl < -8)Gamer.cl = -8;}
  }
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
      Bullet[i].cl += 2;
      if (Bullet[i].cl > 126 || Bullet[i].cl <= 0) {
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
      if (EvilStar[i].distr_ttl_count++ >= EVILSTAR_DEATHANIMATION_TTL) {
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
  static uint8 k = 0;
  if(k == 0) k = create_period;
  if(k == create_period)
  {
    for(int i = 0; i < SMALLSTAR_MAX; i++)
    {
      if(SmallStar[i].state == 0){
        SmallStar[i].state = getrand(1) + 1;
        SmallStar[i].ln = getrand(60);
        SmallStar[i].cl = 127;
        break;
      }
    }
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
      if(SmallStar[i].state != 0) {
      SmallStar[i].cl -= 1;
      if(SmallStar[i].cl < -2) SmallStar[i].state = 0;
      }
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
//--------------------------COMBINED SCHEDULER EVENTS---------------------------
void move_enemy_objects(void) {
  movevilstar();
  movcoin();
}

/*******************************************************************************
 *                              GAME HANDLERS                            
 *******************************************************************************
 */
void statehandler_gameinitnew(void)
{
  menustate = STATE_STARTGAME;
  menuevent = EVENT_NONE;
 
  if(GAME_STORY_STRING_NUM < 4)
  {
    LCD_printstr8x5(gamestory_string[GAME_STORY_STRING_NUM], 0, 0);
    LCD_printstr8x5((uint8*)"‰‡ÎÂÂ...", 7, 78);
    if(B1.BtnON || B2.BtnON || B3.BtnON || B4.BtnON)
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
    Game.level = 0;
    Game.Const1 = 10;
    SchedAddEvent(gunregen, PRD_GAMER_ENERGYREGEN);
    SchedAddEvent(createevilstar, PRD_EVELSTAR_CREATE);
    SchedAddEvent(movbullet, 20);
    SchedAddEvent(move_enemy_objects, PRD_ENEMY_MOVE);
    menuevent = EVENT_EXIT; 
  }
}

void statehandler_gameload(void)
{
  statehandler_gameinitnew();
}

void statehandler_gamerun(void)
{
  if(menustate == STATE_PAUSEMENU)
  {
    SchedResumeEvent(gunregen);
    SchedResumeEvent(createevilstar);
    SchedResumeEvent(movbullet);
    SchedResumeEvent(move_enemy_objects);
  }
  
  static uint8 deadgamerdrawcounter = 20;
  
  menustate = STATE_RUNGAME;
  if(Gamer.health > 0)
  {
    if(B4.BtnON) {
      B4.BtnON = 0;
      menuevent = EVENT_PAUSE;
    }
    else menuevent = EVENT_NONE;
  }
  else   // draw dead player
  {
    if(deadgamerdrawcounter >= 10){
      LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_dead_0_sprite);
       deadgamerdrawcounter--;
    }
    if(deadgamerdrawcounter < 10 && deadgamerdrawcounter > 0) {
      LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_dead_1_sprite);
      deadgamerdrawcounter--;
      if(B1.BtnON || B2.BtnON || B3.BtnON || B4.BtnON) { B1.BtnON = 0; B2.BtnON = 0; B3.BtnON = 0; B4.BtnON = 0;} 
    }
    if(deadgamerdrawcounter == 0)
    {
      LCD_printstr8x5((uint8*)"«¬≈«ƒ¿Õ”À—ﬂ", 3, 30); 
      LCD_printstr8x5((uint8*)"Õ¿—Ã≈–“‹!", 4, 36);
      if(B1.BtnON || B2.BtnON || B3.BtnON || B4.BtnON)
      {
        B1.BtnON = 0; B2.BtnON = 0; B3.BtnON = 0; B4.BtnON = 0;
        deadgamerdrawcounter = 20;
        menuevent = EVENT_EXIT;
      }
    }
  }
  
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
  
  gameprogress(PRD_GAMEPROGRESS);  
}

void stateinit_gamestop(void)
{
  SchedRemoveEvent(gunregen);
  SchedRemoveEvent(createevilstar);
  SchedRemoveEvent(movbullet);
  SchedRemoveEvent(move_enemy_objects);
  for(uint8 i = 0; i < EVILSTAR_MAX; i++) EvilStar[i].state = 0;
  for(uint8 i = 0; i < COIN_MAX; i++) Coin[i].state = 0;
  for(uint8 i = 0; i < BULLET_MAX; i++) Bullet[i].state = 0;
  GAME_STORY_STRING_NUM = 0;
  menustate = STATE_MAINMENU;
  menuevent = EVENT_NONE;
  coursorpos = COURS_POS_1;
}

void stateinit_gameexit(void)
{
  CFlags.RunGameFl = 0;
  CFlags.MenuFl = 1;
  SchedRemoveAllEvents();
}

/*******************************************************************************
 *                              GAME MENU HANDLERS                            
 *******************************************************************************
 */
//EVENT CHECKER
void menu_getevent(void)
{
  static uint8 somethinghappen = 0;
  if (B1.BtnON || B2.BtnON || B3.BtnON || B4.BtnON) {
    B1.BtnON = 0;
    B2.BtnON = 0;
    B3.BtnON = 0;
    B4.BtnON = 0;
    switch(coursorpos)
    {
      case COURS_POS_1:
        menuevent = EVENT_SELPOS_1;
        break;
      case COURS_POS_2:
        menuevent = EVENT_SELPOS_2;
        break;
      case COURS_POS_3:
        menuevent = EVENT_SELPOS_3;
        break;
      case COURS_POS_4:
        menuevent = EVENT_SELPOS_4;
        break;
    }
    somethinghappen = 1;
  }
  if(somethinghappen) somethinghappen = 0;
  else menuevent = EVENT_NONE;
}

void coursormovdisp(void)
{
  //move coursor
  if(menustate != STATE_MAGAZIN)
  {
    if (joystick.down) {
      joystick.down = 0;
      coursorpos++; 
      if(coursorpos >= COURS_POS_3) coursorpos = COURS_POS_3;
    }
    if (joystick.up){
      joystick.up = 0;
      if(coursorpos != COURS_POS_1) coursorpos--; 
    }
  }
  else
  {
    if (joystick.right) {
      joystick.right = 0;
      if(coursorpos >= COURS_POS_4) coursorpos = COURS_POS_4;
      else coursorpos++; 
    }
    if (joystick.left){
      joystick.left = 0;
      if(coursorpos != COURS_POS_1) coursorpos--; 
    }
  }
  //display coursor
  if(menustate != STATE_MAGAZIN)
  {
    switch(coursorpos)
    {
      case COURS_POS_1:
        LCD_printmenucoursor(2, 4);
        break;
      case COURS_POS_2:
        LCD_printmenucoursor(4, 4);
        break;
      case COURS_POS_3:  
        LCD_printmenucoursor(6, 4);
        break;
      case COURS_POS_4:  
        LCD_printmenucoursor(6, 4);
        break;
    }
  }
  else
  {
    switch(coursorpos)
    {
      case COURS_POS_1:
        LCD_printhorline(14, 55, 15);
        break;
      case COURS_POS_2:
        LCD_printhorline(14, 55, 30);
        break;
      case COURS_POS_3:  
        LCD_printhorline(14, 55, 45);
        break;
      case COURS_POS_4:  
        LCD_printhorline(14, 55, 60);
        break;
    }
  }
}

void statehandler_menumain(void)
{
  menustate = STATE_MAINMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"√¿À¿ “»◊≈— »… «¬≈«ƒ≈÷", 0, 0);
  LCD_printstr8x5((uint8*)"ÕŒ¬¿ﬂ »√–¿", 2, 19);
  LCD_printstr8x5((uint8*)"«¿√–”«»“‹ »√–”", 4, 19);
  LCD_printstr8x5((uint8*)"¬€…“»", 6, 19);
  coursormovdisp();
  if(menuevent == EVENT_SELPOS_2) coursorpos = COURS_POS_1; // coursor position when entering the load menu in "SLOT1"
}

void statehandler_menuload(void)
{ 
  menustate = STATE_LOADMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"«¿√–”« ¿ »√–€", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"Õ¿«¿ƒ", 6, 19);
  coursormovdisp();
  if(menuevent == EVENT_SELPOS_3) coursorpos = COURS_POS_2; // coursor position when returning to the main menu in "LOAD"
}

void statehandler_menupause(void)
{
  if(menustate == STATE_RUNGAME)
  {
    SchedPauseEvent(gunregen);
    SchedPauseEvent(createevilstar);
    SchedPauseEvent(movbullet);
    SchedPauseEvent(move_enemy_objects);
  }
  menustate = STATE_PAUSEMENU;
  
  menu_getevent();
  LCD_printstr8x5((uint8*)"œ¿”«¿", 0, 5);
  LCD_printstr8x5((uint8*)"—Œ’–¿Õ»“‹", 2, 19);
  LCD_printstr8x5((uint8*)"¬≈–Õ”“‹—ﬂ   »√–≈", 4, 19);
  LCD_printstr8x5((uint8*)"¬€…“»", 6, 19);
  coursormovdisp();
  
}

void statehandler_menusave(void)
{
  menustate = STATE_SAVEMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"—Œ’–¿Õ≈Õ»≈ »√–€", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"Õ¿«¿ƒ", 6, 19);
  coursormovdisp();
  if(menuevent == EVENT_SELPOS_3) coursorpos = COURS_POS_1; // coursor position when returning to the pause menu in "SAVE"
}

void statehandler_gamesave(void)
{
  menuevent = EVENT_NONE;
}

void statehandler_magazin(void)
{
  static k = ANIM;
  if(menuevent == EVENT_ENTERMAGAZ)
  {
    
  }
  else
  {
    menustate = STATE_MAGAZIN;
    menuevent = EVENT_NONE;

  }
}
//--------------------------SYSTEM FUNCTIONS-------------------------------  
void system_events_period100ms(void) 
{
  check_btn_jstk();
  batcheck();
  createsmallstar(SMALLSTAR_CREATE_PERIOD);
  drawsmallstar();  
  
  screenupdate();
}

void gamemenu(void)
{
  menu_transition_table[menustate][menuevent]();
}

void system_events_period25ms(void) 
{
  movesmallstar(SMALLSTAR_MOVE_PERIOD);
}
/*******************************************************************************
 *                              MAIN ENTRY - GAME CYCLE                     
 *******************************************************************************
 */
void ufobattle(void)
{
  randinit();
  SchedAddEvent(system_events_period25ms, 25);
  SchedAddEvent(gamemenu, 75);
  SchedAddEvent(system_events_period100ms, 100);
  menustate = STATE_MAINMENU;
  menuevent = EVENT_NONE;
  coursorpos = COURS_POS_1;
  
  while (CFlags.RunGameFl)
  {
    SchedEventProcess();
  }
}