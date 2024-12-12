#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct ASPair {
  long area;
  long sides;
} ASPair;

#define ROWS 140
#define COLS 140
#define BUFFER_SIZE 256

ASPair calc_area_sides(int row, int col, char c);
long check_sides(int row, int col, char c);
bool in_bounds(int row, int col);

char grid[ROWS][COLS];
bool visited[ROWS][COLS];

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      grid[row][col] = buffer[col];
    }
    row++;
  }
  fclose(f);

  

  long price = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(!visited[i][j]) {
        ASPair pair  = calc_area_sides(i, j, grid[i][j]);
        price += (pair.area * pair.sides);
      }
    }
  }
  printf("Price: %ld\n", price); 
  return 0;
}

ASPair calc_area_sides(int row, int col, char c) {
  ASPair pair;
  if(!in_bounds(row, col) || grid[row][col] != c || visited[row][col]) {
    pair.area = 0;
    pair.sides = 0;
    return pair;
  }
  
  // Mark current position as visited
  visited[row][col] = true;

  ASPair left = calc_area_sides(row, col - 1, c);
  ASPair right = calc_area_sides(row, col + 1, c);
  ASPair up = calc_area_sides(row - 1, col, c);
  ASPair down = calc_area_sides(row + 1, col, c);

  pair.area = 1 + left.area + right.area + up.area + down.area;  
  pair.sides = left.sides + right.sides + up.sides + down.sides;
  pair.sides += check_sides(row, col, c);
  
  return pair;
}

// Can count sides by counting corners
long check_sides(int row, int col, char c) {
  long sides = 0;
  int dRows[4] = {-1, -1, 1, 1};
  int dCols[4] = {-1, 1, -1, 1};

  for(int i = 0; i < 4; i++) {
    //   +---+  --> Outside corners
    //   |   |
    //   +---+

    // Check for outside corners
    if((!in_bounds(row + dRows[i], col) || grid[row + dRows[i]][col] != c) &&
       (!in_bounds(row, col + dCols[i]) || grid[row][col + dCols[i]] != c)) {
      sides++;
    }

    //           Inside corner
    //    +---+ ^
    //    |   |/
    // +--+   +--+
    // |         |
    // +---------+
    
    // Check for inside corners
    if((in_bounds(row + dRows[i], col) && grid[row + dRows[i]][col] == c) &&
       (in_bounds(row, col + dCols[i]) && grid[row][col + dCols[i]] == c) &&
       grid[row + dRows[i]][col + dCols[i]] != c) {
      sides++;
    }
    
  }
  
  return sides;
}

bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
