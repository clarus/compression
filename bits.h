#ifndef BITS_H
#define BITS_H

#include "common.h"
#include "tree.h"

typedef struct {
  int bits_byte;
  int bits_count;
} bits_t;

void bits_write_file(const char file_name[], const tree_t trees[], int tree_index, int table[][NB_SYMBOLS]);

#endif