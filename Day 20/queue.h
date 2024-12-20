#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct QueueNode {
  int row;
  int col;
  int steps;

  struct QueueNode *prev;
  struct QueueNode *next;
}QueueNode;

typedef struct Queue {
  int size;
  QueueNode *head;
  QueueNode *tail;
}Queue;

Queue *queue_init();
void test_queue();
bool queue_empty(Queue *queue);
void queue_free(Queue *queue);
void queue_offer(Queue *queue, int row, int col, int steps);
QueueNode *queue_poll(Queue *queue);
void print_queue(Queue *queue);

#endif 
