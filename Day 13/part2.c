#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define OFFSET 10000000000000
#define BUFFER_SIZE 256

long min_coins_needed(long matrix[2][2], long px, long py);

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");
  
  long coins = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    // Button A
    long a, b;
    sscanf(buffer, "Button A: X+%ld, Y+%ld", &a, &b);
    
    // Button B
    long c, d;
    fgets(buffer, BUFFER_SIZE, f); // --> should really check if valid, but it always will be
    sscanf(buffer, "Button B: X+%ld, Y+%ld", &c, &d);
    
    // Build matrix
    long matrix[2][2] = {{a, b}, {c, d}};
    
    // Prize
    long px, py;
    fgets(buffer, BUFFER_SIZE, f);
    sscanf(buffer, "Prize: X=%ld, Y=%ld", &px, &py);

    long min = min_coins_needed(matrix, px + OFFSET, py + OFFSET);
    coins += min == 0 ? 0 : min;

    // Skip over the '\n' after each game entry
    fgets(buffer, BUFFER_SIZE, f);
  }
  fclose(f);
  
  printf("Coins: %ld\n", coins);
  return 0;
}


long min_coins_needed(long matrix[2][2], long px, long py) {
  long a_x = matrix[0][0], a_y = matrix[0][1], b_x = matrix[1][0], b_y = matrix[1][1];
  long det = a_x * b_y - a_y * b_x;
  // Don't want to divide by 0
  if(det == 0) {
    return 0;
  }

  double aPresses = (b_y*px  - b_x*py) / det*1.0;
  double bPresses = (a_x*py - a_y*px) / det*1.0;
  
  if(a_x*aPresses + b_x*bPresses == px && a_y*aPresses + b_y*bPresses == py) {
    return (long)(3 * aPresses) + (long)(bPresses);
  }

  return 0;
}
