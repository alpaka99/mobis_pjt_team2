//1. car_state입력,gate,iparking_state.txt에car_state append
#ifndef ENTER_EXIT_MANAGE_H 
#define ENTER_EXIT_MANAGE_H 
#include "array.h"

typedef struct Person{
    int dong;           //동 ex)0이면 임직원아님, 나머지는 임직원
    char contac_num[15];     //연락처 ex) 01012345678
    // char *memo;
} Person;

typedef struct Location{
    char floor[5];      //층 ex) B1,B2,B3
    int row;            //행 ex) 01
    int col;            //열 ex) 04
} Location;

typedef struct Time{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Time;

typedef struct Car_state{
    char car_type[10];       //차종
    char color[10];          //색깔
    char plate_num[15];      //차번호
    
    Location location;          //주차위치
    Time enter_now;             //입차시각
    Time exit_now;              //출차시각
    Person person;
    double cost;
} Car_state;    //128byte

int detail_until_now_cost(Car_state *lpcar);
int enter_exit_time(Car_state *car);
int car_state_append(LPARRAY lpInput, LPARRAY lpCarset, int car_num);
int car_state_remove(LPARRAY lpInput, LPARRAY lpOutput, LPARRAY lpCarset, int car_num);
int disp_car_state(Car_state *lpcar);
int save(LPARRAY lpiArray, LPARRAY lpoArray);
int exit_time(Car_state *lpcar);
int until_now_cost(Car_state *lpcar);
int until_now_calculate(Car_state *lpOcar, double *arg_cost);


#endif 