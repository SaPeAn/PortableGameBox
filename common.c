
#include "common.h"
#include "drv_LCD_ST7565_SPI.h"
#include <stdlib.h>
#include <xc.h>

/*----------------------------------UTILITIES-------------------------------*/
uint8 clamp(uint8 val, uint8 min, uint8 max)
{
  if(val > max) val = max;
  if(val < min) val = min;
  return val;
}

void delay_ms(uint32 ms)
{
  uint32 temp = timestamp;
  while((timestamp - temp) < ms);
}

void randinit(void)
{
  srand((uint8)timestamp);
}

uint8 getrand(uint8 N)
{
  return (rand() % (N + 1));
}

uint8 dig_to_smb(uint8 dig)
{
  switch (dig)
  {
    case 0: return '0';
    case 1: return '1'; 
    case 2: return '2';
    case 3: return '3'; 
    case 4: return '4';
    case 5: return '5'; 
    case 6: return '6'; 
    case 7: return '7'; 
    case 8: return '8';
    case 9: return '9';
  }
  return 0;
}

void u16_to_str(uint8* str, uint16 num, uint8 N)
{ 
  //sprintf((char*)str, "%u", num);
  
  str[0] = dig_to_smb((uint8)(num/10000));
  num %= 10000;
  str[1] = dig_to_smb((uint8)(num/1000));
  num %= 1000;
  str[2] = dig_to_smb((uint8)(num/100));
  num %= 100;
  str[3] = dig_to_smb((uint8)(num/10));
  str[4] = dig_to_smb((uint8)(num%10));
  str[5] = '\0';
  
  if(N == 10)
  {
    uint8 chars = 0;
    for(int i = 0; i < 6; i++)
    {
      if((str[i] == '0') && !chars) continue;
      str[chars] = str[i];
      chars++;
    }
    if(chars == 1) 
    {
      str[0] = '0';
      str[1] = '\0';
    }
  }
      
  if((N < 5) && (N > 0))
  {
    for(uint8 i = 0; i <= N; i++) 
      str[i] = str[5 - N + i];
  }
}
/*----------------------------------------------------------------------------*/

/*-------------------------------INITIALIZATION-------------------------------*/
void Interrupt_init(void)
{
  // INTCON
  GIE_GIEH = 1;  PEIE_GIEL = 1;  TMR0IE = 0;  INT0IE = 0;  RBIE = 0; // глоб.прер/глоб.прер высок.ур;  прер.периф./низк.ур.периф.прер; тмр0.переп.разр.прер; внеш.прер.разр; прер.портБ.прер.
  // INTCON2
  RBPU = 0;  INTEDG0 = 0;  INTEDG1 = 0;  INTEDG2 = 0;  TMR0IP = 0;  RBIP = 0; // портБ.пулап(0-pullUp En; 1-pullUp Dis); фронт.внеш.прер.0; фронт.внеш.прер.1; фронт.внеш.прер.2; тмр0прер.приоритет; портБпрер.приоритет.
  // INTCON3
  INT2IP = 0;  INT1IP = 0;  INT2IE = 0;  INT1IE = 0; // приор.внеш.прер2; приор.внеш.прер1; разр.внеш.прер2; разр.внеш.прер1;
  // PIE1 Peripherial Interrapt Enable 1
  ADIE = 0;  RCIE = 0;  TXIE = 0;  SSPIE = 0;  CCP1IE = 0;  TMR2IE = 0;  TMR1IE = 1;  
  // PIE2 Peripherial Interrapt Enable 2
  OSCFIE = 0;  CMIE = 0;  USBIE = 0;  EEIE = 0;  BCLIE = 0;  HLVDIE = 0;  TMR3IE = 0;  CCP2IE = 0;
  //  IPR1 PERIPHERAL INTERRUPT PRIORITY REGISTER 1
  ADIP = 0;  RCIP = 0;  TXIP = 0;  SSPIP = 0;  CCP1IP = 0;  TMR2IP = 0;  TMR1IP = 1;
  //  IPR2 PERIPHERAL INTERRUPT PRIORITY REGISTER 2
  OSCFIP = 0;  CMIP = 0;  USBIP = 0;  EEIP = 0;  BCLIP = 0;  HLVDIP = 0;  TMR3IP = 0;  CCP2IP = 0;
  // RCON RESET CONTROL REGISTER
  IPEN = 0;  SBOREN = 0; 
}

void timersinit(void)
{
  T0CON = 0b11000111;
  TMR0L = 32;
  TMR0H = 209;

  T1CON = 0b00000101;
  TMR1L = 241;
  TMR1H = 217;    
}

