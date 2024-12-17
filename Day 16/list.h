#include <stdlib.h>

typedef struct ListNode {
  int row;
  int col;

  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

typedef struct List {
  int size;
  
  ListNode *head;
  ListNode *tail;
} List;

void test_list();

void list_insert(List *list, int row, int col);
void list_print(List *list);
List *copy_list(List *list);


List *list_init();
void list_free(List *list);
