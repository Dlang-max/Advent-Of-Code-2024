#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 50
#define COLS 50
#define BUFFER_SIZE 128

typedef struct Robot {
  int row;
  int col;
} Robot;

Robot robot;
char grid[ROWS][2 * COLS];

void simulate_robot(char *moves);
void move_robot(int dRow, int dCol);
bool can_move(int row, int col, int dRow, int dCol);
void move_boxes_up_or_down(int row, int col, int dRow, int dCol);
void print_grid();

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int row = 0;
  // Build the initial grid
  while(row < ROWS && fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      if(buffer[col] == '@') {
        grid[row][2 * col] = '@';
        grid[row][2 * col + 1] = '.';

        // Set the intitial position of the robt
        robot.row = row;
        robot.col = 2 * col;
      } else if (buffer[col] == 'O') {
        grid[row][2 * col] = '[';
        grid[row][2 * col + 1] = ']';
      } else {
        grid[row][2 * col] = buffer[col];
        grid[row][2 * col + 1] = buffer[col];
      }
    }
    row++;
  }
  // Initial Grid
  print_grid();

  // Get rid of the new line character separating the grid
  // and directions
  fgets(buffer, BUFFER_SIZE, f);

  /* Read in the directions */
  while(fgets(buffer, BUFFER_SIZE, f)) {
    simulate_robot(buffer);
  }

  // Final Grid
  print_grid();
  
  // Calculate sum of boxes' GPS coordinates
  long gpsSum = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < 2 * COLS; j++) {
      if(grid[i][j] == '[') {
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
      continue;
      break;
    }
  }
}

void move_robot(int dRow, int dCol) {
  // Move robot and boxes up or down
  if(dCol == 0) {
    if(!can_move(robot.row, robot.col, dRow, dCol)) {
      return;
    }
    move_boxes_up_or_down(robot.row, robot.col, dRow, dCol);
    robot.row += dRow;

    return;
  }


  
  // Move robot and boxes left and right
  int row = robot.row, col = robot.col;

  int moves = 0;
  int boxesInStack = 0;
  while(true) {
    if(grid[row][col] == '#') {
      break;
    }

    if(grid[row][col] == '.') {
      boxesInStack = moves / 2;
      grid[robot.row][robot.col] = '.';
      robot.row += dRow;
      robot.col += dCol;
      break;
    }
    
    moves++;
    row += dRow;
    col += dCol;
  }

  grid[robot.row][robot.col] = '@';
  for(int i = 0; i < boxesInStack; i++) {
    int nextCol = robot.col + (i * dCol * 2);
    if(dCol == -1) {
      // move left
      grid[robot.row][nextCol - 2] = '[';
      grid[robot.row][nextCol - 1] = ']';      
    } else {
      //move right
      grid[robot.row][nextCol + 1] = '[';
      grid[robot.row][nextCol + 2] = ']';  
    }
  } 
}

bool can_move(int row, int col, int dRow, int dCol) {
  if(grid[row][col] == '#') {
    return false;
  }

  if(grid[row][col] == '.') {
    return true;
  }

  if(grid[row][col] == '@') {
    return can_move(row + dRow, col, dRow, dCol);
  }
  
  if(grid[row][col] == ']') {
    return can_move(row + dRow, col, dRow, dCol) && can_move(row + dRow, col - 1, dRow, dCol);
  } else if(grid[row][col] == '[') {
    return can_move(row + dRow, col, dRow, dCol) && can_move(row + dRow, col + 1, dRow, dCol);
  }
}

void move_boxes_up_or_down(int row, int col, int dRow, int dCol) {
  if(grid[row][col] == '.') {
    return;
  }

  if(grid[row][col] == '@') {
    move_boxes_up_or_down(row + dRow, col, dRow, dCol);
    grid[row][col] = '.';
    grid[row + dRow][col] = '@';

    robot.row = row;
    robot.col = col;
  }

  if(grid[row][col] == ']') {
    move_boxes_up_or_down(row + dRow, col, dRow, dCol);
    move_boxes_up_or_down(row + dRow, col - 1, dRow, dCol);

    grid[row][col] = '.';
    grid[row][col - 1] = '.';

    grid[row + dRow][col] = ']';
    grid[row + dRow][col - 1] = '[';
    
  } else if(grid[row][col] == '[') {
    move_boxes_up_or_down(row + dRow, col, dRow, dCol);
    move_boxes_up_or_down(row + dRow, col + 1, dRow, dCol);

    grid[row][col] = '.';
    grid[row][col + 1] = '.';

    grid[row + dRow][col] = '[';
    grid[row + dRow][col + 1] = ']';
  }
}

void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < 2 * COLS; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}
