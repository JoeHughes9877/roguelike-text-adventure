#ifndef VECTOR_H
#define VECTOR_H

struct vector {
  int size;
  int capacity;
  char *elements[];
};

#endif
