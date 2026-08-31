#include "APP/Weather_App.h"

int main(void)
{
    WeatherApp_Init();

    while(1)
    {
        WeatherApp_Update();
    }
}
