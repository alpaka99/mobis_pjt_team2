//2. 현재 발생된 주차요금 출력
#ifndef FEE_CALCULATE_H 
#define FEE_CALCULATE_H 
int calc_diff_min(Car_state *lpcar, int *ret_diff);
int fee_calculate(Car_state *lpOcar);
int get_car_plate_to_put_fee(LPARRAY lp_input_car_Array, char *car_plate_num);



//int check_owner(int plate_num, Personal* person)

//UI상에서는 car_state의 멤버변수값을 입력받고 car_state목록을 탐색하여 일치하는 car_state를 함수에 입력
//+출차할때, 현재시간, 주차이력관리 각 차에 대해서 적용될것으로 예상

#endif