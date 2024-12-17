#include <stdlib.h>
#include <stdio.h>

#include "list.h"


int main() {
  test_list();
  return 0;
}

void test_list() {
  List *list = list_init();
  list_insert(list, 5, 6);
  list_insert(list, 6, 7);
  list_print(list);

  List *copy = copy_list(list);
  list_print(copy);
}




// Implementation of list insert, copy, and print
void list_insert(List *list, int row, int col) {
  ListNode *curr = calloc(1, sizeof(ListNode));
  curr->row = row;
  curr->col = col;

  list->tail->prev->next = curr;
  curr->prev = list->tail->prev;
  curr->next = list->tail;
  list->tail->prev = curr;
  list->size++;
}

List *copy_list(List *list) {
  List *copy = list_init();
  ListNode *curr = list->head->next;
  for(int i = 0; i < list->size; i++) {
    list_insert(copy, curr->row, curr->col);
    curr = curr->next;
  }

  return copy;
}

void list_print(List *list) {
  ListNode *curr = list->head->next;
  while(curr != list->tail) {
    printf("(%d, %d) ", curr->row, curr->col);
    curr = curr->next;
  }
  printf("\n");
}

// Implementation of list init and free
List *list_init() {
  ListNode *head = calloc(1, sizeof(ListNode));
  ListNode *tail = calloc(1, sizeof(ListNode));

  head->row = -1;
  head->col = -1;
  head->prev = NULL;
  head->next = tail;

  tail->row = -1;
  tail->col = -1;
  tail->prev = head;
  tail->next = NULL;

  List *list = calloc(1, sizeof(List));
  list->head = head;
  list->tail = tail;
  list->size = 0;

  return list;
}


void list_free(List *list) {
  ListNode *curr = list->head->next;
  while(curr != list->tail) {
    ListNode *temp = curr;
    curr = curr->next;
    free(temp);
  }

  free(list->head);
  free(list->tail);
  free(list);
}
