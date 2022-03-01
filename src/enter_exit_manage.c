#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "car_positioning.h"
#include <time.h>
#include <string.h>

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
int exit_time(Car_state *lpcar){
    struct tm *today;
    time_t current;
    time(&current);
    today=localtime(&current);

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
    
    if(enter_exit_time(lpcar)){ //입출차시간 갱신
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

int deep_copy(Car_state *psrc, Car_state *pdst){
    // car_type, color, plate_num, location.floor, person.contac_num 에 대해 memcpy.
    // memcpy(&p2, &p1, sizeof(struct Point2D));
    return 0;
}
int car_state_remove(LPARRAY lpInput, LPARRAY lpOutput, LPARRAY lpCarset, int car_num){

    Car_state *lpcar;
    Car_state *tmp_lpcar= (Car_state *)malloc(sizeof(Car_state));

    if(arrayGetAt(lpCarset, car_num, (LPDATA*) &lpcar)) return 1; 
    char plate_num[15];
    strcpy(plate_num, lpcar->plate_num);
    //lpCarset에서 car_num번째 차에 대한 차번호를 얻는다.

    for(int i=0; i<lpInput->size; i++){
        //차번호를 lpInput과 대조하다가 일치하면 remove
        if(strcmp(plate_num, ((Car_state *)lpInput->lpData[i])->plate_num)==0){
            if(arrayGetAt(lpInput, i, (LPDATA*) &tmp_lpcar)) return 1; 
            //지우기전에 lp_output_car_Array에 전달하기 위해 임시저장
            deep_copy(lpcar, tmp_lpcar);
            //깊은 복사 구현 함수 @
            if(arrayRemoveAt(lpInput, i)) return 1; 
            
            if(exit_time(tmp_lpcar)){ //출차시간 갱신
                printf("fail to execute exit_time.\n");
                return 1;   
            }
            if(arrayAdd(lpOutput, (const LPDATA) tmp_lpcar)) return 1;  
            //lp_output_car_Array에 append
            break;
        }
        // lpInput에 일치하는 차번호가 없으면
        printf("해당 자동차는 주차장에 없습니다. \n");
    }

    //주차요금 출력
    //~~
    //
    free(tmp_lpcar);
    return 0;
}
