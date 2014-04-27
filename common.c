#include <stdio.h>
#include <stdlib.h>

void fail(const char message[]) {
  fprintf(stderr, "%s\n", message);
  exit(1);
}