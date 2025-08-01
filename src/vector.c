#include "../include/vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void free_vector(struct vector *vec);
void resize(int newSize, struct vector *vec);
void delete_by_index(struct vector *vec, int index);

void delete_by_value(struct vector *vec, char *target_value) {
  for (int i = 0; i < vec->size; i++) {
    if (strstr(vec->elements[i], target_value) != NULL) {
      for (int j = i; j < vec->size - 1; j++) {
        vec->elements[j] = vec->elements[j + 1];
      }
      vec->size--;
      break;
    }
  }
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

void delete_by_index(struct vector *vec, int index) {

  if (index < 0 || index >= vec->size) {
    printf("Invalid index %d! Nothing to delete.\n", index);
    return;
  }

  free(vec->elements[index]);

  for (int j = index; j < vec->size - 1; j++) {
    vec->elements[j] = vec->elements[j + 1];
  }
  vec->size--;

  if (vec->size > 0) {
    vec->elements = realloc(vec->elements, sizeof(char *) * vec->size);
  } else {
    free(vec->elements);
    vec->elements = NULL;
  }
}
