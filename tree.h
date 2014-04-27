#ifndef TREE_H
#define TREE_H

typedef struct {
  double tree_frequency;
  enum { TREE_LEAF, TREE_NODE } tree_kind;
  union {
    char tree_leaf;
    struct { int tree_left; int tree_right; } tree_node;
  } tree_content;
} tree_t;

void tree_print(const tree_t trees[], int i);
void tree_init(tree_t trees[], const double frequencies[]);
tree_t tree_node(const tree_t trees[], int index1, int index2);

#endif