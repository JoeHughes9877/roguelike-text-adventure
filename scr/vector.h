#ifndef VECTOR_H
#define VECTOR_H

struct vector {
  int size;
  int capacity;
  char **elements;
};

void print_vector(struct vector *vec);
void free_vector(struct vector *vec);
void delete_by_value(struct vector *vec, char *target_value);
void delete_by_index(struct vector *vec, int index);

#endif
