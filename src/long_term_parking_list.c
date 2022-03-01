#include <stdio.h>
#include "array.h"
#include "long_term_parking_list.h"
#include "enter_exit_manage.h"
#include <time.h>

int now_time(Time *now){
    struct tm *today;
    time_t current;
    time(&current);
    today=localtime(&current);
    now->year = today->tm_year + 1900;
    now->month = today->tm_mon + 1;
    now->day = today->tm_mday;
    now->hour = today->tm_hour;
    now->minute = today->tm_min;
}

int time_calc(Car_state *lpcar, Time now, int sel_date)
{
    time_t start, end;
    // printf("현재 년도 : %d\n", now.year);
    // printf("현재 월 : %d\n", now.month);
    // printf("현재 일 : %d\n", now.day);
    // printf("현재 시간 : %d\n", now.hour);
    // printf("현재 분 : %d\n", now.minute);
    start = mktime(&now);
    time(&end);
    printf("입차시각(y) = %d  \n", lpcar->enter_now.year);
    return 0;
}
int long_term_parking_list(LPARRAY lpArray, int sel_date){
    int nErr = ERR_ARRAY_OK;
    Car_state *lpcar;
    Time now;
    now_time(&now);
    int size = arraySize(lpArray);
    for(int i = 0; i < size; i++){
    nErr = arrayGetAt(lpArray, i, (LPDATA*) &lpcar);
    if (ERR_ARRAY_OK != nErr) return 1;
    time_calc(lpcar, now, sel_date);
    }
    return 0;
}