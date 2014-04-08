#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct {
  double *values;
  size_t size;
  int nb_values;
} heap_t;

void add(heap_t *heap, double value);
double get(heap_t *heap);

#endif