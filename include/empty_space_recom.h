// 안쓰는 함수
typedef struct Node{
  int r;
  int c;
  
  struct Node *nxt;
}Node;

typedef struct Queue{
  Node *head;
  Node *tail;
  int size;
}queue;

int empty_space_recom(Car_state parking_lot[3][3][10]);
int init_queue(struct Queue *queue);
int isEmpty(struct Queue *queue);
int enqueue(struct Queue *queue, int r, int c);
int dequeue(struct Queue *queue, int *rPtr, int *cPtr);
