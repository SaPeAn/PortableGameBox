
#ifndef UFO_BATTLE_H
#define	UFO_BATTLE_H

#include "common.h"

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
  uint8  cl;
}tGamer;

tGamer Gamer;

void ufobattle_init(void);
void ufobattle(void);

#endif	/* UFO_BATTLE_H */

