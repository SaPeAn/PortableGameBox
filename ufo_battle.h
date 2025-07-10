
#ifndef UFO_BATTLE_H
#define	UFO_BATTLE_H

#include "common.h"

//------------------------------Game objects------------------------------------
typedef struct
{
  int    health;
  int    energy;
  int    energymax;
  uint32 energy_regenperiod;
  uint8  gasmask_fl;
  uint8  bombs;
  uint16 money;
  uint8  ln;
  int8   cl;
}tGamer;

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
//------------------------------Game vars & init--------------------------------

#define BULLET_MAX   10
#define EVILSTAR_MAX 10
#define COIN_MAX 10
#define EVILSTAR_DISTR_TTL  2
#define COIN_ANIMCOUNT  16

tGamer Gamer;
tBullet Bullet[BULLET_MAX] = {0};
tEvilStar Evil_Star[EVILSTAR_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};

uint8 Max_Bullet = BULLET_MAX;
uint8 Max_Evilstar = EVILSTAR_MAX;
uint8 Max_Coin = COIN_MAX;
uint32 counter = 0;


enum gamestate {
  game_mainmenu = 1,
  game_running = 2,
  game_paused = 3,
  game_exiting = 4
};
enum gamestate gamestate = game_mainmenu;

enum MainMenuPTR{
  GAME_MENU_START = 1,
  GAME_MENU_LOAD = 2,
  GAME_MENU_EXIT = 3
};
enum MainMenuPTR GameMainMenuPTR = 1;

enum PauseMenuPTR{
  GAME_PAUSE_SAVE = 1,
  GAME_PAUSE_RETURN = 2,
  GAME_PAUSE_EXIT = 3
};
enum PauseMenuPTR GamePauseMenuPTR = 1;

enum SaveLoadMenuPTR{
  GAME_SAVELOAD_GAME1 = 1,
  GAME_SAVELOAD_GAME2 = 2,
  GAME_SAVELOAD_EXIT = 3
};
enum SaveLoadMenuPTR GameSaveLoadMenuPTR = 1;
#define   SAVE     0
#define   LOAD     1


void ufobattle_init_newgame(void);
void ufobattle(void);
void gamemainmenu(void);
void gamepausemenu(void);
void gamesaveloadmenu(uint8);


#endif	/* UFO_BATTLE_H */

