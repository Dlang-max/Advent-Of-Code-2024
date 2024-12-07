#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Guard {
  int dir;
  int row;
  int col;
} Guard;

#define ROWS 130
#define COLS 130
#define BUFFER_SIZE 256
#define MAX_STEPS (ROWS * COLS)

int simulate_guard(Guard guard);
bool is_looping(Guard guard);
bool in_bounds(int row, int col);
bool is_obstacle(int row, int col);
void print_grid(void);

// Declare grid and visited matrices as a global variable
bool obstacles[ROWS][COLS];

// Used to avoid placing an obstacle at the same position more than once
bool prevPlacedObstacles[ROWS][COLS];

// How we should update rows and columns based on direction
int rDirs[4] = {-1, 0, 1, 0};
int cDirs[4] = {0, 1, 0, -1};

int main() {
  FILE *f = fopen("./input.txt", "r");
  char buffer[BUFFER_SIZE];

  Guard guard;
  int row = 0;
  // Build the grid and find the guard's starting position
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      if(buffer[col] == '^') {
        guard.dir = 0;
        guard.row = row;
        guard.col = col;
        
        obstacles[row][col] = false;
    
        // Mark the guard's starting position as an invalid place
        // to place an obstacle
        prevPlacedObstacles[row][col] = true;
      } else if (buffer[col] == '#') {
        obstacles[row][col] = true;
      } else {
        obstacles[row][col] = false;
      }
    }
    row++;
  }
  int numLoopsCreated = simulate_guard(guard);
  printf("Loops Created: %d\n", numLoopsCreated);
  
  return 0;
}



int simulate_guard(Guard start) {
  int numLoopsCreated = 0;
  
  Guard guard = start;
  while(true) {
    int nextRow = guard.row + rDirs[guard.dir];
    int nextCol = guard.col + cDirs[guard.dir];

    // We leave the grid on our next move
    if(!in_bounds(nextRow, nextCol)) {
      break;
    }
    
    if(is_obstacle(nextRow, nextCol)) {
      guard.dir = (guard.dir + 1) % 4;
      continue;
    }

    obstacles[nextRow][nextCol] = true;
    if(!prevPlacedObstacles[nextRow][nextCol] && is_looping(start)) {
      numLoopsCreated++;
    }
    obstacles[nextRow][nextCol] = false;

    prevPlacedObstacles[nextRow][nextCol] = true;
    guard.row = nextRow;
    guard.col = nextCol;
  }
  
  return numLoopsCreated;
}

bool is_looping(Guard guard) {
  int steps = 0;
  while(true) {
    int nextRow = guard.row + rDirs[guard.dir];
    int nextCol = guard.col + cDirs[guard.dir];

    // We leave the frid on our next move
    if(!in_bounds(nextRow, nextCol)) {
      return false;
    }
    
    if(is_obstacle(nextRow, nextCol)) {
      guard.dir = (guard.dir + 1) % 4;
      continue;
    }
    
    guard.row = nextRow;
    guard.col = nextCol;

    steps++;
    if(steps > MAX_STEPS) {
      return true;
    }
  }
  
  return false; 
}






bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

bool is_obstacle(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS && obstacles[row][col];
}

void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(obstacles[i][j]) {
        printf("%c", '#');
      } else {
        printf("%c", '.');
      }
    }
    printf("\n");
  }
}
