#include <stdio.h>

#include "common.h"
#include "heap.h"

int father(int i) {
  return (i - 1) / 2;
}

int left_son(int i) {
  return 2 * i + 1;
}

int right_son(int i) {
  return 2 * i + 2;
}

int exchange(heap_t * heap, int i, int j) {
  if (heap->values[i] > heap->values[j]) {
    double tmp = heap->values[i];
    heap->values[i] = heap->values[j];
    heap->values[j] = tmp;
    return 1;
  } else
    return 0;
}

void sort_up(heap_t * heap, int i) {
  if (i != 0 && exchange(heap, father(i), i))
    sort_up(heap, father(i));
}

void sort_down(heap_t * heap, int i) {
  if (left_son(i) < heap->nb_values) {
    if (right_son(i) < heap->nb_values) {
      if (heap->values[left_son(i)] < heap->values[right_son(i)]) {
        if (exchange(heap, i, left_son(i)))
          sort_down(heap, left_son(i));
      } else {
        if (exchange(heap, i, right_son(i)))
          sort_down(heap, right_son(i));
      }
    } else {
      if (exchange(heap, i, left_son(i)))
        sort_down(heap, left_son(i));
    }
  }
}

void heap_add(heap_t * heap, double value) {
  if (heap->nb_values < heap->size) {
    heap->values[heap->nb_values] = value;
    heap->nb_values++;
    sort_up(heap, heap->nb_values -  1);
  } else
    fail("heap_add: the heap is full.");
}

double heap_get(heap_t * heap) {
  if (heap->nb_values > 0) {
    double result = heap->values[0];
    heap->values[0] = heap->values[heap->nb_values - 1];
    heap->nb_values--;
    sort_down(heap, 0);
    return result;
  } else {
    fail("heap_get: the heap is empty.");
    return 0.0;
  }
}

void heap_print(const heap_t * heap) {
  printf("[heap_t] nb_values: %d, size: %d\n[ ", heap->nb_values, (int) heap->size);
  for (int i = 0; i < heap->nb_values; i++)
    printf("%.2f ", heap->values[i]);
  printf("]\n");
}