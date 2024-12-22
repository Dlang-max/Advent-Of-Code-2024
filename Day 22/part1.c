#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PRUNE_FACTOR 16777216
#define GENERATIONS 2000
#define BUFFER_SIZE 256

long generateSecretNumber(long initialSecretNumber);

int main() {

  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");


  long sumOfSecretNums = 0;
  while(fgets(buffer ,BUFFER_SIZE, f)) {
    long initialSecretNum;
    sscanf(buffer, "%ld", &initialSecretNum);
    sumOfSecretNums += generateSecretNumber(initialSecretNum);
  }
  fclose(f);
  
  printf("Sum of Secret Nums: %ld\n", sumOfSecretNums);
  return 0;
}


long generateSecretNumber(long initialSecretNumber) {
  long curr = initialSecretNumber;
  for(int i = 0; i < GENERATIONS; i++) {
    curr = ((curr * 64) ^ curr) % PRUNE_FACTOR;
    curr = ((curr / 32) ^ curr) % PRUNE_FACTOR;
    curr = ((curr * 2048) ^ curr) % PRUNE_FACTOR;
  }
  
  return curr;
}
