#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "hashmap.h"


#define LIST_SIZE 1000
#define BUFFER_SIZE 256
#define HASHMAP_CAPACITY 1000

void *splitLine(char *buffer, int *nums);

int main(void) {
  // Initialize our HashMap
  HashMap *map = hashmap_init(HASHMAP_CAPACITY);
  
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
    put(map, nums[1]);
  }
  fclose(f);

  int separation = 0;
  for(int i = 0; i < LIST_SIZE; i++) {
    separation += (leftList[i] * get(map, leftList[i]));
  }

  printf("Separation: %d\n", separation);
  return 0;
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



/* Implementation of HashMap Methods */
HashMap *hashmap_init(int capacity) {
  // Allocate memory for entries array
  Entry **entries = calloc(capacity, sizeof(Entry *));

  // Allocate memory for the HashMap
  HashMap *map = calloc(1, sizeof(HashMap));

  map->entries = entries;
  map->capacity = 1000;

  return map;
}

void hashmap_free(HashMap *map) {
  Entry **entries = map->entries;
  for(int i = 0; i < map->capacity; i++) {

    Entry *prev;
    Entry *currEntry = entries[i];
    while(currEntry != NULL) {
      prev = currEntry;
      currEntry = currEntry->next;
      free(prev);
    }

    free(map->entries);
    free(map);
  }
}


void put(HashMap *map, int key) {
  Entry **entries = map->entries;

  int index = key % map->capacity;
  Entry *currEntry = entries[index];
  // First entry in the given bucket
  if(currEntry == NULL) {
    Entry *newEntry = calloc(1, sizeof(Entry));
    newEntry->key = key;
    newEntry->value = 1;
    newEntry->next = NULL;
    
    entries[index] = newEntry;
    return;
  }

  
  while(currEntry != NULL) {
    if(currEntry->key == key) {
      currEntry->value++;
      return;
    }

    if(currEntry->next == NULL) {
      Entry *newEntry = calloc(1, sizeof(Entry));
      newEntry->key = key;
      newEntry->value = 1;
      newEntry->next = NULL;

      currEntry->next = newEntry;
      return;
    }

    currEntry = currEntry->next;
  }
}

int get(HashMap *map, int key) {
  Entry **entries = map->entries;

  int index = key % map->capacity;
  Entry *currEntry = entries[index];
  while(currEntry != NULL) {
    if(currEntry->key == key) {
      return currEntry->value;
    }

    currEntry = currEntry->next;
  }

  return 0;
}