void commoninit(void)
{
  TRISB &= 0b11110111; // for Brightness
  TRISC &= 0b11111001; // RC2 - for Sounds, RC1 - Shut Down output
  LATCbits.LC2 = 0;
  LATCbits.LC1 = 1;
  brightPWM = EEPROM_readbyte(PWM_MEMADR);
}

void initbuttons(void)
{
  B1 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 6, &timestamp);
  B2 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 7, &timestamp);
  B3 = CreateBtn(&TRISB, &PORTB, &LATB, 5, 6, &timestamp);
  B4 = CreateBtn(&TRISB, &PORTB, &LATB, 5, 7, &timestamp);
}
/*----------------------------------------------------------------------------*/

/*------------------------------SYSTEM FUNCTIONS------------------------------*/
uint8 getbatlvl(uint8 Ub)
{
  uint8 lvl = (239 - Ub) / 8;
  static uint8 Umax = 240;
  static uint8 Umin = 228;
  static uint8 reslvl = 0;
  if(Ub <= 185) return 100; // bat to low, immediately shotdown code - 100
  Ub = clamp(Ub, 192, 240);
  if((Ub <= Umax) && (Ub >= Umin)) return reslvl;
  else 
  {
    switch(lvl)
    {
      case 0: Umin = 228; Umax = 240; reslvl = 0; break;
      case 1: Umin = 220; Umax = 236; reslvl = 1; break;
      case 2: Umin = 212; Umax = 228; reslvl = 2; break;
      case 3: Umin = 204; Umax = 220; reslvl = 3; break;
      case 4: Umin = 196; Umax = 212; reslvl = 4; break;
      case 5: Umin = 192; Umax = 204; reslvl = 5; break;
    }
  }
  return reslvl;
}

void batcheck(void)
{
  Ubat = adc_getval_an2();
  batlvl = getbatlvl(Ubat);
  if(batlvl == 100) ShutDownLB();
}
        
void ShutDownLB(void)
{
  LCD_bufupload_buferase();
  LATCbits.LC1 = 0;
  LCD_printstr8x5((uint8*)"Низкий заряд батареи!", 1, 0);
  LCD_printstr8x5((uint8*)"Устройство", 3, 0);  
  LCD_printstr8x5((uint8*)"сейчас выключится!", 5, 0);
  LCD_bufupload_buferase();
  while(1);
}

void ShutDown(void)
{
  LCD_bufupload_buferase();
  LATCbits.LC1 = 0;
  LCD_printstr8x5((uint8*)"Выключение...", 3, 0);
  LCD_bufupload_buferase();
  while(1);
}

void getbrightlvl(void)
{
  brightlvl = ((brightPWM - 10) / 30) - 1;
}

void decbright(void)
{
  if(brightPWM <= 40) brightPWM = 70; 
  brightPWM -=30;
  EEPROM_writebyte(PWM_MEMADR, brightPWM);
}

void incbright(void)
{
  if(brightPWM >= 250) brightPWM = 220; 
  brightPWM +=30;
  EEPROM_writebyte(PWM_MEMADR, brightPWM);
}

void BrightPWMgen(uint8 duty_cycle)
{
  PR2 = 0xFF;
  CCPR2L = duty_cycle;
  T2CON = 0b00000100;
  CCP2CON = 0b00001100;
}

void Sounds(uint16 delay)
{
  uint16 j;
  for(uint8 i = 0; i < (delay/10); i++)
  {  
    //LATCbits.LC2 = 0;
    j = delay;
    while(j--);
    //LATCbits.LC2 = 1;
    j = delay;
    while(j--);
  }
}

void rtcrawtobcd(void)
{
  rtcbcd.year = (uint8)((rtcraw.year / 10) << 4) | (rtcraw.year % 10);
  rtcbcd.month = (0x80 | (uint8)((rtcraw.month / 10) << 4)) | rtcraw.month % 10;
  rtcbcd.day = (uint8)((rtcraw.day / 10) << 4) | (rtcraw.day % 10);
  rtcbcd.weekday = rtcraw.weekday;
  rtcbcd.hour = (uint8)((rtcraw.hour / 10) << 4) | (rtcraw.hour % 10);
  rtcbcd.min = (uint8)((rtcraw.min / 10) << 4) | (rtcraw.min % 10);
  rtcbcd.sec = (uint8)((rtcraw.sec / 10) << 4) | (rtcraw.sec % 10);
}

