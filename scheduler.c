#include "scheduler.h"

extern uint32 timestamp;



uint8 AddEvent(void (*func), uint16 period)
{
  callback[registredcalls].callfunc = func;
  callback[registredcalls].period = period;
  return registredcalls++;
}

void SchedPeriodIncr(void)
{
  for(uint8 i = 0; i < registredcalls; i++)
  {
    callback[i].eventcounter++;
  }
}

void ProcessTimerEvent(void)
{
  for(uint8 i = 0; i < registredcalls; i++)
  {
    if(callback[i].eventcounter >= callback[i].period)
    {
      callback[i].eventcounter = 0;
      callback[i].callfunc();
    }
  }
}



