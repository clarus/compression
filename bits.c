#include "bits.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

// A structure to read / write on a file bit by bit.
typedef struct {
  FILE * file;
  int byte; // The current byte to read / write once it will be full.
  int count; // The current number of relevant bits in the byte field.
} t;

t new(FILE * file) {
  return (t) {
    .file = file,
    .byte = 0,
    .count = 0
  };
}

// Write a bit.
void write_bit(t * bits, int bit) {
  bits->byte *= 2;
  bits->byte += bit;
  bits->count++;
  if (bits->count == 8) {
    fputc(bits->byte, bits->file);
    bits->byte = bits->count = 0;
  }
}

// Write a byte.
void write_byte(t * bits, int byte) {
  for (int i = 0; i < 8; i++)
    write_bit(bits, (byte >> (7 - i)) & 1);
}

// Write the Huffman tree trees[index]. We do a DFS printing the contents of the
// tree.
void write_tree(t * bits, const tree_t trees[], int index) {
  switch (trees[index].tree_kind) {
  case TREE_LEAF:
    write_bit(bits, 0); // 0 for a leaf
    write_byte(bits, trees[index].tree_content.tree_leaf);
    break;
  case TREE_NODE:
    write_bit(bits, 1); // 1 for a node
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_left);
    write_tree(bits, trees, trees[index].tree_content.tree_node.tree_right);
    break;
  }
}

// Print the last byte even if it is not full.
void flush(t * bits) {
  fputc(bits->byte << (8 - bits->count), bits->file);
}

// Read a bit.
int read_bit(t * bits) {
  if (bits->count == 0) {
    bits->byte = fgetc(bits->file);
    // if (bits->byte == EOF)
    //   fail("read_bit: end of file not expected.");
    bits->count = 8;
  }
  bits->count--;
  return (bits->byte >> bits->count) & 1;
}

// Read a byte.
int read_byte(t * bits) {
  int byte = 0;
  for (int i = 0; i < 8; i++)
    byte += read_bit(bits) << (7 - i);
  return byte;
}

// Read a Huffman tree written by write_tree. first_index is the index to start
// importing in trees. The returned index is the next index to be read.
int read_tree(t * bits, tree_t trees[], int first_index) {
  if (read_bit(bits) == 0) {
    // Leaf case.
    int c = read_byte(bits);
    trees[first_index] = (tree_t) {
      .tree_frequency = 0.0,
      .tree_kind = TREE_LEAF,
      .tree_content = { .tree_leaf = c }
    };
    return first_index + 1;
  } else {
    // Node case.
    int right_index = read_tree(bits, trees, first_index + 1);
    int next_index = read_tree(bits, trees, right_index);
    trees[first_index] = (tree_t) {
      .tree_frequency = 0.0,
      .tree_kind = TREE_NODE,
      .tree_content = {
        .tree_node = { .tree_left = first_index + 1, .tree_right = right_index }
      }
    };
    return next_index;
  }
}

void bits_write_file(const char file_name[], const tree_t trees[],
  int tree_index, int table[][NB_SYMBOLS]) {
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

  // Get the Huffman tree.
  tree_t trees[NB_TREES];
  read_tree(&bits, trees, 0);

  // Get the file content.
  for (int i = 0; i < size; i++) {
    int tree_index = 0;
    while (trees[tree_index].tree_kind == TREE_NODE) {
      if (read_bit(&bits) == 0)
        tree_index = trees[tree_index].tree_content.tree_node.tree_left;
      else
        tree_index = trees[tree_index].tree_content.tree_node.tree_right;
    }
    fputc(trees[tree_index].tree_content.tree_leaf, stdout);
  }

  // printf("original size: %d\n", size);
  // tree_print(trees, 0);
}