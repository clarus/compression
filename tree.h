#ifndef TREE_H
#define TREE_H

typedef struct {
  double frequency;
  enum { LEAF, NODE } kind;
  union {
    char leaf;
    struct { int left; int right; } node;
  } content;
} tree_t;

void tree_print(const tree_t trees[], int i);
void tree_init(tree_t trees[], const double frequencies[]);

#endif