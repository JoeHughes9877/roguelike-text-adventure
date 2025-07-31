#include "../include/database.h"
#include <ctype.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int generate_random_number(int min_value, int max_value);

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

int generate_random_number_bias(int min_value, int max_value, int bias) {
  bool tmp = rand() < ((RAND_MAX + 1.0) * ((bias + 1) / 2.0));

  if (tmp) {
    return generate_random_number(min_value, max_value);
  } else {
    return 0;
  }

  return rand() % (max_value - min_value + 1);
}

Enemy *locate_enemy(char *player_input) {
  for (int i = 0; i < num_of_enemies_in_room; i++) {
    if (strstr(player_input, (char *)enemies_in_room[i]->name) != NULL) {
      return enemies_in_room[i];
    }
  }
  printf("enemy not found in the room.\n");
  return NULL;
}