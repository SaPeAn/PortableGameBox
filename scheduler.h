
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_CALLBACK    10

static uint8 registredcalls = 0;

extern uint32 timestamp;

typedef struct {
  void (*callfunc)();
  uint32   period;
  uint32   startstamp;
  uint32   eventcounter;
} callback_t;

callback_t callback[MAX_CALLBACK];

void SchedPeriodIncr(void);
uint8 AddEvent(void*, uint32);
void ProcessTimerEvent(void);



#endif	

