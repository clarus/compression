#include "heap.h"
#include "common.h"
#include "tree.h"
#include <stdio.h>


int father(int i) {
  return (i - 1) / 2;
}

int left_son(int i) {
  return 2 * i + 1;
}

int right_son(int i) {
  return 2 * i + 2;
}

double frequency(const tree_t trees[], const heap_t * heap, int i) {
  return trees[heap->heap_indexes[i]].tree_frequency;
}

int exchange(const tree_t trees[], heap_t * heap, int i, int j) {
  if (frequency(trees, heap, i) > frequency(trees, heap, j)) {
    int tmp = heap->heap_indexes[i];
    heap->heap_indexes[i] = heap->heap_indexes[j];
    heap->heap_indexes[j] = tmp;
    return 1;
  } else
    return 0;
}

void sort_up(const tree_t trees[], heap_t * heap, int i) {
  if (i != 0 && exchange(trees, heap, father(i), i))
    sort_up(trees, heap, father(i));
}

void sort_down(const tree_t trees[], heap_t * heap, int i) {
  if (left_son(i) < heap->heap_nb_values) {
    if (right_son(i) < heap->heap_nb_values) {
      if (frequency(trees, heap, left_son(i)) < frequency(trees, heap, right_son(i))) {
        if (exchange(trees, heap, i, left_son(i)))
          sort_down(trees, heap, left_son(i));
      } else {
        if (exchange(trees, heap, i, right_son(i)))
          sort_down(trees, heap, right_son(i));
      }
    } else {
      if (exchange(trees, heap, i, left_son(i)))
        sort_down(trees, heap, left_son(i));
    }
  }
}

void heap_add(const tree_t trees[], heap_t * heap, int index) {
  if (heap->heap_nb_values < heap->heap_size) {
    heap->heap_indexes[heap->heap_nb_values] = index;
    heap->heap_nb_values++;
    sort_up(trees, heap, heap->heap_nb_values -  1);
  } else
    fail("heap_add: the heap is full.");
}

int heap_get(const tree_t trees[], heap_t * heap) {
  if (heap->heap_nb_values > 0) {
    int result = heap->heap_indexes[0];
    heap->heap_indexes[0] = heap->heap_indexes[heap->heap_nb_values - 1];
    heap->heap_nb_values--;
    sort_down(trees, heap, 0);
    return result;
  } else {
    fail("heap_get: the heap is empty.");
    return 0;
  }
}

void heap_print(const tree_t trees[], const heap_t * heap) {
  printf("[heap_t] nb_values: %d, size: %d\n[ ", heap->heap_nb_values, (int) heap->heap_size);
  for (int i = 0; i < heap->heap_nb_values; i++)
    printf("%.3f ", frequency(trees, heap, i));
  printf("]\n");
}