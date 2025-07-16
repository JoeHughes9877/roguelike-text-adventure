#ifndef VECTOR_H
#define VECTOR_H

struct vector {
  int size;
  int capacity;
  char *elements[];
};

void print_vector(struct vector *vec);
void free_vector(struct vector *vec);
void resize(int new_size, struct vector *vec);
void delete_by_value(struct vector *vec, char *target_value);

#endif
