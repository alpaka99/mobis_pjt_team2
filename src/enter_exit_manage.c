#include <stdio.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "car_positioning.h"
#include <time.h>

int car_state_output(Car_state *lpcar)
{
    int nErr;
    
    printf("차종 = %s  ", lpcar->car_type);
    printf("색상 = %s  ", lpcar->color);
    printf("입차시각(y) = %d  ", lpcar->enter_now.year);
    printf("출차시각(y) = %d  ", lpcar->exit_now.year);
    // printf("주차위치 = %s  ", lpcar->location);
    // printf("입주민정보 = %s  ", lpcar->person);
    // printf("번호판 = %s  ", lpcar->plate_num);
    printf("\n======================================\n");

    return 0;
}

int enter_exit_time(Car_state *lpcar){
    struct tm *today;
    time_t current;
    time(&current);
    today=localtime(&current);
    lpcar->enter_now.year = today->tm_year + 1900;
    lpcar->exit_now.year = today->tm_year + 1900;

    return 0;
}
int car_state_append(LPARRAY lpArray, int car_num){
    int nErr = ERR_ARRAY_OK;
    Car_state *lpcar;
    nErr = arrayGetAt(lpArray, car_num, (LPDATA*) &lpcar);  //car_num번째 index의 Car_state주소획득
    if (ERR_ARRAY_OK != nErr) {
        return 1;
    }
    if(enter_exit_time(lpcar)){ //입차시간 갱신
        printf("fail to execute enter_exit_time.\n");
        return 1;   
    }
    if(car_positioning(lpcar)){ // 주차위치 결정
        printf("fail to execute car_positioning.\n");
        return 1;   
    }
    /*iparking_state.txt에 append

    */

    //debug@
    
    //배열에서 얻은 값을 출력  
    car_state_output(lpcar);
    //debug@
    return 0;
}
