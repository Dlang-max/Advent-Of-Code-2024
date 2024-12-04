#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 10000

void copy_str_to_nums(char *src, char *dest, int start, int end) {
  int len = 0;
  for(int i = start; i < end; i++) {
    dest[len++] = src[i];
  }
  dest[len] = '\0';
}

int main() {
  const char *pattern = "mul\\([0-9]+,[0-9]+\\)";
  regex_t regex;
  regmatch_t matches[1];
  regcomp(&regex, pattern, REG_EXTENDED);

  char buffer[BUFFER_SIZE];
  FILE *f = fopen("./input.txt", "r");

  int products = 0;
  while(fgets(buffer, BUFFER_SIZE, f)) {
    char *str = buffer;

    while(regexec(&regex, str, 1, matches, 0) == 0) {
      int start = matches[0].rm_so;
      int end = matches[0].rm_eo;

      char nums[8];
      copy_str_to_nums(str, nums, start + 4, end - 1);
      
      int num1 = atoi(strtok(nums, ","));
      int num2 = atoi(strtok(NULL, ","));
      products += (num1 * num2);
      str += end;
    }
  }
  fclose(f);

  printf("Result: %d\n", products);
  return 0;
}



