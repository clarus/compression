#ifndef BITS_H
#define BITS_H

#include "common.h"
#include "tree.h"

// Print on stdout the bit-encoding of the compression of file_name given
// trees[tree_index] the Huffman tree and table the corresponding Huffman table.
void bits_write_file(const char file_name[], const tree_t trees[],
  int tree_index, int table[][NB_SYMBOLS]);

// Print on stdout the decoding of the compressed file_name.
void bits_read_file(const char file_name[]);

#endif