#ifndef BITS_H
#define BITS_H

#include "common.h"
#include "tree.h"

void bits_write_file(const char file_name[], const tree_t trees[], int tree_index, int table[][NB_SYMBOLS]);
void bits_read_file(const char file_name[]);

#endif