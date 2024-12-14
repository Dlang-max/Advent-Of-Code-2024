#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 103
#define COLS 101
#define ITERATIONS 100
#define BUFFER_SIZE 256

void update_quadrant_totals(int *quadrantTotals, int row, int col);

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  
  int quadrantTotals[4] = {0, 0, 0, 0};
  while(fgets(buffer, BUFFER_SIZE, f)) {
    int row, col, dRow, dCol;
    sscanf(buffer, "p=%d,%d v=%d, %d", &col, &row, &dCol, &dRow);

    int endRow = (row + dRow * ITERATIONS) % ROWS;
    endRow += endRow < 0 ? ROWS : 0;
    
    int endCol = (col + dCol * ITERATIONS) % COLS;
    endCol += endCol < 0 ? COLS : 0;
    
    if(endRow == ROWS / 2 || endCol == COLS / 2) {
      continue;
    }

    update_quadrant_totals(quadrantTotals, endRow, endCol);
  }

  long safetyFactor = 1;
  for(int i = 0; i < 4; i++) {
    safetyFactor *= quadrantTotals[i];
  }


  printf("Safety Factor: %ld\n", safetyFactor);
  
  return 0;
}


void update_quadrant_totals(int *quadrantTotals, int row, int col) {
  if(row < ROWS / 2 && col > COLS / 2) {
    // Quadrant I
    quadrantTotals[0]++;
  } else if (row < ROWS / 2 && col < COLS / 2) {
    // Quadrant II
    quadrantTotals[1]++;
  } else if(row > ROWS / 2 && col < COLS / 2) {
    // Quadrant III
    quadrantTotals[2]++;
  } else {
    // Quadrant IV
    quadrantTotals[3]++;
  }
}
