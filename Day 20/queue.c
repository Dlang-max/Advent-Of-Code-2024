#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

// Queue Methods
Queue *queue_init() {
  QueueNode *head = calloc(1, sizeof(QueueNode)) ;
  head->row = -1;
  head->col = -1;
  head->steps = -1;
  head->prev = NULL;

  QueueNode *tail = calloc(1, sizeof(QueueNode)) ;
  tail->row = -1;
  tail->col = -1;
  head->steps = -1;
  tail->prev = head;
  tail->next = NULL;
  head->next = tail;


  Queue *queue = calloc(1, sizeof(Queue));
  queue->size = 0;
  queue->tail = tail;
  queue->head = head;
}


bool queue_empty(Queue *queue) {
  return queue->size == 0;
}

void queue_free(Queue *queue) {
  QueueNode *curr = queue->head->next;
  while(curr != queue->tail) {
    QueueNode *temp = curr;
    curr = curr->next;
    free(temp);
  }

  free(queue->tail);
  free(queue->head);
  free(queue);
}

void queue_offer(Queue *queue, int row, int col, int steps) {
  QueueNode *newNode = calloc(1, sizeof(QueueNode));
  newNode->row = row;
  newNode->col = col;
  newNode->steps = steps;

  // head <---> node <---> tail
  newNode->prev = queue->tail->prev;
  newNode->next = queue->tail;

  queue->tail->prev->next = newNode;
  queue->tail->prev = newNode;
  queue->size++;

}

QueueNode *queue_poll(Queue *queue) {
  QueueNode *polledNode = queue->head->next;
  queue->head->next = polledNode->next;
  polledNode->next->prev = queue->head;
  queue->size--;

  return polledNode;
}

void print_queue(Queue *queue) {
  if(queue_empty(queue)) {
    return;
  }
  QueueNode *curr = queue->head->next;
  while(curr != queue->tail) {
    printf("(%d, %d) ", curr->row, curr->col);
    curr = curr->next;
  }
  printf("\n");
}
