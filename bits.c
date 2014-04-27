#include "bits.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

bits_t new() {
  return (bits_t) {
    .bits_byte = 0,
    .bits_count = 0
  };
}

void write(bits_t * bits, int bit) {
  bits->bits_byte *= 2;
  bits->bits_byte += bit;
  bits->bits_count++;
  if (bits->bits_count == 8) {
    fputc(bits->bits_byte, stdout);
    bits->bits_byte = bits->bits_count = 0;
  }
}

void write_byte(bits_t * bits, int byte) {
  for (int i = 0; i < 8; i++)
    write(bits, (byte >> (7 - i)) & 1);
}

void write_tree(bits_t * bits, const tree_t trees[], int index) {
  switch (trees[index].tree_kind) {
  case TREE_LEAF:
    write(bits, 0);
    write_byte(bits, trees[index].tree_content.tree_leaf);
    break;
  case TREE_NODE:
    write(bits, 1);
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_left);
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_right);
    break;
  }
}

void flush(bits_t * bits) {
  fputc(bits->bits_byte << (8 - bits->bits_count), stdout);
}

void bits_write_file(const char file_name[], const tree_t trees[], int tree_index, int table[][NB_SYMBOLS]) {
  bits_t bits = new(stdout);

  // Print the total size of the file to compress in bytes.
  struct stat st;
  stat(file_name, &st);
  off_t size = st.st_size;
  for (int i = 0; i < 4; i++)
    fputc((size >> (8 * (3 - i))) & 255, stdout);

  // Print the Huffman table.
  write_tree(&bits, trees, tree_index);

  // Print the Huffman code of each character.
  FILE * file = fopen(file_name, "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");
  int c;
  while ((c = fgetc(file)) != EOF)
    for (int i = 0; table[c][i] != -1; i++)
      write(&bits, table[c][i]);
  flush(&bits);
  fclose(file);
}