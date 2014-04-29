#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "entropy.h"
#include "heap.h"
#include "tree.h"
#include "huffman.h"
#include "bits.h"

int main(int argc, char * argv[]) {
  if (argc < 2)
    fail("Usage: etoile option file\n\
Options:\n\
  -entropy    the entropy at the byte level\n\
  -zip        compress the file on the standard output\n\
  -unzip      uncompress the file on the standard output");
  
  if (strcmp(argv[1], "-entropy") == 0) {
    if (argc != 3)
      fail("Two arguments expecte");
    else {
      FILE * file = fopen(argv[2], "r");
      if (file == NULL)
        fail("Cannot open the given file.");

      double frequencies[NB_SYMBOLS];
      entropy_frequencies(file, frequencies);
      double e = entropy_entropy(frequencies);
      printf("The entropy is %.2f bits.\n", e);

      fclose(file);
    }
  } else if (strcmp(argv[1], "-zip") == 0) {
    if (argc != 3)
      fail("Two arguments expected.");
    else {
      FILE * file = fopen(argv[2], "r");
      if (file == NULL)
        fail("Cannot open the given file.");

      double frequencies[NB_SYMBOLS];
      entropy_frequencies(file, frequencies);
      tree_t trees[NB_TREES];
      tree_init(trees, frequencies);
      int indexes[NB_SYMBOLS];
      heap_t heap = {
        .heap_indexes = indexes,
        .heap_size = NB_SYMBOLS,
        .heap_nb_values = 0
      };
      int table[NB_SYMBOLS][NB_SYMBOLS];
      huffman_huffman(trees, &heap, table);
      // tree_print(trees, heap.heap_indexes[0]);

      fclose(file);

      bits_write_file(argv[2], trees, heap.heap_indexes[0], table);
    }
  } else if (strcmp(argv[1], "-unzip") == 0) {
    if (argc != 3)
      fail("Two arguments expected.");
    else {
      bits_read_file(argv[2]);
    }
  } else
    fail("Unknown command line option.");

  return 0;
}