
#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "common.h"

#define      MAX_EVENT    20

static uint8 registredevents = 0;

typedef struct {
  void (*callfunc)(void);
  uint32   period;
  uint32   eventcounter;
} tEvent;

tEvent event[MAX_EVENT];

void SchedPeriodIncr(void);
uint8 AddEvent(void (*)(void), uint32);
void RemoveAllEvents(void);
void EventProcess(void);



#endif	

