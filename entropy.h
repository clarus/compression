#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>

void entropy_frequencies(FILE * file, double frequencies[]);
double entropy_entropy(const double frequencies[]);

#endif