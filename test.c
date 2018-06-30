#include <stdio.h>
#include <string.h>

int main()
{
    char dayName[5];
    char month[5];
    int day, hours, minutes, seconds, year;

    printf("date: '%s'\n", __DATE__);
    printf("time: '%s'\n", __TIME__);
    printf("timestamp: '%s'\n", __TIMESTAMP__);

    sscanf(__DATE__, "%s %d %d", month, &day, &year);
    sscanf(__TIME__, "%d:%d:%d", &hours, &minutes, &seconds);
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    static const char day_names[] = "MonTueWedThuFriSatSun";

    int imonth = (strstr(month_names, month) - month_names) / 3;
    int iday = (strstr(day_names, dayName) - day_names) / 3;

    printf("weekday: %s\nmonth: %d\nday: %d\nhours: %d\nminutes: %d\nseconds: %d\nyear: %d\n", dayName, imonth, day, hours, 
seconds, year);

    return 0;
}
