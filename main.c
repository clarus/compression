#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "entropy.h"

int main(int argc, char * argv[]) {
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