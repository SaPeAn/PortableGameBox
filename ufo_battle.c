#include "ufo_battle.h"
#include "drv_LCD_ST7565_SPI.h"
#include "drv_RTC_I2C.h"
#include "display_data.h"
#include "scheduler.h"

#define  IF_ANY_BTN_PRESS(a)    if(B1.BtnON || B2.BtnON || B3.BtnON || B4.BtnON)\
                                {B1.BtnON = 0; B2.BtnON = 0; B3.BtnON = 0; B4.BtnON = 0; a}
#define  IF_BTN_B2_PRESS(a)     if(B2.BtnON || B2.HoldON || B2.StuckON)\
                                 {B2.BtnON = 0; a}
#define  IF_BTN_B1_PRESS(a)     if(B1.BtnON || B1.HoldON || B1.StuckON)\
                                 {B1.BtnON = 0; a}


/*******************************************************************************
 *                        SCHEDULER GAME EVENT HANDLERS
 * *****************************************************************************
 */
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

void createbullet(uint8 period) {
  if(Gamer.health > 0){
    IF_BTN_B2_PRESS(
      static uint8 i = 0;
      static uint8 prd = 0;
      if(prd < period) prd++;
      else{
        prd = 0;
        if (!Bullet[i].state && (Gamer.health > 0) && (Gamer.energy >= BULLET_ENERGY_COST)) {
          Gamer.energy -= BULLET_ENERGY_COST;
          Bullet[i].state = 1;
          Bullet[i].ln = Gamer.ln;
          Bullet[i].cl = Gamer.cl + 24;
          Sounds(400);
        }
        i++;
        if (i >= BULLET_MAX) i = 0;
      }
    )
  }
  else IF_BTN_B2_PRESS();
}

void createbomb(uint8 period) {
  if(Gamer.health > 0){
    IF_BTN_B1_PRESS(
      static uint8 prd = 0;
      if(prd < period) prd++;
      else{
        prd = 0;
        if (!Bomb.state && (Gamer.health > 0) && Gamer.bombs) {
          Gamer.bombs --;
          Bomb.state = 1;
          Bomb.ln = Gamer.ln;
          Bomb.cl = Gamer.cl + 24;
          Sounds(1000);
        }
      }
    )
  }
  else IF_BTN_B1_PRESS();
}

