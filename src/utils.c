#include "database.h"
#include <ctype.h>
#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generate_random_number(int min_value, int max_value) {
  return rand() % (max_value - min_value + 1);
}

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

char *lower_player_input(char *input) {
  int input_len = strlen(input);
  for (int i = 0; i < input_len; i++) {
    input[i] = tolower(input[i]);
  }
  return input;
}
