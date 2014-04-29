#include "bits.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct {
  FILE * file;
  int byte;
  int count;
} t;

t new(FILE * file) {
  return (t) {
    .file = file,
    .byte = 0,
    .count = 0
  };
}

void write_bit(t * bits, int bit) {
  bits->byte *= 2;
  bits->byte += bit;
  bits->count++;
  if (bits->count == 8) {
    fputc(bits->byte, bits->file);
    bits->byte = bits->count = 0;
  }
}

void write_byte(t * bits, int byte) {
  for (int i = 0; i < 8; i++)
    write_bit(bits, (byte >> (7 - i)) & 1);
}

void write_tree(t * bits, const tree_t trees[], int index) {
  switch (trees[index].tree_kind) {
  case TREE_LEAF:
    write_bit(bits, 0);
    write_byte(bits, trees[index].tree_content.tree_leaf);
    break;
  case TREE_NODE:
    write_bit(bits, 1);
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_left);
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_right);
    break;
  }
}

void flush(t * bits) {
  fputc(bits->byte << (8 - bits->count), bits->file);
}

int read_bit(t * bits) {
  if (bits->count == 0) {
    bits->byte = fgetc(bits->file);
    if (bits->byte == EOF)
      fail("read_bit: end of file not expected.");
    bits->count = 8;
  }
  bits->count--;
  return (bits->byte >> bits->count) & 1;
}

void bits_write_file(const char file_name[], const tree_t trees[], int tree_index, int table[][NB_SYMBOLS]) {
  t bits = new(stdout);

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
    fail("Cannot open the given file.");
  int c;
  while ((c = fgetc(file)) != EOF)
    for (int i = 0; table[c][i] != -1; i++)
      write_bit(&bits, table[c][i]);
  flush(&bits);
  fclose(file);
}

void bits_read_file(const char file_name[]) {
  FILE * file = fopen(file_name, "r");
  if (file == NULL)
    fail("Cannot open the given file.");
  t bits = new(file);

  // Get the original file size.
  int size = 0;
  for (int i = 0; i < 4; i++)
    size += fgetc(file) << (8 * (3 - i));

  printf("original size: %d\n", size);
}