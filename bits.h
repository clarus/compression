#ifndef BITS_H
#define BITS_H

#include "common.h"
#include <stdio.h>

typedef struct {
  FILE * bits_file;
  int bits_byte;
  int bits_count;
} bits_t;

void bits_write_file(const char file_name[], int table[][NB_SYMBOLS]);

#endif