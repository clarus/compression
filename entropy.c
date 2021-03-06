#include "entropy.h"
#include "common.h"
#include <math.h>

void entropy_frequencies(FILE * file, double frequencies[]) {
  int occurencies[NB_SYMBOLS];
  for (int i = 0; i < NB_SYMBOLS; i++)
    occurencies[i] = 0;

  int c, bytes_read = 0;
  while ((c = fgetc(file)) != EOF) {
    bytes_read++;
    occurencies[c]++;
  }

  for (int i = 0; i < NB_SYMBOLS; i++)
    frequencies[i] = (double) occurencies[i] / (double) bytes_read;
}

double entropy_entropy(const double frequencies[]) {
  double result = 0;
  for (int i = 0; i < NB_SYMBOLS; i++) {
    double x = frequencies[i] * log2(frequencies[i]);
    if (! isnan(x))
      result -= x;
  }
  return result;
}