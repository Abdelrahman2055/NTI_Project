#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "../../Common/Definition.h"

void Eeprom_WriteByte(uint16_t Address, uint8_t Data);

uint8_t Eeprom_ReadByte(uint16_t Address);

#endif