void rtcbcdtoraw(void)
{
  rtcraw.year = (rtcbcd.year >> 4) * 10 + (rtcbcd.year & 0x0F);
  rtcraw.month = ((rtcbcd.month & 0x1F) >> 4) * 10 + (rtcbcd.month & 0x0F);
  rtcraw.day = ((rtcbcd.day & 0x3F) >> 4) * 10 + (rtcbcd.day & 0x0F);
  rtcraw.weekday = rtcbcd.weekday & 0x07;
  rtcraw.hour = ((rtcbcd.hour & 0x3F) >> 4) * 10 + (rtcbcd.hour & 0x0F);
  rtcraw.min = ((rtcbcd.min & 0x7F) >> 4) * 10 + (rtcbcd.min & 0x0F);
  rtcraw.sec = ((rtcbcd.sec & 0x7F) >> 4) * 10 + (rtcbcd.sec & 0x0F);
}
/*----------------------------------------------------------------------------*/

/*-----------------------------BUTTONS FUNCTIONS------------------------------*/
#define  BTN_HOLD_ON_DELAY    75
#define  BTN_STUCK_ON_DELAY   2000
 
tButton CreateBtn(volatile uint8* Tris, volatile uint8* Port, volatile uint8* Lat, const uint8 inputbit, const uint8 outputbit, const uint32* timecounter)
{
  tButton BTN;
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

void check_btn_jstk(void) //Test buttons and joystick
{
  TestBtn(&B1);
  TestBtn(&B2);
  TestBtn(&B3);
  TestBtn(&B4);
  joystick.ox = adc_getval_an0();
  joystick.oy = adc_getval_an1();
  checkjoydir();
}

void TestBtn(tButton* btn)
{
  *(btn->Lat) &= btn->outputmask;
  
  if (!(*(btn->Port) & btn->inputmask) && !btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 50)) {
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
    btn->BtnFl = 1;
    btn->btnTimer = *(btn->timecounter); 
    btn->BtnON = 1;
  }
  if ((*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > 75)) {
    btn->BtnFl = 0;
    btn->HoldON = 0;
    btn->StuckON = 0;
    btn->btnTimer = *(btn->timecounter);
  }
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > BTN_HOLD_ON_DELAY) && ((*(btn->timecounter) - btn->btnTimer) <= BTN_STUCK_ON_DELAY)) {
    btn->HoldON = 1;
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
  }
  if (!(*(btn->Port) & btn->inputmask) && btn->BtnFl && ((*(btn->timecounter) - btn->btnTimer) > BTN_STUCK_ON_DELAY)) {
    btn->HoldON = 0;
    btn->StuckON = 1;
    if(btn->Toggle) btn->Toggle = 0; 
    else btn->Toggle = 1;
  }
  
  *(btn->Lat) |= ~btn->outputmask;
}

uint8 adc_getval_an0()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00000001;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an1()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00000101;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

uint8 adc_getval_an2()
{
  TRISA |= 0b00000111;
  ADCON1 = 0b00001100;   
  ADCON2 = 0b00010010;
  ADCON0 = 0b00001001;
  ADCON0bits.ADON = 1;
  ADCON0bits.GODONE = 1;
  while(ADCON0bits.GODONE);
  return ADRESH;  
}

void getjoypos(void)
{
  joystick.ox = adc_getval_an0();
  joystick.oy = adc_getval_an1();
}

void checkjoydir(void)
{
    getjoypos();
    if(joystick.oy > 150 && joystick.joyFl == 0) {
        joystick.up = 1; 
        joystick.joyFl = 1;
    }
    if(joystick.oy < 100 && joystick.joyFl == 0) {
        joystick.down = 1; 
        joystick.joyFl = 1;
    }
    if(joystick.ox > 150 && joystick.joyFl == 0) {
        joystick.right = 1; 
        joystick.joyFl = 1;
    }
    if(joystick.ox < 100 && joystick.joyFl == 0) {
        joystick.left = 1; 
        joystick.joyFl = 1;
    }
    if(joystick.oy < 150 && joystick.oy > 100 && joystick.ox < 150 && joystick.ox > 100) joystick.joyFl = 0;
}
/*----------------------------------------------------------------------------*/

/*---------------------------SAVE/LOAD FUNCTIONS------------------------------*/

uint8 EEPROM_writebyte(uint8 adr, uint8 byte)
{
  EEADR = adr;
  EEDATA = byte;
  EECON1bits.EEPGD = 0;
  EECON1bits.CFGS = 0;
  EECON1bits.WREN = 1;
  INTCONbits.GIE = 0;
  EECON2 = 0x55;
  EECON2 = 0xAA;
  EECON1bits.WR = 1;
  INTCONbits.GIE = 1;
  EECON1bits.WREN = 0;
  return EECON1bits.WRERR;
}

uint8 EEPROM_readbyte(uint8 adr)
{
  EEADR = adr;
  EECON1bits.EEPGD = 0;
  EECON1bits.CFGS = 0;
  EECON1bits.RD = 1;
  return EEDATA;
}