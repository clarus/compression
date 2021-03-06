#include "tree.h"
#include "common.h"
#include <stdio.h>

void tree_print(const tree_t trees[], int index) {
  printf("%f( ", trees[index].tree_frequency);
  switch (trees[index].tree_kind) {
  case TREE_LEAF:
    printf("%c", trees[index].tree_content.tree_leaf);
    break;
  case TREE_NODE:
    tree_print(trees, trees[index].tree_content.tree_node.tree_left);
    printf(" ");
    tree_print(trees, trees[index].tree_content.tree_node.tree_right);
    break;
  }
  printf(" )\n");
}

void tree_init(tree_t trees[], const double frequencies[]) {
  for (int i = 0; i < NB_SYMBOLS; i++) {
    trees[i] = (tree_t) {
      .tree_frequency = frequencies[i],
      .tree_kind = TREE_LEAF,
      .tree_content = { .tree_leaf = i }
    };
  }
}

tree_t tree_node(const tree_t trees[], int index1, int index2) {
  return (tree_t) {
    .tree_frequency =
      trees[index1].tree_frequency + trees[index2].tree_frequency,
    .tree_kind = TREE_NODE,
    .tree_content = {
      .tree_node = { .tree_left = index1, .tree_right = index2 } }
  };
}