#include "car_positioning.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "display_parking_lot.h"

extern Car_state parking_lot[3][3][10];

int car_positioning(Car_state *car){
    // 주차 위치 결정
    // 임의결정 or 가까운 빈공간 추천 중 선택
    extern Car_state parking_lot[3][3][10];
    while(1){
        system("clear");
        printf("층을 선택해주세요.[B1/B2/B3](0: 이전으로)\n>"); //@
        char floor[10];
        scanf("%s",floor); getchar(); //flush newline
        if(floor[0]=='0'){
            break;
        }else if(floor[0]!='B'){
            printf("잘못입력하셨습니다.\n");
            printf("(다음: 아무거나입력)");
            system("stty -echo");
            char sel_c;
            sel_c=getchar(); clear_buffer();
            system("stty echo");
            continue;
        }
        strcpy(car->location.floor,floor);
        printf("행을 선택해주세요.[A-C]\n>");   //A-C
        char c;
        c=getchar(); 
        int row=(int)c-'A'+1; 
        if(!(row>=1 && row<=3)){
            printf("잘못입력하셨습니다.\n");
            printf("(다음: 아무거나입력)");
            system("stty -echo");
            char sel_c;
            sel_c=getchar(); clear_buffer();
            system("stty echo");
            continue;
        }
        car->location.row=row-1;
        printf("열을 선택해주세요.[1-10]\n>"); 
        char str[10]; char str2[10];
        scanf("%s",str); 
        strncpy(str2,str,2); str[2]='\0'; 
        int col=atoi(str2);
        printf("col: %d",col);
        if(!(col>=1 && col<=10)){
            printf("잘못입력하셨습니다.\n");
            printf("(다음: 아무거나입력)");
            system("stty -echo");
            char sel_c;
            sel_c=getchar(); clear_buffer();
            system("stty echo");
            continue;
        }
        car->location.col=col-1;
        printf("\n");
        break;
    }
    int flr;
    if(strcmp(car->location.floor,"B1")==0) flr =0;
    if(strcmp(car->location.floor,"B2")==0) flr =1;
    if(strcmp(car->location.floor,"B3")==0) flr =2;
    
    //같은 위치에 차량이 존재한다면 
    if(strcmp(parking_lot[flr][car->location.row][car->location.col].plate_num,"")!=0){ 
        return 1;
    }
    parking_lot[flr][car->location.row][car->location.col]=*car;
            
    return 0;
}