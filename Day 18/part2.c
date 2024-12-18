#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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



#define ROWS 71
#define COLS 71
#define BUFFER_SIZE 256

char grid[ROWS][COLS];
bool visited[ROWS][COLS];

Queue *queue_init();
void test_queue();
bool queue_empty(Queue *queue);
void queue_free(Queue *queue);
void queue_offer(Queue *queue, int row, int col, int steps);
QueueNode *queue_poll(Queue *queue);
void print_queue(Queue *queue);

int bfs();
bool in_bounds(int row, int col);
void clear_visited();
void print_grid();

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  while(fgets(buffer, BUFFER_SIZE, f)) {
    int row, col;
    sscanf(buffer, "%d,%d", &row, &col);
    grid[row][col] = '#';

    if(bfs() == -1) {
      printf("(%d, %d)\n", row, col);
      grid[row][col] = '8';
      print_grid();
      break;
    }
  }

  return 0;
}


int bfs() {
  clear_visited();
  int directions[5] = {1, 0, -1, 0, 1};
  
  Queue *queue = queue_init();
  queue_offer(queue, 0, 0, 0);
  visited[0][0] = true;

  while(!queue_empty(queue)) {
    QueueNode *polledNode = queue_poll(queue);
    int row = polledNode->row;
    int col = polledNode->col;
    int steps = polledNode->steps;

    if(row == ROWS - 1 && col == COLS - 1) {
      free(polledNode);
      queue_free(queue);
      return steps;
    }

    for(int i = 1; i < 5; i++) {
      int nRow = row + directions[i - 1];
      int nCol = col + directions[i];

      if(!visited[nRow][nCol] && in_bounds(nRow, nCol) && grid[nRow][nCol] != '#') {
        queue_offer(queue, nRow, nCol, steps + 1);
        visited[nRow][nCol] = true;
      }
    }
    free(polledNode);
  }

  queue_free(queue);
  return -1;
}

void clear_visited() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      visited[i][j] = false;
    }
  }
}

bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}




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


void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(grid[i][j] == '8') {
        printf("8");
      } else if(grid[i][j] != '#') {
        printf(".");
      } else {
        printf("#");
      }
    }
    printf("\n");
  }
}
