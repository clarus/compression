#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "huffman.h"

#define NB_SYMBOLS 256

double entropy(FILE * file) {
  int occurencies[NB_SYMBOLS];
  for (int i = 0; i < NB_SYMBOLS; i++)
    occurencies[i] = 0;

  int c, bytes_read = 0;
  while ((c = fgetc(file)) != EOF) {
    bytes_read++;
    occurencies[c]++;
  }

  double frequencies[NB_SYMBOLS];
  for (int i = 0; i < NB_SYMBOLS; i++)
    frequencies[i] = (double) occurencies[i] / (double) bytes_read;

  double result = 0;
  for (int i = 0; i < NB_SYMBOLS; i++) {
    double x = frequencies[i] * log2(frequencies[i]);
    if (! isnan(x))
      result -= x;
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    fail("One argument expected.\n");
  
  FILE * file = fopen(argv[1], "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");

  double e = entropy(file);
  printf("The entropy is %.2f bits.\n", e);

  fclose(file);

  return 0;
}