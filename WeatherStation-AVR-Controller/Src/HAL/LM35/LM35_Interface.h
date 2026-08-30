#ifndef LM35_INTERFACE_H
#define LM35_INTERFACE_H

#include "../../Common/Definition.h"

void LM35_Init(void);

uint8_t LM35_GetTemperature(void);

#endif
