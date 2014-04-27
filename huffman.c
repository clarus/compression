#include "huffman.h"
#include "common.h"
#include <stdio.h>

void huffman_huffman(tree_t trees[], heap_t * heap) {
  int nb_trees = NB_SYMBOLS;
  for (int i = 0; i < NB_SYMBOLS; i++)
    heap_add(trees, heap, i);
  heap_print(trees, heap);
  while (heap->heap_nb_values > 1) {
    int index1 = heap_get(trees, heap);
    int index2 = heap_get(trees, heap);
    tree_t tree = tree_node(trees, index1, index2);
    printf("got indexes %d and %d\n", index1, index2);
    heap_print(trees, heap);
    printf("adding %f\n", tree.tree_frequency);
    trees[nb_trees] = tree;
    heap_add(trees, heap, nb_trees);
    nb_trees++;
    heap_print(trees, heap);
  }
}