#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct PQNode {
  long score;
  int row;
  int col;
  int dir;
} PQNode;

typedef struct PQ {
  int size;
  int tailIndex; 
  PQNode **elements;
} PQ;



#define ROWS 141
#define COLS 141
#define BUFFER_SIZE 256


char grid[ROWS][COLS];
bool visited[ROWS][COLS];

// Start and End points stored as int arrays
// [row, col]
int start[2];
int end[2];

long dijkstra();
void test_pq();
PQ *pq_init();
void pq_free(PQ *pq);
void pq_offer(PQ *pq, PQNode *node);
PQNode *pq_poll(PQ *pq);
bool pq_empty(PQ *pq);
PQNode *pq_peek(PQ* pq);
void print_pq(PQ *pq);

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      char c = buffer[col];
      grid[row][col] = c;
      if(c == 'S') {
        start[0] = row;
        start[1] = col;
      } else if(c == 'E') {
        end[0] = row;
        end[1] = col;
      }
    }
    row++;
  }
  fclose(f);

  long lowestScore = dijkstra();
  printf("Lowest Score: %ld\n", lowestScore);  
  return 0;
}



long dijkstra() {
  // DIRECTOINS:
  //             E  S  W   N
  int dRow[4] = {0, 1, 0, -1};
  int dCol[4] = {1, 0, -1, 0};
  
  PQ *pq = pq_init();
  PQNode *startNode = calloc(1, sizeof(PQNode));
  startNode->score = 0;
  startNode->row = start[0];
  startNode->col = start[1];
  startNode->dir = 0;
  pq_offer(pq, startNode);
  while(!pq_empty(pq)) {
    PQNode *polledNode = pq_poll(pq);
    long score = polledNode->score;
    int row = polledNode->row;
    int col = polledNode->col;
    int dir = polledNode->dir;
    
    if(row == end[0] && col == end[1]) {
      free(polledNode);
      pq_free(pq);
      return score;
    }

    if(visited[row][col] || grid[row][col] == '#') {
      free(polledNode);
      continue;
    }

    visited[row][col] = true;

    // Add next moves to the PriorityQueue
    // Current Direction    
    PQNode *straight = calloc(1, sizeof(PQNode));
    straight->score = score + 1;
    straight->row = row + dRow[dir];
    straight->col = col + dCol[dir];
    straight->dir = dir;
    pq_offer(pq, straight);
    
    // Turn Clockwise
    PQNode *clockwiseTurn = calloc(1, sizeof(PQNode));
    clockwiseTurn->score = score + 1001;
    int newDir = (dir + 1) % 4;
    clockwiseTurn->row = row + dRow[newDir];
    clockwiseTurn->col = col + dCol[newDir];
    clockwiseTurn->dir = newDir;
    pq_offer(pq, clockwiseTurn);

    // Turn Counterclockwise
    PQNode *counterClockwiseTurn = calloc(1, sizeof(PQNode));
    counterClockwiseTurn->score = score + 1001;
    newDir = (dir - 1 + 4) % 4;
    counterClockwiseTurn->row = row + dRow[newDir];
    counterClockwiseTurn->col = col + dCol[newDir];
    counterClockwiseTurn->dir = newDir;
    pq_offer(pq, counterClockwiseTurn);
    
    free(polledNode);
  }
  
  return -1;
}

void test_pq() {
  PQ *pq = pq_init();
  PQNode n1 = {100, 22, 3};
  PQNode n2 = {1, 33, 4};
  PQNode n3 = {20, 2, 5};
  PQNode n4 = {13, 22, 3};
  PQNode n5 = {-2, 33, 4};
  PQNode n6 = {23, 2, 5};
  
  pq_offer(pq, &n1);
  pq_offer(pq, &n2);
  pq_offer(pq, &n3);
  pq_offer(pq, &n4);
  pq_offer(pq, &n5);
  pq_offer(pq, &n6);
  print_pq(pq);

  printf("%ld\n", pq_peek(pq)->score);
  printf("%d\n", pq_empty(pq));

  printf("%ld\n", pq_poll(pq)->score);
  print_pq(pq);
  printf("%ld\n", pq_poll(pq)->score);
  printf("%ld\n", pq_poll(pq)->score);
  print_pq(pq);

  pq_offer(pq, &n5);
  print_pq(pq);
}




