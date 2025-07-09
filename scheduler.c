#include "scheduler.h"


uint8 AddEvent(void (*func)(void), uint32 period)
{
  event[registredevents].callfunc = func;
  event[registredevents].period = period;
  return registredevents++;
}

void RemoveAllEvents(void)
{
  registredevents = 0;
}

void EventProcess(void)
{
  for(uint8 i = 0; i < registredevents; i++)
  {
    if(event[i].eventcounter >= event[i].period)
    {
      event[i].eventcounter = 0;
      event[i].callfunc();
    }
  }
}

void SchedPeriodIncr(void)
{
  for(uint8 i = 0; i < registredevents; i++)
  {
    event[i].eventcounter++;
  }
}

void SaveEventCounter(void)
{
  for(uint8 i = 0; i < registredevents; i++)
  {
    eventcounter_temp[i] = event[i].eventcounter;   
  }
}

void LoadEventCounter(void)
{
  for(uint8 i = 0; i < registredevents; i++)
  {
    event[i].eventcounter = eventcounter_temp[i];   
  }
}

