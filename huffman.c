#include "huffman.h"
#include <stdio.h>


void displayTree(const tree * tree, int level) {
  for (int i = 0; i < level; i++)
    printf("  ");
  printf("%f", tree->v);
  if (tree->left)
    displayTree(tree->left, level + 1);
  if (tree->right)
    displayTree(tree->right, level + 1);
}

void displayTrees(int n, const tree trees[]) {
  for (int i = 0; i < n; i++)
    displayTree(&trees[i], 0);
}

tree * initialTrees(int n, double frequencies[]) {
  malloc()
}