#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 256

int min_coins_needed(int matrix[2][2], int px, int py);

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");
  
  int coins = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    // Button A
    int a, b;
    sscanf(buffer, "Button A: X+%d, Y+%d", &a, &b);
    
    // Button B
    int c, d;
    fgets(buffer, BUFFER_SIZE, f); // --> should really check if valid, but it always will be
    sscanf(buffer, "Button B: X+%d, Y+%d", &c, &d);
    
    // Build matrix
    int matrix[2][2] = {{a, b}, {c, d}};
    
    // Prize
    int px, py;
    fgets(buffer, BUFFER_SIZE, f);
    sscanf(buffer, "Prize: X=%d, Y=%d", &px, &py);

    int min = min_coins_needed(matrix, px, py);
    coins += min == 0 ? 0 : min;

    // Skip over the '\n' after each game entry
    fgets(buffer, BUFFER_SIZE, f);
  }
  fclose(f);
  
  printf("Coins: %d\n", coins);
  return 0;
}


int min_coins_needed(int matrix[2][2], int px, int py) {
  int a_x = matrix[0][0], a_y = matrix[0][1], b_x = matrix[1][0], b_y = matrix[1][1];
  int det = a_x * b_y - a_y * b_x;
  // Avoid dividing by 0
  if(det == 0) {
    return 0;
  }

  double aPresses = (b_y*px  - b_x*py) / det*1.0;
  double bPresses = (a_x*py - a_y*px) / det*1.0;
  
  if(a_x*aPresses + b_x*bPresses == px && a_y*aPresses + b_y*bPresses == py) {
    return (int)(3 * aPresses) + (int)(bPresses);
  }

  return 0;
}
