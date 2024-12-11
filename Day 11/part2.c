#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
#define NUMS 10
#define ITERATIONS 75
#define LIST_SIZE 8

long blink(long stone, int generation);
void split_number(long splitNums[2], long num);
bool even_num_digits(long num);

// Would use a Hash Table to cache in other languages, but
// I don't want to build my own for C. Just cahce the results
// of single digits. 
long memo[NUMS][ITERATIONS + 1];

int main() {
  
  // Read in the input from input.txt
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");
  fgets(buffer, BUFFER_SIZE, f);
  fclose(f);


  char buffCopy[strlen(buffer) + 1];
  strcpy(buffCopy, buffer);

  long stones = 0;
  char *token = strtok(buffCopy, " ");
  while(token != NULL) {
    // Simulate blinking for all stones in the input
    stones += blink(atol(token), 0);
    token = strtok(NULL, " ");
  }
  
  printf("Stones: %ld\n", stones);
  return 0;
}

long blink(long stone, int generation) {
  if(generation == ITERATIONS) {
    return 1;
  }

  // Return memo[stone][generation] if we've
  // already encountered this state
  if(stone / 10 == 0 && memo[stone][generation] != 0) {
    return memo[stone][generation];
  }

  // Case where stone is 0
  if(stone == 0) {
    memo[stone][generation] = blink(1, generation + 1);
    return memo[stone][generation];
  }

  // Case where stone has an even number of digits
  if (even_num_digits(stone)) {
    // Split the stone
    long splitStones[2];
    split_number(splitStones, stone);

    // splitStone = [rightStone, leftStone]
    long leftStone = splitStones[1];
    long rightStone = splitStones[0];
    long leftStones = blink(leftStone, generation + 1);
    long rightStones = blink(rightStone, generation + 1);

    return leftStones + rightStones;
    
  }

  // Stone meets none of the above criteria
  long stones = blink(stone * 2024, generation + 1);
  if(stone / 10 == 0) {
    memo[stone][generation] = stones;
  }
 
  return stones;
}





/*         HELPER METHODS         */
void split_number(long splitNums[2], long num) {
  long copy = num;
  int digits = 0;
  while(copy > 0) {
    digits++;
    copy /= 10;
  }

  int divisor = 1;
  int half = digits / 2;
  for(int i = 0; i < half; i++) {
    divisor *= 10;
  }
  
  int left = num % divisor;
  int right = num / divisor;

  splitNums[0] = left;
  splitNums[1] = right;
}

bool even_num_digits(long num) {
  int digits = 0;
  while(num > 0) {
    digits++;
    num /= 10;
  }

  return digits % 2 == 0;
}
