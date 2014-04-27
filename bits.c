#include "bits.h"
#include <sys/stat.h>
#include <sys/types.h>

bits_t new(FILE * file) {
  return (bits_t) {
    .bits_file = file,
    .bits_byte = 0,
    .bits_count = 0
  };
}

void write(bits_t * bits, int bit) {
  bits->bits_byte *= 2;
  bits->bits_byte += bit;
  bits->bits_count++;
  if (bits->bits_count == 8) {
    fputc(bits->bits_byte, bits->bits_file);
    bits->bits_byte = bits->bits_count = 0;
  }
}

void flush(bits_t * bits) {
  fputc(bits->bits_byte << (8 - bits->bits_count), bits->bits_file);
}

void bits_write_file(const char file_name[], int table[][NB_SYMBOLS]) {
  FILE * file = fopen(file_name, "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");
  bits_t bits = new(stdout);

  struct stat st;
  stat(file_name, &st);
  off_t size = st.st_size;
  for (int i = 0; i < 4; i++)
    fputc(size >> (8 * (3 - i)), stdout);
  int c;
  while ((c = fgetc(file)) != EOF)
    for (int i = 0; table[c][i] != -1; i++)
      write(&bits, table[c][i]);
  flush(&bits);

  fclose(file);
}