#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define LIST_SIZE 1000
#define BUFFER_SIZE 256

void *splitLine(char *buffer, int *nums);
int compare(const void *a, const void *b);

int main(void) {
  // Buffer for storing each line read from the file
  char buffer[BUFFER_SIZE];

  int nums[2];
  int leftList[LIST_SIZE];
  int rightList[LIST_SIZE];
  
  // Read in input.txt file
  FILE *f = fopen("./input.txt", "r");
  if(f == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // Read in lines from input.txt
  for(int i = 0; i < LIST_SIZE && fgets(buffer, BUFFER_SIZE, f); i++) {
    splitLine(buffer, nums);
    leftList[i] = nums[0];
    rightList[i] = nums[1];    
  }
  fclose(f);
  
  // Sort right and left lists
  qsort(leftList, LIST_SIZE, sizeof(int), compare);
  qsort(rightList, LIST_SIZE, sizeof(int), compare);

  // Find the difference between adjacent elements
  int distance = 0;
  for(int i = 0; i < LIST_SIZE; i++) {
    distance += abs(leftList[i] - rightList[i]);
  }
  
  printf("Distance: %d\n", distance);

  return 0;
}

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

void *splitLine(char *s, int *nums) {
  int leftNum = 0;
  int rightNum = 0;
  
  int i = 0;
  while(isdigit(s[i])) {
    leftNum = 10 * leftNum + (s[i++] - '0');
  }
  nums[0] = leftNum;

  // Skip over white space
  while(!isdigit(s[i])) {
    i++;
  }

  while(isdigit(s[i])) {
    rightNum = 10 * rightNum + (s[i++] - '0');
  }
  nums[1] = rightNum;
}
