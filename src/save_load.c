#include "save_load.h"
#include <stdio.h>
#include <stdlib.h>

int car_set_save(Car_state *lpcar, int size){
    FILE *fwp;
    if((fwp=fopen("../dat/car_set.dat","wb"))==NULL){
        printf("fail to open car_set.dat\n");
        return 1;
    }
    int obj_size=size/sizeof(Car_state);
    for(int i=0; i<obj_size; i++){
        fwrite(lpcar,sizeof(Car_state),1,fwp);
        lpcar++;
    }
    fclose(fwp);
    return 0;
}
int car_set_load(LPARRAY lpArray){
    FILE *frp;
    Car_state *res;
   
    if((frp=fopen("../dat/car_set.dat","rb"))==NULL){
        printf("fail to open car_set.dat\n");
        return 1;
    }    
    while(1){
        res=(Car_state *)malloc(sizeof(Car_state));
        //나중에 free해야함 @
        if( !fread(res,sizeof(Car_state),1,frp) ) {
            free(res);
            break;
        }
        if( arrayAdd(lpArray, (const LPDATA) res) ) return 1;
    }
    fclose(frp);
    return 0;
}

// main함수 내에 아래 내용을 붙혀서 car_set.dat제작.
// Car_state의 크기는 120byte이므로 파일크기확인해서 제대로 save됐는지 확인가능.
// 주차위치, 입차시각, 출차시각 갱신해야 함.

    // Time now;
    // Car_state car[]={ { "sonata", "red", "111가1111", {"B1",1,1}, now, now, {1,"01011111111"}},
    //                     { "G70", "blue", "222가2222", {"B1",1,2}, now, now, {2,"01022222222"}},
    //                     { "casper", "white", "333가3333", {"B1",1,3}, now, now, {3,"01033333333"}},
    //                     { "avante", "red", "444가4444", {"B2",2,4}, now, now, {4,"01044444444"}},
    //                     { "c200", "silver", "555가5555", {"B3",2,5}, now, now, {5,"01055555555"}},
                        
    //                     };
    // car_set_save(car,sizeof(car));

//프로그램 내에서 정보입력받고 car배열 변경하는 방법도 고려할 수 있음

int input_car_save(LPARRAY lpArray){
    FILE *fwp;
    Car_state *res;
    
    if((fwp=fopen("../dat/iparking_state.dat","wb"))==NULL){
        printf("fail to open iparking_state.dat\n");
        return 1;
    }
    for(int i=0; i<lpArray->size; i++){
        Car_state *lpcar;
        if(arrayGetAt(lpArray, i, (LPDATA*) &lpcar)) return 1; 
        fwrite(lpcar,sizeof(Car_state),1,fwp);
    }
    fclose(fwp);
    return 0;
}

int input_car_load(LPARRAY lpArray){
    FILE *frp;
    Car_state *res;
   
    if((frp=fopen("../dat/iparking_state.dat","rb"))==NULL){
        printf("fail to open iparking_state.dat\n");
        return 1;
    }
    
    while(1){
        res=(Car_state *)malloc(sizeof(Car_state));
        //나중에 free해야함 @
        if( !fread(res,sizeof(Car_state),1,frp) ) {
            free(res);
            break;
        }
        if( arrayAdd(lpArray, (const LPDATA) res) ) return 1;
    }
    fclose(frp);
    return 0;
}

int output_car_save(LPARRAY lpArray){
    FILE *fwp;
    Car_state *res;
    
    if((fwp=fopen("../dat/oparking_state.dat","wb"))==NULL){
        printf("fail to open oparking_state.dat\n");
        return 1;
    }
    for(int i=0; i<lpArray->size; i++){
        Car_state *lpcar;
        if(arrayGetAt(lpArray, i, (LPDATA*) &lpcar)) return 1; 
        fwrite(lpcar,sizeof(Car_state),1,fwp);
    }
    fclose(fwp);
    
    return 0;
}

int output_car_load(LPARRAY lpArray){
    FILE *frp;
    Car_state *res;
   
    if((frp=fopen("../dat/oparking_state.dat","rb"))==NULL){
        printf("fail to open oparking_state.dat\n");
        return 1;
    }
    
    while(1){
        res=(Car_state *)malloc(sizeof(Car_state));
        //나중에 free해야함 @
        if( !fread(res,sizeof(Car_state),1,frp) ) {
            free(res);
            break;
        }
        if( arrayAdd(lpArray, (const LPDATA) res) ) return 1;
    }
    fclose(frp);

    return 0;
}
