#include <avr/io.h>
#include <avr/interrupt.h>

#include "Exti_Interface.h"
#include "Exti_Private.h"
#include "Exti_Config.h"

void Exti_Enable(uint8_t Int, uint8_t Sense)
{
    switch(Int)
    {
    case EXTI_INT0:
        MCUCR = (MCUCR & ~(EXTI_SENSE_MASK << ISC00)) | ((Sense & EXTI_SENSE_MASK) << ISC00);
        GICR |= (1 << INT0);
        break;

    case EXTI_INT1:
        MCUCR = (MCUCR & ~(EXTI_SENSE_MASK << ISC10)) | ((Sense & EXTI_SENSE_MASK) << ISC10);
        GICR |= (1 << INT1);
        break;

    case EXTI_INT2:
        if(Sense == EXTI_RISING)
        {
            MCUCSR |= (1 << ISC2);
        }
        else
        {
            MCUCSR &= ~(1 << ISC2);
        }
        GICR |= (1 << INT2);
        break;

    default:
        break;
    }

    sei();
}

void Exti_Disable(uint8_t Int)
{
    switch(Int)
    {
    case EXTI_INT0:
        GICR &= ~(1 << INT0);
        break;

    case EXTI_INT1:
        GICR &= ~(1 << INT1);
        break;

    case EXTI_INT2:
        GICR &= ~(1 << INT2);
        break;

    default:
        break;
    }
}
