#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

#define ROWS 17
#define COLS 17
#define BUFFER_SIZE 256
#define MIN_SCORE 11048


char grid[ROWS][COLS];
char copy[ROWS][COLS];
bool visited[ROWS][COLS];

// Start and End points stored as int arrays
// [row, col]
int start[2];
int end[2];

void dfs(int row, int col, int score, int dir, List *list);
void map_list_to_grid(List *list);
void print_grid();

int main() {
  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int row = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    for(int col = 0; col < COLS; col++) {
      char c = buffer[col];
      grid[row][col] = c;
      if(c == 'S') {
        start[0] = row;
        start[1] = col;
      } else if(c == 'E') {
        end[0] = row;
        end[1] = col;
      }
    }
    row++;
  }

  List *startList = list_init();
  dfs(start[0], start[1], 0, 0, startList);
  
  long seats = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(grid[i][j] == 'O') {
        seats++;
      }
    }
  }

  print_grid();
  printf("Seats: %ld\n", seats);  
  return 0;
}

void dfs(int row, int col, int score, int dir, List *list) {
  int dRow[4] = {0, 1, 0, -1};
  int dCol[4] = {1, 0, -1, 0};

  list_insert(list, row, col);
  if(row == end[0] && col == end[1] && score <= MIN_SCORE) {
    map_list_to_grid(list);
    free(list);
    return;
  }

  if(visited[row][col] || grid[row][col] == '#') {
    free(list);
    return;
  }

  visited[row][col] = true;
  // Straight
  dfs(row + dRow[dir], col + dCol[dir], score + 1, dir, list);

  // Clockwise
  int newDir = (dir + 1) % 4;
  dfs(row + dRow[newDir], col + dCol[newDir], score + 1001, newDir, list);

  // Counterclockwise
  newDir = (dir - 1 + 4) % 4;
  dfs(row + dRow[newDir], col + dCol[newDir], score + 1001, newDir, list);
  visited[row][col] = false;
  list_free(list);
}

void map_list_to_grid(List *list) {
  ListNode *curr = list->head->next;
  while(curr != list->tail) {
    grid[curr->row][curr->col] = 'O';
    curr = curr->next;
  }
}

void print_grid() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}





// List methods
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
