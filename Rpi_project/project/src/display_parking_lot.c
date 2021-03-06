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

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<10;k++){
                memcpy(&parking_lot[i][j][k], &tmp_car, sizeof(tmp_car)); 
            }
        }
    }
    return 0;
}
int display_parking_lot(LPARRAY lp_IArray, LPARRAY lp_OArray){
    extern Car_state parking_lot[3][3][10];
    
    Car_state* tmp;         
    int floor, num_B1=0, num_B2=0, num_B3=0;   

    // ??? mapping
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
    
    for(int i=0;i<3;i++){
        // unicode 참고: https://unicode-table.com/kr/blocks/box-drawing/
        system("clear");
        printf("\n\n====================================================주차현황====================================================");
        printf("\n\n    전체 주차대수: %d/30", lp_IArray->size);
        for(int i=0; i<71; i++) printf(" ");
        printf("0 : 종료\n");
        for(int i=0; i<84; i++) printf(" ");
        printf("아무거나입력: 다음으로\n");
        if(i==0) printf("\n\n    지하 1 층 주차대수: %d/10\n",num_B1);
        else if(i==1) printf("\n\n    지하 2 층 주차대수: %d/10\n",num_B2);
        else if(i==2) printf("\n\n    지하 3 층 주차대수: %d/10\n",num_B3);
        printf("\n    \u250f");
        for(int z=0; z<99; z++){
            printf("\u2501");
        }      
        printf("\u2513\n    \u2503");  
        printf("\t\t\t\t\t┌─────────────────┐\t\t       ┌────────────────────────┐\n");
        printf("\t\t\t\t\t│   지상 출입문   │\t\t       │    MOBIS 주차장 입구   │\n");
        printf("\t\t\t\t\t└─────────────────┘\t\t       └────────────────────────┘\n");
        for(int j=0;j<3;j++){
            char r = (char)(j+(int)'A');
            printf("    ");
            for(int k=0;k<10;k++){
            printf("┌────────┐");
            }printf("\n");
            printf("    ");
            for(int k=0;k<10;k++)
            {
                if(k==9)    printf("│   %c%d  │", r,k+1);
                else printf("│   %c%d   │", r,k+1); // 좌표출력
            }printf("\n");
            printf("    ");
            for(int k=0;k<10;k++){
            printf("├────────┤");
            }printf("\n");
            printf("    ");
            for(int k=0;k<10;k++){
            printf("│        │");
            }printf("\n");

            // 번호판 출력 시작
            printf("    ");
            for(int k=0;k<10;k++)
            {
            if(strcmp(parking_lot[i][j][k].plate_num,"")==0){
                printf("│        │");
            }
            else{
                char str[20]="";
                strncpy(str, parking_lot[i][j][k].plate_num,6);  // UTF-8에서 한글: 3byte
                str[6]='\0';
                printf("│  %s │",str);
            }
            }printf("\n");
            printf("    ");
            for(int k=0;k<10;k++)
            {
            if(strcmp(parking_lot[i][j][k].plate_num,"")==0){
                printf("│        │");
            }
            else{
                char str[20]="";
                strncpy(str, parking_lot[i][j][k].plate_num+6,4);  // UTF-8에서 한글: 3byte
                str[4]='\0';
                printf("│  %s  │", str);
            }
            }printf("\n");
            
            //번호판 출력 끝
            printf("    ");
            for(int k=0;k<10;k++){
            printf("└────────┘");
            }printf("\n");
        }
        printf("\n\n");
        
        char sel;
        system("stty -echo");
        sel=getchar(); clear_buffer();
        system("stty echo");
        system("clear");
        int flag=sel-'0';  // char to int
        if(flag==0){
            save(lp_IArray, lp_OArray);
            exit(0);
        }
    }
    return 0;
}