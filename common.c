#include <stdio.h>
#include <stdlib.h>

void fail(const char message[]) {
  perror(message);
  exit(1);
}