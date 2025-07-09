#include <stdio.h>

char *get_string(void);

int main() {
  printf("what do you do? ");
  char *data = get_string();
  printf("%s\n", data);
}

char *get_string() {
  char *data;
  scanf("%s", data);
  return data;
}
