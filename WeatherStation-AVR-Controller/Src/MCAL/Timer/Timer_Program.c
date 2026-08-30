#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "Timer_Config.h"

volatile uint16_t Timer0_Millis = 0;

ISR(TIMER0_COMP_vect)
{
    Timer0_Millis++;
}

void Timer0_Init(void)
{
    TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00);

    OCR0 = TIMER0_COMPARE_VALUE;

    TCNT0 = 0;

    TIMSK |= (1 << OCIE0);
}

uint16_t Timer0_GetMillis(void)
{
    uint16_t Copy;

    Copy = Timer0_Millis;

    return Copy;
}
