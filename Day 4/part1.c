#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 140
#define COLS 141
#define BUFFER_SIZE 142

int search(char wordSearch[ROWS][COLS], int row, int col);
int search_direction(char wordSearch[ROWS][COLS], int row, int col, int rDir, int cDir);
bool is_valid_pos(int row, int col);

int main() {
  FILE *f = fopen("./input.txt", "r");

  char buffer[BUFFER_SIZE];
  // Build the word search matrix
  char wordSearch[ROWS][COLS];
  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      wordSearch[row][col] = buffer[col];
    }
    row++;
  }

  // Search word search for XMAS
  int xmasCount = 0;
  for(int row = 0; row < ROWS; row++) {
    for(int col = 0; col < COLS; col++) {
      if(wordSearch[row][col] == 'X') {
        xmasCount += search(wordSearch, row, col);
      }
    }
  }  
  fclose(f);
  printf("XMAS Count: %d\n", xmasCount);
  return 0;
}



int search(char wordSearch[ROWS][COLS], int row, int col) {
  int xmasCount = 0;
  // Search left
  xmasCount +=  search_direction(wordSearch, row, col, 0, -1);

  // Search right
  xmasCount += search_direction(wordSearch, row, col, 0, 1);

  // search up
  xmasCount += search_direction(wordSearch, row, col, -1, 0);

  // search down
  xmasCount += search_direction(wordSearch, row, col, 1, 0);

  // search up left
  xmasCount += search_direction(wordSearch, row, col, -1, -1);

  // serach up right
  xmasCount += search_direction(wordSearch, row, col, -1, 1);

  // search down left
  xmasCount += search_direction(wordSearch, row, col, 1, -1);

  // search down right
  xmasCount += search_direction(wordSearch, row, col, 1, 1);

  return xmasCount;
}

int search_direction(char wordSearch[ROWS][COLS], int row, int col, int rDir, int cDir) {
  char str[5] = {};
  for(int i = 0; i < 4; i++) {
    int nextRow = row + (i * rDir);
    int nextCol = col + (i * cDir);
    if(!is_valid_pos(nextRow, nextCol)) {
      break;
    }
    str[i] = wordSearch[nextRow][nextCol];
  }

  return strcmp("XMAS", str) == 0 ? 1 : 0;
}

bool is_valid_pos(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
