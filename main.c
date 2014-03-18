#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fail(const char message[]) {
  perror(message);
  exit(1);
}

double entropy(FILE * file, int nb_bytes) {
  const int nb_symbols = 256 * nb_bytes;
  int occurencies[nb_symbols];
  for (int i = 0; i < nb_symbols; i++)
    occurencies[i] = 0;

  int ok = 1, bytes_read = 0;
  do {
    int symbol = -1;
    for (int i = 0; i < nb_bytes; i++) {
      int c = fgetc(file);
      if (c != EOF) {
        bytes_read++;
        symbol += c << i;
      } else {
        ok = 0;
        break;
      }
    }
    if (symbol > 0)
      occurencies[symbol + 1]++;
  } while (ok);

  double frequencies[nb_symbols];
  for (int i = 0; i < nb_symbols; i++)
    frequencies[i] = (double) occurencies[i] / (double) bytes_read;

  double result = 0;
  for (int i = 0; i < nb_symbols; i++) {
    double x = frequencies[i] * log2(frequencies[i]);
    if (! isnan(x))
      result -= x;
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3)
    fail("One or two arguments expected.\n");
  
  FILE * file = fopen(argv[1], "r");
  if (file == NULL)
    fail("Cannot open the given file.\n");

  int nb_bytes = (argc == 3 ? atoi(argv[2]) : 1);
  printf("DEBUG %d\n", nb_bytes);

  double e = entropy(file, nb_bytes);
  printf("The entropy is %f bits.\n", e);

  fclose(file);

  return 0;
}