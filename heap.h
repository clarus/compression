#ifndef HEAP_H
#define HEAP_H

#include "tree.h"
#include <stddef.h>

// A heap of indexes to an array of Huffman trees.
typedef struct {
  int * heap_indexes; // An array of indexes.
  int heap_size; // The size of heap_indexes (the maximal size of the heap).
  int heap_nb_values; // The current number of elements in the heap.
} heap_t;

// Add an element.
void heap_add(const tree_t trees[], heap_t * heap, int index);

// Remove the element with the lowest frequency.
int heap_get(const tree_t trees[], heap_t * heap);

// Print the heap on stdout.
void heap_print(const tree_t trees[], const heap_t * heap);

#endif