#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "long_term_parking_list.h"
#include "save_load.h"
#include <string.h>

int save(LPARRAY lpiArray, LPARRAY lpoArray);

int main(void){
    LPARRAY lp_input_car_Array = NULL; 
    LPARRAY lp_output_car_Array = NULL; 
    LPARRAY lp_car_set_Array = NULL; 
    if(arrayCreate(&lp_input_car_Array)) return 1;
    if(arrayCreate(&lp_output_car_Array)) return 1;
    if(arrayCreate(&lp_car_set_Array)) return 1;
    
    // car_set변경하고 싶다면 ../dat/car_state.txt참고.
    // dat에 저장된 정보 load
    if(car_set_load(lp_car_set_Array)) return 1;
    if(input_car_load(lp_input_car_Array)) return 1;
    if(output_car_load(lp_output_car_Array)) return 1;

    // 사용자 권한 선택
    system("clear");
    printf("사용자 권한을 선택하세요.(1:Admin 2:User)\n>");
    int auth;
    while(1){
        scanf("%d",&auth); getchar(); //flush newline
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
        printf("type: %8s 입차시각:(%dm:%ds) 출차시각:(%dm:%ds)\n",lpcar->car_type,  lpcar->enter_now.minute, lpcar->enter_now.second, lpcar->exit_now.minute, lpcar->exit_now.second);
    }
    printf("==============\n");

    for(int i=0; i<lp_input_car_Array->size; i++){
        if(arrayGetAt(lp_input_car_Array, i, (LPDATA*) &lpcar)) return 1;
        printf("type: %8s 입차시각:(%dm:%ds) 출차시각:(%dm:%ds)\n",lpcar->car_type,  lpcar->enter_now.minute, lpcar->enter_now.second, lpcar->exit_now.minute, lpcar->exit_now.second);
        printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)|출차시각:(%d.%d.%d %dh:%dm:%ds)|인적사항:(%d동, %s)\n",\
        lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
        lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
        lpcar->exit_now.year, lpcar->exit_now.month, lpcar->exit_now.day, lpcar->exit_now.hour, lpcar->exit_now.minute, lpcar->exit_now.second,\
        lpcar->person.dong, lpcar->person.contac_num); 
    }
    printf("==============\n");

    for(int i=0; i<lp_output_car_Array->size; i++){
        if(arrayGetAt(lp_output_car_Array, i, (LPDATA*) &lpcar)) return 1;
        printf("type: %8s 입차시각:(%dm:%ds) 출차시각:(%dm:%ds)\n",lpcar->car_type,  lpcar->enter_now.minute, lpcar->enter_now.second, lpcar->exit_now.minute, lpcar->exit_now.second);
        printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)|출차시각:(%d.%d.%d %dh:%dm:%ds)|인적사항:(%d동, %s)\n",\
        lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
        lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
        lpcar->exit_now.year, lpcar->exit_now.month, lpcar->exit_now.day, lpcar->exit_now.hour, lpcar->exit_now.minute, lpcar->exit_now.second,\
        lpcar->person.dong, lpcar->person.contac_num); 
    }
    printf("==============\n");
    //test @

    if(auth==1){
        char passwd[]="0000";
        char key[5];
        while(1){
            printf("비밀번호를 입력하세요.(-1:종료)\n>");
            scanf("%s",&key); getchar(); //flush newline
            if(strcmp(passwd,key)==0) break;
            else{
                if(atoi(key)==-1) return 0;
                printf("틀렸습니다.\n");
            }
        }
    }
   
    // load() //iparking_state.txt load해서 (hash table or linked list) 생성

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
            printf("2. 정산기능 \n");
            printf("3. 주차현황확인기능 \n");
            printf("7. exit \n");
            printf("select ---> ");
        }
        int no=0;
        scanf("%d",&no); getchar(); //flush newline
        switch(no){
            case 1:
                while(1){ // 사용자가 시나리오 상으로 구현하기 위해 개입.
                    printf("입출차 여부를 선택하세요.(-1:이전으로, 1:입차, 2:출차) \n>> ");
                    int sel_en_ex=0;
                    scanf("%d",&sel_en_ex); getchar(); //flush newline
                    // aaa @
                    if(sel_en_ex==1){           
                        printf("입차하는 자동차는 몇번 자동차입니까? \n>>");
                        int car_num=0;
                        scanf("%d",&car_num); getchar(); //flush newline
                        if(car_num<1){          
                            printf("해당 자동차는 존재하지 않습니다. \n");
                        } else if(car_state_append(lp_input_car_Array, lp_car_set_Array, car_num-1)){      
                            //lp_input_car_Array에 차량상태 append
                            printf("fail to execute car_state_append.\n");
                            return 1;   
                        }  
                    } else if(sel_en_ex==2){   
                        
                        printf("출차하는 자동차는 몇번 자동차입니까? \n>>");
                        int car_num=0;
                        scanf("%d",&car_num); getchar(); //flush newline
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
                printf("정산기능 \n");
                // 입차한 car_state의 멤버변수 contac_num를 입력하면 현재까지 발생한 요금이 나오게 함. 
                // person.dong이 0이면 임직원 아님.
                // 2대 이상 차량 소유자도 있을 수 있으므로 contac_num에 일치하는 모든 차량에 대한 요금을 츨력해야 함. @
                break;
            case 3:
                printf("주차현황확인기능 \n");
                break;
            case 4:
                printf("차량정보조회 \n");
                break;
            case 5:
                printf("주차이력관리 \n");
                break;
            case 6:
                //printf("장기주차목록 \n");
                system("clear"); // 이전 내용 다 날리기
                while(1){
                printf("몇 일 이상 주차된 차량에 대해 정보를 출력하시겠습니까?(-1 입력 시 뒤로 가기)\n");
                printf("0000년 00월 00일 이전으로 주차된 차량에 대해 확인하고 싶으면 -2을 입력해주세요.\n");
                int sel_date = 0;
                int year = 0, mon = 0, date = 0;
                scanf("%d", &sel_date); getchar();
                if(sel_date == -1) break;
                else if(sel_date == -2) {
                    printf("년도를 입력해주세요. (예 : 2021)\n");
                    scanf("%d", &year); getchar();
                    printf("월을 입력해주세요. %d년  (예 : 3)\n", year);
                    scanf("%d", &mon); getchar();
                    printf("일을 입력해주세요. %d년 %d월 (예 : 1)\n", year, mon);
                    scanf("%d", &date); getchar();
                }
                if(sel_date < -2){
                    printf("올바른 숫자를 입력해주세요. 최소 크기는 1 이상입니다.\n");
                    }
                else if(long_term_parking_list(lp_input_car_Array, sel_date, year, mon, date)) {
                    printf("fail to execute long_term_parking_list.\n");
                    }
                }
                break;
            case 7:
                printf("exit function \n");
                save(lp_input_car_Array,lp_output_car_Array);  //iparking_state.dat에  lp_input_car_Array 저장
                exit(0);
                break;
            default:
                printf("Wrong choice!!\n");
                break;
        }
    }while(1);

    return 0;
}

int save(LPARRAY lpiArray, LPARRAY lpoArray){
    input_car_save(lpiArray);
    output_car_save(lpoArray);
    
    //table형식으로 바꿔야함
    // int cnt=lpInput->size;
    // fprintf(fwp,"순번[%d]: 차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)|출차시각:(%d.%d.%d %dh:%dm:%ds)|인적사항:(%d동, %s)\n",\
    // cnt,\
    // lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
    // lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
    // lpcar->exit_now.year, lpcar->exit_now.month, lpcar->exit_now.day, lpcar->exit_now.hour, lpcar->exit_now.minute, lpcar->exit_now.second,\
    // lpcar->person.dong, lpcar->person.contac_num); 
    // fclose(fwp);
}
