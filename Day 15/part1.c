#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 10
#define COLS 10
#define BUFFER_SIZE 128

typedef struct Robot {
  int row;
  int col;
} Robot;

Robot robot;
char grid[ROWS][COLS];

void simulate_robot(char *moves);
void move_robot(int dRow, int dCol);
bool in_bounds(int row, int col);
void print_grid();

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int row = 0;
  // Build the initial grid
  while(row < ROWS && fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      grid[row][col] = buffer[col];
      // Find the initial location of the robot
      if(buffer[col] == '@') {
        robot.row = row;
        robot.col = col;
      }
    }
    row++;
  }

  // Get rid of the new line character separating the grid
  // and directions
  fgets(buffer, BUFFER_SIZE, f);

  // Read in the directions
  while(fgets(buffer, BUFFER_SIZE, f)) {
    simulate_robot(buffer);
  }

  print_grid();
  
  // Calculate sum of boxes' GPS coordinates
  long gpsSum = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(grid[i][j] == 'O') {
        gpsSum += (100 * i + j);
      }
    }
  }

  printf("GPS Sum: %ld\n", gpsSum);
  return 0;
}

void simulate_robot(char *moves) {
  for(int i = 0; moves[i] != '\0'; i++) {
    char dir = moves[i];
    switch (dir) {
    case '<':
      move_robot(0, -1);
      break;

    case '>':
      move_robot(0, 1);
      break;

    case '^':
      move_robot(-1, 0);
      break;

    case 'v':
      move_robot(1, 0);
      break;

    default:
      printf(":(\n");
      break;
    }
  }
}

void move_robot(int dRow, int dCol) {
  int row = robot.row, col = robot.col;

  int moves = 0;
  int boxesInStack = 0;
  while(true) {
    if(grid[row][col] == '#') {
      break;
    }

    if(grid[row][col] == '.') {
      boxesInStack = moves;
      grid[robot.row][robot.col] = '.';
      robot.row += dRow;
      robot.col += dCol;
      break;
    }
    
    moves++;
    row += dRow;
    col += dCol;
  }

  // Update Grid
  grid[robot.row][robot.col] = '@';
  for(int i = 1; i < boxesInStack; i++) {
    grid[robot.row + (dRow * i)][robot.col + (dCol * i)] = 'O';
  }
  
}

bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}
