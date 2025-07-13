
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_EVENT    10
#define      ON           1
#define      OFF          0

static uint8 SchedulerRegistredEvents = 0;
uint8 SchedulerCounterToggle = OFF;

typedef struct {
  void (*callfunc)(void);
  uint16   period;
  uint16   eventcounter;
} tEvent;

tEvent SchedulerEvent[MAX_EVENT];

void  SchedPeriodIncr(void);
uint8 SchedulerAddEvent(void (*)(void), uint32);
void  SchedulerRemoveAllEvents(void);
void  SchedulerEventProcess(void);


#endif	

