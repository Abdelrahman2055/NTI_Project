#include "Lcd_Interface.h"   
#include <util/delay.h>
#include "Lcd_Private.h"
#include "Lcd_Config.h"

#include "../../MCAL/Dio/Dio_Interface.h"

static void Lcd_Write4Bits(uint8_t Nibble)
{
    uint8_t i;

    for(i = 0; i < 4; i++)
    {
        Dio_SetPinValue(LCD_DATA_PORT, LCD_D4_PIN + i, ((Nibble >> i) & 1));
    }

    Dio_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, HIGH);
    _delay_us(2);
    Dio_SetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, LOW);
}

void Lcd_Init(void)
{
    uint8_t i;

    Dio_SetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, OUTPUT);
    Dio_SetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, OUTPUT);

    for(i = 0; i < 4; i++)
    {
        Dio_SetPinDirection(LCD_DATA_PORT, LCD_D4_PIN + i, OUTPUT);
    }

    _delay_ms(50);

    Lcd_Write4Bits(0x03);
    _delay_ms(5);
    Lcd_Write4Bits(0x03);
    _delay_us(150);
    Lcd_Write4Bits(0x03);
    _delay_us(150);
    Lcd_Write4Bits(0x02);
    _delay_us(150);

    Lcd_SendCommand(LCD_CMD_FUNCTION_SET);
    Lcd_SendCommand(LCD_CMD_DISPLAY_ON);
    Lcd_SendCommand(LCD_CMD_ENTRY_MODE);
    Lcd_SendCommand(LCD_CMD_CLEAR);
    _delay_ms(2);
}

void Lcd_SendCommand(uint8_t Command)
{
    Dio_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, LOW);

    Lcd_Write4Bits(Command >> 4);
    Lcd_Write4Bits(Command);

    _delay_us(50);
}

void Lcd_SendChar(uint8_t Char)
{
    Dio_SetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, HIGH);

    Lcd_Write4Bits(Char >> 4);
    Lcd_Write4Bits(Char);

    _delay_us(50);
}

void Lcd_SendString(const char *Str)
{
    while(*Str)
    {
        Lcd_SendChar(*Str);
        Str++;
    }
}

void Lcd_SendNumber(uint16_t Number)
{
    uint8_t Digits[5];
    uint8_t i = 0;

    if(Number == 0)
    {
        Lcd_SendChar('0');
        return;
    }

    while(Number > 0)
    {
        Digits[i] = (Number % 10) + '0';
        Number /= 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        Lcd_SendChar(Digits[i]);
    }
}

void Lcd_SetCursor(uint8_t Row, uint8_t Col)
{
    if(Row == 0)
    {
        Lcd_SendCommand(LCD_CMD_ROW0 + Col);
    }
    else
    {
        Lcd_SendCommand(LCD_CMD_ROW1 + Col);
    }
}

void Lcd_Clear(void)
{
    Lcd_SendCommand(LCD_CMD_CLEAR);
    _delay_ms(2);
}
