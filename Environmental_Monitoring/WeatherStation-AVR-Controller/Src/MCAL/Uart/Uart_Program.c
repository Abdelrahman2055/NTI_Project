#include <avr/io.h>

#include "Uart_Interface.h"
#include "Uart_Private.h"
#include "Uart_Config.h"

void Uart_Init(void)
{
    uint16_t Ubrr = UART_UBRR_VALUE;

    UBRRH = (uint8_t)(Ubrr >> 8);
    UBRRL = (uint8_t)Ubrr;

    UCSRB = (1 << RXEN) | (1 << TXEN);

    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void Uart_SendByte(uint8_t Data)
{
    while(!(UCSRA & (1 << UDRE)));

    UDR = Data;
}

uint8_t Uart_ReceiveByte(void)
{
    while(!(UCSRA & (1 << RXC)));

    return UDR;
}

uint8_t Uart_ReceiveAvailable(void)
{
    return ((UCSRA >> RXC) & 1);
}

void Uart_SendString(const char *Str)
{
    while(*Str)
    {
        Uart_SendByte(*Str);
        Str++;
    }
}

void Uart_SendNumber(uint16_t Number)
{
    uint8_t Digits[5];
    uint8_t i = 0;

    if(Number == 0)
    {
        Uart_SendByte('0');
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
        Uart_SendByte(Digits[i]);
    }
}
