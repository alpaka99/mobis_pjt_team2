#include "display_parking_lot.h"
#include "enter_exit_manage.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int clear_buffer(void){
    while (getchar() != '\n');
    return 0; 
}
int init_parking_lot(){
    extern Car_state parking_lot[3][3][10];

    Time now;
    Car_state tmp_car={ "", "", "", {"",0,0}, now, now, {0,""},0.0 };
    // parking_lot 초기화
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<10;k++){
                memcpy(&parking_lot[i][j][k], &tmp_car, sizeof(tmp_car)); //깊은 복사
            }
        }
    }
    return 0;
}
int display_parking_lot(LPARRAY lp_IArray){
    extern Car_state parking_lot[3][3][10];

    system("clear");
    printf("\n\n====================================================주차현황====================================================");

    Car_state* tmp;         
    int floor, num_B1=0, num_B2=0, num_B3=0;   

    // 주차장 mapping
    for(int i=0;i<lp_IArray->size;i++){
        if(arrayGetAt(lp_IArray, i, (LPDATA*) &tmp)) return 1;
        
        if(strcmp(tmp->location.floor,"B1")==0){
            floor =0;
            num_B1++;
        }
        if(strcmp(tmp->location.floor,"B2")==0){
            floor =1;
            num_B2++;
        }
        if(strcmp(tmp->location.floor,"B3")==0){
            floor =2;
            num_B3++;
        }
        parking_lot[floor][tmp->location.row][tmp->location.col] = *tmp;
    }
    // UI  @
    // unicode 참고: https://unicode-table.com/kr/blocks/box-drawing/
    printf("\n\n    전체 주차대수: %d/30", lp_IArray->size);
    for(int i=0; i<71; i++) printf(" ");
    printf("0 : 종료\n");
    for(int i=0; i<84; i++) printf(" ");
    printf("아무거나입력: 다음으로\n");

    for(int i=0;i<3;i++){
        if(i==0) printf("\n\n    지하 1 층 주차대수: %d/10\n",num_B1);
        else if(i==1) printf("\n\n    지하 2 층 주차대수: %d/10\n",num_B2);
        else if(i==2) printf("\n\n    지하 3 층 주차대수: %d/10\n",num_B3);
        printf("\n    \u250f");
        for(int z=0; z<99; z++){
            printf("\u2501");
        }      
        printf("\u2513\n    \u2503");  
        for(int j=0;j<3;j++){
            for(int k=0;k<10*3;k++){
                if(0<=k && k<10){
                    printf("%9s\u2503", "");
                }else if(10<=k && k<20){
                    printf("%9s\u2503", parking_lot[i][j][k-10].plate_num); 
                }else{
                    printf("%9s\u2503", "");
                }
                if(k==9 || k==19) printf("\n    \u2503");
            }
            if(j!=2){
                printf("\n    \u2523");
                for(int z=0; z<99; z++){
                    printf("\u2501");
                }      
                printf("\u252b\n    \u2503"); 
            }
            else{
                printf("\n    \u2517");
                for(int z=0; z<99; z++){
                    printf("\u2501");
                }      
                printf("\u251b"); 
            }
        }
        printf("\n\n");
        
        char sel;
        system("stty -echo");
        sel=getchar(); clear_buffer();
        system("stty echo");
        int flag=sel-'0';  // char to int
        if(flag==0) exit(0);
    }
    return 0;
}