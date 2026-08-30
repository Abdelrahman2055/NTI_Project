#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "../../Common/Definition.h"

void Lcd_Init(void);

void Lcd_SendCommand(uint8_t Command);

void Lcd_SendChar(uint8_t Char);

void Lcd_SendString(const char *Str);

void Lcd_SendNumber(uint16_t Number);

void Lcd_SetCursor(uint8_t Row, uint8_t Col);

void Lcd_Clear(void);

#endif
