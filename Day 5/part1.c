#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
    bool error = false;
    for(int i = 0; i < length; i++) {
      for(int j = i + 1; j < length; j++) {
        // Determine if we have an invalid page ordering
        if(map[nums[j]][nums[i]] == 1) {
          error = true;
          break;
        }

        // If we reach the middle page number
        if(i == (length / 2)) {
          currMidNum = nums[i];
        }
      }
      // If we have an invalid edit ordering, the ordering is invalid.
      if(error) {
        break;
      }
    }

    if(!error) {
      midPageNumSum += currMidNum;
    }    
  }
  fclose(f);
  
  printf("Correct Orderings Middle Page Sum: %d\n", midPageNumSum);
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
