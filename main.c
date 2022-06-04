#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define __FIFO_MALLOC_ARR__

#include "fifo.h"

static uint8_t storage[10000];

int main() {
  // test

  fifo_t fifo;

#if defined(__FIFO_LINKED__)
  fifo_init(&fifo);
#elif defined(__FIFO_MALLOC_ARR__)
  fifo_init(&fifo, sizeof(int), 10000);
#else
  fifo_init(&fifo, sizeof(int), 10000, &storage);
#endif

  int n = 10;

  for (int i = 0; i < n; i++) {
    fifo_enqueue(&fifo, &i);
  }

  int sum = 0;

  while (!fifo_empty(&fifo)) {
    int *t = fifo_dequeue(&fifo);
    sum += *t;
  }

  for (int i = 0; i < n; i++) {
    fifo_enqueue(&fifo, &i);
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
