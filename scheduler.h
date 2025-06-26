
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_CALLBACK    10
static uint8 registredcalls = 0;

typedef struct {
  void (*callfunc)();
  uint16   period;
  uint16   eventcounter;
} callback_t;

callback_t callback[MAX_CALLBACK];

void SchedPeriodIncr(void);
uint8 AddEvent(void*, uint16);
void ProcessTimerEvent(void);



#endif	

