#include <stdio.h>
#include "../include/empty_space_recom.h"
#include "../include/enter_exit_manage.h"

int empty_space_recom(Car_state parking_lot[3][3][10])
{
  int f, r, c; //층, 행, 렬
  int nr, nc; // 다음번에 둘러볼 장소의 위치를 저장하는 변수
  int *rPtr = &r;
  int *cPtr = &c;
  int i=0;

  int visited[3][3][10] = {0,};

  while(1)
  {
    printf("주차하고 싶은 층은 입력해주세요(뒤로 가기 = -1) : \n");
    scanf("%d",&f);getchar();

    // 탈출 및 예외처리
    if(f == -1){
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
    int dr[7] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[7] = {0, 1, 1, 1, 0, -1, -1, -1};

    // Queue를 이용한 bfs
    struct Queue q;
    struct Queue *qPtr;
    init_queue(qPtr); // queue 초기화

    enqueue(qPtr,0,5); // 직원용 출입구는 각 층의 [0][5]와 가장 가깝다고 가정

    //0,5가 빈자리일떄
    if(parking_lot[f][0][5].plate_num == "")
    {
      char rr = (char)(0+(int)'A');
      printf("%d층의 추천 자리는 %c%d입니다.\n", f, rr, 5);
      return 0;
    }

    while(!(isEmpty(qPtr))){
      //해당 자리 주변을 둘러봄
      dequeue(qPtr, rPtr, cPtr);

      for(i=0;i<7;i++){
        nr = r+dr[i];
        nc = c+dc[i];
        
        
        if(! (0<nr && nr<3 && 0<nc && nc<10)){ // 범위를 벗어나면
          continue; // next iteration 
        }

        if (visited[f][nr][nc] == 0) // 방문하지 않은 자리 중에
        { 
          if(parking_lot[f][nr][nc].color == "\0") // 자리에 차가 없으면
          {
            char rr = (char)(nr+(int)'A');
            printf("%d층의 추천 자리는 %c%d입니다.\n", f, rr, nc);
            return 0;
          }
          else
          {
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

int init_queue(struct Queue *queue)
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

int enqueue(struct Queue *queue, int r, int c)
{
  Node *newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적생성

  newNode->r = r;
  newNode->c = c;

  if(isEmpty(queue)) // 비어있을때
  {
    queue->head = newNode; // 맨앞을 newNode로 설정
  }

  queue->tail = newNode;
  queue->size++;
}

int dequeue(struct Queue *queue, int *rPtr, int *cPtr)
{
  int r;
  int c;

  Node *ptr;
  if(isEmpty(queue))
  {
    printf("Empty queue dequeue Error");
      return 1;
  }

  ptr = queue->head; // 정보 추출
  *rPtr = ptr->r;
  *cPtr = ptr->c;
  queue->head = ptr->nxt; // queue의 맨 앞을 다음 노드로 이동
  free(ptr);
  queue->size--;

  return 0;

}
