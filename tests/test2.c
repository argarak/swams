#include <string.h>
#include <stdio.h>

int main(void) {
    char buf[10];
    int month, day, year, weekDay;
    
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    sscanf(__DATE__, "%s %d 20%d", buf, &day, &year);

    int hours, minutes, seconds;

    sscanf(__TIME__, "%d:%d:%d", &hours, &minutes, &seconds);

    char dayBuf[10];

    sscanf(__TIMESTAMP__, "%s", dayBuf);

    static const char day_names[] = "MonTueWedThuFriSatSun";

    month = (strstr(month_names, buf) - month_names) / 3 + 1;
    weekDay = (strstr(day_names, dayBuf) - day_names) / 3 + 1;

    printf("%d/%02d/%02d | %d:%d:%d | %d\n", year, month, day, hours, minutes, seconds, weekDay);
}

