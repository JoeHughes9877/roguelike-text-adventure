#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string(char *data) {
  char *buffer = malloc(50);

  if (!buffer) {
    return "failed to get string";
  }

  int current_length = 0;

  if (data) {
    printf("%s", data);
  }

  while (1) {
    fgets(buffer + current_length, 11, stdin);
    int chunk_len = strlen(buffer + current_length);
    current_length += chunk_len;

    if (buffer[current_length - 1] != '\n') {
      buffer = realloc(buffer, current_length + 50);
    }
    if (buffer[current_length - 1] == '\n') {
      break;
    }
  }
  return buffer;
}
