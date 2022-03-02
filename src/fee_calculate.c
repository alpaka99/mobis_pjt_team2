#include <stdio.h>
#include "enter_exit_manage.h"
#include <time.h>
#include "fee_calculate.h"
#include <string.h>

int calc_diff_min(Car_state *lpcar, int *ret_diff){
    struct tm *today;
    time_t current, enter_time, current_time;
    time(&current);
    today=localtime(&current);  //struct tm *

    struct tm set_time;
    set_time.tm_year=lpcar->enter_now.year-1900;
    set_time.tm_mon=lpcar->enter_now.month-1;
    set_time.tm_mday=lpcar->enter_now.day;
    set_time.tm_hour=lpcar->enter_now.hour;
    set_time.tm_min=lpcar->enter_now.minute;
    set_time.tm_sec=lpcar->enter_now.second;
    
    enter_time = mktime(&set_time); //time_t
    current_time = mktime(today); //time_t

    int diff = difftime(current_time, enter_time);
    printf("%d초 지남, 60으로나누면 몫은 %d분 \n",diff, diff/60);

    *ret_diff= diff/60;
    return 0;
}

int fee_calculate(Car_state * lpOcar){
    int diff_min;
    if(calc_diff_min(lpOcar,&diff_min)){  //세부요금규정결정필요@
        printf("fail to execute carc_diff_min.\n");
        return 1;  
    }  
    double coef,cost,cost_pm;
    cost_pm=100; 
    if(lpOcar->person.dong==0){     //임직원 아닌 경우
        coef=1;
    }else{                          //임직원인 경우
        coef=0.5;
    }
    cost=(double)diff_min*cost_pm*coef;
    
    printf("주차요금은 %f원 입니다.\n",cost);
    return 0;
}

int get_car_plate_to_put_fee(LPARRAY lpInput, char *car_plate_num){
    Car_state *tmp_lpcar;
    for(int i=0; i<lpInput->size; i++){
        // 입차목록을 뒤진다.
        if(strcmp(car_plate_num, ((Car_state *)lpInput->lpData[i])->plate_num)==0){
            // car_plate_num와 일치하면
            if(arrayGetAt(lpInput, i, (LPDATA*) &tmp_lpcar)) return 1; 
            // 해당 car_state를 얻는다.
            fee_calculate(tmp_lpcar);
            //car_state에 대해 fee_calculate.
            return 0;
        }
    }
    printf("해당 자동차는 입차하지 않았습니다.\n");
    return 0;
}