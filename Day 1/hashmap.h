#include <stdlib.h>

// HashMap Entry Struct
typedef struct Entry{
  int key;
  int value;
  struct Entry *next;
} Entry;

// HashMap Struct
typedef struct HashMap {
  int capacity;
  Entry **entries;  
} HashMap;

// Creation and Destruction methods
HashMap *hashmap_init(int capacity);
void hashmap_free(HashMap *map);

// Get and Put
void put(HashMap *map, int key);
int get(HashMap *map, int key);
