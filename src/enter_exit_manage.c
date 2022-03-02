#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "car_positioning.h"
#include <time.h>
#include <string.h>
#include "fee_calculate.h"

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
    char plate_num[15];
    strcpy(plate_num, lpcar->plate_num);
    //lpCarset에서 car_num번째 차에 대한 차번호를 얻는다.
   
    for(int i=0; i<lpInput->size; i++){
        if(strcmp(plate_num, ((Car_state *)lpInput->lpData[i])->plate_num)==0){
             //입차목록에 해당 차량이 있다면
            printf("해당 자동차는 이미 입차했습니다. \n");
            return 0;
        }
    }
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

int car_state_remove(LPARRAY lpInput, LPARRAY lpOutput, LPARRAY lpCarset, int car_num){

    Car_state *lpcar;
    Car_state *tmp_lpcar;
    Car_state *lpOcar= (Car_state *)malloc(sizeof(Car_state));

    if(arrayGetAt(lpCarset, car_num, (LPDATA*) &lpcar)) return 1; 
    char plate_num[15];
    strcpy(plate_num, lpcar->plate_num);
    //lpCarset에서 car_num번째 차에 대한 차번호를 얻는다.
    if(lpInput->size==0){
        printf("주차장이 비었습니다.\n");
        return 0;
    }
    for(int i=0; i<lpInput->size; i++){
        //차번호를 lpInput과 대조하다가 일치하면 remove
        if(strcmp(plate_num, ((Car_state *)lpInput->lpData[i])->plate_num)==0){
            if(arrayGetAt(lpInput, i, (LPDATA*) &tmp_lpcar)) return 1; 
            //지우기전에 car_state를 lp_output_car_Array에 전달하기위해 tmp_lpcar로 주소를 가져옴
            memcpy(lpOcar,tmp_lpcar,sizeof(Car_state));
            //tmp_lpcar의 메모리 상태를 lpOcar에 깊은복사
            if(arrayRemoveAt(lpInput, i)) return 1; 
            
            if(exit_time(lpOcar)){ //출차시간 갱신
                printf("fail to execute exit_time.\n");
                return 1;   
            }
            if(arrayAdd(lpOutput, (const LPDATA) lpOcar)) return 1;  
            //lp_output_car_Array에 append

            if(fee_calculate(lpOcar)) return 1;
            //주차요금 계산

            break;
        }
        // lpInput에 일치하는 차번호가 없으면
        if(i==lpInput->size-1){ //0!=-1
            printf("해당 자동차는 주차장에 없습니다. \n");
        }
    }
    
    return 0;
}
