/******************************************************************************/
//      
//    LCD display
//    Controller - ST7565
//    
//    sofrware  hardware SPI
//    
/******************************************************************************/
#ifndef DRV_LCDST7565_H
#define	DRV_LCDST7565_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "common.h"
#include <stdarg.h>
#include "ufo_battle.h"

  typedef enum {
  lines_first,
  columns_first
}tDirect;

typedef struct{
  uint8 pages;
  int8 columns;
  uint8* sprite;
  tDirect direct;
}tSprite;
  
uint8 SPI_transmit(uint8);    
void SPI_writebyte(uint8);
void SPI_init(void);
void LCD_init(void);
void LCD_writebyte(uint8);
void LCD_senddata(const char*, uint8);
void LCD_sendcommands(uint8, ...);
void LCD_setpagecolumn(uint8, uint8);
void LCD_printsmb8x5(const char, uint8, uint8);
void LCD_bufupload_buferase(void);
void LCD_erasestring(uint8, uint8, uint8);
uint8 LCD_printstr8x5(char*, uint8, uint8);
void LCD_printclockanddate(uint8, uint8);

void LCD_printgamer(uint8, uint8, uint8);
void LCD_printpiu(uint8, uint8);
void LCD_printcometa(uint8, uint8);
void LCD_printdistrcometa(uint8, uint8);
void LCD_printmagaz(uint8, uint8);
void LCD_printgamestatbar(tGamer*);
void LCD_printsprite(uint8, int8, tSprite* const);

void LCD_printbatlevel(uint8, uint8, uint8);
void LCD_printbrightnes(uint8, uint8);
void LCD_printmenucoursor(uint8, uint8);
void LCD_printbutselhint(uint8, uint8, uint8);
void LCD_printvertline(uint8, uint8, uint8);
void LCD_printhorline(uint8, uint8, uint8);
void LCD_printweekday(uint8, uint8, uint8);
void LCD_printmonth(uint8, uint8, uint8);

void LCDbuf_upload(void);
void LCDbuf_erase(void);
uint8 LCDbuf_writestring(uint8*, uint8, uint8);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_LCDST7565_H */

