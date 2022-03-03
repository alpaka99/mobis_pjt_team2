#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "long_term_parking_list.h"
#include "save_load.h"
#include "parking_history.h"
#include <string.h>
#include "fee_calculate.h"
#include <ctype.h>
#include "display_parking_lot.h"
#include "parking_status.h"

Car_state parking_lot[3][3][10];

int main(void){
    LPARRAY lp_input_car_Array = NULL; 
    LPARRAY lp_output_car_Array = NULL; 
    LPARRAY lp_car_set_Array = NULL; 

    if(arrayCreate(&lp_input_car_Array)) return 1;
    if(arrayCreate(&lp_output_car_Array)) return 1;
    if(arrayCreate(&lp_car_set_Array)) return 1;
    
    if(car_set_load_csv(lp_car_set_Array)) return 1;
    if(input_car_load(lp_input_car_Array)) return 1;
    if(output_car_load(lp_output_car_Array)) return 1;

    init_parking_lot();
    display_parking_lot(lp_input_car_Array); //@

    // 사용자 권한 선택
    system("clear"); 
    printf("사용자 권한을 선택하세요.(1:Admin 2:User)\n>");
    int auth;
    while(1){
        char sel[5];
        scanf("%s",&sel); getchar(); //flush newline
        auth=atoi(sel); 

        if(auth!=1 && auth!=2){
            printf("잘못 입력했습니다. \n");
            continue;
        }
        break;
    }
    //test @
    printf("==============\n");
    Car_state *lpcar;    
    for(int i=0; i<lp_car_set_Array->size; i++){
        if(arrayGetAt(lp_car_set_Array, i, (LPDATA*) &lpcar)) return 1;
        disp_car_state(lpcar);
    }
    printf("==============\n");

    for(int i=0; i<lp_input_car_Array->size; i++){
        if(arrayGetAt(lp_input_car_Array, i, (LPDATA*) &lpcar)) return 1;
        disp_car_state(lpcar);
    }
    printf("==============\n");

    for(int i=0; i<lp_output_car_Array->size; i++){
        if(arrayGetAt(lp_output_car_Array, i, (LPDATA*) &lpcar)) return 1;
        disp_car_state(lpcar);
    }
    printf("==============\n");
    //test @

    if(auth==1){
        char passwd[]="0000";
        char key[5];
        while(1){
            printf("비밀번호를 입력하세요.(-1:종료)\n>");
            system("stty -echo");
            scanf("%s",&key); getchar(); //flush newline
            printf("\n");
            system("stty echo");
            if(strcmp(passwd,key)==0) break;
            else{
                if(atoi(key)==-1) return 0;
                printf("틀렸습니다.\n");
            }
        }
    }
   
    do{
        if(auth==1){
            printf("1. 입출차관리 \n");
            printf("2. 정산기능 \n");
            printf("3. 주차현황확인기능 \n");
            printf("4. 차량정보조회 \n");  
            printf("5. 주차이력관리 \n");
            printf("6. 장기주차목록 \n");
            printf("7. exit \n");
            printf("select ---> ");
        } else if(auth==2){
            printf("1. 입출차관리 \n");
            printf("2. 정산기능 \n");
            printf("3. 주차현황확인기능 \n");
            printf("7. exit \n");
            printf("select ---> ");
        }
        
        char sel[5];
        scanf("%s",&sel); getchar(); //flush newline
        int no=atoi(sel);           
        
        switch(no){
            case 1:
                while(1){ 
                    printf("입출차 여부를 선택하세요.(-1:이전으로, 1:입차, 2:출차) \n>> ");
                    char sel[5];
                    scanf("%s",&sel); getchar(); //flush newline
                    int sel_en_ex=atoi(sel);
                    if(sel_en_ex==1){           
                        printf("입차하는 자동차는 몇번 자동차입니까? \n>>");
                        char sel[5];
                        scanf("%s",&sel); getchar(); //flush newline
                        int car_num=atoi(sel); 
                        if(car_num<1){          
                            printf("해당 자동차는 존재하지 않습니다. \n");
                        } else if(car_state_append(lp_input_car_Array, lp_car_set_Array, car_num-1)){      
                            //lp_input_car_Array에 차량상태 append
                            printf("fail to execute car_state_append.\n");
                            return 1;   
                        }  
                    } else if(sel_en_ex==2){   
                        printf("출차하는 자동차는 몇번 자동차입니까? \n>");
                        char sel[5];
                        scanf("%s",&sel); getchar(); //flush newline
                        int car_num=atoi(sel); 
                        if(car_num<1){    
                            printf("해당 자동차는 존재하지 않습니다. \n");
                        } else if(car_state_remove(lp_input_car_Array, lp_output_car_Array, lp_car_set_Array, car_num-1)){      
                            //lp_input_car_Array에서 차량상태 remove
                            //lp_output_car_Array에 차량상태 append 
                            printf("fail to execute car_state_pop.\n");
                            return 1;   
                        }
                    } else {
                        if(sel_en_ex==-1) break;
                        printf("잘못 입력했습니다. \n");
                    }
                }
                break;
            case 2:
                // 입차한 car_state의 멤버변수 plate_num를 입력하면 현재까지 발생한 요금이 나오게 함.
                printf("차량번호를 입력하세요.\n>");
                char plate_num[15];
                scanf("%s",plate_num); getchar(); //flush newline
                if(get_car_plate_to_put_fee(lp_input_car_Array, plate_num)){
                    printf("fail to execute get_car_plate_to_put_fee.\n");
                    return 1;
                }
                break;
            case 3:
                display_parking_lot(lp_input_car_Array); 
                break;
            case 4:
                if(auth==1){
                    parking_check(lp_input_car_Array); //@
                }else{
                    printf("접근 불가합니다.\n");
                }
                break;
            case 5:
                if(auth==1){
                    printf("주차이력관리 \n");
                    if(parking_history(lp_input_car_Array,lp_output_car_Array)){
                        printf("fail to execute parking_history.\n");
                    }
                }else{
                    printf("접근 불가합니다.\n");
                }
                break;

            case 6:
                if(auth==1){
                    system("clear");
                    printf("장기주차목록 \n");
                    while(1){
                        printf("다음과 같은 목록 중 검색하고 싶은 양식을 선택해주세요.\n");
                        printf("1. 일 수 (예 : 500일 이상으로 장기 주차한 차량에 대해 검색) \n");
                        printf("2. 날짜 (예 : 2020년 3월 1일 이전에 입차했던 차량에 대해 검색 \n");
                        printf("-1. 뒤로가기 \n");
                        int sel_pl_num = 0; // select parking list num;
                        int sel_date = 0;
                        int year = 0, mon = 0, date = 0;
                        scanf("%s",&sel_pl_num); getchar(); //flush newline
                        if(sel_pl_num == -1) break;
                        else if(sel_pl_num == 1){
                            while(1){
                            scanf("%d", &sel_date); getchar();
                            if(sel_date < 1)
                                printf("올바른 숫자를 입력해주세요. 최소 크기는 1 이상입니다.\n");
                            else break;
                            }
                        }
                        else if(sel_pl_num == 2) {
                            printf("년도를 입력해주세요. (예 : 2021)\n");
                            scanf("%d", &year); getchar();
                            printf("월을 입력해주세요. %d년  (예 : 3)\n", year);
                            scanf("%d", &mon); getchar();
                            printf("일을 입력해주세요. %d년 %d월 (예 : 1)\n", year, mon);
                            scanf("%d", &date); getchar();
                        }
                        if(long_term_parking_list(lp_input_car_Array, sel_date, year, mon, date)) {
                            printf("fail to execute long_term_parking_list.\n");
                            }
                    }
                }else{
                    printf("접근 불가합니다.\n");
                }
                break;
            case 7:
                printf("exit function \n");
                save(lp_input_car_Array,lp_output_car_Array);  //dat 파일에 입차 및 출차 정보 저장
                exit(0);
                break;
            default:
                printf("Wrong choice!!\n");
                break;
        }
    }while(1);

    return 0;
}
