#include "Ldr_Interface.h"
#include "Ldr_Private.h"
#include "Ldr_Config.h"

#include "../../MCAL/Dio/Dio_Interface.h"
#include "../../MCAL/Adc/Adc_Interface.h"

void Ldr_Init(void)
{
    Dio_SetPinDirection(LDR_PORT, LDR_PIN, INPUT);

    Adc_Init();
}

uint8_t Ldr_GetLight(void)
{
    return (uint8_t)(((uint32_t)Adc_ReadChannel(LDR_CHANNEL) * 100UL) / LDR_ADC_MAX);
}
