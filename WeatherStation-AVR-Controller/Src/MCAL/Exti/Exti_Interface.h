#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "../../Common/Definition.h"

void Exti_Enable(uint8_t Int, uint8_t Sense);

void Exti_Disable(uint8_t Int);

#endif
