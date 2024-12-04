#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 256

bool line_safe(int *nums);
void convert_string_to_arr(int *nums, char *line, char *deliminater);
void copy_arr_without_idx(int *copy, int *nums, int skipIndex);

int main(void) {
  // Buffer for storing each line read from the file
  char buffer[BUFFER_SIZE];
  
  // Read in input.txt file
  FILE *f = fopen("./input.txt", "r");
  if(f == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // Read in lines from input.txt
  int safeLines = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {

    // Count safe lines with no errors
    int nums[9] = {};
    convert_string_to_arr(nums, buffer, " ");
    if(line_safe(nums)) {
      safeLines++;
      continue;
    }

    for(int i = 0; nums[i] != '\0'; i++) {
      int copy[9] = {};
      copy_arr_without_idx(copy, nums, i);
      if(line_safe(copy)) {
        safeLines++;
        break;
      }
    }
  }
  fclose(f);
  
  printf("Safe Lines: %d\n", safeLines);
  return 0;
}




bool line_safe(int *nums) {
  bool increasing = nums[0] < nums[1];
  for(int i = 0; nums[i + 1] != '\0'; i++) {
    int prev = nums[i];
    int curr = nums[i + 1];
    if(abs(curr - prev) > 3 ||
      (increasing && curr <= prev) ||
      (!increasing && curr >= prev)) {
      return false;
    }
  }

  return true;
}

void convert_string_to_arr(int *nums, char *line, char *deliminater) {
  char *token = strtok(line, deliminater);

  int i = 0;
  while(token != NULL) {
    nums[i++] = atoi(token);
    token = strtok(NULL, deliminater);
  }
}

void copy_arr_without_idx(int *copy, int *nums, int skipIndex) {
  int i = 0;
  int j = 0;
  while(nums[i] != '\0') {
    if(i == skipIndex) {
      i++;
      continue;
    }

    copy[j++] = nums[i++];
  }
}
