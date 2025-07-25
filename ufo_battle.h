
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
}tGameProcess;

//------------------------------Game objects------------------------------------
typedef struct
{
  int8    health;
  int8    energy;
  int8    energymax;
  uint8  gasmask_fl;
  uint8  bombs;
  uint16 money;
  uint8  ln;
  int8   cl;
}tGamer;

typedef struct {
  uint8 state;
  uint8 ln;
  int8 cl;
}tBullet;

typedef struct{
  uint8  state;  // 0 - Comet disable; 1 - Comet enable; 2 - Comet distroed
  uint8  ln;
  int8   cl;
  uint8  distr_ttl_count;
}tEvilStar;

typedef struct{
  uint8 state;
  uint8 ln;
  int8  cl;
  uint8 animation_count;
}tCoin;

typedef struct{
    uint8 state;
    uint8 ln;
    int8  cl;
}tSmallStar;
//------------------------------Game vars & init--------------------------------

#define BULLET_MAX             8
#define EVILSTAR_MAX           5
#define COIN_MAX               6
#define SMALLSTAR_MAX          12
#define SMALLSTAR_MOVE_PER     2
#define SMALLSTAR_CREATE_PER   7
#define EVILSTAR_DISTR_TTL     2
#define COIN_ANIMATION_PERIOD  16
#define BULLET_ENERGY_COST     2

tGameProcess Game;
uint32 runtimecounter = 0;
tGamer Gamer;
tBullet Bullet[BULLET_MAX] = {0};
tEvilStar EvilStar[EVILSTAR_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};
tSmallStar SmallStar[SMALLSTAR_MAX] = {0};

uint16 PRD_EVELSTAR_CREATE = 1600;
uint8  PRD_ENEMY_MOVE = 18;
uint16 PRD_GAMER_ENERGYREGEN = 400;
uint8  PRD_GAMEPROGRESS = 50;
uint8  GAME_STORY_STRING_NUM = 0;

typedef enum {
  STATE_MAINMENU,
  STATE_LOADMENU,
  STATE_PAUSEMENU,
  STATE_SAVEMENU,
  STATE_MAGAZIN,
  STATE_MAX,
} tMENU_STATE;

typedef enum {
  COURS_POS_1,
  COURS_POS_2,
  COURS_POS_3,
  COURS_POS_4,        
} tCOURSOR_POS;

typedef enum{
  EVENT_NONE,
  EVENT_SELPOS_1,
  EVENT_SELPOS_2,
  EVENT_SELPOS_3,
  EVENT_SELPOS_4,
  EVENT_MAX,
} tMENU_EVENT;

tMENU_STATE menustate = STATE_MAINMENU;
tMENU_STATE menustate_prev = STATE_MAINMENU;
tCOURSOR_POS coursorpos = COURS_POS_1;
tMENU_EVENT menuevent = EVENT_NONE;
uint8 MENU_ENABLE = 1;

void handler_menumain(void);
void handler_gamenewstart(void);
void handler_menuload(void);
void handler_gameexit(void);
void handler_loadslot_0(void);
void handler_loadslot_1(void);
void handler_menupause(void);
void handler_menusave(void);
void handler_gameresume(void);
void handler_gamestop(void);
void handler_saveslot_0(void);
void handler_saveslot_1(void);
void handler_magazin(void);
void handler_gamepause(void);
void gamemenu(void);

void (*const menu_transition_table[STATE_MAX][EVENT_MAX])(void) = {
    [STATE_MAINMENU]        [EVENT_NONE]=              handler_menumain,
    [STATE_MAINMENU]        [EVENT_SELPOS_1]=          handler_gamenewstart,
    [STATE_MAINMENU]        [EVENT_SELPOS_2]=          handler_menuload,
    [STATE_MAINMENU]        [EVENT_SELPOS_3]=          handler_gameexit,
    
    [STATE_LOADMENU]        [EVENT_NONE]=              handler_menuload,
    [STATE_LOADMENU]        [EVENT_SELPOS_1]=          handler_loadslot_0,
    [STATE_LOADMENU]        [EVENT_SELPOS_2]=          handler_loadslot_1,
    [STATE_LOADMENU]        [EVENT_SELPOS_3]=          handler_menumain,
    
    [STATE_PAUSEMENU]       [EVENT_NONE] =             handler_menupause,
    [STATE_PAUSEMENU]       [EVENT_SELPOS_1]=          handler_menusave,
    [STATE_PAUSEMENU]       [EVENT_SELPOS_2]=          handler_gameresume,
    [STATE_PAUSEMENU]       [EVENT_SELPOS_3]=          handler_gamestop,
        
    [STATE_SAVEMENU]        [EVENT_NONE] =             handler_menusave,
    [STATE_SAVEMENU]        [EVENT_SELPOS_1]=          handler_saveslot_0,
    [STATE_SAVEMENU]        [EVENT_SELPOS_2]=          handler_saveslot_1,
    [STATE_SAVEMENU]        [EVENT_SELPOS_3]=          handler_menupause,

    [STATE_MAGAZIN]         [EVENT_NONE] =             handler_magazin,
    };

uint8 gameslot1[20] = "-осярн-";
uint8 gameslot2[20] = "-осярн-";


void ufobattle(void);

#endif	/* UFO_BATTLE_H */

