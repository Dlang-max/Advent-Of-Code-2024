#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128
#define PAGES 100

int get_elements_in_list(char *list);
void convert_list_to_arr(int *arr, char *list);

int main() {

  FILE *f = fopen("./input.txt", "r");
  char buffer[BUFFER_SIZE] = {};

  int map[PAGES][PAGES];
  memset(map, 0, PAGES * PAGES * sizeof(int));
  
  // Read in the ordering from the input file
  while(fgets(buffer, BUFFER_SIZE, f)) {
    if(buffer[1] == '\n') {
      break;
    } 
    int before;
    int after;
    if(sscanf(buffer, "%d|%d", &before, &after) == 2) {    
      map[before][after] = 1;
    }
  }
  
  // Read in lists from input
  int midPageNumSum = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {    
    int length = get_elements_in_list(buffer);
    int nums[length];
    convert_list_to_arr(nums, buffer);
    
    int currMidNum = 0;
    int errors = 0;
    for(int i = 0; i <= length / 2; i++) {
      for(int j = i + 1; j < length; j++) {
        // Swap elements to obtain a correct ordering 
        if(map[nums[j]][nums[i]] == 1) {
          int temp = nums[i];
          nums[i] = nums[j];
          nums[j] = temp;

          // Reset j index because we need to recheck our ordering
          // to see if swapping elements created new ordering errors.
          j = i + 1;
          errors++;
        }
      }
    }
    midPageNumSum += errors > 0 ? nums[length / 2] : 0;
  }
  fclose(f);
  
  printf("Fixed Orderings Middle Page Sum: %d\n", midPageNumSum);
  return 0;
}

/*=======   HELPER METHODS   =======*/
int get_elements_in_list(char *list) {
  int length = 0;
  const char *delim = ",";

  char copy[strlen(list) + 1];
  strcpy(copy, list);
  
  char *token = strtok(copy, delim);
  while(token != NULL) {
    length++;
    token = strtok(NULL, ",");
  }

  return length;
}

void convert_list_to_arr(int *arr, char *list) {
  const char *delim = ",";

  char copy[strlen(list) + 1];
  strcpy(copy, list);
  
  char *token = strtok(copy, delim);
  int i = 0;
  while(token != NULL) {
    arr[i++] = atoi(token);
    token = strtok(NULL, ",");
  }
}
