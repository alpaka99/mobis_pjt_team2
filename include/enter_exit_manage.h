//1. car_state입력,gate,iparking_state.txt에car_state append
#ifndef ENTER_EXIT_MANAGE_H 
#define ENTER_EXIT_MANAGE_H 
#include "array.h"

typedef struct Person{
    int dong;           //동 ex)NULL이면 임직원아님, 나머지는 임직원
    int contac_num;     //연락처
    // char *memo;
} Person;

typedef struct Location{
    char *floor;     //층 ex) B1,B2,B3
    int row;        //행 ex) 01
    int col;        //열 ex) 04
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
    const char *car_type;       //차종
    const char *color;          //색깔
    const char *plate_num;      //차번호
    Location location;          //주차위치
    Time enter_now;             //입차시각
    Time exit_now;              //출차시각
    Person person;
} Car_state;

int enter_exit_time(Car_state *car);
int car_state_append(LPARRAY lpArray, int car_num);
int car_state_remove(LPARRAY lpArray, int car_num);

#endif 