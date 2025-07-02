
#ifndef UFO_BATTLE_H
#define	UFO_BATTLE_H

#ifdef	__cplusplus
extern "C" {
#endif
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

void ufobattle(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UFO_BATTLE_H */

