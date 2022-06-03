#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"

int main() {
  // test

  fifo_t fifo;
  fifo_init(&fifo);

  int n = 1000;

  for (int i = 0; i < n; i++) {
    int *a = malloc(sizeof(int));
    *a = i;
    fifo_enqueue(&fifo, a);
  }

  int sum = 0;

  while (!fifo_empty(&fifo)) {
    int *t;
    t = fifo_dequeue(&fifo);
    sum += *t;
  }

  for (int i = 0; i < n; i++) {
    int *a = malloc(sizeof(int));
    *a = i;
    fifo_enqueue(&fifo, a);
  }

  while (!fifo_empty(&fifo)) {
    int *t;
    t = fifo_dequeue(&fifo);
    sum += *t;
  }

  assert(sum == (n - 1) * n);

  printf("FIFO works without errors.\n");

  return 0;
}
