#include <avr/io.h>
#include <util/atomic.h>  
#include "Eeprom_Interface.h"
#include "Eeprom_Private.h"
#include "Eeprom_Config.h"

void Eeprom_WriteByte(uint16_t Address, uint8_t Data)
{
    while(EECR & (1 << EEWE));

    EEARH = (uint8_t)(Address >> 8);
    EEARL = (uint8_t)Address;

    EEDR = Data;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        EECR |= (1 << EEMWE);
        EECR |= (1 << EEWE);
    }
}

uint8_t Eeprom_ReadByte(uint16_t Address)
{
    while(EECR & (1 << EEWE));

    EEARH = (uint8_t)(Address >> 8);
    EEARL = (uint8_t)Address;

    EECR |= (1 << EERE);

    return EEDR;
}
