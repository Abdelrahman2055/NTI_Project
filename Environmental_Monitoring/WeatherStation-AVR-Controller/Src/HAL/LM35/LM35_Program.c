#include "LM35_Interface.h"
#include "LM35_Private.h"
#include "LM35_Config.h"

#include "../../MCAL/Dio/Dio_Interface.h"
#include "../../MCAL/Adc/Adc_Interface.h"

void LM35_Init(void)
{
    Dio_SetPinDirection(LM35_PORT, LM35_PIN, INPUT);

    Adc_Init();
}

uint8_t LM35_GetTemperature(void)
{
    uint16_t adc_value;
    uint16_t temperature;

    adc_value = Adc_ReadChannel(LM35_CHANNEL);

    temperature = ((uint32_t)adc_value * 500UL) / 1024UL;
    

    return (uint8_t)temperature;
}