
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_EVENT    10
#define      ON           1
#define      OFF          0

static uint8 registredevents = 0;
uint8 SchedulerCounter = OFF;

typedef struct {
  void (*callfunc)(void);
  uint16   period;
  uint16   eventcounter;
} tEvent;

tEvent event[MAX_EVENT];

void SchedPeriodIncr(void);
uint8 AddEvent(void (*)(void), uint32);
void RemoveAllEvents(void);
void EventProcess(void);
void SaveEventCounter(void);
void LoadEventCounter(void);


#endif	

