#include <stdio.h>
#include "array.h"
#include "long_term_parking_list.h"
#include "enter_exit_manage.h"
#include <time.h>
#include "display_parking_lot.h"
#include <stdlib.h>

int time_calc(Car_state *lpcar, int sel_min, int year, int mon, int date)
{
    time_t     tm_st, tm_st2;
    time_t     tm_nd;
    int        tm_day, tm_day2, tm_hour, tm_min, tm_sec;
    double     d_diff, d_diff2;
    struct tm  user_stime, car_stime;
    
    if(sel_min > 0) {                    
        // n분이상 장기주차목록출력하는 경우
        year = lpcar->enter_now.year;
        mon = lpcar->enter_now.month;
        date = lpcar->enter_now.day;
        //입차시각으로 갱신
    }
    user_stime.tm_year   = year-1900;   // 주의 :년도는 1900년부터 시작
    user_stime.tm_mon    = mon-1;       // 주의 :월은 0부터 시작
    user_stime.tm_mday   = date;
    user_stime.tm_hour   = lpcar->enter_now.hour;
    user_stime.tm_min    = lpcar->enter_now.minute;
    user_stime.tm_sec    = lpcar->enter_now.second;
    user_stime.tm_isdst  = 0;           // 썸머 타임 사용 안함
        
    tm_st = mktime( &user_stime);
    time( &tm_nd);
    d_diff = difftime( tm_nd, tm_st);       //현재-입차
    tm_day = d_diff / (60 * 60 * 24);
    d_diff = d_diff - (tm_day * 60 * 60 * 24);
    
    tm_hour = d_diff / (60 * 60);
    d_diff = d_diff - (tm_hour * 60 * 60);
    
    tm_min = d_diff / 60;
    d_diff = d_diff - (tm_min * 60);
    
    tm_sec = d_diff;
    if(sel_min > 0 && tm_min >= sel_min){ // sel_date 보다 tm_day가 더 크면 -> 장기 주차 기간이 내가 설정한 날보다 크면
        until_now_cost(lpcar);
        //현재까지 발생된 주차요금을 포함하여 정보 출력
    }
    else if(sel_min == 0){               //특정 시간 이전 장기주차목록 출력
        car_stime.tm_year = lpcar->enter_now.year - 1900;
        car_stime.tm_mon = lpcar->enter_now.month - 1;
        car_stime.tm_mday = lpcar->enter_now.day;
        car_stime.tm_hour   = lpcar->enter_now.hour;
        car_stime.tm_min    = lpcar->enter_now.minute;
        car_stime.tm_sec    = lpcar->enter_now.second;
        car_stime.tm_isdst  = 0;
        tm_st2 = mktime(&car_stime);
        time( &tm_nd);
        d_diff2 = difftime( tm_st2, tm_st);     
        tm_day2 = d_diff2 / 60;
        // printf("입차-특정시점: %d\n",tm_day2);
        if(tm_day2 <= 0){    
            until_now_cost(lpcar);
        //현재까지 발생된 주차요금을 포함하여 정보 출력
        }
    }
    return 0;
}
int long_term_parking_list(LPARRAY lpArray, int sel_min, int year, int mon, int date){
    int nErr = ERR_ARRAY_OK;
    Car_state *lpcar;
    int size = arraySize(lpArray);
    for(int i = 0; i < size; i++){
    nErr = arrayGetAt(lpArray, i, (LPDATA*) &lpcar);
    if (ERR_ARRAY_OK != nErr) return 1;
        time_calc(lpcar, sel_min, year, mon, date);
    }

    printf("(다음: 아무거나입력)");
    system("stty -echo");
    char sel_c=getchar(); clear_buffer();
    system("stty echo");
    return 0;
}