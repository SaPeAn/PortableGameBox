
#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "common.h"    
    
typedef struct{
  volatile uint8*  Port;
  volatile uint8*  Lat;
  uint8            inputmask;
  uint8            outputmask;
  const uint32*    timecounter;
  uint32           btnTimer;
  uint8            BtnFl;
  uint8            BtnON;
  uint8            Toggle;
  uint8            HoldON;
  uint8            StuckON;
}btn_t;

btn_t CreateBtn(volatile uint8*, volatile uint8*, volatile uint8*, const uint8, const uint8, const uint32*);
void TestBtn(btn_t*);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

