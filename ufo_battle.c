#include "ufo_battle.h"
#include "drv_LCD_ST7565_SPI.h"
#include "drv_RTC_I2C.h"
#include "display_data.h"
#include "scheduler.h"

/*******************************************************************************
 *                              EVENT DESCRIPTIONS
 * *****************************************************************************
 */

void gameprogress(uint8 period)
{
  static uint8 counter = 0;
  if(counter != 0)
  {
    Game.level_progress++;
    if(Game.level_progress > Game.Const1){}
    if(Game.level_progress > Game.Const2){}
    if(Game.level_progress > Game.Const3){}
  }
  else{counter = period;}
  counter--;
}

void createevilstar(void) {
  static uint8 i = 0;
  if (EvilStar[i].state == 0) {
    EvilStar[i].state = 1;
    EvilStar[i].cl = 126;
    EvilStar[i].ln = getrand(40) + 8;
  }
  i++;
  if (i >= Max_Evilstar) i = 0;
}

void createcoin(tEvilStar Evil_Star) {
  static uint8 i = 0;
  if (getrand(2) < 2) return;
  if (Coin[i].state == 0) {
    Coin[i].state = 1;
    Coin[i].cl = Evil_Star.cl;
    Coin[i].ln = Evil_Star.ln;
    Coin[i].animation_count = COIN_ANIMCOUNT;
  }
  i++;
  if (i >= Max_Coin) i = 0;
}

void createbullet(void) {
  if (B2.BtnON || B2.HoldON || B2.StuckON) {
    B2.BtnON = 0;
    static uint8 i = 0;
    if (!Bullet[i].state && (Gamer.health > 0) && (Gamer.energy >= 2)) {
      Gamer.energy -= 2;
      Bullet[i].state = 1;
      Bullet[i].ln = Gamer.ln;
      Bullet[i].cl = Gamer.cl + 28;
      Sounds(400);
    }
    i++;
    if (i >= Max_Bullet) i = 0;
  }
}

void systemtasks(void) {
  check_btn_jstk();
  if (B4.BtnON) {
    B4.BtnON = 0;
    gamepausemenu();
  }
  batcheck();
}

void gunregen(void) //Energy regen
{
  if (Gamer.energy < Gamer.energymax) Gamer.energy++;
}

void movgamer(void) {
  if (joystick.oy > 140 && joystick.oy <= 210){Gamer.ln -= 1; if(Gamer.ln < 8) Gamer.ln = 8;}
  if (joystick.oy > 210 && joystick.oy <= 250){Gamer.ln -= 2;if(Gamer.ln < 8) Gamer.ln = 8;}
  if (joystick.oy > 250){Gamer.ln -= 4; if(Gamer.ln < 8)Gamer.ln = 8;}
  if (joystick.oy < 120 && joystick.oy >= 50){Gamer.ln += 1; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.oy < 50 && joystick.oy >= 10){Gamer.ln += 2; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.oy < 10){Gamer.ln += 4; if(Gamer.ln > 48)Gamer.ln = 48;}
  if (joystick.ox > 140 && joystick.ox <= 210){Gamer.cl += 1; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox > 210 && joystick.ox <= 250){Gamer.cl += 2; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox > 250){Gamer.cl += 4; if(Gamer.cl > 94)Gamer.cl = 94;}
  if (joystick.ox < 120 && joystick.ox >= 50){Gamer.cl -= 1; if(Gamer.cl < -8)Gamer.cl = -8;}
  if (joystick.ox < 50 && joystick.ox >= 10){Gamer.cl -= 2; if(Gamer.cl < -8) Gamer.cl = -8;}
  if (joystick.ox < 10){Gamer.cl -= 4; if(Gamer.cl < -8)Gamer.cl = -8;}
}

void movevilstar(void) {
  for (uint8 i = 0; i < Max_Evilstar; i++) {
    if (EvilStar[i].state == 1) {
      EvilStar[i].cl--;
      if ((EvilStar[i].cl < -29)) EvilStar[i].state = 0;
    }
  }
}

void movbullet(void) {
  for (uint8 i = 0; i < Max_Bullet; i++) {
    if (Bullet[i].state) {
      Bullet[i].cl += 1;
      if (Bullet[i].cl > 127) {
        Bullet[i].state = 0;
        Bullet[i].cl = 0;
      }
    }
  }
}

