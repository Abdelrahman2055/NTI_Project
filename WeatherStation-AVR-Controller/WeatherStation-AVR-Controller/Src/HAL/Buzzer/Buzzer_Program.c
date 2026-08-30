#include "Buzzer_Interface.h"
#include "Buzzer_Private.h"
#include "Buzzer_Config.h"

#include "../../MCAL/Dio/Dio_Interface.h"

void Buzzer_Init(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    Dio_SetPinDirection(BuzzerGroup, BuzzerPin, OUTPUT);
    Dio_SetPinValue(BuzzerGroup, BuzzerPin, LOW);
}

void Buzzer_On(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    Dio_SetPinValue(BuzzerGroup, BuzzerPin, HIGH);
}

void Buzzer_Off(uint8_t BuzzerGroup, uint8_t BuzzerPin)
{
    Dio_SetPinValue(BuzzerGroup, BuzzerPin, LOW);
}