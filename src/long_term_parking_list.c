#include <stdio.h>
#include "array.h"
#include "long_term_parking_list.h"
#include "enter_exit_manage.h"
#include <time.h>

int time_output(Car_state *lpcar)
{
    printf("입차시각(y) = %d  \n", lpcar->enter_now.year);
    return 0;
}
int long_term_parking_list(LPARRAY lpArray){
    int nErr = ERR_ARRAY_OK;
    Car_state *lpcar;
    int size = arraySize(lpArray);
    for(int i = 0; i < size; i++){
    nErr = arrayGetAt(lpArray, i, (LPDATA*) &lpcar);
    if (ERR_ARRAY_OK != nErr) return 1;
    time_output(lpcar);
    }
    return 0;
}