
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
} tGameProcess;

//------------------------------Game objects------------------------------------

typedef struct {
  int8 health;
  int8 energy;
  int8 energymax;
  uint8 gasmask_fl;
  uint8 bombs;
  uint16 money;
  uint8 ln;
  int8 cl;
} tGamer;

typedef struct {
  uint8 state;
  uint8 ln;
  int8 cl;
} tBullet;

typedef struct {
  uint8 state; // 0 - Comet disable; 1 - Comet enable; 2 - Comet distroed
  uint8 ln;
  int8 cl;
  uint8 distr_ttl_count;
} tEvilStar;

typedef struct {
  uint8 state;
  uint8 ln;
  int8 cl;
  uint8 animation_count;
} tCoin;

typedef struct {
  uint8 state;
  uint8 ln;
  int8 cl;
} tSmallStar;
//------------------------------Game vars & init--------------------------------

#define BULLET_MAX                   8
#define EVILSTAR_MAX                 5
#define COIN_MAX                     6
#define SMALLSTAR_MAX                12
#define SMALLSTAR_MOVE_PERIOD        2
#define SMALLSTAR_CREATE_PERIOD      5
#define EVILSTAR_DEATHANIMATION_TTL  2
#define COIN_ANIMATION_PERIOD        10
#define BULLET_ENERGY_COST           2

#define DAMAGE_EVILSTAR        2
#define DAMAGE_BULLET          2
#define DAMAGE_BOMB            10
#define DAMAGE_BOMBSHARD       5
#define DAMAGE_GASCLOUD        1

tGameProcess Game;
uint32 runtimecounter = 0;
tGamer Gamer;
tBullet Bullet[BULLET_MAX] = {0};
tEvilStar EvilStar[EVILSTAR_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};
tSmallStar SmallStar[SMALLSTAR_MAX] = {0};

uint16 PRD_EVELSTAR_CREATE = 1600;
uint8 PRD_ENEMY_MOVE = 18;
uint16 PRD_GAMER_ENERGYREGEN = 400;
uint8 PRD_GAMEPROGRESS = 50;
uint8 GAME_STORY_STRING_NUM = 0;

struct GAMEPROCESFLAGS
{
  unsigned EVELSTAR_ENABLE  :1;
  unsigned CHEMIST_ENABLE   :1;
};
struct GAMEPROCESFLAGS GameFlags = {1, 1};


typedef enum {
  STATE_MAINMENU,
  STATE_LOADMENU,
  STATE_LOADGAME,
  STATE_PAUSEMENU,
  STATE_SAVEMENU,
  STATE_SAVEGAME,
  STATE_STARTGAME,
  STATE_RUNGAME,
  STATE_MAGAZIN,
  STATE_MAX,
} tMENU_STATE;

typedef enum {
  COURS_POS_1,
  COURS_POS_2,
  COURS_POS_3,
  COURS_POS_4,
} tCOURSOR_POS;

typedef enum {
  EVENT_NONE,
  EVENT_SELPOS_1,
  EVENT_SELPOS_2,
  EVENT_SELPOS_3,
  EVENT_SELPOS_4,
  EVENT_PAUSE,
  EVENT_EXIT,
  EVENT_ENTERMAGAZ,
  EVENT_GAMERDEATH,
  EVENT_MAX,
} tMENU_EVENT;

tMENU_STATE menustate = STATE_MAINMENU;
tMENU_STATE menustate_prev = STATE_MAINMENU;
tCOURSOR_POS coursorpos = COURS_POS_1;
tMENU_EVENT menuevent = EVENT_NONE;
uint8 MENU_ENABLE = 1;

void statehandler_menumain(void);
void statehandler_gameinitnew(void);
void statehandler_menuload(void);
void stateinit_gameexit(void);
void statehandler_gameload(void);
void statehandler_menupause(void);
void statehandler_menusave(void);
void stateinit_gamestop(void);
void statehandler_gamesave(void);
void statehandler_magazin(void);
void statehandler_gamerun(void);

void (*const menu_transition_table[STATE_MAX][EVENT_MAX])(void) = {
  [STATE_MAINMENU] [EVENT_NONE] = statehandler_menumain,
  [STATE_MAINMENU] [EVENT_SELPOS_1] = statehandler_gameinitnew,
  [STATE_MAINMENU] [EVENT_SELPOS_2] = statehandler_menuload,
  [STATE_MAINMENU] [EVENT_SELPOS_3] = stateinit_gameexit,

  [STATE_LOADMENU] [EVENT_NONE] = statehandler_menuload,
  [STATE_LOADMENU] [EVENT_SELPOS_1] = statehandler_gameload,
  [STATE_LOADMENU] [EVENT_SELPOS_2] = statehandler_gameload,
  [STATE_LOADMENU] [EVENT_SELPOS_3] = statehandler_menumain,

  [STATE_LOADGAME] [EVENT_NONE] = statehandler_gameload,
  [STATE_LOADGAME] [EVENT_EXIT] = statehandler_gamerun,
  
  [STATE_PAUSEMENU] [EVENT_NONE] = statehandler_menupause,
  [STATE_PAUSEMENU] [EVENT_SELPOS_1] = statehandler_menusave,
  [STATE_PAUSEMENU] [EVENT_SELPOS_2] = statehandler_gamerun,
  [STATE_PAUSEMENU] [EVENT_SELPOS_3] = stateinit_gamestop,

  [STATE_SAVEMENU] [EVENT_NONE] = statehandler_menusave,
  [STATE_SAVEMENU] [EVENT_SELPOS_1] = statehandler_gamesave,
  [STATE_SAVEMENU] [EVENT_SELPOS_2] = statehandler_gamesave,
  [STATE_SAVEMENU] [EVENT_SELPOS_3] = statehandler_menupause,
  
  [STATE_SAVEGAME] [EVENT_NONE] = statehandler_gamesave,
  [STATE_SAVEGAME] [EVENT_EXIT] = statehandler_menusave,

  [STATE_STARTGAME] [EVENT_NONE] = statehandler_gameinitnew,
  [STATE_STARTGAME] [EVENT_EXIT] = statehandler_gamerun,

  [STATE_RUNGAME] [EVENT_NONE] = statehandler_gamerun,
  [STATE_RUNGAME] [EVENT_PAUSE] = statehandler_menupause,
  [STATE_RUNGAME] [EVENT_EXIT] = stateinit_gamestop,
  [STATE_RUNGAME] [EVENT_ENTERMAGAZ] = statehandler_magazin,
  
  [STATE_MAGAZIN] [EVENT_NONE] = statehandler_magazin,
};

uint8 gameslot1[20] = "-осярн-";
uint8 gameslot2[20] = "-осярн-";


void ufobattle(void);

void gamemenu(void);

#endif	/* UFO_BATTLE_H */

