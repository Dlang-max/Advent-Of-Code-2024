#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROWS 130
#define COLS 130
#define BUFFER_SIZE 256



int simulate_guard(char grid[ROWS][COLS], int row, int col);
bool guard_in_bounds(int row, int col);

int main() {
  char grid[ROWS][COLS] = {};
  
  FILE *f = fopen("./input.txt", "r");
  char buffer[BUFFER_SIZE];

  // Build the grid and find the guard's starting position
  int row = 0;
  int guardRow = 0;
  int guardCol = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      grid[row][col] = buffer[col];
      if(buffer[col] == '^') {
        guardRow = row;
        guardCol = col;
      }
    }
    row++;
  }
  flcose(f);
  
  int uniqueSpaces = simulate_guard(grid, guardRow, guardCol);
  printf("Unique Spaces Visited: %d\n", uniqueSpaces);
  return 0;
}

int simulate_guard(char grid[ROWS][COLS], int row, int col) {
  int uniqueSpaces = 0;
  while(guard_in_bounds(row, col)) {
    int nextRow;
    int nextCol;
    
    char guard = grid[row][col];
    char nextGuard;
    
    switch (guard) {  
    case '^':
      nextRow = row - 1;
      nextCol = col;
      nextGuard = '>';
      break;
      
    case 'V':
      nextRow = row + 1;
      nextCol = col;
      nextGuard = '<';
      break;

    case '<':
      nextRow = row;
      nextCol = col - 1;
      nextGuard = '^';
      break;

    case '>':
      nextRow = row;
      nextCol = col + 1;
      nextGuard = 'V';
      break;
      
    default:
      break;
    }

    if(!guard_in_bounds(nextRow, nextCol)) {
      break;
    }

    if(grid[nextRow][nextCol] == '#') {
      grid[row][col] = nextGuard;
    } else if (grid[nextRow][nextCol] == 'X') {
      uniqueSpaces--;
      grid[nextRow][nextCol] = guard;
    } else {
      grid[row][col] = 'X';
      uniqueSpaces++;
      
      grid[nextRow][nextCol] = guard;
      row = nextRow;
      col = nextCol;
    }
  }

  return uniqueSpaces + 1;
}

bool guard_in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
