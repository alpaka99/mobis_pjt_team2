#include <stdio.h>
#include "array.h"
#include "enter_exit_manage.h"
#include "parking_history.h"
#include <stdlib.h>

// int input_car_save_s(LPARRAY lpArray){
//     FILE *fwp;
//     Car_state *res;
    
//     if((fwp=fopen("../dat/io_state.dat","wb"))==NULL){
//         printf("fail to open iparking_state.dat\n");
//         return 1;
//     }
//     for(int i=0; i<lpArray->size; i++){
//         Car_state *lpcar;
//         if(arrayGetAt(lpArray, i, (LPDATA*) &lpcar)) return 1; 
//         fwrite(lpcar,sizeof(Car_state),1,fwp);
//     }
//     fclose(fwp);
//     return 0;
// }

// int output_car_save_s(LPARRAY lpArray){
//     FILE *fwp;
//     Car_state *res;
    
//     if((fwp=fopen("../dat/io_state.dat","a+b"))==NULL){
//         printf("fail to open oparking_state.dat\n");
//         return 1;
//     }
//     for(int i=0; i<lpArray->size; i++){
//         Car_state *lpcar;
//         if(arrayGetAt(lpArray, i, (LPDATA*) &lpcar)) return 1; 
//         fwrite(lpcar,sizeof(Car_state),1,fwp);
//     }
//     fclose(fwp);
    
//     return 0;
// }

// int output_car_load_s(LPARRAY lpArray){
//     FILE *frp;
//     Car_state *res;
   
//     if((frp=fopen("../dat/io_state.dat","rb"))==NULL){
//         printf("fail to open oparking_state.dat\n");
//         return 1;
//     }
    
//     while(1){
//         res=(Car_state *)malloc(sizeof(Car_state));
//         //나중에 free해야함 @
//         if( !fread(res,sizeof(Car_state),1,frp) ) {
//             free(res);
//             break;
//         }
//         if( arrayAdd(lpArray, (const LPDATA) res) ) return 1;
//     }
//     fclose(frp);

//     return 0;
// }

int parking_history(LPARRAY lp_input_car_Array, LPARRAY lp_output_car_Array){
    
    Car_state *lpcar;
    system("clear");
    printf("\n\n");
    printf("현재 입차 내역 : \n\n");
    for(int i=0; i<lp_input_car_Array->size; i++){
        if(arrayGetAt(lp_input_car_Array, i, (LPDATA*) &lpcar)) return 1;
        printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)|인적사항:(%d동, %s)\n",\
        lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
        lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
        lpcar->person.dong, lpcar->person.contac_num); 
    }
    printf("\n\n");
    printf("==============\n");
    printf("\n\n");

    printf("출차 내역 : \n\n");
    for(int i=0; i<lp_output_car_Array->size; i++){
        if(arrayGetAt(lp_output_car_Array, i, (LPDATA*) &lpcar)) return 1;
        printf("차량정보:(%s,%s,%s)|주차위치:(%s,%d,%d)|입차시각:(%d.%d.%d %dh:%dm:%ds)|출차시각:(%d.%d.%d %dh:%dm:%ds)|인적사항:(%d동, %s)\n",\
        lpcar->car_type, lpcar->color, lpcar->plate_num, lpcar->location.floor, lpcar->location.row+1, lpcar->location.col+1,\
        lpcar->enter_now.year, lpcar->enter_now.month, lpcar->enter_now.day, lpcar->enter_now.hour, lpcar->enter_now.minute, lpcar->enter_now.second,\
        lpcar->exit_now.year, lpcar->exit_now.month, lpcar->exit_now.day, lpcar->exit_now.hour, lpcar->exit_now.minute, lpcar->exit_now.second,\
        lpcar->person.dong, lpcar->person.contac_num); 
    }
    printf("\n\n");
    printf("==============\n\n");


    return 0;
}