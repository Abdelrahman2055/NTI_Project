#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "../../Common/Definition.h"

void Uart_Init(void);

void Uart_SendByte(uint8_t Data);

uint8_t Uart_ReceiveByte(void);

uint8_t Uart_ReceiveAvailable(void);

void Uart_SendString(const char *Str);

void Uart_SendNumber(uint16_t Number);

#endif
