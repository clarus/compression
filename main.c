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
  printf("Bytes read: %d\n", bytes_read);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    fail("Exactly one argument expected.\n");
  
  FILE * file = fopen(argv[1], "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");

  printf("Entropy: %f\n", entropy(file));

  fclose(file);

  return 0;
}