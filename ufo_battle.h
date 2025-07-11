
#ifndef UFO_BATTLE_H
#define	UFO_BATTLE_H

#include "common.h"


typedef struct {
  uint8 level;
  uint8 level_progress;
  uint8 difficulty;
  uint8 Const1;
  uint8 Const2;
  uint8 Const3;
}tGameProc;

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
  uint8 state;
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
  uint8 state;
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

tGameProc Game;
tGamer Gamer;
tBullet Bullet[BULLET_MAX] = {0};
tEvilStar EvilStar[EVILSTAR_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};

uint8 Max_Bullet = BULLET_MAX;
uint8 Max_Evilstar = EVILSTAR_MAX;
uint8 Max_Coin = COIN_MAX;
uint32 counter = 0;

enum states
{
    initial = 0,
    state_1,
    state_final
};

enum signals
{
    sign0,
    sign1,
    sign_N
};

enum states FSM_table[3][3] = {
    [initial][sign0] = state_1,
    [initial][sign1] = initial,
    [initial][sign_N] = state_1,
    [state_1][sign0] = initial,
    [state_1][sign1] = state_1,
    [state_1][sign_N] = state_final,
    [state_final][sign0] = initial,
    [state_final][sign1] = initial,
    [state_final][sign_N] = initial
};

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


void ufobattle_startnewgame(void);
void ufobattle(void);
void gamemainmenu(void);
void gamepausemenu(void);
void gamesaveloadmenu(uint8);
void gameprogress(uint8);

#endif	/* UFO_BATTLE_H */

