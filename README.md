환경변수 설정:
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib

실행방법:
cd [파일설치경로]/project/
make
./main

admin권한 비밀번호:
0000

입차 및 출차 내역 초기화:
./init.sh

시나리오를 위해 일정 수의 차량이 입차된 dat을 쓰고 싶은 경우:
cd [파일설치경로]/project/
cp iparking_state.dat dat
