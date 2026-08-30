#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "../../Common/Definition.h"

void Adc_Init(void);

uint16_t Adc_ReadChannel(uint8_t Channel);

#endif
