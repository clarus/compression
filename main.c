#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "entropy.h"
#include "heap.h"
#include "tree.h"
#include "huffman.h"

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

      double frequencies[NB_SYMBOLS];
      entropy_frequencies(file, frequencies);
      double e = entropy_entropy(frequencies);
      printf("The entropy is %.2f bits.\n", e);

      fclose(file);
    }
  } /*else if (strcmp(argv[1], "-heap") == 0) {
    double values[64];
    heap_t heap = {values, 64, 0};
    int sample[] = {4, 6, 3, 7, 9, 3};
    for (int i = 0; i < 6; i++)
      heap_add(&heap, sample[i]);
    heap_print(&heap);
    for (int i = 0; i < 6; i++) {
      printf("-> %d\n", (int) heap_get(&heap));
      heap_print(&heap);
    }
  }*/ else if (strcmp(argv[1], "-huffman") == 0) {
    if (argc != 3)
      fail("Two arguments expected.");
    else {
      FILE * file = fopen(argv[2], "r");
      if (file == NULL)
        fail("Cannot open the given file.\n");

      double frequencies[NB_SYMBOLS];
      entropy_frequencies(file, frequencies);
      tree_t trees[NB_TREES];
      tree_init(trees, frequencies);
      tree_print(trees, 'a');
      tree_print(trees, '*');
      int indexes[NB_SYMBOLS];
      heap_t heap = {
        .heap_indexes = indexes,
        .heap_size = NB_SYMBOLS,
        .heap_nb_values = 0
      };
      huffman_huffman(trees, &heap);
      tree_print(trees, heap.heap_indexes[0]);

      fclose(file);
    }
  } else
    fail("Unknown command line option.");

  return 0;
}