#ifndef TREE_H
#define TREE_H

// A Huffman tree. Each element is a leaf or a node with two sons. The sons are
// localized by an index to an array of trees.
// We use a union type for the two cases leaf or node. tree_king is the tag to
// know if the tree is a leaf or a node. This encoding is cleaner than using the
// NULL pointer convention for the leafs for example. This the representation of
// the OCaml sum types.
typedef struct {
  double tree_frequency;
  enum { TREE_LEAF, TREE_NODE } tree_kind;
  union {
    int tree_leaf; // The character of the leaf.
    struct { int tree_left; int tree_right; } tree_node;
  } tree_content;
} tree_t;

// Print trees[index] on stdout.
void tree_print(const tree_t trees[], int index);

// Generate the trees for each character given the frequencies.
void tree_init(tree_t trees[], const double frequencies[]);

// Creates a new node given the indexes of the two sons.
tree_t tree_node(const tree_t trees[], int index1, int index2);

#endif