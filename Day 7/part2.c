#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LIST_SIZE 30
#define BUFFER_SIZE 256

bool can_build_result(long result, long *nums, int length, int index, long currTotal);
long build_concat(long currTotal, long num);
int convert_str_to_arr(char *str, long *nums);

int main() {  
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");
  
  long totalCalibrationResult = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    char bufferCopy[BUFFER_SIZE];
    strcpy(bufferCopy, buffer);

    // Read in the result that we are trying to get
    long result = atol(strtok(bufferCopy, ":"));

    // Read in the list of numbers that we will perform operation on
    // Original string of numbers
    char *list = strtok(NULL, ":");

    // Numbers of the original string
    long nums[LIST_SIZE];
    memset(nums, -1, LIST_SIZE);
    int len = convert_str_to_arr(list, nums);

    totalCalibrationResult += can_build_result(result, nums, len, 0, 0) ? result : 0;
  }  
  fclose(f);

  printf("Total Calibration Result: %ld\n", totalCalibrationResult);
  return 0;
}


bool can_build_result(long result, long *nums, int length, int i, long currTotal) {
  if(currTotal == result && i == length) {
    return true;
  }

  if(i >= length || currTotal > result) {
    return false;
  }

  bool multiplication = can_build_result(result, nums, length, i + 1, currTotal * nums[i]);  
  bool addition = can_build_result(result, nums, length, i + 1, currTotal + nums[i]);
  bool concatenation = can_build_result(result, nums, length, i + 1, build_concat(currTotal, nums[i]));
  return  multiplication || addition || concatenation;
}

long build_concat(long currTotal, long num) {
  long copy = num; 
  while(copy > 0) {
    copy /= 10;
    currTotal *= 10;
  }

  return currTotal + num;
}

int convert_str_to_arr(char *str, long *nums) {
  char copy[strlen(str) + 1];
  strcpy(copy, str);

  char *tok = strtok(copy, " ");
  int i = 0;
  while(tok != NULL) {
    nums[i++] = atol(tok);
    tok = strtok(NULL, " ");
  }

  return i;
}
