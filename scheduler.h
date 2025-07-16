
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_EVENT    10
#define      ON           1
#define      OFF          0

static uint8 SchedulerRegistredEvents = 0;
uint8 SchedulerCounterToggle = OFF;

typedef struct {
  void     (*callfunc)(void);
  uint16   period;
  uint16   eventcounter;
  uint8    active;
} tEvent;

tEvent SchedulerEvent[MAX_EVENT];

void  SchedPeriodIncr(void);
uint8 SchedulerAddEvent(void (*)(void), uint16);
void  SchedulerRemoveEvent(void (*)(void));
void  SchedulerRemoveAllEvents(void);
void  SchedulerPauseEvent(void (*)(void));
void  SchedulerResumeEvent(void (*)(void));
void  SchedulerEventProcess(void);


#endif	

