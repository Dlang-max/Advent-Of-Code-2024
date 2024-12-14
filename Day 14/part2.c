#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define ROWS 103
#define COLS 101
#define ROBOTS 500
#define ITERATIONS 100
#define CONNECTED_THRESHOLD 100
#define BUFFER_SIZE 256

typedef struct Robot {
  int row;
  int col;

  int dRow;
  int dCol;
} Robot;

char grid[ROWS][COLS];
bool visited[ROWS][COLS];
Robot robots[ROBOTS];

void update_grid();
bool found_christmas_tree();
int connected_robots(int row, int col);
bool in_bounds(int row, int col);
void print_grid();

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int currRobot = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    int row, col, dRow, dCol;
    sscanf(buffer, "p=%d,%d v=%d, %d", &col, &row, &dCol, &dRow);
    Robot robot = {row, col, dRow, dCol};
    robots[currRobot++] = robot;
  }

  int iterations = 0;
  while(true) {
    // update the positions of all robots
    for(int j = 0; j < ROBOTS; j++) {
      Robot robot = robots[j];
      robot.row = (robot.row + robot.dRow) % ROWS;
      robot.row += robot.row < 0 ? ROWS : 0;
      robots[j].row = robot.row;

      robot.col = (robot.col + robot.dCol) % COLS;
      robot.col += robot.col < 0 ? COLS : 0;
      robots[j].col = robot.col;
    }
    
    update_grid();
    iterations++;
    // Performs a DFS to see if the number of connected robots
    // is greater than 100. Arbitrary threshold. Assumed if there
    // are this many connected robots, then a christmas tree was formed.
    if(found_christmas_tree()) {
      break;
    }    
  }
  
  printf("Iterations: %d\n", iterations);
  print_grid();
  
  return 0;
}

void update_grid() {
  // Clear grid
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      grid[i][j] = '.';
      visited[i][j] = false;
    }
  }
  
  // Add robots to grid
  for(int i = 0; i < ROBOTS; i++) {
    grid[robots[i].row][robots[i].col] = 'R';
  }
}

// Iterate over the grid to see if there is a christmas tree
bool found_christmas_tree() {
  for(int i = 0; i < ROWS; i++) {
    for(int  j = 0; j < COLS; j++) {
      if(grid[i][j] == 'R' && !visited[i][j] && connected_robots(i, j) >= CONNECTED_THRESHOLD) {
        return true;
      }
    }
  }

  return false;
}

// Find the number of connected robots in a connected component
int connected_robots(int row, int col) {
  if(!in_bounds(row, col) || visited[row][col] || grid[row][col] != 'R') {
    return 0;
  }
  
  visited[row][col] = true;

  int total = 1;
  // Horizontal and Vertical
  int dirs[5] = {1, 0, -1, 0, 1};
  for(int i = 1; i < 5; i++) {
    total += connected_robots(row + dirs[i - 1], col + dirs[i]);
  }
  // Diagonal
  int dRows[4] = {-1, -1, 1, 1};
  int dCols[4] = {-1, 1, -1, 1};
  for(int i = 0; i < 4; i++) {
    total += connected_robots(row + dRows[i], col + dCols[i]);
  }
  
  return total;
}

// Check if a given row and col are inside the bounds of the grid
bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

// Print grid of robots
void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}
