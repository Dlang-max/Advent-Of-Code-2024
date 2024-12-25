#ifndef LIST_H_
#define LIST_H_

#define ROWS 7
#define COLS 5
#define INITIAL_CAPACITY 50

typedef struct List {
  int length;
  int size;
  int **heights;
} List;

List *list_init(int capacity);
void list_free(List *list);
void free_heights(int **heights, int length);
void list_add(List *list, int *teeth);
void print_heights(List *list);

#endif
