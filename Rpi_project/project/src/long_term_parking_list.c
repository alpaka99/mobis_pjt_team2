#include <stdio.h>
#include "array.h"
#include "long_term_parking_list.h"
#include "enter_exit_manage.h"
#include <time.h>

int time_calc(Car_state *lpcar, int sel_date, int year, int mon, int date)
{
    time_t     tm_st, tm_st2;
    time_t     tm_nd;
    int        tm_day, tm_day2, tm_hour, tm_min, tm_sec;
    double     d_diff, d_diff2;
    struct tm  user_stime, car_stime;
    
    if(sel_date > 0) {
        year = lpcar->enter_now.year;
        mon = lpcar->enter_now.month;
        date = lpcar->enter_now.day;
    }
    
        user_stime.tm_year   = year-1900;   // 주의 :년도는 1900년부터 시작
        user_stime.tm_mon    = mon-1;      // 주의 :월은 0부터 시작
        user_stime.tm_mday   = date;
        user_stime.tm_hour   = 0;
        user_stime.tm_min    = 0;
        user_stime.tm_sec    = 0;
        user_stime.tm_isdst  = 0;        // 썸머 타임 사용 안함
    
    //printf("%s\n", lpcar->car_type);
    
    tm_st = mktime( &user_stime);
    time( &tm_nd);
    d_diff = difftime( tm_nd, tm_st);
    tm_day = d_diff / ( 60 *60 * 24);  // sel_date가 0보다 클 경우 lpcar 내의 차와 현재시간을 비교
    // year, min, date로 들어올 경우 해당 날짜와 현재시간을 비교
    

    if(sel_date > 0 && tm_day >= sel_date){ // sel_date 보다 tm_day가 더 크면 -> 장기 주차 기간이 내가 설정한 날보다 크면
        printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)| 인적사항:(%d동, %s)\n",\
        lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
        lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
        lpcar->person.dong, lpcar->person.contac_num);
    }
    else if(sel_date == 0){
        car_stime.tm_year = lpcar->enter_now.year - 1900;
        car_stime.tm_mon = lpcar->enter_now.month - 1;
        car_stime.tm_mday = lpcar->enter_now.day;
        car_stime.tm_hour   = 0;
        car_stime.tm_min    = 0;
        car_stime.tm_sec    = 0;
        car_stime.tm_isdst  = 0;
        tm_st2 = mktime(&car_stime);
        time( &tm_nd);
        d_diff2 = difftime( tm_nd, tm_st2);
        tm_day2 = d_diff2 / ( 60 *60 * 24);
        if(tm_day2 >= tm_day){
            printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)| 인적사항:(%d동, %s)\n",\
            lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
            lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
            lpcar->person.dong, lpcar->person.contac_num);
        }
    }
        return 0;
}
int long_term_parking_list(LPARRAY lpArray, int sel_date, int year, int mon, int date){
    int nErr = ERR_ARRAY_OK;
    Car_state *lpcar;
    int size = arraySize(lpArray);
    for(int i = 0; i < size; i++){
    nErr = arrayGetAt(lpArray, i, (LPDATA*) &lpcar);
    if (ERR_ARRAY_OK != nErr) return 1;
    time_calc(lpcar, sel_date, year, mon, date);
    }
    return 0;
}