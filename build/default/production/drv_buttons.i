# 1 "drv_buttons.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "drv_buttons.c" 2
# 1 "./drv_buttons.h" 1








# 1 "./common.h" 1
# 12 "./common.h"
typedef unsigned char uint8;
typedef char int8;
typedef unsigned int uint16;
typedef int int16;
typedef unsigned long uint32;
typedef long int32;

uint32 timestamp = 0;
void Delay_ms(uint32);
uint8 getrand(uint8);
void randinit(void);
uint8 dig_to_smb(uint8);
void u16_to_str(uint8*, uint16, uint8);
# 9 "./drv_buttons.h" 2


typedef struct{
  volatile uint8* Port;
  volatile uint8* Lat;
  uint8 inputmask;
  uint8 outputmask;
  const uint32* timecounter;
  uint32 btnTimer;
  uint8 BtnFl;
  uint8 BtnON;
  uint8 Toggle;
  uint8 HoldON;
  uint8 StuckON;
}btn_t;

btn_t CreateBtn(volatile uint8*, volatile uint8*, volatile uint8*, const uint8, const uint8, const uint32*);
void TestBtn(btn_t*);
# 1 "drv_buttons.c" 2





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
  *(Lat) |= ~BTN.outputmask;

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
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 1000) && ((*(btn->timecounter) - btn->btnTimer) <= 2000)) {
    btn->HoldON = 1;
    if(btn->Toggle) btn->Toggle = 0;
    else btn->Toggle = 1;
  }
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 2000)) {
    btn->HoldON = 0;
    btn->StuckON = 1;
    if(btn->Toggle) btn->Toggle = 0;
    else btn->Toggle = 1;
  }

  *(btn->Lat) |= ~btn->outputmask;
}
