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
    return (uint8_t)(Adc_ReadChannel(LM35_CHANNEL) / LM35_STEPS_PER_CELSIUS);
}
