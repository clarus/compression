#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "common.h"
#include "heap.h"
#include "tree.h"

// Compute the Huffman table from a leaf for each character and an empty heap.
// The table is for each character the path from the root in the final Huffman
// tree:
// * 0 for left
// * 1 for right
// * -1 for the end of the path
void huffman_huffman(tree_t trees[], heap_t * heap, int table[][NB_SYMBOLS]);

#endif