
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_CALLBACK    20

static uint8 registredcalls = 0;

typedef struct {
  void (*callfunc)(void);
  uint32   period;
  uint32   startstamp;
  uint32   eventcounter;
} callback_t;

callback_t callback[MAX_CALLBACK];

void SchedPeriodIncr(void);
uint8 AddEvent(void (*)(void), uint32);
void ProcessTimerEvent(void);



#endif	

