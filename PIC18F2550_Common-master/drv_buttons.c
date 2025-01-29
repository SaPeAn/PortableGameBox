#include "drv_buttons.h"

#define  HOLD_ON_DEL    100
#define  STUCK_ON_DEL   2000
 
btn_t CreateBtn(volatile uint8* Tris, volatile uint8* Port, volatile uint8* Lat, const uint8 inputbit, const uint8 outputbit, const uint32* timecounter)
{
  btn_t BTN;
  BTN.Port = Port;
  BTN.Lat = Lat;
  switch (inputbit)
{
    case 0: BTN.inputmask = 0b00000001; break;
    case 1: BTN.inputmask = 0b00000010; break;
    case 2: BTN.inputmask = 0b00000100; break;
    case 3: BTN.inputmask = 0b00001000; break;
    case 4: BTN.inputmask = 0b00010000; break;
    case 5: BTN.inputmask = 0b00100000; break;
    case 6: BTN.inputmask = 0b01000000; break;
    case 7: BTN.inputmask = 0b10000000; break;  
  }
  switch (outputbit)
  {
    case 0: BTN.outputmask = 0b11111110; break;
    case 1: BTN.outputmask = 0b11111101; break;
    case 2: BTN.outputmask = 0b11111011; break;
    case 3: BTN.outputmask = 0b11110111; break;
    case 4: BTN.outputmask = 0b11101111; break;
    case 5: BTN.outputmask = 0b11011111; break;
    case 6: BTN.outputmask = 0b10111111; break;
    case 7: BTN.outputmask = 0b01111111; break;  
  }
  *(Tris) |= BTN.inputmask;
  *(Tris) &= BTN.outputmask;
  *(Lat)  |= ~BTN.outputmask;
          
  BTN.timecounter = timecounter;
  BTN.BtnFl = 0;
  BTN.BtnON = 0;
  BTN.Toggle = 0;
  BTN.HoldON = 0;
  BTN.StuckON = 0;
  BTN.btnTimer = 0;
  return BTN;
}

void TestBtn(btn_t* btn)
{
  *(btn->Lat) &= btn->outputmask;
  
  if (!(*(btn->Port) & btn->inputmask) && !btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 50)) {
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
    btn->BtnFl = 1;
    btn->btnTimer = *(btn->timecounter); 
    btn->BtnON = 1;
  }
  if ((*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 50)) {
    btn->BtnFl = 0;
    btn->HoldON = 0;
    btn->StuckON = 0;
    btn->btnTimer = *(btn->timecounter);
  }
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > HOLD_ON_DEL) && ((*(btn->timecounter) - btn->btnTimer) <= STUCK_ON_DEL)) {
    btn->HoldON = 1;
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
  }
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > STUCK_ON_DEL)) {
    btn->HoldON = 0;
    btn->StuckON = 1;
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
  }
  
  *(btn->Lat) |= ~btn->outputmask;
}
