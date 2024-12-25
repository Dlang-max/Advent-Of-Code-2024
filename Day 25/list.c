#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"


// List Implementation
List *list_init(int capacity) {
  List *list = calloc(1, sizeof(List));
  list->length = capacity;
  list->size = 0;
  list->heights = calloc(capacity, sizeof(int *));

  return list;
}

void list_free(List *list) {
  for(int i = 0; i < list->length; i++) {
    free(list->heights[i]);
  }
  free(list->heights);
  free(list);
}

void free_heights(int **heights, int length) {
  for(int i = 0; i < length; i++) {
    free(heights[i]);
  }
  free(heights);
}

void list_add(List *list, int *teeth) {
  if(list->size == list->length) {
    int originalLength = list->length;
    list->length = 2 * originalLength;
    
    int **newHeights = calloc(list->length, sizeof(int *));
    memcpy(newHeights, list->heights, originalLength * sizeof(int *));
    free(list->heights);
    list->heights = newHeights;
  }

  list->heights[list->size] = teeth;
  list->size++;
}

void print_heights(List *list) {

  for(int i = 0; i < list->size; i++) {
    for(int j = 0; j < COLS; j++) {
      printf("%d", list->heights[i][j]);
    }
    printf("\n");
  }
  
}
