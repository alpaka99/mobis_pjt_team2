#include <stdio.h>
#include <stdlib.h>
#include "../include/empty_space_recom.h"
#include "../include/enter_exit_manage.h"
#include <string.h>
#include "display_parking_lot.h"

int empty_space_recom(Car_state parking_lot[3][3][10])
{
  int f, r, c; //층, 행, 렬
  int nr, nc; // 다음번에 둘러볼 장소의 위치를 저장하는 변수
  int *rPtr = &r;
  int *cPtr = &c;
  int i=0;
  struct Queue q;
  struct Queue *qPtr = &q;

  int visited[3][3][10] = {0,};

  while(1)
  {
    printf("주차하고 싶은 층을 입력해주세요.(0: 이전으로, 1: B1, 2: B2, 3:B3)\n");
    char c;
    c=getchar(); clear_buffer();
    f=(int)c-'0'; 

    // 탈출 및 예외처리
    if(f == 0){
      return 0;
    }
    else if(f>=1 && f<=3){
      f--;
    }
    else{
      printf("옳지 않은 층입니다.\n");
      continue;
    }

    // delta를 사용해서 탐색
    // W, SW, S, SE, E, NE, N, NW
    int dr[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dc[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

// 여기까지 괜춘

    // Queue를 이용한 bfs
    
    init_queue(qPtr); // queue 초기화

    enqueue(qPtr,0,4); // 직원용 출입구는 각 층의 [0][5]와 가장 가깝다고 가정
    visited[f][0][4] = 1;

    //0,5가 빈자리일떄
    if(strcmp(parking_lot[f][0][4].plate_num, "")==0)
    {
      char rr = (char)(0+(int)'A');
      printf("지하 %d층의 추천 자리는 %c%d입니다.\n", f+1, rr, 5);
      return 0;
    }

    while(!(isEmpty(qPtr))){
      //해당 자리 주변을 둘러봄
      dequeue(qPtr, rPtr, cPtr);

      for(i=0;i<8;i++){
        nr = r+dr[i];
        nc = c+dc[i];
        
        printf("%d %d %d : ", f, nr, nc);
        if((0<=nr && nr<=2 && 0<=nc && nc<=9) == 0){ // 범위를 벗어나면
          // printf("CCCCC %d %d\n", nr, nc);
          continue; // next iteration 
        }

        if (visited[f][nr][nc] == 0) // 방문하지 않은 자리 중에
        { 
          if(strcmp(parking_lot[f][nr][nc].plate_num, "")==0) // 자리에 차가 없으면
          {
            char rr = (char)(nr+(int)'A');
            printf("지하 %d층의 추천 자리는 %c%d입니다.\n", f+1, rr+1, nc+1);
            // printf("%d %c %d\n", f, rr, nc);
            return 0;
          }
          else
          {
            // printf("%d %d\n", nr, nc);
            enqueue(qPtr, nr, nc); // queue에 넣고 다음 기준점으로 삼기
            visited[f][nr][nc] = 1;
          }
        }
      }
    }
    // 다 돌았는데 추천 자리가 없음 -> 꽉찼다.
    printf("이 층은 만차입니다! 다른 층을 이용해주세요\n");
    break;
  }
  return 1;
}

void init_queue(struct Queue *queue)
{
  queue->head = queue->tail = NULL;
  queue->size = 0;
};

int isEmpty(struct Queue *queue)
{
  if (queue->size == 0)
    return 1;
  else
    return 0;
}

void enqueue(struct Queue *queue, int r, int c)
{
  Node *newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적생성

  newNode->r = r;
  newNode->c = c;

  newNode->nxt = NULL;

  if(isEmpty(queue)) // 비어있을때
  {
    queue->head = newNode; // 맨앞을 newNode로 설정
  }
  else // queue가 안비었을떄
  {
    queue->tail->nxt = newNode; //현재 맨 뒤의 다음을 newNode로 설정
  }

  queue->tail = newNode; // 현재 맨 뒤를 한칸 뒤로 (nowNode로) 옮김
  queue->size++;
}

void dequeue(struct Queue *queue, int *rPtr, int *cPtr)
{
    Node *ptr;
    if(isEmpty(queue))
    {
      printf("Empty queue dequeue Error");
      return;
    }
    ptr = queue->head; // 정보 추출
    *rPtr = ptr->r;
    *cPtr = ptr->c;
    queue->head = ptr->nxt; // queue의 맨 앞을 다음 노드로 이동
    free(ptr);
    queue->size--;

}
