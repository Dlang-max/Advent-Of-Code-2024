#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 256

bool isLineSafe(char *line);
int getNum(char *s, int *startIndex);


int main(void) {
  // Buffer for storing each line read from the file
  char buffer[BUFFER_SIZE];
  
  // Read in input.txt file
  FILE *f = fopen("./input.txt", "r");
  if(f == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // Read in lines from input.txt
  int safeLines = 0;
  for(int i = 0; fgets(buffer, BUFFER_SIZE, f); i++) {
    safeLines += isLineSafe(buffer) ? 1 : 0;
  }
  fclose(f);
  
  printf("Safe Lines: %d\n", safeLines);
  return 0;
}


bool isLineSafe(char *line) {
  //   p-> c->  
  // "num num num num num"
  int startIndex = 0;
  int prev = getNum(line, &startIndex);
  int curr = getNum(line, &startIndex);

  bool increasing = curr > prev;
  while(line[startIndex] != '\0' && line[startIndex] != '0') {
    if(increasing && (curr <= prev || curr - prev > 3)) {
      return false;
    }

    if(!increasing && (curr >= prev || prev - curr > 3)) {
      return false;
    }

    prev = curr;
    curr = getNum(line, &startIndex);

    if(curr == -1) {
      break;
    }
  }

  return true;
}

int getNum(char *s, int *startIndex) {
  int num = 0;
  int i;
  for(i = *startIndex; s[i] != ' ' && s[i] != '\0' && isdigit(s[i]); i++) {
    num = num * 10 + (s[i] - '0');
  }

  // If we get and invalid num, return -1.
  if(num == 0) {
    return -1;
  }

  // Skip over trailing white space
  if(s[i] == ' ') {
    i++;
  }

  *startIndex = i;
  return num;
}
