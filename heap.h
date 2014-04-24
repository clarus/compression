#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct {
  double * values;
  int size;
  int nb_values;
} heap_t;

void heap_add(heap_t * heap, double value);
double heap_get(heap_t * heap);
void heap_print(const heap_t * heap);

#endif