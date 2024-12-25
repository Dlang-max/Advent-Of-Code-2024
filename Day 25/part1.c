#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

#define ROWS 7
#define COLS 5
#define INITIAL_CAPACITY 50
#define BUFFER_SIZE 256

bool can_fit(int *lockHeights, int *keyHeights);
void process_grid();
void process_locks();
void process_keys();

List *locks, *keys;
char grid[ROWS][COLS];

int main() {
  locks = list_init(INITIAL_CAPACITY);
  keys = list_init(INITIAL_CAPACITY);
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  while(fgets(buffer, BUFFER_SIZE, f)) {
    memset(grid, '\0', ROWS * COLS * sizeof(char));
    for(int row = 0; row < ROWS; row++) {
      for(int col = 0; col < COLS; col++) {
        grid[row][col] = buffer[col];
        
      }
      fgets(buffer, BUFFER_SIZE, f);
    }
    process_grid();    
  }
  fclose(f);

  int uniquePairs = 0;
  for(int i = 0; i < locks->size; i++) {
    for(int j = 0; j < keys->size; j++) {      
      if(can_fit(locks->heights[i], keys->heights[j])) {
        uniquePairs++;
      }
    }
  }

  printf("Unique Lock/Key Pairs: %d\n", uniquePairs);
  list_free(locks);
  list_free(keys);
  return 0;
}

bool can_fit(int *lockHeights, int *keyHeights) {
  for(int i = 0; i < COLS; i++) {
    if(lockHeights[i] + keyHeights[i] > ROWS - 2) {
      return false;
    }
  }

  return true;
}


void process_grid() {
  if(grid[0][0] == '#') {
    process_locks();
  } else {
    process_keys();
  }
}

void process_locks() {
  int *heights = calloc(COLS, sizeof(int));
  // process locks
  for(int col = 0; col < COLS; col++) {
    int row = 1, height = 0;
    while(row < ROWS && grid[row][col] == '#') {
      height++;
      row++;
    }
    heights[col] = height;
  }
  list_add(locks, heights);
}

void process_keys() {
  int *heights = calloc(COLS, sizeof(int));
  // process keys
  for(int col = 0; col < COLS; col++) {
    int row = ROWS - 2, height = 0;
    while(row >= 0 && grid[row][col] == '#') {
      height++;
      row--;
    }
    heights[col] = height;
  }
  list_add(keys, heights);
}






