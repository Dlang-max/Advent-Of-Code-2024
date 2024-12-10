#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROWS 40
#define COLS 40
#define BUFFER_SIZE 64

int dfs(char grid[ROWS][COLS], bool visited[ROWS][COLS], int row, int col, int currVal);
bool in_bounds(int row, int col);
void clear_visited(bool visited[ROWS][COLS]);


int main() {
  
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("input.txt", "r");

  char grid[ROWS][COLS];
  bool visited[ROWS][COLS];
  
  // Load the grid from the input file
  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      grid[row][col] = buffer[col];
    }
    row++;
  }
  fclose(f);

  
  // Process the grid
  int trailheadScores = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {    
      if(grid[i][j] == '0') {
        clear_visited(visited);
        trailheadScores += dfs(grid, visited, i, j, 0);
      }
      
    }
  }

  printf("Trailhead Scores: %d\n", trailheadScores);
  
  return 0;
}

int dfs(char grid[ROWS][COLS], bool visited[ROWS][COLS], int row, int col, int currVal) {
  if(!in_bounds(row, col) || visited[row][col] || grid[row][col] - '0' != currVal) {
    return 0;
  }
  
  if(currVal == 9) {
    return 1;
  }
  
  visited[row][col] = true;
  int left = dfs(grid, visited, row, col - 1, currVal + 1);
  visited[row][col] = false;

  visited[row][col] = true;
  int right = dfs(grid, visited, row, col + 1, currVal + 1);
  visited[row][col] = false;

  visited[row][col] = true;
  int up = dfs(grid, visited, row - 1, col, currVal + 1);
  visited[row][col] = false;

  visited[row][col] = true;
  int down = dfs(grid, visited, row + 1, col, currVal + 1);
  visited[row][col] = false;
  

  return left + right + up + down;
}

bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

void clear_visited(bool visited[ROWS][COLS]) {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      visited[i][j] = false;
    }
  }  
}
