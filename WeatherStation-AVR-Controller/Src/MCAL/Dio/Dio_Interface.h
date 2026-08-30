#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "../../Common/Definition.h"

void Dio_SetPinDirection(uint8_t Port, uint8_t Pin, uint8_t Direction);

void Dio_SetPinValue(uint8_t Port, uint8_t Pin, uint8_t Value);

uint8_t Dio_GetPinValue(uint8_t Port, uint8_t Pin);

void Dio_SetPortDirection(uint8_t Port, uint8_t Direction);

void Dio_SetPortValue(uint8_t Port, uint8_t Value);

uint8_t Dio_GetPortValue(uint8_t Port);

#endif
