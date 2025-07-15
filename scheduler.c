#include "scheduler.h"


uint8 SchedulerAddEvent(void (*func)(void), uint16 period)
{
  SchedulerEvent[SchedulerRegistredEvents].callfunc = func;
  SchedulerEvent[SchedulerRegistredEvents].period = period;
  return SchedulerRegistredEvents++;
}

void SchedulerRemoveAllEvents(void)
{
  SchedulerRegistredEvents = 0;
}

void SchedulerEventProcess(void)
{
  for(uint8 i = 0; i < SchedulerRegistredEvents; i++)
  {
    if(SchedulerEvent[i].eventcounter >= SchedulerEvent[i].period)
    {
      SchedulerEvent[i].eventcounter = 0;
      SchedulerEvent[i].callfunc();
    }
  }
}

void SchedPeriodIncr(void)
{
  if(SchedulerCounterToggle){
    for(uint8 i = 0; i < SchedulerRegistredEvents; i++)
    {
      SchedulerEvent[i].eventcounter++;
    }
  }
}
