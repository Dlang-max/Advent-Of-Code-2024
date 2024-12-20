#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"

#define SKIP_THRESHOLD 100
#define SKIPS 2
#define ROWS 141
#define COLS 141
#define BUFFER_SIZE 256

char grid[ROWS][COLS];
int visited[ROWS][COLS];

int start[2];
int end[2];

void bfs();
int count_skips();
void print_visited();

int max(int a, int b);
int min(int a, int b);

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  // Read in the input file
  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      grid[row][col] = buffer[col];
      if(buffer[col] == 'S') {
        start[0] = row;
        start[1] = col;
      } else if(buffer[col] == 'E') {
        end[0] = row;
        end[1] = col;
      }
    }
    row++;
  }
  fclose(f);

  memset(visited, -1, ROWS * COLS * sizeof(int));
  bfs();
  int skips = count_skips();
  
  printf("Part 1:\n");
  printf("Score: %d\n",visited[end[0]][end[1]]);
  printf("Skips: %d\n", skips);
  
  return 0;
}

// Find the number of steps to reach the end
void bfs() {
  int directions[5] = {1, 0, -1, 0, 1};

  Queue *queue = queue_init();
  queue_offer(queue, start[0], start[1], 0);
  visited[start[0]][start[1]] = 0;
  
  while(!queue_empty(queue)) {
    QueueNode *polledNode = queue_poll(queue);
    int row = polledNode->row;
    int col = polledNode->col;
    int steps = polledNode->steps;
    free(polledNode);
    
    if(row == end[0] && col == end[1]) {
      queue_free(queue);
      return;
    }

    for(int i = 1; i < 5; i++) {
      int nRow = row + directions[i - 1];
      int nCol = col + directions[i];

      if(visited[nRow][nCol] == -1 && grid[nRow][nCol] != '#') {
        queue_offer(queue, nRow, nCol, steps + 1);
        visited[nRow][nCol] = steps + 1;
      }
    }
  }
  queue_free(queue);
}

int count_skips() {
  int directions[5] = {1, 0, -1, 0, 1};
  Queue *queue = queue_init();
  queue_offer(queue, start[0], start[1], 0);

  int skips = 0;
  while(!queue_empty(queue)) {
    QueueNode *polledNode = queue_poll(queue);
    int row = polledNode->row;
    int col = polledNode->col;
    int steps = polledNode->steps;
    free(polledNode);

    if(row == end[0] && col == end[1]) {
      queue_free(queue);
      return skips;
    }

    for(int i = 1; i < 5; i++) {
      int nRow = row + directions[i - 1], nCol = col + directions[i];
      if(visited[nRow][nCol] > steps) {
        queue_offer(queue, nRow, nCol, steps + 1);
      }
    }

    // Find valid skips by iterating over a 20x20 section of the input grid.
    // Will only visit possible skip locations once, so we don't have to worry
    // about a skip starting and ending at the same postion.
    for(int i = max(0, row - SKIPS); i <= min(ROWS - 1, row + SKIPS); i++) {
      for(int j = max(0, col - SKIPS); j <= min(COLS - 1, col + SKIPS); j++) {
        if(grid[i][j] != '#') {
           int manhattan_dist = abs(row - i) + abs(col - j);
           if(manhattan_dist <= SKIPS &&
              visited[i][j] - visited[row][col] - manhattan_dist >= SKIP_THRESHOLD) {
             skips++;
           }
        }
      }
    }
  }
  
  queue_free(queue);
  return -1;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

void print_visited() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(visited[i][j] == -1) {
        printf(".");
      } else {
        printf("X");
      }
    }
    printf("\n");
  }
}

