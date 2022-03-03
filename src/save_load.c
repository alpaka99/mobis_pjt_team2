#include "save_load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int car_set_save(Car_state *lpcar, int size){
    FILE *fwp;
    if((fwp=fopen("./dat/car_set.dat","wb"))==NULL){
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
   
    if((frp=fopen("./dat/car_set.dat","rb"))==NULL){
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
int car_set_load_csv(LPARRAY lpArray){
    FILE *pFile = NULL;
    Car_state *res;
    char str_tmp[1024];
    char *tkn;
    int cnt;
    if((pFile=fopen("./dat/car_set.csv","r"))==NULL){
        printf("fail to open car_set.csv\n");
        return 1;
    }      
    while( !feof( pFile ) ){
        fgets( str_tmp, 1024, pFile );   
        res=(Car_state *)malloc(sizeof(Car_state));       
        tkn = strtok(str_tmp, ",");
        cnt=1;
        while(tkn != NULL){
            switch (cnt)
            {
            case 1:
                strcpy(res->car_type,tkn);
                break;
            case 2:
                strcpy(res->color,tkn);
                break;
            case 3:
                strcpy(res->plate_num,tkn);
                break;
            case 4:
                strcpy(res->location.floor,tkn);
                break;
            case 5:
                res->location.row=atoi(tkn);
                break;
            case 6:
                res->location.col=atoi(tkn);
                break;
            case 7:
                res->enter_now.year=atoi(tkn);
                break;
            case 8:
                res->enter_now.month=atoi(tkn);
                break;
            case 9:
                res->enter_now.day=atoi(tkn);
                break;
            case 10:
                res->enter_now.hour=atoi(tkn);
                break;
            case 11:
                res->enter_now.minute=atoi(tkn);
                break;
            case 12:
                res->enter_now.second=atoi(tkn);
                break;
            case 13:
                res->exit_now.year=atoi(tkn);
                break;
            case 14:
                res->exit_now.month=atoi(tkn);
                break;
            case 15:
                res->exit_now.day=atoi(tkn);
                break;
            case 16:
                res->exit_now.hour=atoi(tkn);
                break;
            case 17:
                res->exit_now.minute=atoi(tkn);
                break;
            case 18:
                res->exit_now.second=atoi(tkn);
                break;
            case 19:
                res->person.dong=atoi(tkn);
                break;
            case 20:
                strcpy(res->person.contac_num,tkn);
                break;
            case 21:
                res->cost=atof(tkn);
                break;    
            default:
                break;
            }
            tkn=strtok(NULL, ",");
            cnt++;
        }
        if( arrayAdd(lpArray, (const LPDATA) res) ) return 1;
    }
    fclose( pFile );
    return 0;
}

int input_car_save(LPARRAY lpArray){
    FILE *fwp;
    Car_state *res;
    
    if((fwp=fopen("./dat/iparking_state.dat","wb"))==NULL){
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
   
    if((frp=fopen("./dat/iparking_state.dat","rb"))==NULL){
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
    
    if((fwp=fopen("./dat/oparking_state.dat","wb"))==NULL){
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
   
    if((frp=fopen("./dat/oparking_state.dat","rb"))==NULL){
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
