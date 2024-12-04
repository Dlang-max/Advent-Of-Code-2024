#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 140
#define COLS 141
#define BUFFER_SIZE 142

int search(char wordSearch[ROWS][COLS], int row, int col);
bool pattern_matches(char wordSearch[ROWS][COLS], char pattern[4], int row, int col);
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
      if(wordSearch[row][col] == 'A') {
        xmasCount += search(wordSearch, row, col);
      }
    }
  }
  
  fclose(f);
  printf("XMAS Count: %d\n", xmasCount);
  return 0;
}



int search(char wordSearch[ROWS][COLS], int row, int col) {
  // Check that all positions are valid
  if(!is_valid_pos(row - 1, col - 1) ||
     !is_valid_pos(row + 1, col - 1) ||
     !is_valid_pos(row - 1, col + 1) ||
     !is_valid_pos(row + 1, col + 1)) {
    return 0;
  }

  char patterns[4][4] = {
    {'M', 'M', 'S', 'S'},
    {'S', 'S', 'M', 'M'},
    {'M', 'S', 'M', 'S'},
    {'S', 'M', 'S', 'M'},
  };
    for(int i = 0; i < 4; i++) {
      if(pattern_matches(wordSearch, patterns[i], row, col)) {
        return 1;
      }
    }

  return 0;  
}

bool pattern_matches(char wordSearch[ROWS][COLS], char pattern[4], int row, int col) {
  return pattern[0] == wordSearch[row - 1][col - 1] && pattern[1] == wordSearch[row + 1][col - 1] &&
    pattern[2] == wordSearch[row - 1][col + 1] && pattern[3] == wordSearch[row + 1][col + 1];
}

bool is_valid_pos(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}
