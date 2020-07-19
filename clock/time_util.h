#ifndef TIMEUTILDEF
#define TIMEUTILDEF
#include <stdint.h>
#include <stdbool.h>
// #include <ESP8266WiFi.h>


struct time {
    int seconds;
    int minutes;
    int hours;
    int day_of_year;
    int day_of_month;
    int day_of_week;
    int month;
    int week;
    bool daylight_saving;
    int year;
};

const uint32_t MINUTE_IN_SECONDS = 60;
const uint32_t HOUR_IN_SECONDS = 3600;
const uint32_t DAY_IN_SECONDS = 24*3600;
const uint32_t WEEK_IN_SECONDS = 7*24*3600;
const uint32_t YEAR_IN_SECONDS = 365*24*3600;
const uint32_t LEAP_YEAR_IN_SECONDS = 366*24*3600;

const int monthDays_non_leap_year[] = {
    31,28,31,30,31,30,31,31,30,31,30,31
};

const int monthDays_cumulative_non_leap_year[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

const int monthDays_leap_year[] = {
    31,29,31,30,31,30,31,31,30,31,30,31
};

const int monthDays_cumulative_leap_year[] = {
    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335
};


struct time get_time_struct(uint32_t time);
bool is_leap_year(int year);
uint32_t year_to_seconds(int year);

#endif