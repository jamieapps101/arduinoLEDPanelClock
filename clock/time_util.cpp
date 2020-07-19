#include "time_util.h"
// #include <ESP8266WiFi.h>


struct time get_time_struct(uint32_t time) {
    int year = 0;
    uint32_t year_seconds = year_to_seconds(year);
    int leap_years = 0;
    while (time > year_seconds) {
        time -= year_seconds;
        year++;
        if (is_leap_year(year)) {
            leap_years++;
        }
        year_seconds = year_to_seconds(year);
    }
    // 0 - Monday
    // starts on thursday
    int day_of_week = 3;
    int week = 0;
    uint32_t temp = time;
    while (temp>WEEK_IN_SECONDS) {
        temp -= WEEK_IN_SECONDS;
        week++;
    }
    while(temp>DAY_IN_SECONDS) {
        day_of_week++;
        temp-=DAY_IN_SECONDS;
    }

    int hour = 0;
    while(temp>HOUR_IN_SECONDS) {
        hour++;
        temp -= HOUR_IN_SECONDS;
    }

    int minute = 0;
    while(temp>MINUTE_IN_SECONDS) {
        minute++;
        temp -= MINUTE_IN_SECONDS;
    }
    int second = temp;

    // add one day per year, and two for leap years
    day_of_week+year+leap_years;
    day_of_week = day_of_week%7;
    int month = 0;
    const int *monthDays;
    const int *cumMonthDays;
    if (is_leap_year(year)) {
        monthDays = monthDays_leap_year;
        cumMonthDays = monthDays_cumulative_leap_year;
    } else {
        monthDays = monthDays_non_leap_year;
        cumMonthDays = monthDays_cumulative_non_leap_year;

    }
    while(time > monthDays[month]*DAY_IN_SECONDS) {
        time -= monthDays[month]*DAY_IN_SECONDS;
        month++;
    }
    int day_of_month = (week*7+day_of_week) - cumMonthDays[month];

    bool daylight_saving = false;
    // if month is bigger than march and less than october
    if (month>2 && month<9) {
        daylight_saving = true;
    }
    /*
    In the UK the clocks go forward 1 hour at 1am on the 
    last Sunday in March, and back 1 hour at 2am on the 
    last Sunday in October. 
    */

    // if in march
    if (month==2) {
        int days_until_next_sunday = 7-day_of_week;
        int days_left_of_month = monthDays[2]-day_of_month;
        if (days_until_next_sunday>days_left_of_month) {
            // ie the last sunday has happened already
            daylight_saving = true;
        }
    }

    // if in october
    if (month==2) {
        int days_until_next_sunday = 7-day_of_week;
        int days_left_of_month = monthDays[2]-day_of_month;
        if (days_until_next_sunday>days_left_of_month) {
            // ie the last sunday has happened already
            daylight_saving = true;
        }
    }
    struct time return_time;
    return_time.seconds = second;
    return_time.minutes = minute;
    return_time.hours = hour;
    return_time.day_of_year = week*7+day_of_week;
    return_time.day_of_month = day_of_month;
    return_time.day_of_week = day_of_week;
    return_time.month = month;
    return_time.week = week;
    return_time.daylight_saving = daylight_saving;
    return_time.year = year+1970;
    return return_time;
}

bool is_leap_year(int year) {
    if ((year%4) && ((year%400) || !(year%100))) {
        return true;
    } else {
        return false;
    }
}

uint32_t year_to_seconds(int year) {
    if (is_leap_year(year)) {
        return LEAP_YEAR_IN_SECONDS;
    } else {
        return YEAR_IN_SECONDS;
    }
}