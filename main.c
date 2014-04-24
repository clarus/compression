#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "entropy.h"
#include "heap.h"

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
  } else if (strcmp(argv[1], "-heap") == 0) {
    double values[100];
    heap_t heap = {values, 100, 0};
    int sample[] = {4, 6, 3, 7, 9, 3};
    for (int i = 0; i < 6; i++)
      heap_add(&heap, sample[i]);
    heap_print(&heap);
    for (int i = 0; i < 6; i++) {
      printf("-> %d\n", (int) heap_get(&heap));
      heap_print(&heap);
    }
  } else
    fail("Unknown command line option.");

  return 0;
}