// INIT and FREE methods for PriorityQueue
PQ *pq_init() {
  PQNode **elements = calloc(1000, sizeof(PQNode *));
  PQ *pq = calloc(1, sizeof(PQ));

  pq->elements = elements;
  pq->size = 0;
  pq->tailIndex = 0;
  
}

void pq_free(PQ *pq) {
  PQNode **elements = pq->elements;
  for(int i = 0; elements[i] != NULL; i++) {
    free(elements[i]);
  }
  
  free(elements);
  free(pq);
}

void pq_offer(PQ *pq, PQNode *node) {
  pq->elements[pq->tailIndex] = node;
  // Fix Up
  int currIndex = pq->tailIndex;
  int parentIndex = (currIndex - 1) / 2;
  while(currIndex != 0 && pq->elements[currIndex]->score < pq->elements[parentIndex]->score) {
    PQNode *temp = pq->elements[currIndex];
    pq->elements[currIndex] = pq->elements[parentIndex];
    pq->elements[parentIndex] = temp;

    currIndex = parentIndex;
    parentIndex = (currIndex - 1) / 2;
  }

  pq->size++;
  pq->tailIndex++;
}

PQNode *pq_poll(PQ *pq) {
  if(pq_empty(pq)) {
    return NULL;
  }

  PQNode *polledNode = pq->elements[0];
  PQNode *lastNodeOffered = pq->elements[pq->tailIndex - 1];
  
  pq->elements[0] = lastNodeOffered;
  pq->elements[pq->tailIndex - 1] = NULL;
  
  int currIndex = 0;
  int leftChildIndex = 2 * currIndex + 1;
  int rightChildIndex = 2 * currIndex + 2;
  while(pq->elements[leftChildIndex] != NULL &&
        pq->elements[leftChildIndex]->score < pq->elements[currIndex]->score ||
        pq->elements[rightChildIndex] != NULL &&
        pq->elements[rightChildIndex]->score < pq->elements[currIndex]->score) {

    if(pq->elements[leftChildIndex] != NULL &&
       pq->elements[rightChildIndex] != NULL) {
      
      int minIndex = pq->elements[leftChildIndex]->score < pq->elements[rightChildIndex]->score ? leftChildIndex : rightChildIndex;
     
      PQNode *temp = pq->elements[currIndex];
      pq->elements[currIndex] = pq->elements[minIndex];
      pq->elements[minIndex] = temp;

      currIndex = minIndex;
      leftChildIndex = 2 * currIndex + 1;
      rightChildIndex = 2 * currIndex + 2;
    } else {
      PQNode *temp = pq->elements[currIndex];
      pq->elements[currIndex] = pq->elements[leftChildIndex];
      pq->elements[leftChildIndex] = temp;

      currIndex = leftChildIndex;
      leftChildIndex = 2 * currIndex + 1;
      rightChildIndex = 2 * currIndex + 2;
    }
  }

  pq->size--;
  pq->tailIndex--;

  return polledNode;
}

bool pq_empty(PQ *pq) {
  return pq->size == 0;
}

PQNode *pq_peek(PQ* pq) {
  if(pq_empty(pq)) {
    return NULL;
  }
  
  return pq->elements[0];
}

void print_pq(PQ *pq) {
  for(int i = 0; pq->elements[i] != NULL; i++) {
    printf("(%d, %d) ", pq->elements[i]->row, pq->elements[i]->col);
  }
  printf("\n");
}


