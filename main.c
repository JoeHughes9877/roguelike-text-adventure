#include "header.h"
#include <stdio.h>

char *get_string(void);

int main() {
  printf("what do you do? ");
  char *data = get_string();
  printf("%s\n", data);
}
