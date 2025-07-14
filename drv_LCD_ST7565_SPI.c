/******************************************************************************/
//      
//    LCD display
//    Controller - ST7565
//    
//    sofrware  hardware SPI
//    
/******************************************************************************/

#include "drv_LCD_ST7565_SPI.h"
#include <xc.h>
#include "display_data.h"
#include "drv_RTC_I2C.h"
#include <stdlib.h>
#include <xc8debug.h>

#define    BUF_EN   // BUF_EN - working through the buffer, BUF_DIS - direct 


#define   RS      LATAbits.LA3    // 1-data/0-cmd
#define   RSE     LATAbits.LA4    //Display reset
#define   CS      LATCbits.LC6

#define  HW_SPI  // SPI type software(SW_SPI)/hardware(HW_SPI) 

uint8 dispbuffer[8][128] = {0};
uint8 bufpg = 0;
uint8 bufcl = 0;

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

void SPI_init(void) {
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

void SPI_init(void) {
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
#endif
/*----------------------------------------------------------------------------*/

/*------------------------LCD FUNCTIONS---------------------------------------*/
void LCD_init(void) {
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
  CS = 0;
  SPI_TRANSMIT_FUNC(0xA2 | 0); // LCD Bias Set -- x=0 : 1/9 (default); x=1 :  1/7
  SPI_TRANSMIT_FUNC(0xA0 | 0); // Segment Driver Direction Select 0->131(0);  Segment Driver Direction Select 131->0(1))
  SPI_TRANSMIT_FUNC(0xC0 | 8); // Common Output Mode Select 0->63(0)); Common Output Mode Select 63->0(8)  
  SPI_TRANSMIT_FUNC(0x20 | 0x6); // V5 Voltage Regulator Internal Resistor Ratio Set 0:3.0; 1:3.5; 2:4; 3:4.5; 4:5.0(default); 5:5.5; 6:6; 7:6.4;
  SPI_TRANSMIT_FUNC(0x28 | 0b111); // Power Controller Set a=1 :  Booster circuit on; b=1 :  Voltage regulator circuit on; c=1 :  
  // Voltage follower circuit on; default: 000, must be 111
  SPI_TRANSMIT_FUNC(0x81); // The Electronic Volume Mode Set (contrast) (default 0010 0000) - first byte (command id)
  SPI_TRANSMIT_FUNC(0x20); // The Electronic Volume Mode Set (contrast) (default 0010 0000) - second byte (value)
  SPI_TRANSMIT_FUNC(0x40 | 0); // Display Start Line Set (0-63)
  SPI_TRANSMIT_FUNC(0xB0 | 0); // Page Address Set (0-7))
  SPI_TRANSMIT_FUNC(0x10 | 0); // Column Address Set - first byte (0-15)
  SPI_TRANSMIT_FUNC(0x00 | 0); // Column Address Set - second byte (0-15)
  SPI_TRANSMIT_FUNC(0xAE | 1); // Display on(1) / Display off (0)
  SPI_TRANSMIT_FUNC(0xA6 | 0); // Display Normal(0) / Display Reverse(1)
  CS = 1;
  RS = 1;
}

void LCD_setpagecolumn(uint8 pg, uint8 cl) {
#ifdef BUF_EN
  bufpg = pg;
  bufcl = cl;
#else
  uint8 clL = cl & 0x0F;
  uint8 clH = cl >> 4;
  LCD_sendcommands(3, (0xB0 | pg), (0x10 | clH), (0x00 | clL));
#endif
}

void LCD_printsmb8x5(const char ch, uint8 pg, uint8 cl) {
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(char_8x5[ch], 5);
  LCD_setpagecolumn(pg, cl + 5);
  LCD_writebyte(0x00);
}

uint8 LCD_printstr8x5(char *str, uint8 pg, uint8 cl) {
  if (str == NULL) str = str_null;
  uint8 i = 0;
  while (str[i]) {
    LCD_printsmb8x5(str[i], pg, cl);
    cl += 6;
    if (cl > 122) {
      pg++;
      cl = 0;
    }
    if (pg > 7) return 0;
    i++;
  }
  return i;
}

void LCD_erasestring(uint8 length, uint8 pg, uint8 cl) {
  LCD_setpagecolumn(pg, cl);
  for (uint8 i = 0; i < length; i++) LCD_writebyte(0x00);
}

void LCD_bufupload_buferase(void) {
#ifdef BUF_EN
  LCDbuf_upload();
  LCDbuf_erase();
#else
  for (uint8 j = 0; j < 8; j++) {
    LCD_sendcommands(3, (0xB0 + j), 0x10, 0x00);
    if (j > 7) j = 0;
    for (uint8 i = 0; i < 128; i++) LCD_writebyte(0);
  }
  LCD_sendcommands(3, 0xB0, 0x10, 0x00);
#endif
}

void LCD_senddata(const char* byte, uint8 N) {
#ifdef BUF_EN
  for (uint8 i = 0; i < N; i++) {
    dispbuffer[bufpg][bufcl + i] |= byte[i];
    if (bufcl > 127) bufpg++;
    if (bufpg > 7) return;
  }
#else
  CS = 0;
  for (uint8 i = 0; i < N; i++) SPI_TRANSMIT_FUNC(byte[i]);
  CS = 1;
#endif
}

void LCD_sendcommands(uint8 N, ...) {
  RS = 0;
  CS = 0;
  va_list arg;
  va_start(arg, N);
  for (uint8 i = 0; i < N; i++) {
    SPI_TRANSMIT_FUNC(va_arg(arg, uint8));
  }
  va_end(arg);
  RS = 1;
  CS = 1;
}

void LCD_writebyte(uint8 byte) {
#ifdef BUF_EN
  dispbuffer[bufpg][bufcl] |= byte;
  bufcl++;
#else
  CS = 0;
  SPI_TRANSMIT_FUNC(byte);
  CS = 1;
#endif
}
/*----------------------------------------------------------------------------*/

/*------------------------WORKING THROUGH THE BUFFER--------------------------*/
void LCDbuf_upload(void) {
  for (uint8 j = 0; j < 8; j++) {
    LCD_sendcommands(3, (0xB0 + j), 0x10, 0x00);
    CS = 0;
    for (uint8 i = 0; i < 128; i++) SPI_TRANSMIT_FUNC(dispbuffer[j][i]);
    CS = 1;
  }
}

void LCDbuf_erase(void) {
  for (uint8 j = 0; j < 8; j++)
    for (uint8 i = 0; i < 128; i++) dispbuffer[j][i] = 0;
}
/*----------------------------------------------------------------------------*/

/*-----------------------------SYSTEM MENU ELEMENTS---------------------------*/

void LCD_printweekday(uint8 wdaynum, uint8 pg, uint8 cl) {
  LCD_printstr8x5(weekday[wdaynum], pg, cl);
}

void LCD_printmonth(uint8 mon, uint8 pg, uint8 cl) {
  LCD_printstr8x5(month[mon - 1], pg, cl);
}

void LCD_printclockanddate(uint8 pg, uint8 cl) {
  char wday[3] = {0};
  char month[4] = {0};
  char day[3] = {dig_to_smb((rtcbcd.day & 0x30) >> 4), dig_to_smb(rtcbcd.day & 0x0F), '\0'};
  char hours[3] = {dig_to_smb(rtcraw.hour / 10), dig_to_smb(rtcraw.hour % 10), '\0'};
  char colon[4] = {0x00, 0x12, 0x00}; // ':' colon
  char minutes[3] = {dig_to_smb(rtcraw.min / 10), dig_to_smb(rtcraw.min % 10), '\0'};
  LCD_printstr8x5(day, pg, cl);
  LCD_printmonth(rtcraw.month, pg, cl + 14);
  LCD_printweekday(rtcraw.weekday, pg, cl + 35);
  LCD_printstr8x5(hours, pg, cl + 49);
  LCD_setpagecolumn(pg, cl + 61);
  LCD_senddata(colon, 3);
  LCD_printstr8x5(minutes, pg, cl + 64);
}

void LCD_printbrightnes(uint8 pg, uint8 cl) //  size 26 column
{
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(bright_icon, 8);
  LCD_setpagecolumn(pg, cl + 9);
  LCD_senddata(bright_lvl[brightlvl], 15);
}

void LCD_printbatlevel(uint8 lvl, uint8 pg, uint8 cl) {
  if (lvl == 100) lvl = 5; // 100 -shutdown code
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(battary_2[lvl], 20);
}

void LCD_printmenucoursor(uint8 pg, uint8 cl) {
  LCD_setpagecolumn(pg, cl);
  LCD_senddata(menu_pointer, 8);
}

void LCD_printbutselhint(uint8 hintnum, uint8 pg, uint8 cl) {
  for (uint8 j = 0; j < 4; j++) {
    LCD_setpagecolumn(pg + j, cl);
    for (uint8 i = 0; i < 32; i++) LCD_writebyte(but_sel_hint[hintnum][(i * 4 + j)]);
  }
}

void LCD_printvertline(uint8 linelength, uint8 startline, uint8 cl) {
  if ((linelength - startline) > 63) return;
  uint8 startpg = startline / 8;
  uint8 bitshifting = (startline % 8);
  uint8 lengthinpages = (linelength - (8 - bitshifting)) / 8;
  uint8 temp = (uint8) (0xFF << bitshifting);
  LCD_setpagecolumn(startpg, cl);
  LCD_senddata(&temp, 1);
  temp = 0xFF;
  for (uint8 i = 0; i < lengthinpages; i++) {
    LCD_setpagecolumn(startpg + 1 + i, cl);
    LCD_senddata(&temp, 1);
  }
  temp = 0xFF >> (8 - (linelength - (8 - bitshifting)) % 8);
  LCD_setpagecolumn(startpg + 1 + lengthinpages, cl);
  LCD_senddata(&temp, 1);
}

void LCD_printhorline(uint8 linelength, uint8 startstring, uint8 cl) {
  if ((linelength - cl) > 127) return;
  uint8 startpg = startstring / 8;
  uint8 bitshifting = (startstring % 8);
  uint8 temp = (uint8) (0x1 << bitshifting);
  LCD_setpagecolumn(startpg, cl);
  for (uint8 i = 0; i < linelength; i++) {
    LCD_setpagecolumn(startpg, cl + i);
    LCD_senddata(&temp, 1);
  }
}
/*----------------------------------------------------------------------------*/

/*------------------------------GAME OBJECTS----------------------------------*/
void LCD_printsprite(uint8 startline, int8 startcolumn, tSprite * const Sprite) {
  int8 columns_max = 0;
  uint16 m = 0, mprev = 0;
  uint8 column_shift = 0;
  if (startcolumn < 0) {
    bufcl = 0;
    columns_max = Sprite->columns + startcolumn;
    if (columns_max < 0) columns_max = 0;
    m = (-startcolumn) * Sprite->pages;
    column_shift = -startcolumn;
  } 
  else {
    bufcl = startcolumn;
    columns_max = (((int16)startcolumn + (int16)Sprite->columns) > 127) ? (127 - startcolumn) : Sprite->columns;
  }
  bufpg = startline / 8;
  uint8 shift = startline % 8;
  switch (Sprite->direct) {
    case columns_first:
      for (uint8 j = 0; j < columns_max; j++) {
        for (uint8 i = 0; i < (shift ? (Sprite->pages + 1) : Sprite->pages); i++) {
          if (i == 0) {
            dispbuffer[bufpg + i][bufcl + j] |= Sprite->sprite[m] << shift;
            mprev = m;
            m++;
          }
          if ((i > 0) && (i < Sprite->pages)) {
            dispbuffer[bufpg + i][bufcl + j] |= (Sprite->sprite[mprev] >> (8 - shift)) | (Sprite->sprite[m] << shift);
            mprev = m;
            m++;
          }
          if (i == Sprite->pages) {
            dispbuffer[bufpg + i][bufcl + j] |= Sprite->sprite[mprev] >> (8 - shift);
          }
        }
      }
      break;
    case lines_first:
      for (uint8 i = 0; i < (shift ? (Sprite->pages + 1) : Sprite->pages); i++) {
        for (uint8 j = 0; j < columns_max; j++) {
          if (i == 0) {
            dispbuffer[bufpg + i][bufcl + j] |= Sprite->sprite[j + column_shift] << shift;
          }
          if ((i > 0) && (i < Sprite->pages)) {
            dispbuffer[bufpg + i][bufcl + j] |= (Sprite->sprite[(i - 1) * Sprite->columns + j + column_shift] >> (8 - shift)) | (Sprite->sprite[i * Sprite->columns + j + column_shift] << shift);
          }
          if (i == Sprite->pages) {
            dispbuffer[bufpg + i][bufcl + j] |= Sprite->sprite[(i - 1) * Sprite->columns + j + column_shift] >> (8 - shift);
          }
        }
      }
      break;
  }
}

void LCD_printgamestatbar(tGamer* gamer) {
  for (uint8 i = 0; i < 128; i++) dispbuffer[0][i] |= GameStatusBar[i];
  for (uint8 i = 9; i < (9 + gamer->health); i++) dispbuffer[0][i] |= 0b00111100; // helth bar
  for (uint8 i = 102; i < (102 + gamer->energy); i++) dispbuffer[0][i] |= 0b00111100; // energy bar
  dispbuffer[0][102 + gamer->energymax] |= 0b01111110;
  uint8 money[5];
  u16_to_str(money, gamer->money, 10);
  uint8 bombs[2];
  u16_to_str(bombs, gamer->bombs, 10);
  LCD_printstr8x5(money, 0, 50);
  LCD_printstr8x5(bombs, 0, 81);
}
/*----------------------------------------------------------------------------*/

