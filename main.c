#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"

#define MAX_N 1000

static uint8_t storage[MAX_N];

int main() {
  // test

  fifo_t fifo;
  error_t err;

#if defined(__FIFO_LINKED__)
  err = fifo_init(&fifo);
#elif defined(__FIFO_MALLOC_ARR__)
  err = fifo_init(&fifo, sizeof(int), MAX_N);
#else
  err = fifo_init(&fifo, sizeof(int), MAX_N, &storage);
#endif

  assert(err == FIFO_SUCCESS);

  int n = MAX_N;

  for (int i = 0; i < n * 100; i++) {
    for (int j = 0; j < n; j++) {
      err = fifo_enqueue(&fifo, &i);
      assert(err == FIFO_SUCCESS);
      fifo_dequeue(&fifo);
    }
  }

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
