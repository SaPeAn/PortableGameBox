#include "scheduler.h"


uint8 SchedulerAddEvent(void (*func)(void), uint16 period)
{
  SchedulerEvent[SchedulerRegistredEvents].callfunc = func;
  SchedulerEvent[SchedulerRegistredEvents].period = period;
  SchedulerEvent[SchedulerRegistredEvents].active = ON;
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
    for(uint8 i = 0; i < SchedulerRegistredEvents; i++) {
      if(SchedulerEvent[i].active) 
        SchedulerEvent[i].eventcounter++;
    }
  }
}

void  SchedulerRemoveEvent(void (*func)(void))
{
    uint8 temp_fl = 0;
    for(uint8 i = 0; i < SchedulerRegistredEvents; i++){
        if(SchedulerEvent[i].callfunc == func || temp_fl) {
            temp_fl = 1;
            SchedulerEvent[i].callfunc = SchedulerEvent[i+1].callfunc;
        }
    }
    SchedulerRegistredEvents--;
}

void  SchedulerPauseEvent(void (*func)(void))
{
    for(uint8 i = 0; i < SchedulerRegistredEvents; i ++){
        if(SchedulerEvent[i].callfunc == func){
            SchedulerEvent[i].active = OFF;
        }
    }
}
void  SchedulerResumeEvent(void (*func)(void))
{
    for(uint8 i = 0; i < SchedulerRegistredEvents; i ++){
        if(SchedulerEvent[i].callfunc == func){
            SchedulerEvent[i].active = ON;
        }
    }
}