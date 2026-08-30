#ifndef BUZZER_INTERFACE_H
#define BUZZER_INTERFACE_H

#include "../../Common/Definition.h"

void Buzzer_Init(uint8_t BuzzerGroup, uint8_t BuzzerPin);

void Buzzer_On(uint8_t BuzzerGroup, uint8_t BuzzerPin);

void Buzzer_Off(uint8_t BuzzerGroup, uint8_t BuzzerPin);

#endif