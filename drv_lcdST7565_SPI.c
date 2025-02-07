/******************************************************************************/
//      
//    LCD display
//    Controller - ST7565
//    
//    sofrware  hardware SPI
//    
/******************************************************************************/


#include "drv_lcdST7565_SPI.h"
#include <xc.h>
#include "display_data.h"
#include "drv_swi2cRTC.h"
#include <stdlib.h>

#define   RS      LATAbits.LA3    // 1-data/0-cmd
#define   RSE     LATAbits.LA4    //Display reset
#define   CS      LATCbits.LC6

#define  HW_SPI  // SPI type software(SW_SPI)/hardware(HW_SPI) 

/*-------------------------------SW SPI---------------------------------------*/
#ifdef SW_SPI

#define  SPI_TRANSMIT_FUNC      SPI_TX

extern void SPI_TX(uint8);

#define   SDO          LATCbits.LC7
#define   SCK          LATBbits.LB1
#define   CS           LATCbits.LC6
#define   SDO_tris     TRISCbits.RC7
#define   SCL_tris     TRISBbits.RB1
#define   CS_tris      TRISCbits.RC6

void SPI_init(void)
{
  SDO_tris = 0;
  SCL_tris = 0;
  CS_tris = 0;
  CS = 1;
  SCK = 1;
}
#endif
/*----------------------------------------------------------------------------*/

/*---------------------------------HW SPI-------------------------------------*/
#ifdef   HW_SPI
extern uint8 HW_SPI_TX(uint8);
#define  SPI_TRANSMIT_FUNC      HW_SPI_TX

void SPI_init(void)
{
  TRISBbits.RB1 = 0; // RB1 - SCK (Master mode))
  TRISBbits.RB0 = 1; // RB0 - SDI
  TRISCbits.RC7 = 0; // RC7 - SDO
  TRISCbits.RC6 = 0; // RC6 - CS
  LATCbits.LC6 = 1; // CS set
  SSPCON1 = 0b00110010; // Enables serial port([5] - 1); Idle state for clock is a high level (CKP) ([4] - 1); 
                        // SPI Master mode, clock =  ([3-0] - 0000(SPI Fosc/4); 0001 (SPI Fosc/16); 0010 (SPI Fosc/64))
  
  SSPSTATbits.SMP = 1;
  SSPSTATbits.CKE = 0;
}

uint8 SPI_transmit(uint8 bt)
  {
    SSPBUF = bt;
    while(!SSPSTATbits.BF);
    return SSPBUF;
  }

#endif
/*----------------------------------------------------------------------------*/

/*------------------------LCD FUNCTIONS---------------------------------------*/
void LCD_init(void)
{
  TRISAbits.RA3 = 0; //RSE
  TRISAbits.RA4 = 0; //RS
  RSE = 1;
  RS = 1;
  CS = 1;
  delay_ms(2);
  RSE = 0;
  delay_ms(2);
  RSE = 1;
  RS = 0;
  LCD_writebyte(0xA2 | 0);       // LCD Bias Set -- x=0 : 1/9 (default); x=1 :  1/7
  LCD_writebyte(0xA0 | 0);       // Segment Driver Direction Select 0->131(0);  Segment Driver Direction Select 131->0(1))
  LCD_writebyte(0xC0 | 8);       // Common Output Mode Select 0->63(0)); Common Output Mode Select 63->0(8)  
  LCD_writebyte(0x20 | 0x6);     // V5 Voltage Regulator Internal Resistor Ratio Set 0:3.0; 1:3.5; 2:4; 3:4.5; 4:5.0(default); 5:5.5; 6:6; 7:6.4;
  LCD_writebyte(0x28 | 0b111);   // Power Controller Set a=1 :  Booster circuit on; b=1 :  Voltage regulator circuit on; c=1 :  
                                 // Voltage follower circuit on; default: 000, must be 111
  LCD_writebyte(0x81);           // The Electronic Volume Mode Set (contrast) (default 0010 0000) - first byte (command id)
  LCD_writebyte(0x20);           // The Electronic Volume Mode Set (contrast) (default 0010 0000) - second byte (value)
  LCD_writebyte(0x40 | 0);       // Display Start Line Set (0-63)
  LCD_writebyte(0xB0 | 0);       // Page Address Set (0-7))
  LCD_writebyte(0x10 | 0);       // Column Address Set - first byte (0-15)
  LCD_writebyte(0x00 | 0);       // Column Address Set - second byte (0-15)
  LCD_writebyte(0xAE | 1);       // Display on(1) / Display off (0)
  LCD_writebyte(0xA6 | 0);       // Display Normal(0) / Display Reverse(1)
  RS = 1;
}

