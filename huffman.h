#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "common.h"
#include "heap.h"
#include "tree.h"

void huffman_huffman(tree_t trees[], heap_t * heap, int table[][NB_SYMBOLS]);

#endif