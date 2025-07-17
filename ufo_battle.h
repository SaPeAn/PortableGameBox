
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
  int8 cl;
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
  int8  cl;
  uint8 animation_count;
}tCoin;

typedef struct{
    uint8 state;
    uint8 ln;
    int8  cl;
    int8  dln;
    int8  dcl;
    int16  tg;
    uint8 animation_count;
}tSmallStar;
//------------------------------Game vars & init--------------------------------

#define BULLET_MAX   10
#define EVILSTAR_MAX 10
#define COIN_MAX 10
#define SMALLSTAR_MAX   27
#define EVILSTAR_DISTR_TTL  2
#define COIN_ANIMCOUNT  16

tGameProcess Game;
tGamer Gamer;
tBullet Bullet[BULLET_MAX] = {0};
tEvilStar EvilStar[EVILSTAR_MAX] = {0};
tCoin Coin[COIN_MAX] = {0};
tSmallStar SmallStar[SMALLSTAR_MAX] = {0};

uint8 Max_Bullet = BULLET_MAX;
uint8 Max_Evilstar = EVILSTAR_MAX;
uint8 Max_Coin = COIN_MAX;
uint32 counter = 0;

typedef enum {
  STATE_MMSTARTNEWGAME,
  STATE_MMLOADGAME,
  STATE_MMEXIT,
  STATE_GAMERUN,
  STATE_PMSAVE,
  STATE_PMRETURN,
  STATE_PMEXIT,
  STATE_LMSLOT1,
  STATE_LMSLOT2,
  STATE_LMRETURN,
  STATE_SMSLOT1,
  STATE_SMSLOT2,
  STATE_SMRETURN,
  STATE_MAX,
} tGAME_STATE;

typedef enum{
  EVENT_NONE,
  EVENT_JOYUP,
  EVENT_JOYDOWN,
  EVENT_B2PRESS,
  EVENT_B3PRESS,
  EVENT_B4PRESS,
  EVENT_GAMERDEATH,
  EVENT_MAX,
} tGAME_EVENT;

tGAME_STATE gamestate = STATE_MMSTARTNEWGAME;
tGAME_EVENT gameevent = EVENT_NONE;

void rungame(void);
void exitgame(void);
void stopgamehandler(void);
void loadslot1(void);
void loadslot2(void);
void saveslot1(void);
void saveslot2(void);

void startnewgame(void);
void mmloadgame(void);
void mmstartnewgame(void);
void lmslot1(void);
void mmexitgame(void);
void lmslot2(void);
void lmreturn(void);
void pmsave(void);
void pmreturn(void);
void pmexit(void);
void smslot1(void);
void smslot2(void);
void smreturn(void);
void smallstarmovedesplay(uint8);
void resumegamehandler(void);

