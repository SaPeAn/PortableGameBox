
#ifndef DRV_LCDST7565_H
#define	DRV_LCDST7565_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "common.h"
#include <stdarg.h>   

uint8 SPI_transmit(uint8);    
void SPI_WriteByte(uint8);
void SPI_init(void);
void LCD_Init(void);
void LCD_WriteByte(uint8);
void LCD_SendData(const uint8*, uint8);
void LCD_SendCommands(uint8, ...);
void LCD_Set_PageColumn(uint8, uint8);
void LCD_printSmb8x5(const uint8, uint8, uint8);
void LCD_Erase(void);
uint8 LCD_printStr8x5(uint8*, uint8, uint8);
void LCD_PrintClock(uint8, uint8, uint8);
void print_ufo(uint8, uint8);
void print_piu(uint8, uint8);
void print_cometa(uint8, uint8);
void print_distr_cometa(uint8, uint8);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_LCDST7565_H */

