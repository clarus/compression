#include "huffman.h"
#include "common.h"
#include <stdio.h>

void tree_to_table(const tree_t trees[], int index, int table[][NB_SYMBOLS], int prefix[], int depth) {
  switch (trees[index].tree_kind) {
  case TREE_LEAF:
    for (int i = 0; i < depth; i++)
      table[trees[index].tree_content.tree_leaf][i] = prefix[i];
    table[trees[index].tree_content.tree_leaf][depth] = -1;
    break;
  case TREE_NODE:
    prefix[depth] = 0;
    tree_to_table(trees, trees[index].tree_content.tree_node.tree_left, table, prefix, depth + 1);
    prefix[depth] = 1;
    tree_to_table(trees, trees[index].tree_content.tree_node.tree_right, table, prefix, depth + 1);
    break;
  }
}

void print_table(int table[][NB_SYMBOLS]) {
  for (int i = 0; i < NB_SYMBOLS; i++) {
    printf("%c: ", (char) i);
    for (int j = 0; j < NB_SYMBOLS; j++)
      if (table[i][j] == -1)
        break;
      else
        printf("%d", table[i][j]);
    printf("\n");
  }
}

void huffman_huffman(tree_t trees[], heap_t * heap, int table[][NB_SYMBOLS]) {
  int nb_trees = NB_SYMBOLS;
  for (int i = 0; i < NB_SYMBOLS; i++)
    heap_add(trees, heap, i);
  // heap_print(trees, heap);
  while (heap->heap_nb_values > 1) {
    int index1 = heap_get(trees, heap);
    int index2 = heap_get(trees, heap);
    tree_t tree = tree_node(trees, index1, index2);
    // printf("got indexes %d and %d\n", index1, index2);
    // heap_print(trees, heap);
    // printf("adding %f\n", tree.tree_frequency);
    trees[nb_trees] = tree;
    heap_add(trees, heap, nb_trees);
    nb_trees++;
    // heap_print(trees, heap);
  }
  int prefix[NB_SYMBOLS];
  tree_to_table(trees, heap->heap_indexes[0], table, prefix, 0);
  // print_table(table);
}