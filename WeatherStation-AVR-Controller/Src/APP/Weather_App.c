#include <avr/interrupt.h>
#include <util/delay.h>

#include "../Common/Definition.h"

#include "../HAL/Lcd/Lcd_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"
#include "../HAL/Ldr/Ldr_Interface.h"
#include "../HAL/Buzzer/Buzzer_Interface.h"
#include "../HAL/Buzzer/Buzzer_Config.h"

#include "../MCAL/Timer/Timer_Interface.h"
#include "../MCAL/Uart/Uart_Interface.h"
#include "../MCAL/Eeprom/Eeprom_Interface.h"
#include "../MCAL/Exti/Exti_Interface.h"
#include "../MCAL/Exti/Exti_Config.h"

#include "Weather_App.h"

#define TEMP_ALARM_THRESHOLD   40
#define LIGHT_ALARM_THRESHOLD  15

#define SAMPLE_PERIOD_MS 1000
#define LOG_PERIOD_MS    5000

#define LOG_MAX_RECORDS   120
#define LOG_BASE_ADDRESS  4
#define LOG_COUNT_ADDRESS 0

#define BUZZER_PORT_ID BUZZER_PORTC
#define BUZZER_PIN_ID  0

#define WELCOME_DELAY_MS 1500

static volatile uint8_t DumpRequested = 0;
static volatile uint8_t AlarmMuted = 0;

static uint16_t LastSampleTime = 0;
static uint16_t LastLogTime = 0;
static uint8_t RecordCount = 0;

ISR(INT0_vect)
{
    DumpRequested = 1;
}

ISR(INT1_vect)
{
    AlarmMuted = 1;
}

static void WeatherApp_LoadLogCount(void)
{
    RecordCount = Eeprom_ReadByte(LOG_COUNT_ADDRESS);

    if(RecordCount == 0xFF)
    {
        RecordCount = 0;
    }
}

static void WeatherApp_DumpLog(void)
{
    uint16_t i;
    uint8_t Temp;
    uint8_t Light;

    Uart_SendString("index,temp,light\r\n");

    for(i = 0; i < RecordCount; i++)
    {
        Temp = Eeprom_ReadByte(LOG_BASE_ADDRESS + (i * 2));
        Light = Eeprom_ReadByte(LOG_BASE_ADDRESS + (i * 2) + 1);

        Uart_SendNumber(i);
        Uart_SendByte(',');
        Uart_SendNumber(Temp);
        Uart_SendByte(',');
        Uart_SendNumber(Light);
        Uart_SendString("\r\n");
    }

    Uart_SendString("total,");
    Uart_SendNumber(RecordCount);
    Uart_SendString("\r\n");
}

void WeatherApp_Init(void)
{
    Lcd_Init();
    LM35_Init();
    Ldr_Init();

    Buzzer_Init(BUZZER_PORT_ID, BUZZER_PIN_ID);

    Uart_Init();
    Timer0_Init();
    sei();
    Exti_Enable(EXTI_INT0, EXTI_RISING);    
    Exti_Enable(EXTI_INT1, EXTI_FALLING);

    WeatherApp_LoadLogCount();

    Lcd_SetCursor(0, 0);
    Lcd_SendString("Weather Station");
    Lcd_SetCursor(1, 0);
    Lcd_SendString("Team 3");
    _delay_ms(WELCOME_DELAY_MS);
    Lcd_Clear();

    Uart_SendString("Weather Station Ready\r\n");
}

void WeatherApp_Update(void)
{
    uint8_t Temperature;
    uint8_t Light;

    if(Uart_ReceiveAvailable())
    {
        uint8_t Cmd = Uart_ReceiveByte();

        if(Cmd == 'D')
        {
            DumpRequested = 1;
        }
        else if(Cmd == 'C')
        {
            RecordCount = 0;
            Eeprom_WriteByte(LOG_COUNT_ADDRESS, RecordCount);
            Uart_SendString("log cleared\r\n");
        }
    }

    if(DumpRequested)
    {
        DumpRequested = 0;
        WeatherApp_DumpLog();
    }

    if((uint16_t)(Timer0_GetMillis() - LastSampleTime) >= SAMPLE_PERIOD_MS)
    {
        LastSampleTime = Timer0_GetMillis();

        Temperature = LM35_GetTemperature();
        Light = Ldr_GetLight();

        Lcd_SetCursor(0, 0);
        Lcd_SendString("T:");
        Lcd_SendNumber(Temperature);
        Lcd_SendString("C  L:");
        Lcd_SendNumber(Light);
        Lcd_SendString("%   ");

        if(Temperature >= TEMP_ALARM_THRESHOLD || Light <= LIGHT_ALARM_THRESHOLD)
        {
            if(AlarmMuted)
            {
                Buzzer_Off(BUZZER_PORT_ID, BUZZER_PIN_ID);
                Lcd_SetCursor(1, 0);
                Lcd_SendString("ALARM! Muted    ");
            }
            else
            {
                Buzzer_On(BUZZER_PORT_ID, BUZZER_PIN_ID);
                Lcd_SetCursor(1, 0);
                Lcd_SendString("ALARM!          ");
            }
        }
        else
        {
            AlarmMuted = 0;
            Buzzer_Off(BUZZER_PORT_ID, BUZZER_PIN_ID);
            Lcd_SetCursor(1, 0);
            Lcd_SendString("Log:");
            Lcd_SendNumber(RecordCount);
            Lcd_SendString(" recs       ");
        }

        if((uint16_t)(Timer0_GetMillis() - LastLogTime) >= LOG_PERIOD_MS)
        {
            LastLogTime = Timer0_GetMillis();

            if(RecordCount < LOG_MAX_RECORDS)
            {
                Eeprom_WriteByte(LOG_BASE_ADDRESS + (RecordCount * 2), Temperature);
                Eeprom_WriteByte(LOG_BASE_ADDRESS + (RecordCount * 2) + 1, Light);

                RecordCount++;

                Eeprom_WriteByte(LOG_COUNT_ADDRESS, RecordCount);
            }
        }
    }
}
