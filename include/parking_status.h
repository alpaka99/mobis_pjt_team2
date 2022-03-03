#ifndef PARKING_STATUS_H
#define PARKING_STATUS_H

#include "array.h"
#include <stdio.h>
#include "enter_exit_manage.h"

int parking_status_check(LPARRAY lpArray);
int inputline(FILE* fp, char** str, int *str_size);
int info_car_num(LPARRAY lpArray,char *car_num, int *flag);
int info_car_loc(LPARRAY lpArray, char *car_loc, int *flag, int str_size);
int parking_check(LPARRAY lpArray);

#endif