#ifndef HEAP_H
#define HEAP_H

#include "tree.h"
#include <stddef.h>

typedef struct {
  int * heap_indexes;
  int heap_size;
  int heap_nb_values;
} heap_t;

void heap_add(const tree_t trees[], heap_t * heap, int index);
int heap_get(const tree_t trees[], heap_t * heap);
void heap_print(const tree_t trees[], const heap_t * heap);

#endif