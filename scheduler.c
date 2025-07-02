#include "scheduler.h"


uint8 AddEvent(void (*func), uint32 period)
{
  callback[registredcalls].callfunc = func;
  callback[registredcalls].period = period;
  return registredcalls++;
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

void SchedPeriodIncr(void)
{
  for(uint8 i = 0; i < registredcalls; i++)
  {
    callback[i].eventcounter++;
  }
}




