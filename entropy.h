#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>

// Compute in frequencies the array of frequencies for each character.
void entropy_frequencies(FILE * file, double frequencies[]);

// Compute the entropy given the frequency of each character.
double entropy_entropy(const double frequencies[]);

#endif