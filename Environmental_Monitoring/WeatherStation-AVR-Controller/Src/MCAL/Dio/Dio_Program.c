#include <avr/io.h>

#include "Dio_Interface.h"
#include "Dio_Private.h"
#include "Dio_Config.h"

void Dio_SetPinDirection(uint8_t Port, uint8_t Pin, uint8_t Direction)
{
    switch(Port)
    {
    case PORTA_ID:
        if(Direction == OUTPUT)
        {
            DDRA |= (1 << Pin);
        }
        else
        {
            DDRA &= ~(1 << Pin);
        }
        break;

    case PORTB_ID:
        if(Direction == OUTPUT)
        {
            DDRB |= (1 << Pin);
        }
        else
        {
            DDRB &= ~(1 << Pin);
        }
        break;

    case PORTC_ID:
        if(Direction == OUTPUT)
        {
            DDRC |= (1 << Pin);
        }
        else
        {
            DDRC &= ~(1 << Pin);
        }
        break;

    case PORTD_ID:
        if(Direction == OUTPUT)
        {
            DDRD |= (1 << Pin);
        }
        else
        {
            DDRD &= ~(1 << Pin);
        }
        break;

    default:
        break;
    }
}

void Dio_SetPinValue(uint8_t Port, uint8_t Pin, uint8_t Value)
{
    switch(Port)
    {
    case PORTA_ID:
        if(Value == HIGH)
        {
            PORTA |= (1 << Pin);
        }
        else
        {
            PORTA &= ~(1 << Pin);
        }
        break;

    case PORTB_ID:
        if(Value == HIGH)
        {
            PORTB |= (1 << Pin);
        }
        else
        {
            PORTB &= ~(1 << Pin);
        }
        break;

    case PORTC_ID:
        if(Value == HIGH)
        {
            PORTC |= (1 << Pin);
        }
        else
        {
            PORTC &= ~(1 << Pin);
        }
        break;

    case PORTD_ID:
        if(Value == HIGH)
        {
            PORTD |= (1 << Pin);
        }
        else
        {
            PORTD &= ~(1 << Pin);
        }
        break;

    default:
        break;
    }
}

uint8_t Dio_GetPinValue(uint8_t Port, uint8_t Pin)
{
    uint8_t PinValue = LOW;

    switch(Port)
    {
    case PORTA_ID:
        PinValue = ((PINA >> Pin) & 1);
        break;

    case PORTB_ID:
        PinValue = ((PINB >> Pin) & 1);
        break;

    case PORTC_ID:
        PinValue = ((PINC >> Pin) & 1);
        break;

    case PORTD_ID:
        PinValue = ((PIND >> Pin) & 1);
        break;

    default:
        break;
    }

    return PinValue;
}

void Dio_SetPortDirection(uint8_t Port, uint8_t Direction)
{
    switch(Port)
    {
    case PORTA_ID:
        DDRA = Direction;
        break;

    case PORTB_ID:
        DDRB = Direction;
        break;

    case PORTC_ID:
        DDRC = Direction;
        break;

    case PORTD_ID:
        DDRD = Direction;
        break;

    default:
        break;
    }
}

void Dio_SetPortValue(uint8_t Port, uint8_t Value)
{
    switch(Port)
    {
    case PORTA_ID:
        PORTA = Value;
        break;

    case PORTB_ID:
        PORTB = Value;
        break;

    case PORTC_ID:
        PORTC = Value;
        break;

    case PORTD_ID:
        PORTD = Value;
        break;

    default:
        break;
    }
}

uint8_t Dio_GetPortValue(uint8_t Port)
{
    uint8_t PortValue = 0;

    switch(Port)
    {
    case PORTA_ID:
        PortValue = PINA;
        break;

    case PORTB_ID:
        PortValue = PINB;
        break;

    case PORTC_ID:
        PortValue = PINC;
        break;

    case PORTD_ID:
        PortValue = PIND;
        break;

    default:
        break;
    }

    return PortValue;
}
