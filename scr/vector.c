#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_vector(struct vector *vec);

void delete_by_value(int new_size, struct vector *vec, char *target_value) {
  int current_max_index = vec->size - 1;

  char **temp_storage = malloc(new_size * sizeof(char *));

  for (int index = 0; index < new_size; index++) {
    if (strcmp(vec->elements[index], target_value) != 0) {
      continue;
    } else {
      memcpy(&vec[index], &temp_storage[index], sizeof(int));
    }
  }

  vec->capacity = new_size;

  if (current_max_index > new_size) {
    current_max_index = new_size;
  }

  free_vector(vec);
}

void resize(int new_size, struct vector *vec) {
  int current_max_index = vec->size - 1;

  char **temp_storage = malloc(new_size * sizeof(char *));

  for (int index = 0; index < new_size; index++) {
    memcpy(&vec[index], &temp_storage[index], sizeof(int));
  }

  vec->capacity = new_size;

  if (current_max_index > new_size) {
    current_max_index = new_size;
  }

  free_vector(vec);
}

void free_vector(struct vector *vec) {
  if (!vec) {
    return;
  }

  for (int i = 0; i < vec->size; i++) {
    free(vec->elements[i]);
  }
  free(vec);
}

void print_vector(struct vector *vec) {
  for (int i = 0; i < vec->size; i++) {
    printf("%s\n", vec->elements[i]);
  }
}
