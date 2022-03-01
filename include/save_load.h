#ifndef SAVE_LOAD_H 
#define SAVE_LOAD_H 
#include "enter_exit_manage.h"

int car_set_save(Car_state *lpcar, int size);
int car_set_load(LPARRAY lpArray);
int input_car_load(LPARRAY lpArray);
int output_car_load(LPARRAY lpArray);
int input_car_save(LPARRAY lpArray);
int output_car_save(LPARRAY lpArray);
#endif 