#include <stdio.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "car_positioning.h"
#include <time.h>

int enter_exit_time(Car_state *lpcar){
    struct tm *today;
    time_t current;
    time(&current);
    today=localtime(&current);
    lpcar->enter_now.year = today->tm_year + 1900;
    lpcar->enter_now.month = today->tm_mon + 1 ;
    lpcar->enter_now.day = today->tm_mday;
    lpcar->enter_now.hour = today->tm_hour;
    lpcar->enter_now.minute = today->tm_min;
    lpcar->enter_now.second = today->tm_sec;

    lpcar->exit_now.year = today->tm_year + 1900;
    lpcar->exit_now.month = today->tm_mon + 1 ;
    lpcar->exit_now.day = today->tm_mday;
    lpcar->exit_now.hour = today->tm_hour;
    lpcar->exit_now.minute = today->tm_min;
    lpcar->exit_now.second = today->tm_sec;
    return 0;
}
int car_state_append(LPARRAY lpInput, LPARRAY lpCarset, int car_num){
    Car_state *lpcar;

    if(arrayGetAt(lpCarset, car_num, (LPDATA*) &lpcar)) return 1; //car_num번째 index의 Car_state주소획득
    
    if(enter_exit_time(lpcar)){ //입차시간 갱신
        printf("fail to execute enter_exit_time.\n");
        return 1;   
    }
    if(car_positioning(lpcar)){ // 주차위치 결정
        printf("fail to execute car_positioning.\n");
        return 1;
    }
    if(arrayAdd(lpInput, (const LPDATA) lpcar)) return 1;   //lp_input_car_Array에 append

    return 0;
}
// int car_state_pop(LPARRAY lpInput, LPARRAY lpCarset, int car_num){

// }
