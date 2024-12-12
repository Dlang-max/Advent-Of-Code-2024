#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct PAPair {
  long perimeter;
  long area;
} PAPair;

#define ROWS 140
#define COLS 140
#define BUFFER_SIZE 256

PAPair calc_perimeter_area(int row, int col, char c);
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
        PAPair pair  = calc_perimeter_area(i, j, grid[i][j]);
        price += (pair.perimeter * pair.area);
      }
    }
  }
  printf("Price: %ld\n", price); 
  return 0;
}

PAPair calc_perimeter_area(int row, int col, char c) {
  PAPair pair;
  if(!in_bounds(row, col) || grid[row][col] != c) {
    pair.perimeter = 1;
    pair.area = 0;
    return pair;
  }

  if(visited[row][col]) {
    pair.perimeter = 0;
    pair.area = 0;
    return pair;
  }
  
  // Mark current position as visited
  visited[row][col] = true;

  PAPair left = calc_perimeter_area(row, col - 1, c);
  PAPair right = calc_perimeter_area(row, col + 1, c);
  PAPair up = calc_perimeter_area(row - 1, col, c);
  PAPair down = calc_perimeter_area(row + 1, col, c);

  pair.perimeter = left.perimeter + right.perimeter + up.perimeter + down.perimeter;
  pair.area = 1 + left.area + right.area + up.area + down.area;  
  return pair;
  
}

bool in_bounds(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