void movcoin(void) {
  for (uint8 i = 0; i < Max_Coin; i++) {
    if (Coin[i].state == 1) {
      Coin[i].cl -= 1;
      if (Coin[i].cl < -9) Coin[i].state = 0;
    }
  }
}

void bullet_evilstar_collision(void) {
  for (uint8 j = 0; j < Max_Bullet; j++) {
    for (uint8 i = 0; i < Max_Evilstar; i++) {
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
  for (uint8 i = 0; i < Max_Evilstar; i++) {
    if ((EvilStar[i].cl <= (Gamer.cl + 29)) && ((EvilStar[i].cl + 25) >= Gamer.cl) &&
            ((EvilStar[i].ln + 15) > Gamer.ln) && (EvilStar[i].ln < (Gamer.ln + 15)) &&
            (EvilStar[i].state == 1) && (Gamer.health > 0)) {
      EvilStar[i].state = 2;
      Gamer.health -= 4;
      Sounds(600);
    }
  }

  //Gamer's death hendler
  if (Gamer.health <= 0) {
    Sounds(600);
    gamestate = game_mainmenu;
  }
}

void gamer_coin_collision(void) {
  for (uint8 i = 0; i < Max_Coin; i++) {
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
  for (uint8 i = 0; i < Max_Evilstar; i++) {
    if (EvilStar[i].state == 1) {
      LCD_printsprite(EvilStar[i].ln, EvilStar[i].cl, &evilstar_sprite);
    }
    if (EvilStar[i].state == 2) {
      LCD_printsprite(EvilStar[i].ln, EvilStar[i].cl, &distr_evilstar_sprite);
      if (EvilStar[i].distr_ttl_count++ >= EVILSTAR_DISTR_TTL) {
        EvilStar[i].distr_ttl_count = 0;
        EvilStar[i].state = 0;
        createcoin(EvilStar[i]);
      }
    }
  }
}

void drawcoin(void) {
  for (uint8 i = 0; i < Max_Coin; i++) {
    if (Coin[i].state == 1) {
      Coin[i].animation_count--;
      if (Coin[i].animation_count >= (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln + 1, Coin[i].cl, &coin_sprite);
      if (Coin[i].animation_count < (COIN_ANIMCOUNT / 2)) LCD_printsprite(Coin[i].ln - 1, Coin[i].cl, &coin_sprite);
      if (Coin[i].animation_count == 0) Coin[i].animation_count = COIN_ANIMCOUNT;
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
  for (uint8 i = 0; i < Max_Bullet; i++) {
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

void check_collision(void) {
  bullet_evilstar_collision();
  gamer_evilstar_collision();
  gamer_coin_collision();
}

void draw_and_screenupdate(void) {
  drawevilstar();
  drawcoin();
  drawgamer();
  drawbullet();
  drawinfo();
  screenupdate();
}

void move_enemy_objects(void) {
  movevilstar();
  movcoin();
}

void cleargameobjects(void)
{
  for(uint8 i = 0; i < EVILSTAR_MAX; i++) EvilStar[i].state = 0;
  for(uint8 i = 0; i < COIN_MAX; i++) Coin[i].state = 0;
  for(uint8 i = 0; i < BULLET_MAX; i++) Bullet[i].state = 0;
}

/*******************************************************************************
 *                              GAME MENU HANDLERS                            
 *******************************************************************************
 */
//--------------------------MAIN MENU--------------------------
void gamemainmenu(void)
{
  SchedulerCounterToggle = OFF;
  while (1) {
    check_btn_jstk();
    if (joystick.down) {
      joystick.down = 0;
      GameMainMenuPTR++;
      if (GameMainMenuPTR > 3) GameMainMenuPTR = 3;
    }
    if (joystick.up) {
      joystick.up = 0;
      GameMainMenuPTR--;
      if (GameMainMenuPTR < 1) GameMainMenuPTR = 1;
    }
    switch (GameMainMenuPTR) {
      case GAME_MENU_START:
        LCD_printmenucoursor(2, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          ufobattle_startnewgame();
          return;
        }
        break;
      case GAME_MENU_LOAD:
        LCD_printmenucoursor(4, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          gamesaveloadmenu(LOAD);
        }
        break;
      case GAME_MENU_EXIT:
        LCD_printmenucoursor(6, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          CFlags.RunGameFl = 0;
          CFlags.MenuFl = 1;
          gamestate = game_exiting;
          return;
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
//--------------------------PAUSE MENU-----------------------------
void gamepausemenu(void) {
  SchedulerCounterToggle = OFF;
  while (1) {
    check_btn_jstk();
    if (joystick.down) {
      joystick.down = 0;
      GamePauseMenuPTR++;
      if (GamePauseMenuPTR > 3) GamePauseMenuPTR = 3;
    }
    if (joystick.up) {
      joystick.up = 0;
      GamePauseMenuPTR--;
      if (GamePauseMenuPTR < 1) GamePauseMenuPTR = 1;
    }

    switch (GamePauseMenuPTR) {
      case GAME_PAUSE_SAVE:
        LCD_printmenucoursor(2, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          gamesaveloadmenu(SAVE);
        }
        break;
      case GAME_PAUSE_RETURN:
        LCD_printmenucoursor(4, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          SchedulerCounterToggle = ON;
          return;
        }
        break;
      case GAME_PAUSE_EXIT:
        LCD_printmenucoursor(6, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          gamestate = game_mainmenu;
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
}
//-----------------------SAVE/LOAD MENU--------------------------
void gamesaveloadmenu(uint8 safe_load) {
  while (1) {
    check_btn_jstk();
    if (joystick.down) {
      joystick.down = 0;
      GameSaveLoadMenuPTR++;
      if (GameSaveLoadMenuPTR > 3) GameSaveLoadMenuPTR = 3;
    }
    if (joystick.up) {
      joystick.up = 0;
      GameSaveLoadMenuPTR--;
      if (GameSaveLoadMenuPTR < 1) GameSaveLoadMenuPTR = 1;
    }

    switch (GameSaveLoadMenuPTR) {
      case GAME_SAVELOAD_GAME1:
        LCD_printmenucoursor(2, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
        }
        break;
      case GAME_SAVELOAD_GAME2:
        LCD_printmenucoursor(4, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
        }
        break;
      case GAME_SAVELOAD_EXIT:
        LCD_printmenucoursor(6, 4);
        if (B2.BtnON) {
          B2.BtnON = 0;
          return;
        }
        break;
    }
    if (safe_load == SAVE) LCD_printstr8x5("ÑÎÕÐÀÍÅÍÈÅ ÈÃÐÛ", 0, 5);
    else LCD_printstr8x5("ÇÀÃÐÓÇÊÀ ÈÃÐÛ", 0, 5);
    LCD_printstr8x5("ÑÎÕÐ.ÈÃÐÀ 1", 2, 19);
    LCD_printstr8x5("ÑÎÕÐ.ÈÃÐÀ 2", 4, 19);
    LCD_printstr8x5("ÍÀÇÀÄ", 6, 19);
    LCD_bufupload_buferase();
    delay_ms(50);
  }
}

/*******************************************************************************
 *                              LOAD/SAVE/STARTNEW GAME 
 * *****************************************************************************
 */
void ufobattle_startnewgame(void) 
{
  cleargameobjects();
  randinit();
  
  Gamer.health = 24;
  Gamer.energy = 6;
  Gamer.energymax = 6;
  Gamer.energy_regenperiod = 200;
  Gamer.gasmask_fl = 0;
  Gamer.bombs = 0;
  Gamer.money = 0;
  Gamer.ln = 16;
  Gamer.cl = 0;
  
  RemoveAllEvents();
  AddEvent(systemtasks, 50);
  AddEvent(gunregen, Gamer.energy_regenperiod);
  AddEvent(createevilstar, 800);
  AddEvent(createbullet, 100);
  AddEvent(movgamer, 40);
  AddEvent(movbullet, 5);
  AddEvent(move_enemy_objects, 18);
  AddEvent(check_collision, 100);
  AddEvent(draw_and_screenupdate, 100);

  SchedulerCounterToggle = ON;
  gamestate = game_running;
}
/*******************************************************************************
 *                              MAIN ENTRY - GAME CYCLE                     
 *******************************************************************************
 */
void ufobattle(void)
{
  
  while (CFlags.RunGameFl)
  {
    switch (gamestate) {
      case game_mainmenu:
        gamemainmenu();
        break;
      case game_running:
        EventProcess();
        break;
      case game_exiting:
        CFlags.RunGameFl = 0;
        CFlags.MenuFl = 1;
        break;
    }
  }
  RemoveAllEvents();
  gamestate = game_mainmenu;
  
}