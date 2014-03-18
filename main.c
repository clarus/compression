#include <stdio.h>
#include <stdlib.h>

void fail(const char message[]) {
  perror(message);
  exit(1);
}

double entropy(FILE * file) {
  int occurencies[256];
  for (int i = 0; i < 256; i++)
    occurencies[i] = 0;

  int c, bytes_read = 0;
  while ((c = fgetc(file)) != EOF) {
    bytes_read++;
    occurencies[c]++;
  }
  printf("DEBUG Bytes read: %d\n", bytes_read);

  double frequencies[256];
  for (int i = 0; i < 256; i++)
    frequencies[i] = (double) occurencies[i] / (double) bytes_read;
  for (int i = 0; i < 256; i++)
    printf("DEBUG f[%d] = %f\n", i, frequencies[i]);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    fail("Exactly one argument expected.\n");
  
  FILE * file = fopen(argv[1], "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");

  double e = entropy(file);
  printf("DEBUG Entropy: %f\n", e);

  fclose(file);

  return 0;
}