void (*const transition_table[STATE_MAX][EVENT_MAX])(void) = {
    [STATE_MMSTARTNEWGAME] [EVENT_NONE]=        mmstartnewgame,
    [STATE_MMSTARTNEWGAME] [EVENT_B2PRESS]=     startnewgame,
    [STATE_MMSTARTNEWGAME] [EVENT_JOYDOWN]=     mmloadgame,
    [STATE_MMSTARTNEWGAME] [EVENT_JOYUP]=       mmstartnewgame,
    
    [STATE_MMLOADGAME]     [EVENT_NONE]=        mmloadgame,
    [STATE_MMLOADGAME]     [EVENT_B2PRESS]=     lmslot1,
    [STATE_MMLOADGAME]     [EVENT_JOYUP]=       mmstartnewgame,
    [STATE_MMLOADGAME]     [EVENT_JOYDOWN]=     mmexitgame,
    
    [STATE_MMEXIT]         [EVENT_NONE] =       mmexitgame,
    [STATE_MMEXIT]         [EVENT_B2PRESS] =    exitgame,
    [STATE_MMEXIT]         [EVENT_JOYUP] =      mmloadgame,
    [STATE_MMEXIT]         [EVENT_JOYDOWN] =    mmexitgame,
    
    [STATE_LMSLOT1]        [EVENT_NONE] =       lmslot1,
    [STATE_LMSLOT1]        [EVENT_B2PRESS] =    loadslot1,
    [STATE_LMSLOT1]        [EVENT_JOYDOWN] =    lmslot2,
    [STATE_LMSLOT1]        [EVENT_JOYUP] =      lmslot1,
    
    [STATE_LMSLOT2]        [EVENT_NONE] =       lmslot2,
    [STATE_LMSLOT2]        [EVENT_B2PRESS] =    loadslot2,
    [STATE_LMSLOT2]        [EVENT_JOYUP] =      lmslot1,
    [STATE_LMSLOT2]        [EVENT_JOYDOWN] =    lmreturn,
    
    [STATE_LMRETURN]       [EVENT_NONE] =       lmreturn,
    [STATE_LMRETURN]       [EVENT_B2PRESS] =    mmloadgame,
    [STATE_LMRETURN]       [EVENT_JOYUP] =      lmslot2,
    [STATE_LMRETURN]       [EVENT_JOYDOWN] =    lmreturn,
    
    [STATE_GAMERUN]        [EVENT_NONE] =       rungame,
    [STATE_GAMERUN]        [EVENT_B4PRESS] =    pmsave,
    [STATE_GAMERUN]        [EVENT_B3PRESS] =    pmsave,
    [STATE_GAMERUN]        [EVENT_GAMERDEATH] = stopgamehandler,
    
    [STATE_PMSAVE]         [EVENT_NONE] =       pmsave,
    [STATE_PMSAVE]         [EVENT_B2PRESS] =    smslot1,
    [STATE_PMSAVE]         [EVENT_JOYDOWN] =    pmreturn,
    [STATE_PMSAVE]         [EVENT_JOYUP] =      pmsave,
    
    [STATE_PMRETURN]       [EVENT_NONE] =       pmreturn,
    [STATE_PMRETURN]       [EVENT_B2PRESS] =    resumegamehandler,
    [STATE_PMRETURN]       [EVENT_JOYUP] =      pmsave,
    [STATE_PMRETURN]       [EVENT_JOYDOWN] =    pmexit,
    
    [STATE_PMEXIT]         [EVENT_NONE] =       pmexit,
    [STATE_PMEXIT]         [EVENT_B2PRESS] =    stopgamehandler,
    [STATE_PMEXIT]         [EVENT_JOYUP] =      pmreturn,
    [STATE_PMEXIT]         [EVENT_JOYDOWN] =    pmexit,
    
    [STATE_SMSLOT1]        [EVENT_NONE] =       smslot1,
    [STATE_SMSLOT1]        [EVENT_B2PRESS] =    saveslot1,
    [STATE_SMSLOT1]        [EVENT_JOYDOWN] =    smslot2,
    [STATE_SMSLOT1]        [EVENT_JOYUP] =      smslot1,
    
    [STATE_SMSLOT2]        [EVENT_NONE] =       smslot2,
    [STATE_SMSLOT2]        [EVENT_B2PRESS] =    saveslot2,
    [STATE_SMSLOT2]        [EVENT_JOYUP] =      smslot1,
    [STATE_SMSLOT2]        [EVENT_JOYDOWN] =    smreturn,
    
    [STATE_SMRETURN]       [EVENT_NONE] =       smreturn,
    [STATE_SMRETURN]       [EVENT_B2PRESS] =    pmsave,
    [STATE_SMRETURN]       [EVENT_JOYUP] =      smslot2,
    [STATE_SMRETURN]       [EVENT_JOYDOWN] =    smreturn,
};

#define   SAVE     0
#define   LOAD     1
#define   SLOT1    0
#define   SLOT2    1
uint8 gameslot1[20] = "-осярн-";
uint8 gameslot2[20] = "-осярн-";


void ufobattle(void);

#endif	/* UFO_BATTLE_H */

