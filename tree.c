#include "common.h"
#include <stdio.h>

typedef struct {
  double frequency;
  enum { LEAF, NODE } kind;
  union {
    char leaf;
    struct { int left; int right; } node;
  } content;
} tree_t;

void tree_print(const tree_t trees[], int i) {
  printf("%f( ", trees[i].frequency);
  switch (trees[i].kind) {
  case LEAF:
    printf("%c", trees[i].content.leaf);
    break;
  case NODE:
    tree_print(trees, trees[i].content.node.left);
    printf(" ");
    tree_print(trees, trees[i].content.node.right);
    break;
  }
  printf(" )");
}

void tree_init(tree_t trees[], const double frequencies[]) {
  for (int i = 0; i < NB_SYMBOLS; i++) {
    trees[i] = (tree_t) {
      .frequency = frequencies[i],
      .kind = LEAF,
      .content = { .leaf = i }
    };
  }
}