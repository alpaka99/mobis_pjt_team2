#include "car_positioning.h"
#include <stdio.h>
#include <string.h>

int car_positioning(Car_state *car){
    // 주차 위치 결정
    // 임의결정 or 가까운 빈공간 추천 중 선택
    extern Car_state parking_lot[3][3][10];

    printf("층수를 선택해주세요.[B1/B2/B3]\n>");
    char floor[10];
    // gets(floor);  floor[strlen(floor)-1]='\0';
    scanf("%s",floor); getchar(); //flush newline
    strcpy(car->location.floor,floor);
    printf("행을 선택해주세요.[1-3]\n>");   
    int row;
    scanf("%d",&row); getchar(); //flush newline
    car->location.row=row-1;
    printf("열을 선택해주세요.[1-10]\n>"); 
    int col;
    scanf("%d",&col); getchar(); //flush newline
    car->location.col=col-1;
    int flr;

    if(strcmp(car->location.floor,"B1")==0) flr =0;
    if(strcmp(car->location.floor,"B2")==0) flr =1;
    if(strcmp(car->location.floor,"B3")==0) flr =2;
    parking_lot[flr][car->location.row][car->location.col]=*car;
    return 0;
}