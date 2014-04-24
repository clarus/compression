#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "entropy.h"

int main(int argc, char * argv[]) {
  if (argc < 2)
    fail("At least one argument expected.\n");
  
  if (strcmp(argv[1], "-entropy") == 0) {
    if (argc != 3)
      fail("Two arguments expected.");
    else {
      FILE * file = fopen(argv[2], "r");
      if (file == NULL)
        fail("Cannot open the given file.\n");

      double e = entropy(file);
      printf("The entropy is %.2f bits.\n", e);

      fclose(file);
    }
  } else
    fail("Unknown command line option.");

  return 0;
}