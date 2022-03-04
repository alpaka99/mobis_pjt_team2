#include "enter_exit_manage.h"
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

int empty_space_recom(struct Car_state parking_lot[3][3][10]);
void init_queue(struct Queue *queue);
int isEmpty(struct Queue *queue);
void enqueue(struct Queue *queue, int r, int c);
void dequeue(struct Queue *queue, int *rPtr, int *cPtr);
