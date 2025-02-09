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

uint8 SPI_transmit(uint8);    
void SPI_writebyte(uint8);
void SPI_init(void);
void LCD_init(void);
void LCD_writebyte(uint8);
void LCD_senddata(const uint8*, uint8);
void LCD_sendcommands(uint8, ...);
void LCD_setpagecolumn(uint8, uint8);
void LCD_printsmb8x5(const uint8, uint8, uint8);
void LCD_erase(void);
void LCD_erasestring(uint8, uint8, uint8);
uint8 LCD_printstr8x5(uint8*, uint8, uint8);
void LCD_printclockanddate(uint8, uint8);
void LCD_printufo(uint8, uint8);
void LCD_printpiu(uint8, uint8);
void LCD_printcometa(uint8, uint8);
void LCD_printdistrcometa(uint8, uint8);
void LCD_printbatlevel(uint8, uint8, uint8);
void LCD_printbrightnes(uint8, uint8);
void LCD_printmenucoursor(uint8, uint8);
void LCD_printbutselhint(uint8, uint8, uint8);
void LCD_printvertline(uint8, uint8, uint8);
void LCD_printhorline(uint8, uint8, uint8);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_LCDST7565_H */

