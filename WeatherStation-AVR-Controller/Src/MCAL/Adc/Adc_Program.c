#include <avr/io.h>

#include "Adc_Interface.h"
#include "Adc_Private.h"
#include "Adc_Config.h"

void Adc_Init(void)
{
    switch(ADC_VREF)
    {
    case ADC_VREF_AREF:
        ADMUX = 0;
        break;

    case ADC_VREF_AVCC:
        ADMUX = (1 << REFS0);
        break;

    case ADC_VREF_INTERNAL:
        ADMUX = (1 << REFS1) | (1 << REFS0);
        break;

    default:
        ADMUX = 0;
        break;
    }

    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t Adc_ReadChannel(uint8_t Channel)
{
    uint16_t Value;

    ADMUX &= 0xE0;
    ADMUX |= (Channel & ADC_CHANNEL_MASK);

    ADCSRA |= (1 << ADSC);

    while(ADCSRA & (1 << ADSC));

    Value = ADCL;
    Value |= ((uint16_t)ADCH << 8);

    return Value;
}