void gunregen(uint16 period) //Energy regen
{
  static uint16 prd = 0;
  if ((Gamer.energy < Gamer.energymax) && (Gamer.health > 0)) 
  {
    if(prd < (period- 1)) prd++;
    else { 
      prd = 0; 
      Gamer.energy++;
    }
  }
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

void movbomb(void) {
  static uint8 explosionanimcount = 20; 
  if (Bomb.state == 1){
    Bomb.cl += 4;
    if (Bomb.cl > 85) {
      Bomb.state = 2;
      Bomb.cl -= 16;
      Bomb.ln -= 16;
      Sounds(1200);
    }
  }
  if(Bomb.state > 1){
    if(explosionanimcount >= 18) Bomb.state = 2;
    if(explosionanimcount < 18 && explosionanimcount >= 10) Bomb.state = 3;
    if(explosionanimcount < 10) Bomb.state = 4;
    if(explosionanimcount == 0) Bomb.state = 0;
    explosionanimcount--;
  }
  else explosionanimcount = 20;
}

void movcoin(void) {
  for (uint8 i = 0; i < COIN_MAX; i++) {
    if (Coin[i].state == 1) {
      Coin[i].cl -= 1;
      if (Coin[i].cl < -9) Coin[i].state = 0;
    }
  }
}

void movminmagaz(void){
  static uint8 prd = 0;
  if(MinMagaz.state){
    if(++prd == 12)
    {
      prd = 0;
      MinMagaz.cl -= 3;
      if(MinMagaz.cl < -34) {
        MinMagaz.state = 0;
        SchedResumeEvent(createevilstar);
      }
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

void bomb_evilstar_collision(void) {
  if(Bomb.state > 1){
    for (uint8 i = 0; i < EVILSTAR_MAX; i++) {
      if (((EvilStar[i].cl + 25) >= Bomb.cl) && (EvilStar[i].cl <= (Bomb.cl + 35)) && (EvilStar[i].ln <= (Bomb.ln + 35)) &&
              ((EvilStar[i].ln + 10) > Bomb.ln) && EvilStar[i].state == 1) {
        EvilStar[i].state = 2;
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

void gamer_minmagaz_collision(void) {
  if(MinMagaz.state){
    if ((MinMagaz.cl <= (Gamer.cl + 29)) && ((MinMagaz.cl + 30) >= Gamer.cl) &&
            ((MinMagaz.ln + 28) > Gamer.ln) && (MinMagaz.ln < (Gamer.ln + 15)) &&
            (Gamer.health > 0)) {
      MinMagaz.state = 0;
      gameevent = EVENT_ENTERMAGAZ;
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
      if (EvilStar[i].distr_ttl_count++ >= EVILSTAR_DEATHANIMATION_PERIOD) {
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

void drawminmagaz(void) {
    if (MinMagaz.state) {
      LCD_printsprite(MinMagaz.ln, MinMagaz.cl, &minimag_sprite);
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

void drawbomb(uint16 period) 
{
  if (Bomb.state) {
    if(Bomb.state < 2){
      if (Bomb.animation_count >= (3 * period / 4)) LCD_printsprite(Bomb.ln, Bomb.cl, &bomb_sprite[0]);
      if ((Bomb.animation_count < (3 * period / 4)) && 
         (Bomb.animation_count >= (2 * period / 4))) LCD_printsprite(Bomb.ln, Bomb.cl, &bomb_sprite[1]);
      if ((Bomb.animation_count < (2 * period / 4)) && 
         (Bomb.animation_count >= (period / 4))) LCD_printsprite(Bomb.ln, Bomb.cl, &bomb_sprite[2]);
      if (Bomb.animation_count < (period / 4)) LCD_printsprite(Bomb.ln, Bomb.cl, &bomb_sprite[3]);
      if (Bomb.animation_count == 0) Bomb.animation_count = period;
      Bomb.animation_count--;
    }
    else{
      switch(Bomb.state){
        case 2:
          LCD_printsprite(Bomb.ln, Bomb.cl, &bombshards_sprite[0]);
          break;
        case 3:
          LCD_printsprite(Bomb.ln, Bomb.cl, &bombshards_sprite[1]);
          break;
        case 4: 
          LCD_printsprite(Bomb.ln, Bomb.cl, &bombshards_sprite[2]);
          break;
      }
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

void gameprogress(uint8 period)
{
  static uint8 counter = 0;
  if(Gamer.health > 0)
  {
    if(counter == period)
    {
      Game.level_progress++;
      counter = 0;
    }

    if(Game.level_progress == Game.Const1 && counter == 0){
      MinMagaz.state = 1;
      MinMagaz.cl = 127;
      SchedPauseEvent(createevilstar);
    }

    if(Game.level_progress > Game.Const2){}
    if(Game.level_progress > Game.Const3){}

    counter++;
  }
}
//--------------------------COMBINED SCHEDULER EVENTS---------------------------
void move_enemy_objects(void) {
  movevilstar();
  movcoin();
  movminmagaz();
}

/*******************************************************************************
 *                              GAME HANDLERS                            
 *******************************************************************************
 */
void statehandler_gameinitnew(void)
{
  gamestate = STATE_STARTGAME;
  gameevent = EVENT_NONE;
 
  if(GAME_STORY_STRING_NUM < 4)
  {
    LCD_printstr8x5(gamestory_string[GAME_STORY_STRING_NUM], 0, 0);
    LCD_printstr8x5((uint8*)"�����...", 7, 78);
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
    Gamer.energymax = 4;
    Gamer.gasmask_fl = 0;
    Gamer.bombs = 0;
    Gamer.money = 999;
    Gamer.ln = 16;
    Gamer.cl = 0;
    
    Game.level_progress = 0;
    Game.Const1 = 2;
    GameFlags.gameflagsreg = 0b00001101;
    
    SchedAddEvent(createevilstar, PRD_EVELSTAR_CREATE);
    SchedAddEvent(movbullet, 20);
    SchedAddEvent(move_enemy_objects, PRD_ENEMY_MOVE);
    gameevent = EVENT_EXIT; 
  }
}

void statehandler_gameload(void)
{
  statehandler_gameinitnew();
}

void statehandler_gamerun(void)
{
  if(gamestate == STATE_PAUSEMENU)
  {
    SchedResumeEvent(createevilstar);
    SchedResumeEvent(movbullet);
    SchedResumeEvent(move_enemy_objects);
  }
  
  static uint8 deadgamerdrawcounter = GAMERDEATH_ANIMATION_PERIOD;
  
  gamestate = STATE_RUNGAME;
  if(Gamer.health > 0)
  {
    if(B4.BtnON) {
      B4.BtnON = 0;
      gameevent = EVENT_PAUSE;
    }
    else gameevent = EVENT_NONE;
  }
  else   // draw dead player
  {
    if(deadgamerdrawcounter >= (3 * (GAMERDEATH_ANIMATION_PERIOD / 4))){
      LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_dead_0_sprite);
       deadgamerdrawcounter--;
    }
    if(deadgamerdrawcounter < (3 * (GAMERDEATH_ANIMATION_PERIOD / 4) + (GAMERDEATH_ANIMATION_PERIOD % 4)) && deadgamerdrawcounter > 0) {
      LCD_printsprite(Gamer.ln, Gamer.cl, &gamer_dead_1_sprite);
      deadgamerdrawcounter--;
      IF_ANY_BTN_PRESS()
    }
    if(deadgamerdrawcounter == 0)
    {
      LCD_printstr8x5((uint8*)"�����������", 3, 30); 
      LCD_printstr8x5((uint8*)"��������!", 4, 36);
      IF_ANY_BTN_PRESS(
        deadgamerdrawcounter = GAMERDEATH_ANIMATION_PERIOD;
        gameevent = EVENT_EXIT;
      )
    }
  }
  
  movgamer();
  gunregen(PRD_GAMER_ENERGYREGEN);
  createbullet(BULLET_GENERATE_PERIOD);
  createbomb(BOMB_GENERATE_PERIOD);  
  movbomb();
  bullet_evilstar_collision();
  gamer_evilstar_collision();
  gamer_coin_collision();
  gamer_minmagaz_collision();
  bomb_evilstar_collision();
  drawevilstar();
  drawcoin();
  drawminmagaz();
  drawbullet();
  drawbomb(BOMB_ANIMATION_PERIOD);
  drawgamer();
  drawinfo();
  
  gameprogress(PRD_GAMEPROGRESS);  
}

void stateinit_gamestop(void)
{
  SchedRemoveEvent(createevilstar);
  SchedRemoveEvent(movbullet);
  SchedRemoveEvent(move_enemy_objects);
  for(uint8 i = 0; i < EVILSTAR_MAX; i++) EvilStar[i].state = 0;
  for(uint8 i = 0; i < COIN_MAX; i++) Coin[i].state = 0;
  for(uint8 i = 0; i < BULLET_MAX; i++) Bullet[i].state = 0;
  GAME_STORY_STRING_NUM = 0;
  Game.level_progress = 0;
  gamestate = STATE_MAINMENU;
  gameevent = EVENT_NONE;
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
  IF_ANY_BTN_PRESS(
          switch(coursorpos)
          {
            case COURS_POS_1:
              gameevent = EVENT_SELPOS_1;
              break;
            case COURS_POS_2:
              gameevent = EVENT_SELPOS_2;
              break;
            case COURS_POS_3:
              gameevent = EVENT_SELPOS_3;
              break;
            case COURS_POS_4:
              gameevent = EVENT_SELPOS_3;
              break;
            case COURS_POS_5:
              gameevent = EVENT_SELPOS_3;
              break;
          }
          somethinghappen = 1;
          )
  if(somethinghappen) somethinghappen = 0;
  else gameevent = EVENT_NONE;
}

void magaz_getevent(void)
{
  static uint8 somethinghappen = 0;
  IF_ANY_BTN_PRESS(
          switch(coursorpos)
          {
            case COURS_POS_1:
              gameevent = EVENT_EXIT;
              break;
            case COURS_POS_2:
              gameevent = EVENT_SELPOS_1;
              break;
            case COURS_POS_3:
              gameevent = EVENT_SELPOS_2;
              break;
            case COURS_POS_4:
              gameevent = EVENT_SELPOS_3;
              break;
            case COURS_POS_5:
              gameevent = EVENT_SELPOS_4;
              break;
          }
          somethinghappen = 1;
          )
  if(somethinghappen) somethinghappen = 0;
  else gameevent = EVENT_NONE;
}

void coursormovdisp(void)
{
  //move coursor
  if(gamestate != STATE_MAGAZIN)
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
      if(coursorpos >= COURS_POS_5) coursorpos = COURS_POS_5;
      else coursorpos++; 
    }
    if (joystick.left){
      joystick.left = 0;
      if(coursorpos != COURS_POS_1) coursorpos--; 
    }
  }
  //display coursor
  if(gamestate != STATE_MAGAZIN)
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
      case COURS_POS_5:  
        LCD_printmenucoursor(6, 4);
        break;
    }
  }
  else
  {
    switch(coursorpos)
    {
      case COURS_POS_1:
        LCD_printhorline(26, 63, 36);
        LCD_printhorline(26, 54, 36);
        LCD_printvertline(9, 54, 36);
        LCD_printvertline(9, 54, 62);
        break;
      case COURS_POS_2:
        LCD_printhorline(12, 61, 66);
        LCD_printhorline(12, 62, 66);
        LCD_printvertline(3, 58, 66);
        LCD_printvertline(3, 58, 78);
        break;
      case COURS_POS_3:  
        LCD_printhorline(18, 61, 78);
        LCD_printhorline(18, 62, 78);
        LCD_printvertline(3, 58, 78);
        LCD_printvertline(3, 58, 96);
        break;
      case COURS_POS_4:  
        LCD_printhorline(14, 61, 97);
        LCD_printhorline(14, 62, 97);
        LCD_printvertline(3, 58, 97);
        LCD_printvertline(3, 58, 111);
        break;
      case COURS_POS_5:  
        LCD_printhorline(14, 61, 111);
        LCD_printhorline(14, 62, 111);
        LCD_printvertline(3, 58, 111);
        LCD_printvertline(3, 58, 125);
        break;
    }
  }
}

void statehandler_menumain(void)
{
  gamestate = STATE_MAINMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"������������� �������", 0, 0);
  LCD_printstr8x5((uint8*)"����� ����", 2, 19);
  LCD_printstr8x5((uint8*)"��������� ����", 4, 19);
  LCD_printstr8x5((uint8*)"�����", 6, 19);
  coursormovdisp();
  if(gameevent == EVENT_SELPOS_2) coursorpos = COURS_POS_1; // coursor position when entering the load menu in "SLOT1"
}

void statehandler_menuload(void)
{ 
  gamestate = STATE_LOADMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"�������� ����", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"�����", 6, 19);
  coursormovdisp();
  if(gameevent == EVENT_SELPOS_3) coursorpos = COURS_POS_2; // coursor position when returning to the main menu in "LOAD"
}

void statehandler_menupause(void)
{
  if(gamestate == STATE_RUNGAME)
  {
    SchedPauseEvent(createevilstar);
    SchedPauseEvent(movbullet);
    SchedPauseEvent(move_enemy_objects);
  }
  gamestate = STATE_PAUSEMENU;
  
  menu_getevent();
  LCD_printstr8x5((uint8*)"�����", 0, 5);
  LCD_printstr8x5((uint8*)"���������", 2, 19);
  LCD_printstr8x5((uint8*)"��������� � ����", 4, 19);
  LCD_printstr8x5((uint8*)"�����", 6, 19);
  coursormovdisp();
}

void statehandler_menusave(void)
{
  gamestate = STATE_SAVEMENU;
  menu_getevent();
  LCD_printstr8x5((uint8*)"���������� ����", 0, 5);
  LCD_printstr8x5(gameslot1, 2, 19);
  LCD_printstr8x5(gameslot2, 4, 19);
  LCD_printstr8x5((uint8*)"�����", 6, 19);
  coursormovdisp();
  if(gameevent == EVENT_SELPOS_3) coursorpos = COURS_POS_1; // coursor position when returning to the pause menu in "SAVE"
}

void statehandler_gamesave(void)
{
  gameevent = EVENT_NONE;
}

//------------------magazin buygoods functions----------------------
void magaz_buybomb(void)
{
  if(Gamer.money >= BOMB_MONEY_COST && Gamer.bombs < 9){
    Gamer.money -= BOMB_MONEY_COST;
    Gamer.bombs++;
  }
  gameevent = EVENT_NONE;
}
void magaz_buygasmask(void)
{
  if(Gamer.money >= GASMASK_MONEY_COST && !Gamer.gasmask_fl){
    Gamer.money -= GASMASK_MONEY_COST;
    Gamer.gasmask_fl = 1;
  }
  gameevent = EVENT_NONE;
}
void magaz_buyenergy(void)
{
  if(Gamer.money >= BATTERY_MONEY_COST && Gamer.energymax < GAMER_ENERGY_MAX){
    Gamer.money -= BATTERY_MONEY_COST;
    Gamer.energymax += BATTERY_ENERGY_BUST;
    Gamer.energy = Gamer.energymax;
    if(Gamer.energymax > GAMER_ENERGY_MAX) Gamer.energymax = GAMER_ENERGY_MAX;
  }
  gameevent = EVENT_NONE;
}
void magaz_buyhealth(void)
{
  if(Gamer.money >= HEALTH_MONEY_COST && Gamer.health < GAMER_HEALTH_MAX){
    Gamer.money -= HEALTH_MONEY_COST;
    Gamer.health += HEALTH_REGEN; 
    if(Gamer.health > GAMER_HEALTH_MAX) Gamer.health = GAMER_HEALTH_MAX;
  }
  gameevent = EVENT_NONE;
}

//-----------------------------MAGAZIN MENU HANDLER---------------------------
void statehandler_magazin(void)
{
  if(gamestate == STATE_RUNGAME){
    SchedPauseEvent(createevilstar);
    SchedPauseEvent(movbullet);
    SchedPauseEvent(move_enemy_objects);
  }
  gamestate = STATE_MAGAZIN; 
  if(gameevent == EVENT_ENTERMAGAZ) // entering magazin animation
  {
    static uint8 j = MAGAZIN_INTROANIMATION_PERIOD;
    static uint8 k = MAGAZIN_FIRSTENTERINFO_PERIOD;
    if(GameFlags.FirstMagazEnter) {
      if(k == 0){
        LCD_printstr8x5(gamestory_string[4], 1, 0);
        LCD_printstr8x5((uint8*)"�����...", 7, 78);
        IF_ANY_BTN_PRESS(
                GameFlags.FirstMagazEnter = 0;
                k = MAGAZIN_FIRSTENTERINFO_PERIOD;
                )
      }
      else {
        IF_ANY_BTN_PRESS()
        k--;
      }
    }
    else {
      LCD_printsprite(8, (64 + (int8)j * 4), &magazin_sprite);
      j--;
      IF_ANY_BTN_PRESS()
      if(j == 0) {
        gameevent = EVENT_NONE;
        j = MAGAZIN_INTROANIMATION_PERIOD;
      }
    }
  }
  else
  {
    coursormovdisp();
    magaz_getevent();
    LCD_printsprite(8, 64, &magazin_sprite);
    LCD_printstr8x5((uint8*)"����:", 3, 94);
    LCD_printstr8x5((uint8*)"�������", 1, 80);
    LCD_printstr8x5((uint8*)"���.", 7, 38);
    uint8 price[5];
    switch(coursorpos)
    {
      case COURS_POS_1:
        LCD_printstr8x5((uint8*)"��\n��������!", 2, 0);
        break;
      case COURS_POS_2:
        LCD_printstr8x5((uint8*)"<�����!!!\n�������\n�������!", 2, 0);
        u16_to_str(price, BOMB_MONEY_COST, 2);
        LCD_printstr8x5((uint8*)price, 4, 94);
        break;
      case COURS_POS_3:
        LCD_printstr8x5((uint8*)"�����\n����������\n� �������?", 2, 0);
        u16_to_str(price, GASMASK_MONEY_COST, 2);
        LCD_printstr8x5((uint8*)price, 4, 94);
        break;
      case COURS_POS_4:
        LCD_printstr8x5((uint8*)"���������!", 2, 0);
        u16_to_str(price, BATTERY_MONEY_COST, 2);
        LCD_printstr8x5((uint8*)price, 4, 94);
        break;
      case COURS_POS_5:
        LCD_printstr8x5((uint8*)"�������!", 2, 0);
        u16_to_str(price, HEALTH_MONEY_COST, 2);
        LCD_printstr8x5((uint8*)price, 4, 94);
        break;
    }
  }
  #if 1
  if(Gamer.cl > 8) Gamer.cl -= 4; else Gamer.cl = 0;
  if(Gamer.ln < 40) Gamer.ln += 4; else Gamer.ln = 47;
  drawgamer();
  #endif
  drawinfo();
}

void stateinit_exitmagazin(void)
{
  static uint8 counter = 0;
  if(++counter < 15) LCD_printsprite((8 + counter * 4), 64, &magazin_sprite);
  else {
    counter = 0;
    gamestate = STATE_RUNGAME;
    gameevent = EVENT_NONE;
    SchedResumeEvent(createevilstar);
    SchedResumeEvent(movbullet);
    SchedResumeEvent(move_enemy_objects);    
  }
  drawgamer();
  drawinfo();
}
//--------------------------SYSTEM FUNCTIONS-------------------------------  
void system_events_period25ms(void) 
{
  movesmallstar(SMALLSTAR_MOVE_PERIOD);
}

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
  gamestate_transition_table[gamestate][gameevent]();
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
  gamestate = STATE_MAINMENU;
  gameevent = EVENT_NONE;
  coursorpos = COURS_POS_1;
  
  while (CFlags.RunGameFl)
  {
    SchedEventProcess();
  }
}