void LCD_setpagecolumn(uint8 pg, uint8 cl)
{
  uint8 clL = cl & 0x0F;
  uint8 clH = cl >> 4;
  LCD_sendcommands(3, (0xB0 | pg), (0x10 | clH), (0x00 | clL));  
}

void LCD_printsmb8x5(const uint8 ch, uint8 pg, uint8 cl)
{
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(char_8x5[ch], 5);
  LCD_setpagecolumn(pg, cl+5);
  LCD_writebyte(0x00);
}

uint8 LCD_printstr8x5(uint8 *str, uint8 pg, uint8 cl)
{
  static const uint8 str1[] = "NULL";
  if(str == NULL) str = str1;
  uint8 i = 0;
  while(str[i])
  {
    LCD_printsmb8x5(str[i], pg, cl);
    cl += 6;
    if(cl > 122) {pg++; cl = 0;}
    if(pg > 7) return 0;
    i++;
  }
  return i;
}

void LCD_erase(void)
{
  for(uint8 j = 0; j < 8; j++){ 
    LCD_sendcommands(3, (0xB0 + j), 0x10, 0x00); 
    if(j > 7) j = 0; 
    for(uint8 i = 0; i<128; i++) LCD_writebyte(0);
  }
  LCD_sendcommands(3, 0xB0, 0x10, 0x00);
}

void LCD_senddata(const uint8* byte, uint8 N)
{
  CS = 0;
  for(uint8 i = 0; i < N; i++) SPI_TRANSMIT_FUNC(byte[i]);
  CS = 1;
}

void LCD_sendcommands(uint8 N, ...)
{
  RS = 0;
  CS = 0;
  va_list arg;
  va_start(arg, N);
  for(uint8 i = 0; i < N; i++) {
  SPI_TRANSMIT_FUNC(va_arg(arg,uint8));
  }
  va_end(arg);
  RS = 1;
  CS = 1;
}

void LCD_writebyte(uint8 byte)
{
  CS = 0;
  SPI_TRANSMIT_FUNC(byte);
  CS = 1;
}
/*----------------------------------------------------------------------------*/

/*-----------------------------SYSTEM MENU ELEMENTS---------------------------*/
void LCD_printclockanddate(uint8 pg, uint8 cl)
{
  uint8 wday[3] = {0};
  uint8 month[4] = {0};
  uint8 day[3] = {dig_to_smb((rtcbcd.rtcpar.day & 0x30) >> 4), dig_to_smb(rtcbcd.rtcpar.day & 0x0F), '\0'};
  switch(rtcraw.rtcpar.weekday)
  {
    case 0: wday[0] = 'Â'; wday[1] = 'Ñ'; break;
    case 1: wday[0] = 'Ï'; wday[1] = 'Í'; break;
    case 2: wday[0] = 'Â'; wday[1] = 'Ò'; break;
    case 3: wday[0] = 'Ñ'; wday[1] = 'Ð'; break;
    case 4: wday[0] = '×'; wday[1] = 'Ò'; break;
    case 5: wday[0] = 'Ï'; wday[1] = 'Ò'; break;
    case 6: wday[0] = 'Ñ'; wday[1] = 'Á'; break;
  }
  switch(rtcraw.rtcpar.month)
  {
    case 0:  month[0] = 'ß'; month[1] = 'Í'; month[2] = 'Â'; break;
    case 1:  month[0] = 'Ô'; month[1] = 'Å'; month[2] = 'Â'; break;
    case 2:  month[0] = 'Ì'; month[1] = 'À'; month[2] = 'Ð'; break;
    case 3:  month[0] = 'À'; month[1] = 'Ï'; month[2] = 'Ð'; break;
    case 4:  month[0] = 'Ì'; month[1] = 'À'; month[2] = 'É'; break;
    case 5:  month[0] = 'È'; month[1] = 'Þ'; month[2] = 'Í'; break;
    case 6:  month[0] = 'È'; month[1] = 'Þ'; month[2] = 'Ë'; break;
    case 7:  month[0] = 'À'; month[1] = 'Â'; month[2] = 'Ã'; break;
    case 8:  month[0] = 'Ñ'; month[1] = 'Å'; month[2] = 'Í'; break;
    case 9:  month[0] = 'Î'; month[1] = 'Ê'; month[2] = 'Ò'; break;
    case 10: month[0] = 'Í'; month[1] = 'Î'; month[2] = 'ß'; break;
    case 11: month[0] = 'Ä'; month[1] = 'Å'; month[2] = 'Ê'; break;
  }
  uint8 hours[3] = {dig_to_smb(rtcraw.rtcpar.hour / 10), dig_to_smb(rtcraw.rtcpar.hour % 10), '\0'}; 
  uint8 colon[4] = {0x00,0x12,0x00}; // ':' colon
  uint8 minutes[3] = {dig_to_smb(rtcraw.rtcpar.min / 10), dig_to_smb(rtcraw.rtcpar.min % 10), '\0'};
  LCD_printstr8x5(day, pg, cl);
  LCD_printstr8x5(month, pg, cl + 14);
  LCD_printstr8x5(wday, pg, cl + 35);
  LCD_printstr8x5(hours, pg, cl + 49);
  LCD_setpagecolumn(pg, cl + 61);
  LCD_senddata(colon, 3);
  LCD_printstr8x5(minutes, pg, cl + 64);
}


