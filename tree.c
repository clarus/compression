#include "tree.h"
#include "common.h"
#include <stdio.h>

void tree_print(const tree_t trees[], int i) {
  printf("%f( ", trees[i].tree_frequency);
  switch (trees[i].tree_kind) {
  case TREE_LEAF:
    printf("%c", trees[i].tree_content.tree_leaf);
    break;
  case TREE_NODE:
    tree_print(trees, trees[i].tree_content.tree_node.tree_left);
    printf(" ");
    tree_print(trees, trees[i].tree_content.tree_node.tree_right);
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