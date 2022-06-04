#ifndef __FIFO__
#define __FIFO__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(__FIFO_LINKED__)

typedef struct node node_t;

struct node {
  node_t *next;
  void *value;
};

typedef struct {
  node_t *head;
  node_t **back;
} fifo_t;

#else

typedef struct {
  size_t element_size;
  void *storage;
  void *front;
  void *back;
  size_t len;
  size_t max_len;
} fifo_t;

#endif

#if defined(__FIFO_LINKED__)

void fifo_init(fifo_t *);

#elif defined(__FIFO_MALLOC_ARR__)

void fifo_init(fifo_t *, size_t, size_t);

#else

void fifo_init(fifo_t *, size_t, size_t, void *);

#endif

void fifo_enqueue(fifo_t *, void *);

void *fifo_dequeue(fifo_t *);

void *fifo_peek(fifo_t *);

uint8_t fifo_empty(fifo_t *);

#endif