void LCD_printbrightnes(uint8 pg, uint8 cl) //  size 26 column
{
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(bright_icon, 8);
  LCD_setpagecolumn(pg, cl+9);
  LCD_senddata(bright_lvl[brightlvl], 15);
}

void LCD_printbatlevel(uint8 lvl, uint8 pg, uint8 cl)
{
  if(lvl == 100) lvl = 5; // 100 -shutdown code
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(battary_2[lvl], 20);
}

void LCD_printmenupointer(uint8 pg, uint8 cl)
{
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(menu_pointer[0], 11);
  LCD_setpagecolumn(pg + 1, cl);
  LCD_senddata(menu_pointer[1], 11);
}

void LCD_printbutselhint(uint8 hintnum, uint8 pg, uint8 cl)
{
  for(uint8 j = 0; j< 4; j++)
  {
    LCD_setpagecolumn(pg + j, cl);
    CS = 0;
    for(uint8 i = 0; i < 32; i++) SPI_TRANSMIT_FUNC(but_sel_hint[hintnum][(i * 4 + j)]);
    CS = 1;
  }
}

void LCD_printvertline(uint8 linelength, uint8 startstring, uint8 cl)
{
  if((linelength - startstring) > 63) return;
  uint8 startpg = startstring / 8;
  uint8 bitshifting = (startstring % 8);
  uint8 lengthinpages = (linelength - (8 - bitshifting)) / 8;  
  uint8 temp = 0xFF << bitshifting;
  LCD_setpagecolumn(startpg, cl);
  LCD_senddata(&temp, 1);
  temp = 0xFF;
  for(uint8 i = 0; i < lengthinpages; i++)
  {
    LCD_setpagecolumn(startpg + 1 + i, cl);
    LCD_senddata(&temp, 1);
  } 
  temp = 0xFF >> (8 - (linelength - (8 - bitshifting)) % 8);
  LCD_setpagecolumn(startpg + 1 + lengthinpages, cl);
  LCD_senddata(&temp, 1);
}

void LCD_printhortline(uint8 linelength, uint8 startstring, uint8 cl)
{
  if((linelength - cl) > 127) return;
  uint8 startpg = startstring / 8;
  uint8 bitshifting = (startstring % 8); 
  uint8 temp = 0x1 << bitshifting;
  LCD_setpagecolumn(startpg, cl);
  for(uint8 i = 0; i < linelength; i++)
  {
    LCD_setpagecolumn(startpg, cl + i);
    LCD_senddata(&temp, 1);
  }
}
/*----------------------------------------------------------------------------*/

/*------------------------------GAME OBJECTS----------------------------------*/
void LCD_print_piu(uint8 page, uint8 col)
{
  LCD_setpagecolumn(page, col);
  LCD_senddata(tar_bullet, 8);
}

void LCD_print_ufo(uint8 page, uint8 col)
{
  LCD_setpagecolumn(page, col);
  LCD_senddata(tarelka[0], 27);
  LCD_setpagecolumn((page+1), col);
  LCD_senddata(tarelka[1], 27);
}

void LCD_print_cometa(uint8 page, uint8 col)
{
  LCD_setpagecolumn(page, col);
  LCD_senddata(cometa[0], 28);
  LCD_setpagecolumn((page+1), col);
  LCD_senddata(cometa[1], 28);
}

void LCD_print_distr_cometa(uint8 page, uint8 col)
{
  LCD_setpagecolumn(page, col);
  LCD_senddata(distr_cometa[0], 28);
  LCD_setpagecolumn((page+1), col);
  LCD_senddata(distr_cometa[1], 28);
}

/*----------------------------------------------------------------------------*/

