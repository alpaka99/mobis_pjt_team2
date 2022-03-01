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
